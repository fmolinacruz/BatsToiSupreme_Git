// Copyright 2022 The Reallusion Authors. All Rights Reserved.

#include "RLLiveLink.h"
#include "RLLiveLinkCommands.h"
#include "RLLiveLinkStyle.h"

/// for UI
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

/// for Json
#include "JsonGlobals.h"
#include "JsonObjectConverter.h"
#include "Policies/JsonPrintPolicy.h"
#include "Policies/PrettyJsonPrintPolicy.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonTypes.h"
#include "Dom/JsonValue.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializerMacros.h"

/// for Blueprint
#include "Interfaces/IPluginManager.h"
/// Developer/DesktopPlatform
#include "DesktopPlatformModule.h"

/// Editor/BlueprintGraph
#include "K2Node_VariableGet.h"

/// Editor/UnrealEd
#include "Editor.h"
#include "EditorAnimUtils.h"
#include "EdGraphUtilities.h"
#include "FileHelpers.h"
#include "ObjectTools.h"
#include "Factories/TextureFactory.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

////for transfer scene
///for timer
#include "TimerManager.h"
/// for Merging Actors
#include "MeshMergeModule.h"
#include "Misc/ScopedSlowTask.h"
#include "Components/ShapeComponent.h"

/// for Export FBX
#include "Exporters/FbxExportOption.h"
#include "Misc/FeedbackContext.h"
#include "Exporters/Exporter.h"
#include "AssetExportTask.h"
#include "UObject/GCObjectScopeGuard.h"

#include "SSkeletonWidget.h"
#include "EditorAnimUtils.h"

// for Import FBX
#include "AssetImportTask.h"
#include "Factories/FbxFactory.h"
#include "FbxImporter.h"
#include "AssetRegistry/AssetRegistryModule.h"

/// Runtime/AssetRegistry
#if ( ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3 )
#include "AssetRegistry/AssetRegistryModule.h"
#else
#include "AssetRegistryModule.h"
#endif
#include "AssetToolsModule.h"

/// Runtime/Core
#include "HAL/PlatformFilemanager.h"

/// Runtime/Engine
#include "EngineUtils.h"
#include "Animation/AnimBlueprint.h"
#include "Animation/Skeleton.h"
#include "Components/BillboardComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/ObjectLibrary.h"
#include "Engine/SCS_Node.h"
#include "Engine/Selection.h"

#include "LevelEditorViewport.h"
#include "SLevelViewport.h"

/// for core.h
#include "Async/Async.h"
#include "Async/AsyncWork.h"
#include "Misc/FileHelper.h"
#include "Misc/MessageDialog.h"

#include "IImageWrapper.h" 
#include "IImageWrapperModule.h"
#include "Components/RectLightComponent.h"
#include "CineCameraComponent.h"

// for Level Sequence
#include "LevelSequence.h"
#include "MovieScene.h"
#include "ILevelSequenceEditorToolkit.h"
#include "ISequencer.h"
#include "MovieSceneToolHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Sections/MovieScene3DTransformSection.h"
#include "Tracks/MovieScene3DTransformTrack.h"
#include "Tracks/MovieSceneSkeletalAnimationTrack.h"
#include "SequencerUtilities.h"
#include "Animation/SkeletalMeshActor.h"
#include "CineCameraActor.h"
#include "Tracks/MovieSceneFloatTrack.h"
#include "Tracks/MovieSceneCameraCutTrack.h"
#include "Sections/MovieSceneCameraCutSection.h"

// for Live Link Transfer Progress Info
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SProgressBar.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

#include "RLLiveLinkUtility.h"

#define PLUGIN_NAME "LiveLink"
#define INSTALL_PLUGIN_MESSAGE "Please Enable The Live Link plugin \n\rThe Live Link plugin can be enabled by opening the \"Plugins\" Window (Edit / Plugins) \n\rDo a search for \"Live Link\" and check the box to Enable it."
#define LOCTEXT_NAMESPACE "FRLLiveLinkModule"
#define RECV_BUFFER_SIZE 1024 * 1024
#define DEFAULT_PARENT_ACTOR "iClone_Origin"

// for Setup Wrinkle BP
#define ExpSequence    FString( "ExpSequence" )
#define ExpPoseAsset   FString( "ExpPoseAsset" )
#define WrinkleAnimBP  FString( "WrinkleAnimBlueprint" )

void FRLLiveLinkModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
    FRLLiveLinkStyle::Initialize();
    FRLLiveLinkStyle::ReloadTextures();

    m_strCurUProjectPath = FPaths::ConvertRelativePathToFull( FPaths::GetProjectFilePath() );
    m_strCurEngineCmdexePath = GetCommandletExePath();
    FRLLiveLinkCommands::Register();

    m_kPluginCommands = MakeShareable( new FUICommandList );

    FLevelEditorModule& kLevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>( "LevelEditor" );

    // init toolbar
    TSharedPtr<FExtender> spToolbarExtender = MakeShareable( new FExtender );
    FName kExtensionHook = "";
    EExtensionHook::Position eHookPosition;
    if ( ENGINE_MAJOR_VERSION < 5 )
    {
        kExtensionHook = "Settings";
        eHookPosition = EExtensionHook::After;
    }
    else
    {
        kExtensionHook = "Play";
        eHookPosition = EExtensionHook::Before;
    }
    spToolbarExtender->AddToolBarExtension( kExtensionHook,
                                            eHookPosition,
                                            m_kPluginCommands,
                                            FToolBarExtensionDelegate::CreateRaw( this, &FRLLiveLinkModule::AddToolBar ) );
    kLevelEditorModule.GetToolBarExtensibilityManager()->AddExtender( spToolbarExtender );

    InitSocket();

    // Initialize the blueprint file name according to the unreal version
    m_strCineCameraBlueprint = "LiveLinkCineCameraBlueprint";
    m_strCharacterBlueprint  = "CCLiveLink";
    m_strPointLightBlueprint = "LiveLinkPointLightBlueprint";
    m_strDirLightBlueprint   = "LiveLinkDirectionalLightBlueprint";
    m_strSpotLightBlueprint  = "LiveLinkSpotLightBlueprint";
    m_strRectLightBlueprint  = "LiveLinkRectLightBlueprint";

#if ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION == 20
    m_strPointLightBlueprint = "LiveLinkPointLightBlueprint_v20";
    m_strDirLightBlueprint   = "LiveLinkDirectionalLightBlueprint_v20";
    m_strSpotLightBlueprint  = "LiveLinkSpotLightBlueprint_v20";
#endif
#if ( ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION >= 23 ) || ENGINE_MAJOR_VERSION >= 5
    m_strCineCameraBlueprint = "LiveLinkCineCameraBlueprint_v23";
    m_strCharacterBlueprint  = "CCLiveLink_v23";
    m_strPointLightBlueprint = "LiveLinkPointLightBlueprint_v23";
    m_strDirLightBlueprint   = "LiveLinkDirectionalLightBlueprint_v23";
    m_strSpotLightBlueprint  = "LiveLinkSpotLightBlueprint_v23";
    m_strRectLightBlueprint  = "LiveLinkRectLightBlueprint_v23";
#endif
#if ( ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION >= 24 ) || ENGINE_MAJOR_VERSION >= 5
    m_strCineCameraBlueprint = "LiveLinkCineCameraBlueprint_v24";
#endif
#if ( ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION >= 25 ) || ENGINE_MAJOR_VERSION >= 5
    m_strCineCameraBlueprint = "LiveLinkCineCameraBlueprint_v25";
#endif

    InitialProgressWidget();
    FRLLiveLinkModule::AddMenuEntryInRightClick();
}

void FRLLiveLinkModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.
    Stop();
    m_pThread->Kill( true );
    delete m_pThread;
    if ( m_pListenerSocket )
    {
        m_pListenerSocket->Close();
        m_pSocketSubsystem->DestroySocket( m_pListenerSocket );
    }
    if ( m_pConnectionSocket )
    {
        m_pConnectionSocket->Close();
        m_pSocketSubsystem->DestroySocket( m_pConnectionSocket );
    }
    FRLLiveLinkStyle::Shutdown();
    FRLLiveLinkCommands::Unregister();
}

void FRLLiveLinkModule::InitSocket()
{
    // Create Listener Socket
    m_pListenerSocket = FTcpSocketBuilder( TEXT( "ICLLiveLink Listen Socket" ) )
        .AsReusable()
        .BoundToAddress( FIPv4Address( 127, 0, 0, 1 ) )
        .BoundToPort( m_uDevicePort )
        .Listening( 8 )
        .WithReceiveBufferSize( RECV_BUFFER_SIZE );

    m_kRecvBuffer.SetNumUninitialized( RECV_BUFFER_SIZE );
    if ( m_pListenerSocket )
    {
        m_pSocketSubsystem = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM );
        Start();
    }
}

FString FRLLiveLinkModule::GetCommandletExePath()
{
    FString strResult;
    FString strCurEngineRootDir = FPaths::ConvertRelativePathToFull( FPaths::EngineDir() );
    FString strExecutableName = FPlatformProcess::ExecutableName( false );
#if PLATFORM_WINDOWS
    // turn UE4editor into UE4editor-cmd
    if ( strExecutableName.EndsWith( ".exe", ESearchCase::IgnoreCase ) && !FPaths::GetBaseFilename( strExecutableName ).EndsWith( "-cmd", ESearchCase::IgnoreCase ) )
    {
        FString strNewExeName = strExecutableName.Left( strExecutableName.Len() - 4 ) + "-Cmd.exe";
        if ( FPaths::FileExists( strNewExeName ) )
        {
            strExecutableName = strNewExeName;
        }
    }
#endif

    strResult += strCurEngineRootDir + "Binaries/Win64/" + strExecutableName;
    return strResult;
}

void FRLLiveLinkModule::AddToolBar( FToolBarBuilder& kBuilder )
{
    kBuilder.AddComboButton( FUIAction(),
                             FOnGetContent::CreateRaw( this, &FRLLiveLinkModule::FillComboButton, m_kPluginCommands ),
                             LOCTEXT( "LiveLink", "iClone Live Link" ),
                             LOCTEXT( "LiveLinkTip", "Execute IC LiveLink action" ),
                             FSlateIcon( FRLLiveLinkStyle::GetStyleSetName(), "RLLiveLink.PluginAction" ) );
}

// FRunnable interface
void FRLLiveLinkModule::Start()
{
    m_strThreadName = "ICLiveLink Service";
    m_strThreadName.AppendInt( FAsyncThreadIndex::GetNext() );
    m_pThread = FRunnableThread::Create( this, *m_strThreadName, 128 * 1024, TPri_Lowest, FPlatformAffinity::GetPoolThreadMask() );
}

void FRLLiveLinkModule::Stop()
{
    m_bStopping = true;
}

uint32 FRLLiveLinkModule::Run()
{
    TSharedRef<FInternetAddr> pRemoteAddr = m_pSocketSubsystem->CreateInternetAddr();
    while ( !m_bStopping && !GIsCookerLoadingPackage && !IsRunningCommandlet() )
    {
        FPlatformProcess::Sleep( 0.03f );
        bool bPending = false;
        if ( m_pListenerSocket->HasPendingConnection( bPending ) && bPending )
        {
            //Already have a Connection? destroy previous
            if ( m_pConnectionSocket )
            {
                m_pConnectionSocket->Close();
                m_pSocketSubsystem->DestroySocket( m_pConnectionSocket );
            }
            //New Connection receive!
            m_pConnectionSocket = m_pListenerSocket->Accept( *pRemoteAddr, TEXT( "IC TCP Received Socket Connection" ) );
        }
        if ( m_pConnectionSocket )
        {
            //Global cache of current Remote Address
            m_kRemoteAddressForConnection = FIPv4Endpoint( pRemoteAddr );
            uint32 uSize = 0;
            while ( m_pConnectionSocket->HasPendingData( uSize ) )
            {
                int32 nRead = 0;
                if ( m_pConnectionSocket->Recv( m_kRecvBuffer.GetData(), m_kRecvBuffer.Num(), nRead ) )
                {
                    if ( nRead > 0 )
                    {
                        TcpCommandData spReceivedData = MakeShareable( new TArray<uint8>() );
                        spReceivedData->SetNumUninitialized( nRead );
                        memcpy( spReceivedData->GetData(), m_kRecvBuffer.GetData(), nRead );
                        m_kDataInQueue.Add( spReceivedData );
                        AsyncTask( ENamedThreads::GameThread, [ this, spReceivedData ]()
                        {
                            HandleReceivedData( spReceivedData );
                        } );
                    }
                }
            }
        }
    }
    return 0;
}

void FRLLiveLinkModule::HandleReceivedData( TcpCommandData spReceivedData )
{
    FString strJsonString;
    strJsonString.Empty( spReceivedData->Num() );
    for ( uint8& uByte : *spReceivedData.Get() )
    {
        strJsonString += TCHAR( uByte );
    }

    TSharedPtr<FJsonObject> spJsonObject;
    if ( FRLLiveLinkUtility::ParseStringToJson( strJsonString, spJsonObject ) )
    {
        FFunctionGraphTask::CreateAndDispatchWhenReady( [ spJsonObject, this ]()
        {
            if ( spJsonObject->Values.Contains( "PreImportData" ) )
            {
                auto& spJsonValue = spJsonObject->Values[ "PreImportData" ];
                ProcessPreImportData( spJsonValue );
            }

            if ( spJsonObject->Values.Contains( "isPlaceAssets" ) )
            {
                m_bIsPlaceAssets = spJsonObject->Values[ "isPlaceAssets" ].Get()->AsBool();
            }

            if ( spJsonObject->Values.Contains( "BuildAssets" ) )
            {
                auto& spAvatarJsonValue = spJsonObject->Values[ "BuildAssets" ];
                ProcessObjectData( spAvatarJsonValue, m_bIsPlaceAssets );

                MoveMotionAssetPath( spAvatarJsonValue, false );

                TSharedPtr<FJsonObject> spReturnJson = MakeShareable( new FJsonObject );
                spReturnJson->SetBoolField( "FinishBuildAsset", true );

                SendJsonToIC( spReturnJson );

            }

            if ( spJsonObject->Values.Contains( "CreateCamera" ) )
            {
                auto& spCameraJsonValue = spJsonObject->Values[ "CreateCamera" ];
                ProcessCameraData( spCameraJsonValue, m_bIsPlaceAssets );
                LoadCameraPerFrameDatas();
                PushProgress( spCameraJsonValue->AsArray().Num() );
            }

            if ( spJsonObject->Values.Contains( "LoadCameraPerframeData" ) )
            {
                auto& spCameraJsonValue = spJsonObject->Values[ "LoadCameraPerframeData" ];
                size_t uSize = spCameraJsonValue->AsArray().Num();
                if ( uSize > 0 )
                {
                    ShowProgress();
                }
                LoadCameraPerFrameDatas();
                PushProgress( uSize );
            }

            if ( spJsonObject->Values.Contains( "CreateLight" ) )
            {
                auto& spLightJsonValue = spJsonObject->Values[ "CreateLight" ];
                ProcessLightData( spLightJsonValue, m_bIsPlaceAssets );
            }

            if ( spJsonObject->Values.Contains( "CreateProp" ) )
            {
                auto& spPropJsonValue = spJsonObject->Values[ "CreateProp" ];
                ProcessObjectData( spPropJsonValue, m_bIsPlaceAssets );

                MoveMotionAssetPath( spPropJsonValue, true );
            }

            if ( spJsonObject->Values.Contains( "CreateMotions" ) )
            {
                auto& spPropJsonValue = spJsonObject->Values[ "CreateMotions" ];
                ProcessMotionData( spPropJsonValue );
            }

            if ( spJsonObject->Values.Contains( "GetRequire" ) )
            {
                auto& spGetRequireJsonValue = spJsonObject->Values[ "GetRequire" ];
                ProcessRequireFromIC( spGetRequireJsonValue );
            }

            if ( spJsonObject->Values.Contains( "CheckAndDeleteDuplicatedAsset" ) )
            {
                auto& spGetRequireJsonValue = spJsonObject->Values[ "CheckAndDeleteDuplicatedAsset" ];
                m_kAssetTempData.Reset();
                CheckAndDeleteDuplicatedAsset( spGetRequireJsonValue );
            }

            if ( spJsonObject->Values.Contains( "CheckSkeletonAssetExist" ) )
            {
                auto& spCheckSkeletonAssetExistJsonValue = spJsonObject->Values[ "CheckSkeletonAssetExist" ];
                m_kAssetTempData.Reset();
                CheckSkeletonAssetExist( spCheckSkeletonAssetExistJsonValue );
            }
            if ( spJsonObject->Values.Contains( "CheckAssetExist" ) )
            {
                auto& spCheckAssetExistJsonValue = spJsonObject->Values[ "CheckAssetExist" ];
                m_kAssetTempData.Reset();
                CheckAssetExist( spCheckAssetExistJsonValue );
            }
            if ( spJsonObject->Values.Contains( "CheckICLiveLinkVersion" ) )
            {
                auto& spCheckICVersionJsonValue = spJsonObject->Values[ "CheckICLiveLinkVersion" ];
                CheckICVersion( spCheckICVersionJsonValue );
            }
            if ( spJsonObject->Values.Contains( "iCloneAPClose" ) )
            {
                if ( m_pConnectionSocket )
                {
                    m_pConnectionSocket->Close();
                    m_pSocketSubsystem->DestroySocket( m_pConnectionSocket );
                }
                //reset socket ptr
                m_pConnectionSocket = nullptr;
            }

            if ( IsImportAssetsDone() && m_bCreateLevelSequencer )
            {
                if ( SetupLevelSequencer() )
                {
                    ResetEditorImportSetting();
                }
            }

            RemoveTcpCommandData();
        }, TStatId(), nullptr, ENamedThreads::GameThread );
    }
}

bool FRLLiveLinkModule::BuildBlueprint( const FString& strAssetFolder, const FString& strAssetName, bool bToScene )
{
    if ( strAssetFolder.IsEmpty() || strAssetName.IsEmpty() )
    {
        return false;
    }
    USkeletalMesh* pSkeletalMesh = Cast< USkeletalMesh >( StaticLoadObject( USkeletalMesh::StaticClass(), NULL, *( strAssetFolder + strAssetName + "." + strAssetName ) ) );
    if ( !pSkeletalMesh )
    {
        return false;
    }
    FAssetRegistryModule::AssetCreated( pSkeletalMesh );
    pSkeletalMesh->MarkPackageDirty();
    USkeleton* pSkeleton = pSkeletalMesh->Skeleton;

    //Save Skeleton Mesh
    UPackage* const pSkeletonAssetPackage = pSkeletalMesh->GetOutermost();
    pSkeletonAssetPackage->SetDirtyFlag( true );
    TArray<UPackage*> kSkeletonPackagesToSave;
    kSkeletonPackagesToSave.Add( pSkeletonAssetPackage );
    FEditorFileUtils::PromptForCheckoutAndSave( kSkeletonPackagesToSave, false, /*bPromptToSave=*/ false );

    FString strRootGamePath = strAssetFolder;
    FString strRootPath = strRootGamePath;
    strRootPath.RemoveFromStart( TEXT( "/Game/" ) );
    strRootPath = FPaths::ProjectContentDir() + strRootPath;

    FString strWrinkleAsset = strRootPath + strAssetName + "_ExpPoseAsset.uasset";
    bool bWrinkleAssetExist = FPaths::FileExists( strWrinkleAsset );
    if ( !bWrinkleAssetExist )
    {
        //Wrinkle setup
        FString strWrinkleNameForCheck = "head_wm1_normal_head_wm1_browRaiseInner_L";

#if ENGINE_MAJOR_VERSION >=5 && ENGINE_MINOR_VERSION >= 3
        const FCurveMetaData* pCurveData = pSkeleton->GetCurveMetaData( FName( strWrinkleNameForCheck ) );
        if ( pCurveData && pCurveData->Type.bMaterial )
        {
            BuildWrinkleBlueprint( strRootGamePath, pSkeletalMesh );
        }
#else
        const auto pNameMapping = pSkeleton->GetSmartNameContainer( USkeleton::AnimCurveMappingName );
        if ( pNameMapping )
        {
            const FCurveMetaData* pCurveData = pNameMapping->GetCurveMetaData( FName( strWrinkleNameForCheck ) );
            if ( pCurveData && pCurveData->Type.bMaterial )
            {
                BuildWrinkleBlueprint( strRootGamePath, pSkeletalMesh );
            }
    }
#endif

    }

    // 處理Live Link Bone blueprint
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    FString strPluginPath = IPluginManager::Get().FindPlugin( TEXT( "RLLiveLink" ) )->GetBaseDir();
    FString strTargetPath = strRootPath + "/" + m_strCharacterBlueprint + ".uasset";
    FString strSourceFilePath = strPluginPath + "/Content/" + m_strCharacterBlueprint + ".rluasset";
    bool bIsAlreadyExists = kPlatformFile.FileExists( *strTargetPath );
    if ( bIsAlreadyExists )
    {
        return true;
    }

    bool bRet = kPlatformFile.CopyFile( *strTargetPath, *strSourceFilePath );
    if ( !bRet )
    {
        return false;
    }

    FString strAnimBlueprintPath = strRootGamePath + m_strCharacterBlueprint + "." + m_strCharacterBlueprint;
    UAnimBlueprint* pAnimBlueprint = Cast<UAnimBlueprint>( StaticLoadObject( UAnimBlueprint::StaticClass(), NULL, *( strAnimBlueprintPath ), NULL, LOAD_DisableDependencyPreloading | LOAD_DisableCompileOnLoad ) );
    if ( pAnimBlueprint )
    {
        FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pAnimBlueprint );
        FAssetRegistryModule::AssetCreated( pAnimBlueprint );
        pAnimBlueprint->MarkPackageDirty();

        pAnimBlueprint->TargetSkeleton = pSkeleton;
        pAnimBlueprint->SetPreviewMesh( pSkeletalMesh, true );
        auto pMesh = pAnimBlueprint->GetPreviewMesh();
        pAnimBlueprint->Modify( true );

        //Compile
        TWeakObjectPtr<UAnimBlueprint> pWeekAnimBlueprint = pAnimBlueprint;
        TArray<TWeakObjectPtr<UObject>> kAssetsToRetarget;
        kAssetsToRetarget.Add( pWeekAnimBlueprint );
        EditorAnimUtils::RetargetAnimations( pAnimBlueprint->TargetSkeleton, pSkeletalMesh->Skeleton, kAssetsToRetarget, false, NULL, false );

        FKismetEditorUtilities::CompileBlueprint( pAnimBlueprint );
        UPackage* const pAssetPackage = pAnimBlueprint->GetOutermost();
        pAssetPackage->SetDirtyFlag( true );

        //Save
        TArray<UPackage*> kPackagesToSave;
        kPackagesToSave.Add( pAssetPackage );
        FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
    }

    // 處理Live Link Morph blueprint
    strTargetPath = strRootPath + "CCLiveLink_Blueprint.uasset";
    strSourceFilePath = strPluginPath + "/Content/CCLiveLink_Blueprint.rluasset";
    bRet = kPlatformFile.CopyFile( *strTargetPath, *strSourceFilePath );
    if ( !bRet )
    {
        return false;
    }

    FString strMorphBlueprintPath = strRootGamePath + "CCLiveLink_Blueprint.CCLiveLink_Blueprint";
    UBlueprint* pBlueprint = Cast< UBlueprint >( StaticLoadObject( UBlueprint::StaticClass(), NULL, *( strMorphBlueprintPath ) ) );
    if ( pBlueprint )
    {
        AActor* pLiveLinkActor = Cast<AActor>( pBlueprint->GeneratedClass->ClassDefaultObject );
        if ( pLiveLinkActor )
        {
            USkeletalMeshComponent* pSkeletalMeshComponent = pLiveLinkActor->FindComponentByClass<USkeletalMeshComponent>();
            if ( pSkeletalMeshComponent )
            {
                pSkeletalMeshComponent->SetAnimInstanceClass( pAnimBlueprint->GeneratedClass );
                pSkeletalMeshComponent->SetSkeletalMesh( pAnimBlueprint->GetPreviewMesh(), true );
            }
        }

        FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pBlueprint );
        FAssetRegistryModule::AssetCreated( pBlueprint );
        pBlueprint->MarkPackageDirty();

        //Get Graph Text
        FString strTextToImport;
        FString strSourceFilePathText = IPluginManager::Get().FindPlugin( TEXT( "RLLiveLink" ) )->GetBaseDir() + "/Content/LiveLinkCode_Character.txt";
        FFileHelper::LoadFileToString( strTextToImport, *strSourceFilePathText );

        //Edit Text for current name
        FString strTextPath = strRootGamePath;
        strTextPath.RemoveFromStart( TEXT( "/Game" ) );
        strTextToImport = strTextToImport.Replace( TEXT( "LiveLinkANName" ), *m_strCharacterBlueprint ); //set anim_blueprint
        strTextToImport = strTextToImport.Replace( TEXT( "LiveLinkBPName" ), TEXT( "CCLiveLink_Blueprint" ) );
        strTextToImport = strTextToImport.Replace( TEXT( "/ObjectPath" ), *strTextPath );
        strTextToImport = strTextToImport.Replace( TEXT( "//" ), TEXT( "/" ) );

        //Set Graph from Text
        UEdGraph* pGraph = pBlueprint->UbergraphPages[ 0 ];
        check( pGraph );
        TSet<UEdGraphNode*> kPastedNodes;
        FEdGraphUtilities::ImportNodesFromText( pGraph, strTextToImport, kPastedNodes );

        //Set SubjectName variable
        for ( FBPVariableDescription& pVar : pBlueprint->NewVariables )
        {
            if ( pVar.VarName == "SubjectName" )
            {
                pVar.DefaultValue = pSkeletalMesh->GetName();
                FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pBlueprint );
            }
        }

        //Compile
        FKismetEditorUtilities::CompileBlueprint( pBlueprint );
        UPackage* const pAssetPackage = pBlueprint->GetOutermost();
        pAssetPackage->SetDirtyFlag( true );

        //Save
        TArray<UPackage*> kPackagesToSave;
        kPackagesToSave.Add( pAssetPackage );
        FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );

        // 場景中New出角色
        if ( bToScene )
        {
            UClass* pClassToSpawn = Cast< UClass >( pBlueprint->GeneratedClass );
            pLiveLinkActor = FRLLiveLinkUtility::SpawnActorToViewport( pClassToSpawn, "" );
            if ( pLiveLinkActor )
            {
                pLiveLinkActor->SetActorLabel( pSkeletalMesh->GetName(), false );
                SetDefaultParentActor( pLiveLinkActor, FAttachmentTransformRules::KeepRelativeTransform );

                //set focus view on actor
                SelectAndFocusActor( pLiveLinkActor, false, true );
            }
        }
    }
    //Rename Blueprint
    UObject* pAnimBlueprintObject = Cast<UObject>( pAnimBlueprint );
    UObject* pBlueprintObject = Cast<UObject>( pBlueprint );
    RenameAsset( pAnimBlueprintObject, strAssetName + "_AnimationBlueprint" );
    RenameAsset( pBlueprintObject, strAssetName + "_Blueprint" );
    return true;
}

void FRLLiveLinkModule::ProcessObjectData( const TSharedPtr<FJsonValue>& spJsonValue, bool bPlaceAsset )
{
    if ( spJsonValue )
    {
        auto spBuildArray = spJsonValue->AsArray();
        if ( !spBuildArray.IsEmpty() )
        {
            ShowProgress();
        }
        for ( auto& spAssetJsonValue : spBuildArray )
        {
            if ( auto spAssetObject = spAssetJsonValue->AsObject() )
            {
                auto kAssetMap = spAssetObject->Values;
                FString strAssetName = kAssetMap[ "Name" ]->AsString();
                FString strAssetPath = kAssetMap[ "Path" ]->AsString();
                bool bImportFbx = kAssetMap.Contains( "ImportFbx" ) && kAssetMap[ "ImportFbx" ]->AsBool();

                if ( bImportFbx )
                {
                    ProcessImportObject( strAssetName );

                    bool bImportMotion = kAssetMap.Contains( "ImportMotion" ) ? kAssetMap[ "ImportMotion" ]->AsBool() : false;
                    if ( bImportMotion )
                    {
                        ProcessImportMotion( strAssetName );
                    }
                }

                if ( !strAssetName.IsEmpty() )
                {
                    USkeletalMesh* pSkeletalMesh = Cast< USkeletalMesh >( StaticLoadObject( USkeletalMesh::StaticClass(), NULL, *( strAssetPath + strAssetName + "." + strAssetName ) ) );
                    if ( pSkeletalMesh )
                    {
                        //Check if Asset has Deleted Actor Need Putting Back
                        bool bNeedPutAssetBack = false;
                        for ( auto kTempData : m_kAssetTempData )
                        {
                            if ( kTempData.strFolderName == strAssetName )
                            {
                                bNeedPutAssetBack = true;
                                break;
                            }
                        }

                        bool bPlaceAsssetObject = ( bNeedPutAssetBack ) ? false : bPlaceAsset;
                        BuildBlueprint( strAssetPath, strAssetName, bPlaceAsssetObject );

                        //Reset Avatar In Scene
                        FString strMorphBlueprintPath = strAssetPath + strAssetName + "_Blueprint." + strAssetName + "_Blueprint";
                        UBlueprint* pBlueprint = Cast< UBlueprint >( StaticLoadObject( UBlueprint::StaticClass(), NULL, *( strMorphBlueprintPath ) ) );

                        if ( bNeedPutAssetBack && pBlueprint )
                        {
                            PutAssetBackToSceneAfterReplace( pBlueprint );
                        }
                    }

                }
                PushProgress( 1 );
                RemoveFbxFiles( strAssetName );
            }
        }
    }
}

void FRLLiveLinkModule::RenameAsset( UObject* pAssetObject, const FString& strNewAssetName )
{
    //Rename Asset
    FAssetToolsModule& kAssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>( "AssetTools" );
    TArray<FAssetRenameData> kAssetsAndNames;
    const FString strPackagePath = FPackageName::GetLongPackagePath( pAssetObject->GetOutermost()->GetName() );
    new( kAssetsAndNames ) FAssetRenameData();
    kAssetsAndNames[ 0 ].NewName = strNewAssetName;
    kAssetsAndNames[ 0 ].NewPackagePath = strPackagePath;
    kAssetsAndNames[ 0 ].Asset = pAssetObject;
    kAssetToolsModule.Get().RenameAssetsWithDialog( kAssetsAndNames );
}

void FRLLiveLinkModule::ProcessCameraData( const TSharedPtr<FJsonValue>& spJsonValue, bool bPlaceAsset )
{
    if ( spJsonValue )
    {
        auto spBuildArray = spJsonValue->AsArray();
        if ( !spBuildArray.IsEmpty() )
        {
            ShowProgress();
        }
        for ( auto& spAssetJsonValue : spBuildArray )
        {
            if ( auto spAssetObject = spAssetJsonValue->AsObject() )
            {
                auto kAssetMap = spAssetObject->Values;
                FString strCameraName = kAssetMap[ "Name" ]->AsString();
                if ( !strCameraName.IsEmpty() )
                {
                    //Check if Asset has Deleted Actor Need Putting Back
                    bool bNeedPutAssetBack = false;
                    for ( auto kTempData : m_kAssetTempData )
                    {
                        if ( kTempData.strFolderName == strCameraName )
                        {
                            bNeedPutAssetBack = true;
                            break;
                        }
                    }

                    bool bPlaceAsssetObject = ( bNeedPutAssetBack ) ? false : bPlaceAsset;
                    UBlueprint* pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Camera", m_strCineCameraBlueprint, strCameraName, false );
                    SetupCineCamera( pBlueprint );
                    if ( bPlaceAsssetObject )
                    {
                        LoadToScene( pBlueprint );
                    }
                    //Reset Avatar In Scene
                    if ( bNeedPutAssetBack && pBlueprint )
                    {
                        PutAssetBackToSceneAfterReplace( pBlueprint );
                    }
                }
            }
        }
    }
}

void FRLLiveLinkModule::ProcessLightData( const TSharedPtr<FJsonValue>& spJsonValue, bool bPlaceAsset )
{
    if ( spJsonValue )
    {
        auto spBuildArray = spJsonValue->AsArray();
        for ( auto& spAssetJsonValue : spBuildArray )
        {
            if ( auto spAssetObject = spAssetJsonValue->AsObject() )
            {
                auto kAssetMap = spAssetObject->Values;
                FString strLightName = kAssetMap[ "Name" ]->AsString();
                if ( !strLightName.IsEmpty() )
                {
                    //Check if Asset has Deleted Actor Need Putting Back
                    bool bNeedPutAssetBack = false;
                    for ( auto kTempData : m_kAssetTempData )
                    {
                        if ( kTempData.strFolderName == strLightName )
                        {
                            bNeedPutAssetBack = true;
                            break;
                        }
                    }
                    bool bPlaceAsssetObject = ( bNeedPutAssetBack ) ? false : bPlaceAsset;

                    UBlueprint* pBlueprint = nullptr;
                    ELightType eLightType = static_cast< ELightType >( ( int )kAssetMap[ "Type" ]->AsNumber() );
                    switch ( eLightType )
                    {
                        case ELightType::Directional:
                        {
                            pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Light", m_strDirLightBlueprint, strLightName, false );
                            break;
                        }
                        case ELightType::Point:
                        {
                            pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Light", m_strPointLightBlueprint, strLightName, false );
                            break;
                        }
                        case ELightType::Spot:
                        case ELightType::Rect:
                        {
                            if ( eLightType == ELightType::Spot )
                            {
                                pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Light", m_strSpotLightBlueprint, strLightName, false );
                            }
                            else
                            {
                                pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Light", m_strRectLightBlueprint, strLightName, false );
                                if ( pBlueprint )
                                {
                                    AActor* pLightActor = Cast<AActor>( pBlueprint->GeneratedClass->ClassDefaultObject );
                                    if ( pLightActor )
                                    {
                                        URectLightComponent* pRectLightComponent = pLightActor->FindComponentByClass<URectLightComponent>();
                                        if ( pRectLightComponent )
                                        {
                                            pRectLightComponent->IntensityUnits = ELightUnits::Lumens;
                                            FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pBlueprint );
                                            FKismetEditorUtilities::CompileBlueprint( pBlueprint );
                                            UPackage* const pAssetPackage = pBlueprint->GetOutermost();
                                            pAssetPackage->SetDirtyFlag( true );
                                            TArray<UPackage*> kPackagesToSave;
                                            kPackagesToSave.Add( pAssetPackage );
                                            FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
                                        }
                                    }
                                }
                            }
                        }
                    }

                    if ( pBlueprint )
                    {
                        bool bContainsTexture = kAssetMap.Contains( "Rect_Texture_Path" );
                        if ( bContainsTexture )
                        {
                            FString strRectTexturePath = kAssetMap[ "Rect_Texture_Path" ]->AsString();
                            IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
                            if ( kPlatformFile.FileExists( *strRectTexturePath ) )
                            {
#if ( ENGINE_MAJOR_VERSION <= 4 && ENGINE_MINOR_VERSION >= 21 ) || ENGINE_MAJOR_VERSION >= 5
                                FString strSaveTo = TEXT( "/Game/RLContent/Light/" + strLightName + "_Rect_Src_Texture" );
                                UTexture2D* pRectTexture = LoadTextureFromFile( strRectTexturePath, strSaveTo );
                                if ( pRectTexture )
                                {
                                    // Set Blueprint Texture
                                    AActor* pLightActor = Cast<AActor>( pBlueprint->GeneratedClass->ClassDefaultObject );
                                    if ( pLightActor )
                                    {
                                        URectLightComponent* pRectLightComponent = pLightActor->FindComponentByClass<URectLightComponent>();
                                        if ( pRectLightComponent )
                                        {
                                            UTexture2D* pUeRectTexture = RotateTexture2D( pRectTexture );
                                            pRectLightComponent->SetSourceTexture( pUeRectTexture );
                                            // Save Blueprint
                                            FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pBlueprint );
                                            FKismetEditorUtilities::CompileBlueprint( pBlueprint );
                                            UPackage* const pAssetPackage = pBlueprint->GetOutermost();
                                            pAssetPackage->SetDirtyFlag( true );
                                            TArray<UPackage*> kPackagesToSave;
                                            kPackagesToSave.Add( pAssetPackage );
                                            FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
                                        }
                                    }
                                }
#endif
                                bool bDeleted = kPlatformFile.DeleteFile( *strRectTexturePath );
                            }
                        }
                        bool bContainsIes = kAssetMap.Contains( "Ies_File_Path" );
                        if ( bContainsIes )
                        {
                            FString strIesFilePath = kAssetMap[ "Ies_File_Path" ]->AsString();
                            IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
                            if ( kPlatformFile.FileExists( *strIesFilePath ) )
                            {
                                FString strSaveTo = TEXT( "/Game/RLContent/Light/" + strLightName + "_Ies" );
                                UTextureLightProfile* pIes = LoadTextureLightProfileFromFile( strIesFilePath, strSaveTo );
                                if ( pIes )
                                {
                                    // Set Blueprint Texture
                                    AActor* pLightActor = Cast<AActor>( pBlueprint->GeneratedClass->ClassDefaultObject );
                                    if ( pLightActor )
                                    {
                                        ULightComponent* pLightComponent = pLightActor->FindComponentByClass<ULightComponent>();
                                        if ( pLightComponent )
                                        {
                                            pLightComponent->SetIESTexture( pIes );
                                            // Save Blueprint
                                            FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pBlueprint );
                                            FKismetEditorUtilities::CompileBlueprint( pBlueprint );
                                            UPackage* const pAssetPackage = pBlueprint->GetOutermost();
                                            pAssetPackage->SetDirtyFlag( true );
                                            TArray<UPackage*> kPackagesToSave;
                                            kPackagesToSave.Add( pAssetPackage );
                                            FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
                                        }
                                    }
                                }
                                bool bDeleted = kPlatformFile.DeleteFile( *strIesFilePath );
                            }
                        }
                    }
                    AActor* pLight = nullptr;
                    if ( bPlaceAsssetObject )
                    {
                        pLight = LoadToScene( pBlueprint );
                    }
                    if ( bNeedPutAssetBack && pBlueprint )
                    {
                        pLight = PutAssetBackToSceneAfterReplace( pBlueprint );
                    }
                    if ( pLight )
                    {
                        if ( USceneComponent* pSceneComponent = pLight->FindComponentByClass<USceneComponent>() )
                        {
                            pSceneComponent->Mobility = EComponentMobility::Movable;
                        }
                    }
                }
            }
        }
    }
}

void FRLLiveLinkModule::ProcessRequireFromIC( const TSharedPtr<FJsonValue>& spJsonValue )
{
    if ( spJsonValue )
    {
        TSharedPtr<FJsonObject> spReturnJson = MakeShareable( new FJsonObject );
        auto spGetArray = spJsonValue->AsArray();
        for ( auto& spAssetJsonValue : spGetArray )
        {
            FString strCmd = spAssetJsonValue->AsString();
            if ( strCmd == "GetCmdExePath" )
            {
                spReturnJson->SetStringField( "GetCmdExePath", m_strCurEngineCmdexePath );
            }
            else if ( strCmd == "GetProjectPath" )
            {
                spReturnJson->SetStringField( "GetProjectPath", m_strCurUProjectPath );
            }
            else if ( strCmd == "CheckCCPlugin" )
            {
                bool bCheckCCPlugin;
                auto kPlugin = IPluginManager::Get().FindPlugin( TEXT( "RLPlugin" ) );
                bCheckCCPlugin = ( !kPlugin ) ? false :
                    ( kPlugin->IsEnabled() ) ? true : false;
                spReturnJson->SetBoolField( "CheckCCPlugin", bCheckCCPlugin );
            }
            else if ( strCmd == "CheckUnrealLiveLinkVersion" )
            {
                auto kPlugin = IPluginManager::Get().FindPlugin( TEXT( "RLLiveLink" ) );
                const FPluginDescriptor& Descriptor = kPlugin->GetDescriptor();
                spReturnJson->SetNumberField( "CheckUnrealLiveLinkVersion", FCString::Atod( *Descriptor.VersionName ) );
            }
        }
        FString strJson;
        if ( spReturnJson.IsValid() && spReturnJson->Values.Num() > 0 )
        {
            TSharedRef<TJsonWriter<TCHAR>> spJsonWriter = TJsonWriterFactory<>::Create( &strJson );
            FJsonSerializer::Serialize( spReturnJson.ToSharedRef(), spJsonWriter );
        }
        TCHAR* pSerializedChar = strJson.GetCharArray().GetData();

        FTCHARToUTF8 kConverted( pSerializedChar ); //string to utf8
        int32 nSent = 0;
        if ( m_pConnectionSocket )
        {
            m_pConnectionSocket->Send( ( uint8* )kConverted.Get(), kConverted.Length(), nSent );
        }
    }
}

void FRLLiveLinkModule::ProcessMotionData( const TSharedPtr< FJsonValue >& spJsonValue )
{
    if ( spJsonValue )
    {
        auto spBuildArray = spJsonValue->AsArray();
        if ( !spBuildArray.IsEmpty() )
        {
            ShowProgress();
        }

        for ( auto& spAssetJsonValue : spBuildArray )
        {
            if ( auto spAssetObject = spAssetJsonValue->AsObject() )
            { 
                auto kAssetMap = spAssetObject->Values;
                FString strAssetName = kAssetMap[ "Name" ]->AsString();
                FString strAssetPath = kAssetMap[ "Path" ]->AsString();
                ProcessImportMotion( strAssetName );
                PushProgress( 1 );
                RemoveFbxFiles( strAssetName );
            }
        }
    }
}

void FRLLiveLinkModule::CheckAndDeleteDuplicatedAsset( const TSharedPtr<FJsonValue>& spJsonValue )
{
    if ( spJsonValue )
    {
        auto spGetArray = spJsonValue->AsArray();
        bool bResult = true;
        for ( auto& spExportList : spGetArray )
        {
            auto kExportData = spExportList.Get()->AsObject()->Values;
            FString strExportName = kExportData[ "Name" ]->AsString();
            FString strExportType = kExportData[ "Type" ]->AsString();

            if ( strExportType == "Avatar" || strExportType == "Prop" )
            {
                //DeleteFolder
                bResult = DeleteFolder( "/Game/RLContent/" + strExportName );
            }
            else if ( strExportType == "Camera" )
            {
                bResult = DeleteActorInScene( "/RLContent/Camera", strExportName );
            }
            else if ( strExportType == "Light" )
            {
                bResult = DeleteActorInScene( "/RLContent/Light", strExportName );
            }
            else
            {
                bResult = false;
            }
        }

        //SendMessageBack
        TSharedPtr<FJsonObject> spReturnJson = MakeShareable( new FJsonObject );
        spReturnJson->SetBoolField( "CheckAndDeleteDuplicatedAssetDone", bResult );

        FString strJson;
        if ( spReturnJson.IsValid() && spReturnJson->Values.Num() > 0 )
        {
            TSharedRef<TJsonWriter<TCHAR>> spJsonWriter = TJsonWriterFactory<>::Create( &strJson );
            FJsonSerializer::Serialize( spReturnJson.ToSharedRef(), spJsonWriter );
        }
        TCHAR* pSerializedChar = strJson.GetCharArray().GetData();

        FTCHARToUTF8 kConverted( pSerializedChar ); //string to utf8
        int32 nSent = 0;
        if ( m_pConnectionSocket )
        {
            m_pConnectionSocket->Send( ( uint8* )kConverted.Get(), kConverted.Length(), nSent );
        }
    }
}

void FRLLiveLinkModule::CheckSkeletonAssetExist( const TSharedPtr<FJsonValue>& spJsonValue )
{
    if ( spJsonValue )
    {
        TSharedPtr< FJsonObject > spAvatarsResult = MakeShareable( new FJsonObject );
        TSharedPtr< FJsonObject > spPropResult = MakeShareable( new FJsonObject );
        auto spGetArray = spJsonValue->AsArray();
        for ( auto& spExportList : spGetArray )
        {
            auto kExportData = spExportList.Get()->AsObject()->Values;
            FString strExportName = kExportData[ "Name" ]->AsString();
            FString strExportType = kExportData[ "Type" ]->AsString();

            bool bExist = true;
            FString strPath = "/RLContent/" + strExportName;
            IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
            FString strSkeletonFilePath = FPaths::ProjectContentDir() + strPath + "/" + strExportName + "_Skeleton.uasset";
            if ( !kPlatformFile.FileExists( *strSkeletonFilePath ) )
            {
                bExist = false;
            }
            if ( strExportType == "Avatar" )
            {
                spAvatarsResult->SetBoolField( strExportName, bExist );
            }
            else if ( strExportType == "Prop" )
            {
                spPropResult->SetBoolField( strExportName, bExist );
            }
        }

        //SendMessageBack
        TSharedPtr< FJsonObject > spReturnJson = MakeShareable( new FJsonObject );
        TSharedPtr< FJsonObject > spCheckResult = MakeShareable( new FJsonObject );
        spCheckResult->SetObjectField( "Avatar", spAvatarsResult );
        spCheckResult->SetObjectField( "Prop", spPropResult );
        spReturnJson->SetObjectField( "CheckSkeletonAssetExistDone", spCheckResult );

        FString strJson;
        if ( spReturnJson.IsValid() && spReturnJson->Values.Num() > 0 )
        {
            TSharedRef<TJsonWriter<TCHAR>> spJsonWriter = TJsonWriterFactory<>::Create( &strJson );
            FJsonSerializer::Serialize( spReturnJson.ToSharedRef(), spJsonWriter );
        }
        TCHAR* pSerializedChar = strJson.GetCharArray().GetData();

        FTCHARToUTF8 kConverted( pSerializedChar ); //string to utf8
        int32 nSent = 0;
        if ( m_pConnectionSocket )
        {
            m_pConnectionSocket->Send( ( uint8* )kConverted.Get(), kConverted.Length(), nSent );
        }
    }
}

void FRLLiveLinkModule::CheckAssetExist( const TSharedPtr< FJsonValue >& spJsonValue )
{
    if ( spJsonValue )
    {
        TSharedPtr< FJsonObject > spResult = MakeShareable( new FJsonObject );
        auto spGetArray = spJsonValue->AsArray();
        for ( auto& spExportList : spGetArray )
        {
            auto kExportData = spExportList.Get()->AsObject()->Values;
            FString strAssetName = kExportData[ "Name" ]->AsString();
            FString strAssetPath = kExportData[ "Path" ]->AsString();

            bool bExist = true;
            IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
            FString strSkeletonFilePath = FPaths::ProjectContentDir() + strAssetPath;
            if ( !kPlatformFile.FileExists( *strSkeletonFilePath ) )
            {
                bExist = false;
            }
            spResult->SetBoolField( strAssetName, bExist );
        }

        //SendMessageBack
        TSharedPtr< FJsonObject > spReturnJson = MakeShareable( new FJsonObject );
        spReturnJson->SetObjectField( "CheckAssetExistDone", spResult );

        FString strJson;
        if ( spReturnJson.IsValid() && spReturnJson->Values.Num() > 0 )
        {
            TSharedRef<TJsonWriter<TCHAR>> spJsonWriter = TJsonWriterFactory<>::Create( &strJson );
            FJsonSerializer::Serialize( spReturnJson.ToSharedRef(), spJsonWriter );
        }
        TCHAR* pSerializedChar = strJson.GetCharArray().GetData();

        FTCHARToUTF8 kConverted( pSerializedChar ); //string to utf8
        int32 nSent = 0;
        if ( m_pConnectionSocket )
        {
            m_pConnectionSocket->Send( ( uint8* )kConverted.Get(), kConverted.Length(), nSent );
        }
    }
}

void FRLLiveLinkModule::CheckICVersion( const TSharedPtr< FJsonValue >& spJsonValue )
{
    if ( spJsonValue )
    {

        if ( spJsonValue->AsNumber() >= 100 )
        {
            TransferSceneToIC( m_iMergeMode );
        }
        else
        {
            FText strMsg = FText::FromString( "Please make sure iClone is running properly.\nOr the current version of iClone does not support this feature. \nPlease upgrade to iClone 8.1 or later then try again." );
            FMessageDialog::Open( EAppMsgType::Ok, strMsg );
            return;
        }

    }
}

void FRLLiveLinkModule::ProcessPreImportData( const TSharedPtr<FJsonValue>& spJsonValue )
{
    ResetEditorImportSetting();
    ResetImportTaskCount();

    auto spEditorImportData = spJsonValue->AsObject();
    if ( spEditorImportData->Values.Contains( "ApFps" ) )
    {
        int nApFps =  spEditorImportData->Values[ "ApFps" ]->AsNumber();
        m_kApFps = FFrameRate( nApFps, 1 );
    }
    if ( spEditorImportData->Values.Contains( "LiveLinkFps" ) )
    {
        int nLiveLinkFps =  spEditorImportData->Values[ "LiveLinkFps" ]->AsNumber();
        m_kLiveLinkFps = FFrameRate( nLiveLinkFps, 1 );
    }
    if ( spEditorImportData->Values.Contains( "FrameRange" ) )
    {
        auto spFrameRange = spEditorImportData->Values[ "FrameRange" ]->AsArray();
        int nStartFrame = spFrameRange.GetData()[ 0 ]->AsNumber();
        int nEndFrame = spFrameRange.GetData()[ 1 ]->AsNumber();
        int nFrameSize = ( nEndFrame - nStartFrame ) + 1;
        m_kMotionFrameSize = FFrameTime( ConvertFrameTimeFromeICloneToUnreal( nFrameSize ) );
    }
    if ( spEditorImportData->Values.Contains( "TaskAmount" ) )
    {
        m_nImportAmount = spEditorImportData->Values[ "TaskAmount" ]->AsNumber();
    }
    if ( spEditorImportData->Values.Contains( "CreateLevelSequencer" ) )
    {
        m_bCreateLevelSequencer = spEditorImportData->Values[ "CreateLevelSequencer" ]->AsBool();
    }
    if ( spEditorImportData->Values.Contains( "FbxPath" ) )
    {
        m_strLiveLinkTempPath = spEditorImportData->Values[ "FbxPath" ]->AsString();
    }
    if ( spEditorImportData->Values.Contains( "isPlaceAssets" ) )
    {
        m_bIsPlaceAssets = spEditorImportData->Values[ "isPlaceAssets" ]->AsBool();
    }
}
//Add SubMenu-----------------------------------------------------------------------------------------------
TSharedRef<SWidget> FRLLiveLinkModule::FillComboButton( TSharedPtr<class FUICommandList> spCommands )
{
    FMenuBuilder kMenuBuilder( true, spCommands );

    //iClone block
    kMenuBuilder.BeginSection( "iCloneKeys", LOCTEXT( "KeysMenuiClone", "Positioning" ) );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "iCloneNode", "Create Live Link Origin" ),
        LOCTEXT( "iCloneNodeTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CreateEmptyNodeForiClone ) )
    );
    kMenuBuilder.EndSection();

    //Character block
    kMenuBuilder.BeginSection( "CharacterKeys", LOCTEXT( "KeysMenuCharacter", "Character" ) );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Character", "Apply Blueprint to Selected Character(s)" ),
        LOCTEXT( "CharacterTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::SetUpAllCharacterToBlueprint ) )
    );
    kMenuBuilder.EndSection();

    //Prop block
    kMenuBuilder.BeginSection( "PropKeys", LOCTEXT( "KeysMenuProp", "Prop" ) );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Prop", "Apply Blueprint to Selected Prop(s)" ),
        LOCTEXT( "PropTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::SetUpAllCharacterToBlueprint ) )
    );
    kMenuBuilder.EndSection();

    //Camera menu block
    kMenuBuilder.BeginSection( "CameraKeys", LOCTEXT( "KeysMenuCamera", "Camera" ) );
    /*kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Camera", "Create Camera" ),
        LOCTEXT( "CameraTip", "Create Camera Blueprint To Scene" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CreateCamera ) )
    );*/
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "CineCamera", "Create Cine Camera" ),
        LOCTEXT( "CineCameraTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CreateCineCamera ) )
    );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "CameraAdd", "Apply Blueprint to Selected Camera(s)" ),
        LOCTEXT( "CameraAddTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::SetUpAllCameraToBlueprint ) )
    );
    kMenuBuilder.EndSection();

    //Light menu block
    kMenuBuilder.BeginSection( "LightKeys", LOCTEXT( "KeysMenuLight", "Light" ) );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "SpotLight", "Create Spotlight" ),
        LOCTEXT( "SpotLightTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CreateSpotLight ) )
    );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "PointLight", "Create Point Light" ),
        LOCTEXT( "PointLightTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CreatePointLight ) )
    );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "RectLight", "Create Rect Light" ),
        LOCTEXT( "RectLightTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CreateRectLight ) )
    );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "DirectionalLight", "Create Directional Light" ),
        LOCTEXT( "DirectionalLightTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CreateDirectionalLight ) )
    );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "SpotLightAdd", "Apply Blueprint to Selected Light(s)" ),
        LOCTEXT( "SpotLightAddTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::SetUpAllLightToBlueprint ) )
    );
    kMenuBuilder.EndSection();

    kMenuBuilder.BeginSection( "iClone Data Link", LOCTEXT( "iClone Data Link", "iClone Data Link" ) );
    {
        kMenuBuilder.AddSubMenu(
            LOCTEXT( "Transfer to iClone", "Transfer to iClone" ),
            LOCTEXT( "Transfer to iClone", "" ),
            FNewMenuDelegate::CreateRaw( this, &FRLLiveLinkModule::FillTransferSceneMenu ),
            false,
            FSlateIcon()
        );
    }
    kMenuBuilder.EndSection();
    //Help menu block
    kMenuBuilder.BeginSection( "HelpKeys", LOCTEXT( "KeysMenuHelp", "Learn" ) );
    FString strWebID00 = "ICLIVELINK_005";
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Help0Add", "What is iClone Live Link?" ),
        LOCTEXT( "Help0AddTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::LiveLinkHelpMenu, strWebID00 ) )
    );
    FString strWebID01 = "ICLIVELINK_006";
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Help1Add", "Download a full-version evaluation of the tools" ),
        LOCTEXT( "Help1AddTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::LiveLinkHelpMenu, strWebID01 ) )
    );
    FString strWebID02 = "ICLIVELINK_002";
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "HelpOnlineAdd", "Online Manual" ),
        LOCTEXT( "HelpOnlineAddTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::LiveLinkHelpMenu, strWebID02 ) )
    );
    FString strWebID03 = "ICLIVELINK_003";
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "HelpVideoAdd", "Video Tutorials" ),
        LOCTEXT( "HelpVideoAddTip", "" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::LiveLinkHelpMenu, strWebID03 ) )
    );
    kMenuBuilder.EndSection();
    return kMenuBuilder.MakeWidget();
}

//for outliner and viewport right click
void FRLLiveLinkModule::AddMenuEntryInRightClick()
{
    FLevelEditorModule& kLevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>( TEXT( "LevelEditor" ) );
    auto& kViewportExtenders = kLevelEditorModule.GetAllLevelViewportContextMenuExtenders();
    kViewportExtenders.Add( FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateRaw( this, &FRLLiveLinkModule::OutlinerMenuExtend ) );
}

TSharedRef<FExtender> FRLLiveLinkModule::OutlinerMenuExtend( const TSharedRef<FUICommandList> kCommandList, const TArray<AActor*> pActors )
{
    TSharedRef<FExtender> kExtender = MakeShared<FExtender>();
    kExtender->AddMenuExtension(
        "ActorAsset",
        EExtensionHook::After,
        kCommandList,
        FMenuExtensionDelegate::CreateLambda( [ this ]( FMenuBuilder& kMenuBuilder )
        {
            kMenuBuilder.BeginSection( "iClone Data Link", LOCTEXT( "iClone Data Link", "iClone Data Link" ) );
            {
                kMenuBuilder.AddSubMenu(
                    LOCTEXT( "Transfer to iClone", "Transfer to iClone" ),
                    LOCTEXT( "Transfer to iClone", "" ),
                    FNewMenuDelegate::CreateRaw( this, &FRLLiveLinkModule::FillTransferSceneMenu ),
                    false,
                    FSlateIcon()
                );
            }
            kMenuBuilder.EndSection();
        } )
    );
    return kExtender;
}

void FRLLiveLinkModule::FillTransferSceneMenu( FMenuBuilder& kMenuBuilder )
{
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Transfer to iClone", "Transfer to iClone" ),
        LOCTEXT( "Transfer to iClone", "Transfer to iClone" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CheckICVersionBeforeTransferScene, ETransferMode::Batch ) )
    );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Transfer to iClone (Merged)", "Transfer to iClone (Merged)" ),
        LOCTEXT( "Transfer to iClone (Merged)", "Transfer to iClone (Merged)" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CheckICVersionBeforeTransferScene, ETransferMode::Merge ) )
    );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Transfer to iClone (Simplified)", "Transfer to iClone (Simplified)" ),
        LOCTEXT( "Transfer to iClone (Simplified)", "Transfer to iClone (Simplified)" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CheckICVersionBeforeTransferScene, ETransferMode::Simplify ) )
    );
    /*kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Transfer to iClone ( batch ( merge ) )", "Transfer to iClone ( batch ( merge ) )" ),
        LOCTEXT( "Transfer to iClone ( batch ( merge ) )", "Transfer to iClone ( batch ( merge ) )" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CheckICVersionBeforeTransferScene, ETransferMode::BatchMerge ) )
    );
    kMenuBuilder.AddMenuEntry(
        LOCTEXT( "Transfer to iClone ( batch ( simplify ) )", "Transfer to iClone ( batch ( simplify ) )" ),
        LOCTEXT( "Transfer to iClone ( batch ( simplify ) )", "Transfer to iClone ( batch ( simplify ) )" ),
        FSlateIcon(),
        FUIAction( FExecuteAction::CreateRaw( this, &FRLLiveLinkModule::CheckICVersionBeforeTransferScene, ETransferMode::BatchSimplify ) )
    );*/
}

//Menu Button Event----------------------------------------------------------------------------------
void FRLLiveLinkModule::CreateEmptyNodeForiClone()
{
    UWorld* const pWorld = GEditor->GetEditorWorldContext().World();
    for ( TActorIterator<AActor> pActorItr( pWorld ); pActorItr; ++pActorItr )
    {
        //Check already owned
        if ( pActorItr->GetActorLabel().ToLower() == DEFAULT_PARENT_ACTOR && pActorItr->GetClass() == AActor::StaticClass() )
        {
            return;
        }
    }
    AActor* pLiveLinkActor = FRLLiveLinkUtility::SpawnActorToViewport( AActor::StaticClass(), DEFAULT_PARENT_ACTOR);
    if ( !pLiveLinkActor )
    {
        return;
    }

    //Create LiveLink Icon Uasset
    FString strIconName = TEXT( DEFAULT_PARENT_ACTOR );
    UBillboardComponent* pBillboardComponent = NewObject<UBillboardComponent>( pLiveLinkActor, TEXT( DEFAULT_PARENT_ACTOR ) );
    if ( pBillboardComponent )
    {
        pBillboardComponent->SetFlags( RF_Transactional );
        UTexture2D* pSprite = LoadObject<UTexture2D>( nullptr, *( "/Engine/EditorResources/" + strIconName ) );
        if ( !pSprite )
        {
            FString strPackageName = TEXT( "/Engine/EditorResources/" + strIconName );
            FString strFilePath = IPluginManager::Get().FindPlugin( TEXT( "RLLiveLink" ) )->GetBaseDir() / TEXT( "Resources/iclivelink.png" );
            TArray<uint8> kRawData;
            if ( FFileHelper::LoadFileToArray( kRawData, *strFilePath ) )
            {
                UPackage* pAssetPackage = CreatePackage( *strPackageName );
                if ( pAssetPackage )
                {
                    UTextureFactory* kTexFactory = NewObject<UTextureFactory>();
                    EObjectFlags kFlags = RF_Public | RF_Standalone;

                    kRawData.Add( 0 );
                    const uint8* Ptr = &kRawData[ 0 ];
                    UObject* kTexAsset = kTexFactory->FactoryCreateBinary( UTexture::StaticClass(), pAssetPackage, FName( DEFAULT_PARENT_ACTOR ), kFlags, NULL, *FPaths::GetExtension( strFilePath ), Ptr, Ptr + kRawData.Num() - 1, GWarn );
                    if ( kTexAsset )
                    {
                        UTexture* kTexture = Cast<UTexture>( kTexAsset );
                        kTexAsset->MarkPackageDirty();
                        ULevel::LevelDirtiedEvent.Broadcast();
                        kTexAsset->PostEditChange();
                        FAssetRegistryModule::AssetCreated( kTexAsset );
                        pAssetPackage->SetDirtyFlag( true );

                        //Save
                        TArray<UPackage*> kPackagesToSave;
                        kPackagesToSave.Add( pAssetPackage );
                        FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );

                        //Reset sprite
                        pSprite = LoadObject<UTexture2D>( nullptr, *( "/Engine/EditorResources/" + strIconName ) );
                    }
                }
            }
        }

        //Set Livelink Icon
        if ( pSprite )
        {
            pBillboardComponent->SetSprite( pSprite );
            pLiveLinkActor->SetActorHiddenInGame( true );
            pLiveLinkActor->SetRootComponent( pBillboardComponent );
            pLiveLinkActor->AddInstanceComponent( pBillboardComponent );
            pLiveLinkActor->RegisterAllComponents();
        }
    }

    //set focus view on actor
    SelectAndFocusActor( pLiveLinkActor, false, true );
}

void FRLLiveLinkModule::LiveLinkHelpMenu( FString strWebID )
{
    FPlatformProcess::LaunchURL( *( "https://www.reallusion.com/linkcount/linkcount.aspx?lid=" + strWebID ), NULL, NULL );
}

void FRLLiveLinkModule::CheckICVersionBeforeTransferScene( const ETransferMode iMode )
{
    m_iMergeMode = iMode;

    GEditor->GetTimerManager()->SetTimer(
        m_kCountdownRecheckICVersionTimerHandle,
        FTimerDelegate::CreateLambda( [ this ]()
        {
            FText strMsg = FText::FromString( "Please make sure iClone is running properly.\nOr the current version of iClone does not support this feature. \nPlease upgrade to iClone 8.1 or later then try again." );
            FMessageDialog::Open( EAppMsgType::Ok, strMsg );
        } ),
        1.0f,
        false
    );
    TSharedPtr<FJsonObject> spReturnJson = MakeShareable( new FJsonObject );
    spReturnJson->SetBoolField( "CheckICLiveLinkVersion", false );

    SendJsonToIC( spReturnJson );
}

void FRLLiveLinkModule::TransferSceneToIC( ETransferMode iMode )
{
    GEditor->GetTimerManager()->ClearTimer( m_kCountdownRecheckICVersionTimerHandle );

    bool bExportFbxResult = false;
    TArray<struct ExportFbxSetting> kExportFbxSettingList;

    FDateTime Now = FDateTime::Now();
    FString strCurrentTime = FString::Printf( TEXT( "%d_%d_%d_%d_%d_%d" ),
                                              Now.GetYear(), Now.GetMonth(), Now.GetDay(), Now.GetHour(), Now.GetMinute(), Now.GetSecond() );
    FString strExportDirectory = FDesktopPlatformModule::Get()->GetUserTempPath() + "UELiveLink/";

    if ( iMode == ETransferMode::BatchMerge || iMode == ETransferMode::BatchSimplify )
    {
        TSet<UStaticMesh*> kStaticMeshList;
        BatchTransferSceneToIClone( iMode, kStaticMeshList );

        strExportDirectory = strExportDirectory + "Batch/" + strCurrentTime;
        for ( auto pStaticMesh : kStaticMeshList )
        {
            struct ExportFbxSetting kExportFbxSetting;
            kExportFbxSetting.pObjectToExport = pStaticMesh;
            kExportFbxSetting.strSaveFilePath = strExportDirectory + "/" + pStaticMesh->GetName() + ".FBX";

            kExportFbxSettingList.Add( kExportFbxSetting );
        }
#if ENGINE_MAJOR_VERSION > 4
        if ( !kExportFbxSettingList.IsEmpty() )
#else
        if ( kExportFbxSettingList.Num() )
#endif
        {
            bExportFbxResult = ExportFbx( kExportFbxSettingList );
            DeletePackageInContentBrowser( FPackageName::GetLongPackagePath( kExportFbxSettingList[ 0 ].pObjectToExport->GetPathName() ) );
        }
    }
    else if ( iMode == ETransferMode::Batch )
    {
        strExportDirectory = strExportDirectory + "Batch/" + strCurrentTime;
        FString strExportObjectName = "UE_Actor";

        USelection* pSelectedActors = GEditor->GetSelectedActors();

        if ( pSelectedActors->CountSelections<AActor>() == 0 )
        {
            return;
        }
        else if ( pSelectedActors->CountSelections<AActor>() == 1 )
        {
#if ENGINE_MAJOR_VERSION > 4
            strExportObjectName = pSelectedActors->GetTop<AActor>()->GetActorNameOrLabel();
#else
            strExportObjectName = pSelectedActors->GetTop<AActor>()->GetActorLabel().Len() != 0 ? pSelectedActors->GetTop<AActor>()->GetActorLabel() : pSelectedActors->GetTop<AActor>()->GetName();
#endif
        }
        FString strSaveFilePath = strExportDirectory + "/" + strExportObjectName + ".FBX";

        TSet<AActor*> kDeselectedActors;
        if ( !DeselectNonStaticMeshActors( kDeselectedActors ) )
        {
            for ( auto pDeselectedActors : kDeselectedActors )
            {
                GEditor->GetSelectedActors()->Select( Cast<UObject>( pDeselectedActors ) );
            }
            return;
        }

        bExportFbxResult = ExportSelected( strSaveFilePath );

        //在把原本deselect 掉的select回來
        for ( auto pDeselectedActors : kDeselectedActors )
        {
            GEditor->GetSelectedActors()->Select( Cast<UObject>( pDeselectedActors ) );
        }
    }
    else if ( iMode == ETransferMode::Merge || iMode == ETransferMode::Simplify )
    {
        FString strExportMeshMergePathToLoad = "";
        if ( !RunMergeFromSelection( iMode, strExportMeshMergePathToLoad ) )
        {
            //FText strMsg = FText::FromString( "Fail to merge" );
            //FMessageDialog::Open( EAppMsgType::Ok, strMsg );
            return;
        }

        //get UObject
        UStaticMesh* pStaticMesh = Cast<UStaticMesh>( StaticLoadObject( UStaticMesh::StaticClass(), nullptr, *( strExportMeshMergePathToLoad ) ) );

        //export fbx 
        if ( !pStaticMesh )
        {
            return;
        }

        switch ( iMode )
        {
            case ETransferMode::Merge:
                strExportDirectory = strExportDirectory + "Merged/" + strCurrentTime;
                break;
            case ETransferMode::Simplify:
                strExportDirectory = strExportDirectory + "Simplified/" + strCurrentTime;
                break;
        }
        struct ExportFbxSetting kExportFbxSetting;
        kExportFbxSetting.pObjectToExport = pStaticMesh;
        kExportFbxSetting.strSaveFilePath = strExportDirectory + "/" + pStaticMesh->GetName() + ".FBX";

        kExportFbxSettingList.Add( kExportFbxSetting );

        bExportFbxResult = ExportFbx( kExportFbxSettingList );
        //delete temp merged object in content browser
        DeletePackageInContentBrowser( FPackageName::GetLongPackagePath( strExportMeshMergePathToLoad ) );
    }
    if ( bExportFbxResult )
    {
        TSharedPtr<FJsonObject> spReturnJson = MakeShareable( new FJsonObject );

        spReturnJson->SetStringField( "DataLinkExportedFbxFilePath", strExportDirectory );
        if ( iMode == ETransferMode::Batch )
        {
            spReturnJson->SetStringField( "DataLinkExportedFbxTargetCollectionName", "UE_Scene" );
        }
        else
        {
            spReturnJson->SetStringField( "DataLinkExportedFbxTargetCollectionName", "UE_Merged" );
        }

        SendJsonToIC( spReturnJson );

    }
    else
    {
        FText strMsg = FText::FromString( "Fail to export" );
        FMessageDialog::Open( EAppMsgType::Ok, strMsg );
    }
}

bool CheckActorComponentCanBeTransferToIC( UPrimitiveComponent* pPrimComponent )
{
    if ( !pPrimComponent->IsVisible() )
    {
        return false;
    }

    if ( UStaticMeshComponent* pStaticMeshComponent = Cast<UStaticMeshComponent>( pPrimComponent ) )
    {
        UStaticMesh* pStaticMesh = pStaticMeshComponent->GetStaticMesh();

        if ( pStaticMesh )
        {
            return true;
        }
    }

    return false;
}

bool FRLLiveLinkModule::DeselectNonStaticMeshActors( TSet<AActor*>& kDeselectedActors )
{
    USelection* pSelectedActors = GEditor->GetSelectedActors();

    TSet<AActor*> pActors;

    for ( FSelectionIterator pIter( *pSelectedActors ); pIter; ++pIter )
    {
        AActor* pActor = Cast<AActor>( *pIter );
        if ( pActor )
        {
            pActors.Add( pActor );
            // Add child actors & actors found under foundations

#if ENGINE_MAJOR_VERSION >= 5
            pActor->EditorGetUnderlyingActors( pActors );
#else
            EditorGetUnderlyingActors( pActor, pActors );
#endif
        }
    }

    for ( AActor* pActor : pActors )
    {
        check( pActor != nullptr );

        TArray<UPrimitiveComponent*> pPrimComponents;
        pActor->GetComponents<UPrimitiveComponent>( pPrimComponents );
        bool bInclude = false;
        for ( UPrimitiveComponent* pPrimComponent : pPrimComponents )
        {
            if ( CheckActorComponentCanBeTransferToIC( pPrimComponent ) )
            {
                bInclude = true;
                break;
            }
        }
        if ( !bInclude )
        {
            pSelectedActors->Deselect( Cast<UObject>( pActor ) );
            kDeselectedActors.Add( pActor );
        }
    }
    int iAfterDeselection = pSelectedActors->CountSelections<AActor>();

    if ( iAfterDeselection == 0 )
    {
        FText strMsg = FText::FromString( "The selected actor(s) do not have static mesh." );
        FMessageDialog::Open( EAppMsgType::Ok, strMsg );
        return false;
    }
#if ENGINE_MAJOR_VERSION > 4
    else if ( !kDeselectedActors.IsEmpty() )
#else
    else if ( kDeselectedActors.Num() )
#endif
    {
        FString strListOfActorsName = "";
        for ( AActor* pDeselectedActor : kDeselectedActors )
        {
#if ENGINE_MAJOR_VERSION > 4
            strListOfActorsName = strListOfActorsName + pDeselectedActor->GetActorNameOrLabel() + "\n";
#else
            FString strActorName = pDeselectedActor->GetActorLabel().Len() != 0 ? pDeselectedActor->GetActorLabel() : pDeselectedActor->GetName();
            strListOfActorsName = strListOfActorsName + strActorName + "\n";
#endif
        }
        FText strMsg = FText::FromString( "Some actors do not have static mesh.\nPress Continue to skip these actors or Cancel to end the procedure.\n\r" + strListOfActorsName );
        const EAppReturnType::Type eChoice = FMessageDialog::Open( EAppMsgType::OkCancel, strMsg );

        if ( eChoice == EAppReturnType::Cancel )
        {
            return false;
        }
    }

    return true;
}

void FRLLiveLinkModule::SendJsonToIC( const TSharedPtr<FJsonObject>& spReturnJson )
{
    FString strJson;
    if ( spReturnJson.IsValid() && spReturnJson->Values.Num() > 0 )
    {
        TSharedRef<TJsonWriter<TCHAR>> spJsonWriter = TJsonWriterFactory<>::Create( &strJson );
        FJsonSerializer::Serialize( spReturnJson.ToSharedRef(), spJsonWriter );
    }
    TCHAR* pSerializedChar = strJson.GetCharArray().GetData();

    FTCHARToUTF8 kConverted( pSerializedChar ); //string to utf8
    int32 nSent = 0;

    if ( m_pConnectionSocket )
    {
        m_pConnectionSocket->Send( ( uint8* )kConverted.Get(), kConverted.Length(), nSent );
    }
    else
    {
        GEditor->GetTimerManager()->ClearTimer( m_kCountdownRecheckICVersionTimerHandle );
        FText strMsg = FText::FromString( "Please make sure iClone is running properly.\nOr the current version of iClone does not support this feature. \nPlease upgrade to iClone 8.1 or later then try again." );
        FMessageDialog::Open( EAppMsgType::Ok, strMsg );
    }
}
//Export Fbx
//修改自void FAssetFileContextMenu::ExecuteExport()
bool FRLLiveLinkModule::ExportFbx( const struct ExportFbxSetting& kExportFbxSetting )
{
    TArray<struct ExportFbxSetting> kExportFbxSettings;
    kExportFbxSettings.Add( kExportFbxSetting );

    if ( kExportFbxSettings.Num() > 0 )
    {
        return ExportAssetsInternal( kExportFbxSettings );
    }

    return false;
}

bool FRLLiveLinkModule::ExportFbx( const TArray<struct ExportFbxSetting>& kExportFbxSettings )
{
    if ( kExportFbxSettings.Num() > 0 )
    {
        return ExportAssetsInternal( kExportFbxSettings );
    }

    return false;
}
//修改自void UAssetToolsImpl::ExportAssetsInternal
bool FRLLiveLinkModule::ExportAssetsInternal( const TArray<struct ExportFbxSetting>& kExportFbxSettings, bool bPromptIndividualFilenames ) const//bPromptIndividualFilenames應該是要每個object個別指定位置用吧?
{
    if ( kExportFbxSettings.Num() == 0 )
    {
        return false;
    }

    GWarn->BeginSlowTask( NSLOCTEXT( "UnrealEd", "Exporting", "Exporting" ), true );

    // Create an array of all available exporters.
    TArray<UExporter*> kExporters;
    ObjectTools::AssembleListOfExporters( kExporters );

    //Array to control the batch mode and the show options for the exporters that will be use by the selected assets
    TArray<UExporter*> pUsedExporters;

    // Export the objects.
    bool bAnyObjectMissingSourceData = false;
    for ( int32 Index = 0; Index < kExportFbxSettings.Num(); ++Index )
    {
        GWarn->StatusUpdate( Index, kExportFbxSettings.Num(), FText::Format( NSLOCTEXT( "UnrealEd", "Exportingf", "Exporting ({0} of {1})" ), FText::AsNumber( Index ), FText::AsNumber( kExportFbxSettings.Num() ) ) );

        UObject* pObjectToExport = kExportFbxSettings[ Index ].pObjectToExport;
        if ( !pObjectToExport )
        {
            continue;
        }

        if ( pObjectToExport->GetOutermost()->HasAnyPackageFlags( PKG_DisallowExport ) )
        {
            continue;
        }

        // Find all the exporters that can export this type of object and construct an export file dialog.
        TArray<FString> kPreferredExtensions;
        //把可以用的exporter挑出來
        // Iterate in reverse so the most relevant file formats are considered first.
        for ( int32 iExporterIndex = kExporters.Num() - 1; iExporterIndex >= 0; --iExporterIndex )
        {
            UExporter* pExporter = kExporters[ iExporterIndex ];
            if ( pExporter->SupportedClass )
            {
                const bool bObjectIsSupported = pExporter->SupportsObject( pObjectToExport );
                if ( bObjectIsSupported )
                {
                    // Get a string representing of the exportable types.
                    check( pExporter->FormatExtension.IsValidIndex( pExporter->PreferredFormatIndex ) );
                    for ( int32 iFormatIndex = pExporter->FormatExtension.Num() - 1; iFormatIndex >= 0; --iFormatIndex )
                    {
                        const FString strFormatExtension = pExporter->FormatExtension[ iFormatIndex ];

                        if ( iFormatIndex == pExporter->PreferredFormatIndex )
                        {
                            kPreferredExtensions.Add( strFormatExtension );
                        }
                    }
                }
            }
        }

        // Skip this object if no exporter found for this resource type.
        if ( kPreferredExtensions.Num() == 0 )
        {
            continue;
        }

        // Create the path, then make sure the target file is not read-only.
        if ( IFileManager::Get().FileExists( *kExportFbxSettings[ Index ].strSaveFilePath ) )
        {
            IFileManager::Get().Delete( *kExportFbxSettings[ Index ].strSaveFilePath );
        }

        const FString strObjectExportPath( FPaths::GetPath( kExportFbxSettings[ Index ].strSaveFilePath ) );
        const bool bFileInSubdirectory = strObjectExportPath.Contains( TEXT( "/" ) );
        if ( bFileInSubdirectory && ( !IFileManager::Get().MakeDirectory( *strObjectExportPath, true ) ) )
        {
            FMessageDialog::Open( EAppMsgType::Ok, FText::Format( NSLOCTEXT( "UnrealEd", "Error_FailedToMakeDirectory", "Failed to make directory {0}" ), FText::FromString( strObjectExportPath ) ) );

            return false;
        }
        else if ( IFileManager::Get().IsReadOnly( *kExportFbxSettings[ Index ].strSaveFilePath ) )
        {
            FMessageDialog::Open( EAppMsgType::Ok, FText::Format( NSLOCTEXT( "UnrealEd", "Error_CouldntWriteToFile_F", "Couldn't write to file '{0}'. Maybe file is read-only?" ), FText::FromString( kExportFbxSettings[ Index ].strSaveFilePath ) ) );

            return false;
        }
        else
        {
            //設定 FBX export setting
            UFbxExportOption* kFbxExportOption = GetMutableDefault<UFbxExportOption>();
            kFbxExportOption->LevelOfDetail = false;
            kFbxExportOption->Collision = false;
            kFbxExportOption->bExportMorphTargets = false;
            kFbxExportOption->VertexColor = false;
            kFbxExportOption->bExportLocalTime = false;
            // We have a writeable file.  Now go through that list of exporters again and find the right exporter and use it.
            TArray<UExporter*>	kValidExporters;

            for ( int32 iExporterIndex = 0; iExporterIndex < kExporters.Num(); ++iExporterIndex )
            {
                UExporter* pExporter = kExporters[ iExporterIndex ];
                if ( pExporter->SupportsObject( pObjectToExport ) )
                {
                    check( pExporter->FormatExtension.Num() == pExporter->FormatDescription.Num() );
                    for ( int32 iFormatIndex = 0; iFormatIndex < pExporter->FormatExtension.Num(); ++iFormatIndex )
                    {
                        const FString FormatExtension = pExporter->FormatExtension[ iFormatIndex ];
                        if ( FCString::Stricmp( *FormatExtension, *FPaths::GetExtension( kExportFbxSettings[ Index ].strSaveFilePath ) ) == 0 ||
                             FCString::Stricmp( *FormatExtension, TEXT( "*" ) ) == 0 )
                        {
                            kValidExporters.Add( pExporter );
                            break;
                        }
                    }
                }
            }

            // Handle the potential of multiple exporters being found
            UExporter* pExporterToUse = NULL;
            if ( kValidExporters.Num() == 1 )
            {
                pExporterToUse = kValidExporters[ 0 ];
            }
            else if ( kValidExporters.Num() > 1 )
            {
                // Set up the first one as default
                pExporterToUse = kValidExporters[ 0 ];

                // ...but search for a better match if available
                for ( int32 iExporterIdx = 0; iExporterIdx < kValidExporters.Num(); ++iExporterIdx )
                {
                    if ( kValidExporters[ iExporterIdx ]->GetClass()->GetFName() == pObjectToExport->GetExporterName() )
                    {
                        pExporterToUse = kValidExporters[ iExporterIdx ];
                        break;
                    }
                }
            }

            // If an exporter was found, use it.
            if ( pExporterToUse )
            {

                if ( !pUsedExporters.Contains( pExporterToUse ) )
                {
                    pExporterToUse->SetBatchMode( kExportFbxSettings.Num() > 1 && !bPromptIndividualFilenames );
                    pExporterToUse->SetCancelBatch( false );
                    pExporterToUse->SetShowExportOption( true );
                    pExporterToUse->AddToRoot();
                    pUsedExporters.Add( pExporterToUse );
                }

                UAssetExportTask* pExportTask = NewObject<UAssetExportTask>();
                FGCObjectScopeGuard ExportTaskGuard( pExportTask );
                pExportTask->Object = pObjectToExport;
                pExportTask->Exporter = pExporterToUse;
                pExportTask->Filename = kExportFbxSettings[ Index ].strSaveFilePath;
                pExportTask->bSelected = false;
                pExportTask->bReplaceIdentical = true;
                pExportTask->bPrompt = false;
                pExportTask->bUseFileArchive = pObjectToExport->IsA( UPackage::StaticClass() );
                pExportTask->bWriteEmptyFiles = false;
                pExportTask->Options = kFbxExportOption;
                pExportTask->bAutomated = true;
                if ( !UExporter::RunAssetExportTask( pExportTask ) ) //when fail -> return false
                {
                    return false;
                }

                if ( pExporterToUse->GetBatchMode() && pExporterToUse->GetCancelBatch() )
                {
                    //Exit the export file loop when there is a cancel all
                    break;
                }

            }
        }
    }

    //Set back the default value for the all used exporters
    for ( UExporter* pUsedExporter : pUsedExporters )
    {
        pUsedExporter->SetBatchMode( false );
        pUsedExporter->SetCancelBatch( false );
        pUsedExporter->SetShowExportOption( true );
        pUsedExporter->RemoveFromRoot();
    }
    pUsedExporters.Empty();

    if ( bAnyObjectMissingSourceData )
    {
        FMessageDialog::Open( EAppMsgType::Ok, NSLOCTEXT( "UnrealEd", "Exporter_Error_SourceDataUnavailable", "No source data available for some objects.  See the log for details." ) );
    }

    GWarn->EndSlowTask();

    return true;
}
//修改自void FEditorFileUtils::Export(bool bExportSelectedActorsOnly)
bool FRLLiveLinkModule::ExportSelected( const FString& strSaveFilePath )
{
    UWorld* World = GWorld;
    if ( !strSaveFilePath.IsEmpty() )
    {
        const FString strObjectExportPath( FPaths::GetPath( strSaveFilePath ) );
        const bool bFileInSubdirectory = strObjectExportPath.Contains( TEXT( "/" ) );
        if ( bFileInSubdirectory && ( !IFileManager::Get().MakeDirectory( *strObjectExportPath, true ) ) )
        {
            FMessageDialog::Open( EAppMsgType::Ok, FText::Format( NSLOCTEXT( "UnrealEd", "Error_FailedToMakeDirectory", "Failed to make directory {0}" ), FText::FromString( strObjectExportPath ) ) );

            return false;
        }
        else
        {
            FString MapFileName = FPaths::GetCleanFilename( *strSaveFilePath );
            const FText LocalizedExportingMap = FText::Format( NSLOCTEXT( "UnrealEd", "ExportingMap_F", "Exporting map: {0}..." ), FText::FromString( MapFileName ) );
            GWarn->BeginSlowTask( LocalizedExportingMap, true );

            UFbxExportOption* kFbxExportOption = GetMutableDefault<UFbxExportOption>();
            kFbxExportOption->LevelOfDetail = false;
            kFbxExportOption->Collision = false;
            kFbxExportOption->bExportMorphTargets = false;
            kFbxExportOption->VertexColor = false;
            kFbxExportOption->bExportLocalTime = false;

            UAssetExportTask* pExportTask = NewObject<UAssetExportTask>();
            FGCObjectScopeGuard ExportTaskGuard( pExportTask );
            pExportTask->Object = World;
            pExportTask->Exporter = NULL;
            pExportTask->Filename = strSaveFilePath;
            pExportTask->bSelected = true;
            pExportTask->bReplaceIdentical = true;
            pExportTask->bPrompt = false;
            pExportTask->bUseFileArchive = false;
            pExportTask->bWriteEmptyFiles = false;
            pExportTask->Options = kFbxExportOption;
            pExportTask->bAutomated = true;

            if ( !UExporter::RunAssetExportTask( pExportTask ) )
            {
                return false;
            }

            GWarn->EndSlowTask();
            return true;
        }
    }
    return false;
}

//merge actors
bool FRLLiveLinkModule::RunMergeFromSelection( ETransferMode eMergeMode, FString& strPackageName )
{
    TArray<TSharedPtr<FMergeComponentData>> kSelectionDataList;
    if ( !BuildMergeComponentDataFromSelection( kSelectionDataList ) )
    {
        return false; // if user press cancel
    }

    if ( kSelectionDataList.Num() == 0 || !HasAtLeastOneStaticMesh( kSelectionDataList ) )
    {
        FText strMsg = FText::FromString( "The selected actor(s) do not have static mesh." );
        FMessageDialog::Open( EAppMsgType::Ok, strMsg );
        return false;
    }

    //FString strPackageName;
    if ( GetPackageNameForMergeAction( GetDefaultPackageName(), strPackageName ) )
    {
        bool bResult = false;

        switch ( eMergeMode )
        {
            case ETransferMode::Merge:
                bResult = RunMerge( strPackageName, kSelectionDataList );
                break;

            case ETransferMode::Simplify:
                bResult = RunSimplify( strPackageName, kSelectionDataList );
                //因為最後外部在取object的時候只取static mesh，所以strPackageName會改成static mesh的path
                strPackageName = FPackageName::GetLongPackagePath( strPackageName ) + TEXT( "/SM_" ) + FPackageName::GetShortName( strPackageName );
                break;
        }
        return bResult;
    }
    else
    {
        return false;
    }
}
bool FRLLiveLinkModule::RunSimplify( const FString& strPackageName, const TArray<TSharedPtr<FMergeComponentData>>& kSelectedComponents )//bReplaceSourceActors 在這裡永遠都是false
{
    TArray<AActor*> pActors;
    TArray<ULevel*> pUniqueLevels;
    TArray<UObject*> pAssetsToSync;

    BuildActorsListFromMergeComponentsData( kSelectedComponents, pActors, nullptr );

    if ( pActors.Num() )
    {
        // Get the module for the mesh merge utilities
        const IMeshMergeUtilities& kMeshMergeUtilities = FModuleManager::Get().LoadModuleChecked<IMeshMergeModule>( "MeshMergeUtilities" ).GetUtilities();

        GWarn->BeginSlowTask( LOCTEXT( "MeshProxy_CreatingProxy", "Creating Mesh Proxy" ), true );
        GEditor->BeginTransaction( LOCTEXT( "MeshProxy_Create", "Creating Mesh Proxy" ) );

        FVector kProxyLocation = FVector::ZeroVector;
        TArray<UObject*> pNewAssetsToSync;

        FCreateProxyDelegate kProxyDelegate;
        kProxyDelegate.BindLambda(
            [ &pNewAssetsToSync ]( const FGuid kGuid, TArray<UObject*>& kInAssetsToSync )
        {

        } );

        // Extracting static mesh components from the selected mesh components in the dialog
        TArray<UStaticMeshComponent*> pStaticMeshComponentsToMerge;

        for ( const TSharedPtr<FMergeComponentData>& pSelectedComponent : kSelectedComponents )
        {
            // Determine whether or not this component should be incorporated according the user settings
            if ( pSelectedComponent->bShouldIncorporate && pSelectedComponent->PrimComponent.IsValid() )
            {
                if ( UStaticMeshComponent* pStaticMeshComponent = Cast<UStaticMeshComponent>( pSelectedComponent->PrimComponent.Get() ) )
                    pStaticMeshComponentsToMerge.Add( pStaticMeshComponent );
            }
        }
        pStaticMeshComponentsToMerge.RemoveAll( []( UStaticMeshComponent* pVal ) { return pVal->GetStaticMesh() == nullptr; } );
#if ENGINE_MAJOR_VERSION > 4
        if ( !pStaticMeshComponentsToMerge.IsEmpty() )
#else
        if ( pStaticMeshComponentsToMerge.Num() )
#endif
        {
            FGuid kJobGuid = FGuid::NewGuid();
            kMeshMergeUtilities.CreateProxyMesh( pStaticMeshComponentsToMerge, m_kMeshProxySetting, nullptr, strPackageName, kJobGuid, kProxyDelegate );
        }

        GEditor->EndTransaction();
        GWarn->EndSlowTask();
    }

    return true;
}

void FRLLiveLinkModule::BuildActorsListFromMergeComponentsData( const TArray<TSharedPtr<FMergeComponentData>>& kInComponentsData, TArray<AActor*>& pOutActors, TArray<ULevel*>* pOutLevels /* = nullptr */ )
{
    for ( const TSharedPtr<FMergeComponentData>& pSelectedComponent : kInComponentsData )
    {
        if ( pSelectedComponent->PrimComponent.IsValid() )
        {
            AActor* pActor = pSelectedComponent->PrimComponent.Get()->GetOwner();
            pOutActors.AddUnique( pActor );
            if ( pOutLevels )
                pOutLevels->AddUnique( pActor->GetLevel() );
        }
    }
}

bool FRLLiveLinkModule::RunMerge( const FString& strPackageName, const TArray<TSharedPtr<FMergeComponentData>>& kSelectedComponents )//bReplaceSourceActors 在這裡永遠都是false
{
    const IMeshMergeUtilities& kMeshUtilities = FModuleManager::Get().LoadModuleChecked<IMeshMergeModule>( "MeshMergeUtilities" ).GetUtilities();
    TArray<ULevel*> kUniqueLevels;

    m_kMeshMergeSettings.bPivotPointAtZero = true;

    FVector kMergedActorLocation;
    TArray<UObject*> pAssetsToSync;
    // Merge...
    {
        FScopedSlowTask kSlowTask( 0, LOCTEXT( "MergingActorsSlowTask", "Merging actors..." ) );
        kSlowTask.MakeDialog();

        // Extracting static mesh components from the selected mesh components in the dialog
        TArray<UPrimitiveComponent*> pComponentsToMerge;

        for ( const TSharedPtr<FMergeComponentData>& pSelectedComponent : kSelectedComponents )
        {
            // Determine whether or not this component should be incorporated according the user settings
            if ( pSelectedComponent->bShouldIncorporate && pSelectedComponent->PrimComponent.IsValid() )
            {
                pComponentsToMerge.Add( pSelectedComponent->PrimComponent.Get() );
            }
        }

        if ( pComponentsToMerge.Num() )
        {
            UWorld* pWorld = pComponentsToMerge[ 0 ]->GetWorld();
            checkf( pWorld != nullptr, TEXT( "Invalid World retrieved from Mesh components" ) );
            const float fScreenAreaSize = TNumericLimits<float>::Max();

            // If the merge destination package already exists, it is possible that the mesh is already used in a scene somewhere, or its materials or even just its textures.
            // Static primitives uniform buffers could become invalid after the operation completes and lead to memory corruption. To avoid it, we force a global reregister.
            if ( FindObject<UObject>( nullptr, *strPackageName ) )
            {
                kMeshUtilities.MergeComponentsToStaticMesh( pComponentsToMerge, pWorld, m_kMeshMergeSettings, nullptr, nullptr, strPackageName, pAssetsToSync, kMergedActorLocation, fScreenAreaSize, true );
            }
            else
            {
                kMeshUtilities.MergeComponentsToStaticMesh( pComponentsToMerge, pWorld, m_kMeshMergeSettings, nullptr, nullptr, strPackageName, pAssetsToSync, kMergedActorLocation, fScreenAreaSize, true );
            }
        }
    }
    return true;
}

bool FRLLiveLinkModule::GetPackageNameForMergeAction( const FString& strDefaultPackageName, FString& strOutPackageName )
{
    if ( strOutPackageName != "" )
    {
        return true;
    }
    if ( strDefaultPackageName.Len() > 0 )
    {
        const FString strDefaultPath = FPackageName::GetLongPackagePath( strDefaultPackageName );
        const FString strDefaultName = FPackageName::GetShortName( strDefaultPackageName );
        //之後再看路徑要改哪裡，現在先用預設的
        FString strSaveObjectPath = strDefaultPath + "/Temp/" + strDefaultName;
        if ( !strSaveObjectPath.IsEmpty() && CreatePackage( *strSaveObjectPath ) )
        {
            strOutPackageName = FPackageName::ObjectPathToPackageName( strSaveObjectPath );
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        strOutPackageName = strDefaultPackageName;
        return true;
    }
}
void FRLLiveLinkModule::EditorGetUnderlyingActors( AActor* pActor, TSet<AActor*>& kOutUnderlyingActors ) const
{
    TInlineComponentArray<UChildActorComponent*> pChildActorComponents;
    pActor->GetComponents( pChildActorComponents );

    kOutUnderlyingActors.Reserve( kOutUnderlyingActors.Num() + pChildActorComponents.Num() );

    for ( UChildActorComponent* pChildActorComponent : pChildActorComponents )
    {
        if ( AActor* pChildActor = pChildActorComponent->GetChildActor() )
        {
            bool bAlreadySet = false;
            kOutUnderlyingActors.Add( pChildActor, &bAlreadySet );
            if ( !bAlreadySet )
            {
                FRLLiveLinkModule::EditorGetUnderlyingActors( pChildActor, kOutUnderlyingActors );
            }
        }
    }
}
bool FRLLiveLinkModule::BuildMergeComponentDataFromSelection( TArray<TSharedPtr<FMergeComponentData>>& kOutComponentsData )
{
    kOutComponentsData.Empty();

    // Retrieve selected actors
    USelection* pSelectedActors = GEditor->GetSelectedActors();

    TSet<AActor*> pActors;
    TSet<AActor*> pNotIncludedActors;

    for ( FSelectionIterator pIter( *pSelectedActors ); pIter; ++pIter )
    {
        AActor* pActor = Cast<AActor>( *pIter );
        if ( pActor )
        {
            pActors.Add( pActor );
            // Add child actors & actors found under foundations

#if ENGINE_MAJOR_VERSION >= 5
            pActor->EditorGetUnderlyingActors( pActors );
#else
            EditorGetUnderlyingActors( pActor, pActors );
#endif
        }
    }

    for ( AActor* pActor : pActors )
    {
        check( pActor != nullptr );

        bool bNotStaticMesh = true;
        TArray<UPrimitiveComponent*> pPrimComponents;
        pActor->GetComponents<UPrimitiveComponent>( pPrimComponents );
        for ( UPrimitiveComponent* pPrimComponent : pPrimComponents )
        {
            bool bInclude = false; // Should put into UI list
            bool bShouldIncorporate = false; // Should default to part of merged mesh
            bool bIsMesh = false;

            if ( CheckActorComponentCanBeTransferToIC( pPrimComponent ) )
            {
                bShouldIncorporate = ( Cast<UStaticMeshComponent>( pPrimComponent )->GetStaticMesh() != nullptr );
                bInclude = true;
                bIsMesh = true;
            }

            if ( bInclude )
            {
                kOutComponentsData.Add( TSharedPtr<FMergeComponentData>( new FMergeComponentData( pPrimComponent ) ) );
                TSharedPtr<FMergeComponentData>& pComponentData = kOutComponentsData.Last();
                pComponentData->bShouldIncorporate = bShouldIncorporate;
                bNotStaticMesh = false;
            }
        }
        if ( bNotStaticMesh )
        {
            pNotIncludedActors.Add( pActor );
        }
    }
#if ENGINE_MAJOR_VERSION > 4
    if ( !pNotIncludedActors.IsEmpty() && pNotIncludedActors.Num() < pActors.Num() )
#else
    if ( pNotIncludedActors.Num() && pNotIncludedActors.Num() < pActors.Num() )
#endif
    {

        FString strListOfActorsName = "";
        for ( AActor* pNotIncludedActor : pNotIncludedActors )
        {
#if ENGINE_MAJOR_VERSION > 4
            strListOfActorsName = strListOfActorsName + pNotIncludedActor->GetActorNameOrLabel() + "\n";
#else
            FString strActorName = pNotIncludedActor->GetActorLabel().Len() != 0 ? pNotIncludedActor->GetActorLabel() : pNotIncludedActor->GetName();
            strListOfActorsName = strListOfActorsName + strActorName + "\n";
#endif
        }
        FText strMsg = FText::FromString( "Some actors do not have static mesh.\nPress Continue to skip these actors or Cancel to end the procedure.\n\r" + strListOfActorsName );
        const EAppReturnType::Type eChoice = FMessageDialog::Open( EAppMsgType::OkCancel, strMsg );

        if ( eChoice == EAppReturnType::Cancel )
        {
            return false;
        }
    }
    return true;
}

bool FRLLiveLinkModule::HasAtLeastOneStaticMesh( const TArray<TSharedPtr<FMergeComponentData>>& kComponentsData )
{
    for ( const TSharedPtr<FMergeComponentData>& pComponentData : kComponentsData )
    {
        if ( !pComponentData->bShouldIncorporate )
            continue;

        const bool bIsMesh = ( Cast<UStaticMeshComponent>( pComponentData->PrimComponent.Get() ) != nullptr );

        if ( bIsMesh )
            return true;
    }

    return false;
}

FString FRLLiveLinkModule::GetDefaultPackageName() const
{
    FString strPackageName = FPackageName::FilenameToLongPackageName( FPaths::ProjectContentDir() + TEXT( "IC_MERGED" ) );

    USelection* pSelectedActors = GEditor->GetSelectedActors();
    // Iterate through selected actors and find first static mesh asset
    // Use this static mesh path as destination package name for a merged mesh
    for ( FSelectionIterator pIter( *pSelectedActors ); pIter; ++pIter )
    {
        AActor* pActor = Cast<AActor>( *pIter );
        if ( pActor )
        {
#if ENGINE_MAJOR_VERSION > 4
            FString strActorName = pActor->GetActorNameOrLabel();
#else
            FString strActorName = pActor->GetActorLabel().Len() != 0 ? pActor->GetActorLabel() : pActor->GetName();
#endif
            strPackageName = FString::Printf( TEXT( "%s_%s" ), *strPackageName, *strActorName );
            break;
        }
    }

    if ( strPackageName.IsEmpty() )
    {
        strPackageName = MakeUniqueObjectName( NULL, UPackage::StaticClass(), *strPackageName ).ToString();
    }

    return strPackageName;
}

bool FRLLiveLinkModule::CheckAssetExist( const FString& strAssetPath )
{
    FAssetRegistryModule& kAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>( "AssetRegistry" );
    FAssetData AssetData = kAssetRegistryModule.Get().GetAssetByObjectPath( *strAssetPath );

    return AssetData.IsValid();
}

bool FRLLiveLinkModule::BatchTransferSceneToIClone( ETransferMode eMergeMode, TSet<UStaticMesh*>& kStaticMeshList )
{
    kStaticMeshList.Empty();

    TArray<AActor*> kSelectedActors;
    TArray<TSharedPtr<FMergeComponentData>> kSelectionDataList;
    TArray<struct ExportFbxSetting> kExportFbxSettingList;

    if ( !BuildMergeComponentDataFromSelection( kSelectionDataList ) )
    {
        return false; // if user press cancel
    }

    if ( kSelectionDataList.Num() == 0 || !HasAtLeastOneStaticMesh( kSelectionDataList ) )
    {
        FText strMsg = FText::FromString( "The selected actor(s) do not have static mesh." );
        FMessageDialog::Open( EAppMsgType::Ok, strMsg );
        return false;
    }

    for ( auto pSelectionData : kSelectionDataList )
    {
        AActor* pActor = pSelectionData->PrimComponent.Get()->GetOwner();

        FString strPackageBaseName = FPackageName::FilenameToLongPackageName( FPaths::ProjectContentDir() + TEXT( "Temp/" ) ) + pActor->GetName();
        FString strPackageName = strPackageBaseName;
        int iSerialNumber = 0;

        auto strCheckPackageName = [ &eMergeMode, &strPackageName ]() -> FString
        {
            if ( eMergeMode == ETransferMode::BatchSimplify )
            {
                return FPackageName::GetLongPackagePath( strPackageName ) + TEXT( "/SM_" ) + FPackageName::GetShortName( strPackageName );
            }
            else
            {
                return strPackageName;
            }
        };

        while ( CheckAssetExist( strCheckPackageName() ) )
        {
            strPackageName = FString::Printf( TEXT( "%s_%d" ), *strPackageBaseName, iSerialNumber );
            ++iSerialNumber;
        }

        if ( GetPackageNameForMergeAction( "", strPackageName ) )
        {
            TArray<TSharedPtr<FMergeComponentData>> kDataToMerge;
            kDataToMerge.Add( pSelectionData );

            bool bResult = false;

            switch ( eMergeMode )
            {
                case ETransferMode::BatchMerge:
                    bResult = RunMerge( strPackageName, kDataToMerge );
                    break;

                case ETransferMode::BatchSimplify:
                    bResult = RunSimplify( strPackageName, kDataToMerge );
                    //因為最後外部在取object的時候只取static mesh，所以strPackageName會改成static mesh的path
                    strPackageName = FPackageName::GetLongPackagePath( strPackageName ) + TEXT( "/SM_" ) + FPackageName::GetShortName( strPackageName );
                    break;

            }

            if ( !bResult )
            {
                continue;
            }
        }

        UStaticMesh* pStaticMesh = Cast<UStaticMesh>( StaticLoadObject( UStaticMesh::StaticClass(), nullptr, *( strPackageName ) ) );

        if ( !pStaticMesh )
        {
            continue;
        }
        kStaticMeshList.Add( pStaticMesh );
    }

    return true;
}

void FRLLiveLinkModule::CreateCamera()
{
    auto pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Camera", "LiveLinkCameraBlueprint", "Camera", true );
    if ( pBlueprint )
    {
        LoadToScene( pBlueprint );
    }
}

void FRLLiveLinkModule::CreateCineCamera()
{
    auto pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Camera", m_strCineCameraBlueprint, "Camera", true );
    if ( pBlueprint )
    {
        SetupCineCamera( pBlueprint );
        LoadToScene( pBlueprint );
    }
}

void FRLLiveLinkModule::CreateDirectionalLight()
{
    auto pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Light", m_strDirLightBlueprint, "Directional_Light", true );
    if ( pBlueprint )
    {
        LoadToScene( pBlueprint );
    }
}

void FRLLiveLinkModule::CreateSpotLight()
{
    auto pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Light", m_strSpotLightBlueprint, "Spotlight", true );
    if ( pBlueprint )
    {
        LoadToScene( pBlueprint );
    }
}

void FRLLiveLinkModule::CreatePointLight()
{
    auto pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Light", m_strPointLightBlueprint, "Point_Light", true );
    if ( pBlueprint )
    {
        LoadToScene( pBlueprint );
    }
}

void FRLLiveLinkModule::CreateRectLight()
{
    auto pBlueprint = CreateLiveLinkBlueprint( "/RLContent/Light", m_strRectLightBlueprint, "Rectlight", true );
    if ( pBlueprint )
    {
        LoadToScene( pBlueprint );
    }
}

void FRLLiveLinkModule::SetUpAllCameraToBlueprint()
{
    if ( !CheckPluginInstalled( PLUGIN_NAME ) )
    {
        FMessageDialog::Open( EAppMsgType::Ok, FText::FromString( INSTALL_PLUGIN_MESSAGE ) );
        return;
    }

    TArray<AActor*> kCineCameraActorList = GetSelectedActorByType( "CineCameraActor" );
    if ( kCineCameraActorList.Num() <= 0 )
    {
        FText strMsg = FText::FromString( "Make sure to select the correct object type\n\r- Please select a camera" );
        FMessageDialog::Open( EAppMsgType::Ok, strMsg );
    }
    else
    {
        for ( AActor* pActor : kCineCameraActorList )
        {
            CreateLiveLinkBlueprintFromActor( pActor, "/RLContent/Camera", m_strCineCameraBlueprint, "Camera" );
        }
    }
}

void FRLLiveLinkModule::SetUpAllLightToBlueprint()
{
    if ( !CheckPluginInstalled( PLUGIN_NAME ) )
    {
        FMessageDialog::Open( EAppMsgType::Ok, FText::FromString( INSTALL_PLUGIN_MESSAGE ) );
        return;
    }
    TArray<AActor*> kDirectionalLightActorList = GetSelectedActorByType( "DirectionalLight" );
    TArray<AActor*> kPointLightActorList = GetSelectedActorByType( "PointLight" );
    TArray<AActor*> kSpotLightActorList = GetSelectedActorByType( "SpotLight" );
    TArray<AActor*> kRectLightActorList = GetSelectedActorByType( "RectLight" );
    if ( kDirectionalLightActorList.Num() <= 0
         && kPointLightActorList.Num() <= 0
         && kSpotLightActorList.Num() <= 0
         && kRectLightActorList.Num() <= 0 )
    {
        FText strMsg = FText::FromString( "Make sure to select the correct object type\n\r- Please select a light" );
        FMessageDialog::Open( EAppMsgType::Ok, strMsg );
    }
    else
    {
        for ( AActor* pActor : kDirectionalLightActorList )
        {
            CreateLiveLinkBlueprintFromActor( pActor, "/RLContent/Light", m_strDirLightBlueprint, "Directional_Light" );
        }
        for ( AActor* pActor : kPointLightActorList )
        {
            CreateLiveLinkBlueprintFromActor( pActor, "/RLContent/Light", m_strPointLightBlueprint, "Point_Light" );
        }
        for ( AActor* pActor : kSpotLightActorList )
        {
            CreateLiveLinkBlueprintFromActor( pActor, "/RLContent/Light", m_strSpotLightBlueprint, "Spotlight" );
        }
        for ( AActor* pActor : kRectLightActorList )
        {
            CreateLiveLinkBlueprintFromActor( pActor, "/RLContent/Light", m_strRectLightBlueprint, "Rectlight" );
        }
    }
}

void FRLLiveLinkModule::SetUpAllCharacterToBlueprint()
{
    if ( !CheckPluginInstalled( PLUGIN_NAME ) )
    {
        FMessageDialog::Open( EAppMsgType::Ok, FText::FromString( INSTALL_PLUGIN_MESSAGE ) );
        return;
    }

    TArray<AActor*> kSkeletalActorList = GetSelectedActorByType( "SkeletalMeshActor" );

    if ( kSkeletalActorList.Num() <= 0 )
    {
        FText strMsg = FText::FromString( "Make sure to select the correct object type\n\r- Please select a 'Skeletal Mesh'" );
        FMessageDialog::Open( EAppMsgType::Ok, strMsg );
    }
    else
    {
        for ( AActor* pActor : kSkeletalActorList )
        {
            //Save Actor parent First
            AActor* pParentActor = pActor->GetAttachParentActor();

            //Check skeleton invalid
            USkeletalMeshComponent* pSkeletalMeshComponent = pActor->FindComponentByClass<USkeletalMeshComponent>();
            if ( !pSkeletalMeshComponent )
            {
                return;
            }
            USkeletalMesh* pSkeletalMesh = pSkeletalMeshComponent->SkeletalMesh;
            if ( !pSkeletalMesh )
            {
                return;
            }
            if ( !pSkeletalMesh->Skeleton ) //Error Get Skeleton
            {
                FText strMsg = FText::FromString( "Error To Get Skeleton \n\rPlease make sure the mesh has vaild skeleton" );
                FMessageDialog::Open( EAppMsgType::Ok, strMsg );
                return;
            }

            //Get Character Assset Path
            FString strActorPath;
            TArray<FString> kSpiltWord;
            pActor->GetDetailedInfo().ParseIntoArray( kSpiltWord, TEXT( "/" ), true );
            for ( int i = 0; i < kSpiltWord.Num() - 1; ++i )
            {
                strActorPath += "/" + kSpiltWord[ i ];
            }
            strActorPath = strActorPath.Replace( TEXT( "/Game" ), TEXT( "" ) );

            //Make Character Anim Blueprint
            IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
            FString strPluginPath = IPluginManager::Get().FindPlugin( TEXT( "RLLiveLink" ) )->GetBaseDir();
            FString strSourceFilePath = strPluginPath + "/Content/" + m_strCharacterBlueprint + ".rluasset";
            FString strTargetPath = FPaths::ProjectContentDir() + strActorPath + "/" + m_strCharacterBlueprint + ".uasset";
            bool bRet = kPlatformFile.CopyFile( *strTargetPath, *strSourceFilePath );
            if ( !bRet )
            {
                return;
            }

            //Set Anim Blueprint Data
            FString strAnimBlueprintPath = "/Game" + strActorPath + "/" + m_strCharacterBlueprint + "." + m_strCharacterBlueprint;
            UAnimBlueprint* pAnimBlueprint = Cast<UAnimBlueprint>( StaticLoadObject( UAnimBlueprint::StaticClass(), NULL, *( strAnimBlueprintPath ), NULL, LOAD_DisableDependencyPreloading | LOAD_DisableCompileOnLoad ) );
            if ( !pAnimBlueprint )
            {
                return;
            }

            FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pAnimBlueprint );
            FAssetRegistryModule::AssetCreated( pAnimBlueprint );
            pAnimBlueprint->MarkPackageDirty();

            //Get Skeleton
            pAnimBlueprint->TargetSkeleton = pSkeletalMesh->Skeleton;
            pAnimBlueprint->SetPreviewMesh( pSkeletalMesh, true );
            auto pMesh = pAnimBlueprint->GetPreviewMesh();
            pAnimBlueprint->Modify( true );

            //Compile
            TWeakObjectPtr<UAnimBlueprint> pWeekAnimBlueprint = pAnimBlueprint;
            TArray<TWeakObjectPtr<UObject>> kAssetsToRetarget;
            kAssetsToRetarget.Add( pWeekAnimBlueprint );
            EditorAnimUtils::RetargetAnimations( pAnimBlueprint->TargetSkeleton, pSkeletalMesh->Skeleton, kAssetsToRetarget, false, NULL, false );

            FKismetEditorUtilities::CompileBlueprint( pAnimBlueprint );
            UPackage* const pAssetPackage = pAnimBlueprint->GetOutermost();
            pAssetPackage->SetDirtyFlag( true );

            //Save Anim Blueprint
            TArray<UPackage*> kPackagesToSave;
            kPackagesToSave.Add( pAssetPackage );
            FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );

            //Set Anim Blueprint to Blueprint
            pSkeletalMeshComponent->SetAnimInstanceClass( pAnimBlueprint->GeneratedClass );
            UBlueprint* pCharacterBlueprint = CreateLiveLinkBlueprintFromActor( pActor,
                                                                                strActorPath,
                                                                                "CCLiveLink_Blueprint",
                                                                                pActor->GetActorLabel(),
                                                                                "LiveLinkCode_Character" );
            if ( !pCharacterBlueprint )
            {
                return;
            }

            //Save Blueprint
            UPackage* const pBPAssetPackage = pCharacterBlueprint->GetOutermost();
            pBPAssetPackage->SetDirtyFlag( true );
            TArray<UPackage*> kBPPackagesToSave;
            kBPPackagesToSave.Add( pBPAssetPackage );
            FEditorFileUtils::PromptForCheckoutAndSave( kBPPackagesToSave, false, /*bPromptToSave=*/ false );

            //Reparent Actor
            if ( pParentActor )
            {
                UWorld* const pWorld = GEditor->GetEditorWorldContext().World();
                for ( TActorIterator<AActor> kActorItr( pWorld, pCharacterBlueprint->GeneratedClass.Get() ); kActorItr; ++kActorItr )
                {
                    kActorItr->AttachToActor( pParentActor, FAttachmentTransformRules::KeepWorldTransform );
                    //Set Default parent
                    SetDefaultParentActor( *kActorItr, FAttachmentTransformRules::KeepWorldTransform );
                }
            }
        }
    }
}

bool FRLLiveLinkModule::SetupCineCamera( UBlueprint* pCameraBlueprint )
{
    AActor* pCameraActor = Cast<AActor>( pCameraBlueprint->GeneratedClass->ClassDefaultObject );
    if ( pCameraActor )
    {
        UCineCameraComponent* pCineCameraComponent = pCameraActor->FindComponentByClass<UCineCameraComponent>();
        if ( pCineCameraComponent )
        {
            pCineCameraComponent->PostProcessSettings.bOverride_AutoExposureMethod = true;
            pCineCameraComponent->PostProcessSettings.AutoExposureMethod = EAutoExposureMethod::AEM_Manual;
            pCineCameraComponent->PostProcessSettings.bOverride_AutoExposureBias = true;
            pCineCameraComponent->PostProcessSettings.AutoExposureBias = 0.f;
            pCineCameraComponent->PostProcessSettings.bOverride_AutoExposureApplyPhysicalCameraExposure = true;
            pCineCameraComponent->PostProcessSettings.AutoExposureApplyPhysicalCameraExposure = 0;
            FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pCameraBlueprint );
            FKismetEditorUtilities::CompileBlueprint( pCameraBlueprint );
            UPackage* const pAssetPackage = pCameraBlueprint->GetOutermost();
            pAssetPackage->SetDirtyFlag( true );
            TArray<UPackage*> kPackagesToSave;
            kPackagesToSave.Add( pAssetPackage );
            FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
            return true;
        }
    }
    return false;
}

//Get All Selected Actor
TArray<AActor*> FRLLiveLinkModule::GetSelectedActorByType( const FString& strType )
{
    TArray<AActor*> kActors;
    for ( FSelectionIterator kIter( *GEditor->GetSelectedActors() ); kIter; ++kIter )
    {
        if ( *kIter->GetClass()->GetName() == strType )
        {
            AActor* pSelectedActor = Cast<AActor>( *kIter );
            if ( pSelectedActor )
            {
                kActors.Add( pSelectedActor );
            }
        }
    }
    return kActors;
}

//Add LiveLink Blueprint-----------------------------------------------------------------------------
UBlueprint* FRLLiveLinkModule::CreateLiveLinkBlueprintFromActor( AActor* pActor,
                                                                 const FString& strPath,
                                                                 const FString& strSource,
                                                                 const FString& strSubjectName,
                                                                 const FString& strDataText )
{
    if ( !pActor )
    {
        return nullptr;
    }
    if ( !CheckPluginInstalled( PLUGIN_NAME ) )
    {
        FMessageDialog::Open( EAppMsgType::Ok, FText::FromString( INSTALL_PLUGIN_MESSAGE ) );
        return nullptr;
    }

    //Check Duplicate and add SerialNumber
    FString strOrginActorTargetName = pActor->GetFName().ToString();
    FString strTargetName = strOrginActorTargetName;
    FString strNamePath = FPaths::ProjectContentDir() + strPath + "/" + strTargetName + ".uasset";
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if ( kPlatformFile.FileExists( *strNamePath ) )
    {
        int nAssetsIndex = 0;
        while ( true )
        {
            strTargetName = strOrginActorTargetName + "_" + FString::FromInt( nAssetsIndex );
            strNamePath = FPaths::ProjectContentDir() + strPath + "/" + strTargetName + ".uasset";
            if ( !kPlatformFile.FileExists( *strNamePath ) )
            {
                break;
            }
            ++nAssetsIndex;
        }
    }

    //Get Default LiveLink
    UBlueprint* pBlueprintDefault = CreateLiveLinkBlueprint( strPath, strSource, strSubjectName, true );
    if ( !pBlueprintDefault )
    {
        return nullptr;
    }

    //Save Actor parent and Name First
    AActor* pParentActor = pActor->GetAttachParentActor();
    const FString strOriginName = pActor->GetActorLabel();

    //New Blueprint fome actor
#if ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 3
    FKismetEditorUtilities::FCreateBlueprintFromActorParams kParams;
    UBlueprint* pBlueprintActor = FKismetEditorUtilities::CreateBlueprintFromActor( "/Game" + strPath + "/" + strTargetName, pActor, kParams );
#else
    UBlueprint* pBlueprintActor = FKismetEditorUtilities::CreateBlueprintFromActor( "/Game" + strPath + "/" + strTargetName, pActor, true );
#endif
    if ( !pBlueprintActor )
    {
        return nullptr;
    }
    FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pBlueprintActor );
    pBlueprintActor->MarkPackageDirty();

    //Get Default LiveLink and Set
    UBlueprintGeneratedClass* pBPGC = Cast<UBlueprintGeneratedClass>( pBlueprintDefault->GeneratedClass.Get() );
    if ( pBPGC && pBPGC->SimpleConstructionScript )
    {
        for ( USCS_Node* pNode : pBPGC->SimpleConstructionScript->GetAllNodes() )
        {
            if ( pNode->GetVariableName().ToString() == "LiveLink" )
            {
                //Clone Component and setup
                UBlueprintGeneratedClass* pBPGCTarget = Cast<UBlueprintGeneratedClass>( pBlueprintActor->GeneratedClass.Get() );
                USimpleConstructionScript* pSCS = pBPGCTarget->SimpleConstructionScript;
                USCS_Node* pNewNode = pSCS->CreateNode( pNode->ComponentClass );
                pBPGCTarget->SimpleConstructionScript->AddNode( pNewNode );
                break;
            }
        }
    }

    //Get SubjectName variable and Set
    for ( FBPVariableDescription& pVar : pBlueprintDefault->NewVariables )
    {
        if ( pVar.VarName == "SubjectName" )
        {
            pVar.DefaultValue = strSubjectName;
            FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pBlueprintDefault );

            //Add variables
            pBlueprintActor->NewVariables.Insert( pVar, 0 );
        }
    }

    //Get Default Morph and Set
    UEdGraph* pUCSGraph = nullptr;
    TArray< UEdGraph* > kMacroGraphs = pBlueprintDefault->MacroGraphs;
    for ( TArray<UEdGraph*>::TIterator pGraphIt( kMacroGraphs ); pGraphIt; ++pGraphIt )
    {
        UEdGraph* pGraph = *pGraphIt;
        if ( pGraph->GetFName().ToString() == "RLLiveLink" )
        {
            pUCSGraph = pGraph;
        }
    }
    UEdGraph* pClonedGraph = FEdGraphUtilities::CloneGraph( pUCSGraph, pBlueprintActor );
    pClonedGraph->Rename( TEXT( "RLLiveLink" ) );
    pBlueprintActor->MacroGraphs.Add( pClonedGraph );

    //Get Graph Text
    FString strTextToImport;
    FString strSourceFilePathText = IPluginManager::Get().FindPlugin( TEXT( "RLLiveLink" ) )->GetBaseDir() + "/Content/" + strDataText + ".txt";
    FFileHelper::LoadFileToString( strTextToImport, *strSourceFilePathText );

    //Edit Text for current name
    strTextToImport = strTextToImport.Replace( TEXT( "LiveLinkANName" ), *m_strCharacterBlueprint ); //set anim_blueprint
    strTextToImport = strTextToImport.Replace( TEXT( "LiveLinkBPName" ), *strTargetName );
    strTextToImport = strTextToImport.Replace( TEXT( "/ObjectPath" ), *strPath );

    //Set Graph from Text
    UEdGraph* pGraph = pBlueprintActor->UbergraphPages[ 0 ];
    check( pGraph );
    TSet<UEdGraphNode*> kPastedNodes;
    FEdGraphUtilities::ImportNodesFromText( pGraph, strTextToImport, kPastedNodes );

    //Compile
    FKismetEditorUtilities::CompileBlueprint( pBlueprintActor );
    GEngine->BroadcastLevelActorListChanged();

    //Remove default clone asset
    FAssetRegistryModule::AssetDeleted( pBlueprintDefault );

    //Delete default clone
    TArray<UObject*> kAssetObjectsInPath;
    kAssetObjectsInPath.Add( pBlueprintDefault );
    ObjectTools::AddExtraObjectsToDelete( kAssetObjectsInPath );
    ObjectTools::ForceDeleteObjects( kAssetObjectsInPath, false );

    //Reparent Actor
    if ( pBlueprintActor )
    {
        UWorld* const pWorld = GEditor->GetEditorWorldContext().World();
        for ( TActorIterator<AActor> kActorItr( pWorld, pBlueprintActor->GeneratedClass.Get() ); kActorItr; ++kActorItr )
        {
            AActor* pBPActor = *kActorItr;
            if ( pParentActor )
            {
                //Set parent back after replace
                pBPActor->AttachToActor( pParentActor, FAttachmentTransformRules::KeepWorldTransform );
            }
            //Set Default parent and Rename to origin actor name
            SetDefaultParentActor( pBPActor, FAttachmentTransformRules::KeepWorldTransform );
            pBPActor->SetActorLabel( strOriginName );
        }
    }

    //Save Blueprint
    UPackage* const pAssetPackage = pBlueprintActor->GetOutermost();
    pAssetPackage->SetDirtyFlag( true );
    FAssetRegistryModule::AssetCreated( pBlueprintActor );

    TArray<UPackage*> kPackagesToSave;
    kPackagesToSave.Add( pAssetPackage );
    FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, false );

    return pBlueprintActor;
}

//Create LiveLink Blueprint--------------------------------------------------------------------------
UBlueprint* FRLLiveLinkModule::CreateLiveLinkBlueprint( const FString& strPath,
                                                        const FString& strSource,
                                                        const FString& strSubjectName,
                                                        bool bCheckSerialNumber )
{
    if ( !CheckPluginInstalled( PLUGIN_NAME ) )
    {
        FMessageDialog::Open( EAppMsgType::Ok, FText::FromString( INSTALL_PLUGIN_MESSAGE ) );
        return nullptr;
    }

    //New Folder Path
    FString strFolderPath = FPaths::ProjectContentDir() + strPath;
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if ( !kPlatformFile.DirectoryExists( *strFolderPath ) )
    {
        if ( !kPlatformFile.CreateDirectoryTree( *strFolderPath ) )
        {
            return nullptr;
        }
    }

    //Check Asset Name
    FString strTargetName;
    if ( bCheckSerialNumber )
    {
        int nAssetsIndex = 0;
        while ( true )
        {
            strTargetName = strSubjectName + "_" + FString::FromInt( nAssetsIndex );
            FString strNamePath = FPaths::ProjectContentDir() + strPath + "/" + strTargetName + ".uasset";
            if ( !kPlatformFile.FileExists( *strNamePath ) )
            {
                break;
            }
            ++nAssetsIndex;
        }
    }
    else
    {
        strTargetName = strSubjectName;
    }

    //Check if blueprint exist need to delete file
    TArray< CSceneTempData > kAssetTempData;
    FString strBlueprintFilePath = FPaths::ProjectContentDir() + strPath + "/" + strTargetName + ".uasset";
    if ( kPlatformFile.FileExists( *strBlueprintFilePath ) )
    {
        FString strBlueprintLoadPath = "/Game" + strPath + "/" + strTargetName + "." + strTargetName;
        UBlueprint* pBlueprint = Cast<UBlueprint>( StaticLoadObject( UBlueprint::StaticClass(), nullptr, *( strBlueprintLoadPath ) ) );
        if ( !pBlueprint )
        {
            return nullptr;
        }

        //Remove default clone asset
        FAssetRegistryModule::AssetDeleted( pBlueprint );

        UObject* pAssetObject = Cast<UObject>( pBlueprint );
        TArray< UObject* > kBlueprints;
        kBlueprints.Add( pAssetObject );

        ObjectTools::AddExtraObjectsToDelete( kBlueprints );
        ObjectTools::ForceDeleteObjects( kBlueprints, false );
    }

    //Clone Blueprint
    FString strPluginPath = IPluginManager::Get().FindPlugin( TEXT( "RLLiveLink" ) )->GetBaseDir();
    FString strSourceFilePath = strPluginPath + "/Content/" + strSource + ".rluasset";
    FString strTargetPath = FPaths::ProjectContentDir() + strPath + "/" + strTargetName + ".uasset";
    kPlatformFile.CopyFile( *strTargetPath, *strSourceFilePath );

    //Get Current Blueprint
    FString strBlueprintPathToLoad = "/Game" + strPath + "/" + strTargetName + "." + strSource;
    UBlueprint* pBlueprint = Cast<UBlueprint>( StaticLoadObject( UBlueprint::StaticClass(), nullptr, *( strBlueprintPathToLoad ) ) );
    if ( !pBlueprint )
    {
        return nullptr;
    }

    //Rename Asset
    FAssetToolsModule& kAssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>( "AssetTools" );
    TArray<FAssetRenameData> kAssetsAndNames;
    UObject* pAssetObject = Cast<UObject>( pBlueprint );
    const FString strPackagePath = FPackageName::GetLongPackagePath( pAssetObject->GetOutermost()->GetName() );
    new( kAssetsAndNames ) FAssetRenameData();
    kAssetsAndNames[ 0 ].NewName = strTargetName;
    kAssetsAndNames[ 0 ].NewPackagePath = strPackagePath;
    kAssetsAndNames[ 0 ].Asset = pAssetObject;
    kAssetToolsModule.Get().RenameAssetsWithDialog( kAssetsAndNames );

    //Set Subject Name
    for ( FBPVariableDescription& pVar : pBlueprint->NewVariables )
    {
        if ( pVar.VarName == "SubjectName" )
        {
            pVar.DefaultValue = strSubjectName;
            FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pBlueprint );
        }
    }

    FKismetEditorUtilities::CompileBlueprint( pBlueprint );
    UPackage* const pAssetPackage = pBlueprint->GetOutermost();
    pAssetPackage->SetDirtyFlag( true );
    FAssetRegistryModule::AssetCreated( pBlueprint );

    //Save
    TArray<UPackage*> kPackagesToSave;
    kPackagesToSave.Add( pAssetPackage );
    FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
    return pBlueprint;
}

void FRLLiveLinkModule::SetDefaultParentActor( AActor* pActor, FAttachmentTransformRules eAttachmentRules )
{
    UWorld* const pWorld = GEditor->GetEditorWorldContext().World();
    for ( TActorIterator<AActor> ActorItr( pWorld ); ActorItr; ++ActorItr )
    {
        if ( ActorItr->GetActorLabel().ToLower() == DEFAULT_PARENT_ACTOR && ActorItr->GetClass() == AActor::StaticClass() )
        {
            pActor->AttachToActor( *ActorItr, eAttachmentRules );
            break;
        }
    }
}

bool FRLLiveLinkModule::CheckPluginInstalled( const FString& strPluginName )
{
    auto kPlugin = IPluginManager::Get().FindPlugin( strPluginName );
    return ( !kPlugin ) ? false : ( kPlugin->IsEnabled() ) ? true : false;
}

void FRLLiveLinkModule::SelectAndFocusActor( AActor* pActor, bool bFocus, bool bSelect )
{
    if ( pActor )
    {
        //focus view
        if ( bFocus )
        {
            TArray<AActor*> kActors;
            kActors.Add( pActor );
            GEditor->MoveViewportCamerasToActor( kActors, true );
        }

        //Select newly created actor
        if ( bSelect )
        {
            GEditor->SelectNone( false, true, false );
            GEditor->SelectActor( pActor, true, false );
            GEditor->NoteSelectionChange();
        }
    }
}

void FRLLiveLinkModule::MoveMotionAssetPath( const TSharedPtr<FJsonValue>& spJsonValue, bool bIsProp )
{
    if ( spJsonValue )
    {
        auto spBuildArray = spJsonValue->AsArray();
        for ( auto& spAssetJsonValue : spBuildArray )
        {
            if ( auto spAssetObject = spAssetJsonValue->AsObject() )
            {
                auto kAssetMap = spAssetObject->Values;
                FString strAssetName = kAssetMap[ "Name" ]->AsString();
                FString strAssetPath = kAssetMap[ "Path" ]->AsString();
                if ( !strAssetName.IsEmpty() )
                {
                    if ( bIsProp )
                    {
                        ProcessPropMotionNameAndPath( strAssetPath, strAssetName );
                        ReAssignMotionSkeleton( strAssetPath );
                    }
                    else
                    {
                        ProcessAvatarMotionNameAndPath( strAssetPath, strAssetName );
                        ReAssignMotionSkeleton( strAssetPath );
                    }
                }
            }
        }
    }
}

void FRLLiveLinkModule::ProcessAvatarMotionNameAndPath( const FString& strAssetPath, const FString& strAssetName )
{
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    FAssetRegistryModule& kAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>( TEXT( "AssetRegistry" ) );
    FAssetToolsModule& kAssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>( "AssetTools" );

    FString strMotionFolderPath = strAssetPath + "Motion";
    FPackageName::TryConvertLongPackageNameToFilename( strMotionFolderPath + "/", strMotionFolderPath );
    if ( kPlatformFile.CreateDirectory( *strMotionFolderPath ) )
    {
        //取放在motion folder外的anim sequence
        TArray<FAssetData> kObjectList;

        FARFilter kFilter;
        kFilter.PackagePaths.Add( *strAssetPath );
        kFilter.bRecursivePaths = false;
        kFilter.ClassPaths.Add( UAnimSequence::StaticClass()->GetClassPathName() );

        kAssetRegistryModule.Get().GetAssets( kFilter, kObjectList );

        if ( kPlatformFile.FileExists( *( strMotionFolderPath + strAssetName + "_0_Open_A_UE4.uasset" ) ) )
        {
            kPlatformFile.DeleteFile( *( strMotionFolderPath + strAssetName + "_0_Open_A_UE4.uasset" ) );

            TArray<FAssetData> kDeleteObjectList;
            kAssetRegistryModule.Get().GetAssetsByPackageName( FName( *( strAssetPath + "Motion/" + strAssetName + "_0_Open_A_UE4" ) ), kDeleteObjectList );
            DeleteAssets( kDeleteObjectList );
        }
        else if ( kPlatformFile.FileExists( *( strMotionFolderPath + strAssetName + "_Anim.uasset" ) ) )
        {
            kPlatformFile.DeleteFile( *( strMotionFolderPath + strAssetName + "_Anim.uasset" ) );

            TArray<FAssetData> kDeleteObjectList;
            kAssetRegistryModule.Get().GetAssetsByPackageName( FName( *( strAssetPath + "Motion/" + strAssetName + "_Anim" ) ), kDeleteObjectList );
            DeleteAssets( kDeleteObjectList );
        }
        if ( kObjectList.Num() <= 0 )
        {
            return;
        }
        /*
        * 用在會有兩段motion一起進來要修正名字的情況
        */
        /*if ( kObjectList.Num() > 1 )
        {

            for ( auto& kObject : kObjectList )
            {
                FString strNewFileName = kObject.AssetName.ToString().Replace( *( strAssetName + "_Anim" ), *strAssetName );

                TArray<FAssetRenameData> kAssetsAndNames;
                UObject* pAssetObject = kObject.GetAsset();

                new( kAssetsAndNames ) FAssetRenameData();
                kAssetsAndNames[ 0 ].NewName = strNewFileName;
                kAssetsAndNames[ 0 ].NewPackagePath = strAssetPath + "Motion";
                kAssetsAndNames[ 0 ].Asset = pAssetObject;
                kAssetToolsModule.Get().RenameAssets( kAssetsAndNames );

                FString strNewFilePath = strAssetPath + "Motion/" + strNewFileName;
                FString strPath = kObject.PackageName.ToString();
                MoveAsset( strPath, strNewFilePath );

            }
        }
        else
        {
            FString strNewFileName = kObjectList[ 0 ].AssetName.ToString().Replace( *( strAssetName + "_Anim" ), *( strAssetName + "_0_Open_A_UE4" ) );

            TArray<FAssetRenameData> kAssetsAndNames;
            UObject* pAssetObject = kObjectList[ 0 ].GetAsset();
            new( kAssetsAndNames ) FAssetRenameData();
            kAssetsAndNames[ 0 ].NewName = strNewFileName;
            kAssetsAndNames[ 0 ].NewPackagePath = strAssetPath + "Motion";
            kAssetsAndNames[ 0 ].Asset = pAssetObject;
            kAssetToolsModule.Get().RenameAssets( kAssetsAndNames );

            FString strNewFilePath = strAssetPath + "Motion/" + strNewFileName;
            FString strPath = kObjectList[ 0 ].PackageName.ToString();
            MoveAsset( strPath, strNewFilePath );
        }*/
        for ( const auto& kObject : kObjectList )
        {
            FString strNewFilePath = strAssetPath + "Motion/" + kObject.AssetName.ToString();
            FString strPath = kObject.PackageName.ToString();
            MoveAsset( strPath, strNewFilePath );
        }
    }

}
void FRLLiveLinkModule::ProcessPropMotionNameAndPath( const FString& strAssetPath, const FString& strAssetName )
{
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    FAssetRegistryModule& kAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>( TEXT( "AssetRegistry" ) );
    FAssetToolsModule& kAssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>( "AssetTools" );

    FString strMotionFolderPath = strAssetPath + "/Motion";
    FPackageName::TryConvertLongPackageNameToFilename( strMotionFolderPath + "/", strMotionFolderPath );

    if ( kPlatformFile.CreateDirectory( *strMotionFolderPath ) )
    {
        //取放在motion folder外的anim sequence
        TArray<FAssetData> kObjectList;

        FARFilter kFilter;
        kFilter.PackagePaths.Add( *strAssetPath );
        kFilter.bRecursivePaths = false;
        kFilter.ClassPaths.Add( UAnimSequence::StaticClass()->GetClassPathName() );

        kAssetRegistryModule.Get().GetAssets( kFilter, kObjectList );

        for ( const auto& kObject : kObjectList )
        {
            /*FDateTime kNow = FDateTime::Now();
            FString strNewFileName = FString::Printf( TEXT( "%s_%d_%d_%d_%d_%d_%d" ),
                                                      *strAssetName, kNow.GetYear(), kNow.GetMonth(), kNow.GetDay(), kNow.GetHour(), kNow.GetMinute(), kNow.GetSecond() );

            TArray<FAssetRenameData> kAssetsAndNames;
            UObject* pAssetObject = kObjectList[ 0 ].GetAsset();
            new( kAssetsAndNames ) FAssetRenameData();
            kAssetsAndNames[ 0 ].NewName = strNewFileName;
            kAssetsAndNames[ 0 ].NewPackagePath = strAssetPath + "Motion";
            kAssetsAndNames[ 0 ].Asset = pAssetObject;
            kAssetToolsModule.Get().RenameAssets( kAssetsAndNames );*/

            FString strNewFilePath = strAssetPath + "/Motion/" + kObject.AssetName.ToString();
            FString strPath = kObject.PackageName.ToString();
            MoveAsset( strPath, strNewFilePath );
        }
    }

}
void FRLLiveLinkModule::MoveAsset( const FString& strFromAssetPath, const FString& strToAssetPath )
{
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();

    FString strCurrentFilePath = "";
    FPackageName::TryConvertLongPackageNameToFilename( strFromAssetPath, strCurrentFilePath );//current
    strCurrentFilePath = strCurrentFilePath + ".uasset";

    FString strTargetFilePath = "";
    FPackageName::TryConvertLongPackageNameToFilename( strToAssetPath, strTargetFilePath );//current
    strTargetFilePath = strTargetFilePath + ".uasset";

    kPlatformFile.MoveFile( *strTargetFilePath, *strCurrentFilePath );
}
void FRLLiveLinkModule::ReAssignMotionSkeleton( const FString& strCurrentPath )
{
    FAssetRegistryModule& kAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>( TEXT( "AssetRegistry" ) );

    TArray<FAssetData> kAnimObjectList;
    TArray<FAssetData> kSkeletonObjectList;

    FARFilter kAnimFilter;
    kAnimFilter.PackagePaths.Add( *strCurrentPath );
    kAnimFilter.bRecursivePaths = true;
    kAnimFilter.ClassPaths.Add( UAnimSequence::StaticClass()->GetClassPathName() );

    kAssetRegistryModule.Get().GetAssets( kAnimFilter, kAnimObjectList );

    FARFilter kSkeletonFilter;
    kSkeletonFilter.PackagePaths.Add( *strCurrentPath );
    kSkeletonFilter.bRecursivePaths = true;
    kSkeletonFilter.ClassPaths.Add( USkeleton::StaticClass()->GetClassPathName() );

    kAssetRegistryModule.Get().GetAssets( kSkeletonFilter, kSkeletonObjectList );

    if ( !kSkeletonObjectList.Num() )
    {
        return;
    }

    for ( auto kAnimObject : kAnimObjectList )
    {
        if ( UAnimationAsset* pAnimAsset = Cast<UAnimationAsset>( ( kAnimObject.GetAsset() ) ) )
        {
            if ( USkeleton* pSkeletonAsset = pAnimAsset->GetSkeleton() )
            {
                continue;
            }
#if ENGINE_MAJOR_VERSION <= 4
            TArray<UObject*> kAssetsToRetarget;
#else
            TArray<TObjectPtr<UObject>> kAssetsToRetarget;
#endif
            kAssetsToRetarget.Add( pAnimAsset );
            ReplaceMissingSkeleton( kAssetsToRetarget, kSkeletonObjectList[ 0 ].GetAsset() );
        }
    }
}
//修改自FReply SReplaceMissingSkeletonDialog::OnButtonClick(EAppReturnType::Type ButtonID)
#if ENGINE_MAJOR_VERSION <= 4
void FRLLiveLinkModule::ReplaceMissingSkeleton( const TArray<UObject*>& kAnimAssetsToRetarget, UObject* kSkeletonAsset ) const
#else
void FRLLiveLinkModule::ReplaceMissingSkeleton( const TArray<TObjectPtr<UObject>>& kAnimAssetsToRetarget, const TObjectPtr<UObject>& kSkeletonAsset ) const
#endif
{
    // record anim assets that need skeleton replaced
    TArray<TWeakObjectPtr<UObject>> kAnimsToFix;

    for ( auto kAnimObject : kAnimAssetsToRetarget )
    {
        kAnimsToFix.Add( CastChecked< UObject >( kAnimObject ) );
    }
#if ENGINE_MAJOR_VERSION <= 4
    if ( USkeleton* kReplacementSkeleton = Cast<USkeleton>( kSkeletonAsset ) )
#else
    if ( const TObjectPtr<USkeleton> kReplacementSkeleton = CastChecked<USkeleton>( kSkeletonAsset ) )
#endif
    {
        constexpr bool bRetargetReferredAssets = true;
        constexpr bool bConvertSpaces = false;
        FAnimationRetargetContext kRetargetContext( kAnimsToFix, bRetargetReferredAssets, bConvertSpaces );
        // since we are replacing a missing skeleton, we don't want to duplicate the asset
        // setting this to null prevents assets from being duplicated
        const FNameDuplicationRule* pNameRule = nullptr;

        EditorAnimUtils::RetargetAnimations( nullptr, kReplacementSkeleton, kRetargetContext, bRetargetReferredAssets, pNameRule );
    }
}

void FRLLiveLinkModule::GetObjectsFromPackage( const FARFilter& kFilter, TArray<FAssetData>& kObjectList, const FARFilter& kIgnoreObjectFilter )
{
    FAssetRegistryModule& kAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>( TEXT( "AssetRegistry" ) );

    kAssetRegistryModule.Get().GetAssets( kFilter, kObjectList );

    if ( !kIgnoreObjectFilter.IsEmpty() )
    {
        TArray<FAssetData> kIgnoreObjectList;
        kAssetRegistryModule.Get().GetAssets( kIgnoreObjectFilter, kIgnoreObjectList );

        if ( kObjectList.Num() > 0 && kIgnoreObjectList.Num() > 0 )
        {
            for ( auto kIgnoreObject : kIgnoreObjectList )
            {
                kObjectList.Remove( kIgnoreObject );
            }
        }
    }
}

bool FRLLiveLinkModule::DeleteAssets( const TArray<FAssetData>& kObjectList )
{
    if ( kObjectList.Num() <= 0 )
    {
        return false;
    }
    UWorld* const pWorld = GEditor->GetEditorWorldContext().World();
    TArray<UObject*> kAssetsToDelete;
    for ( auto kObject : kObjectList )
    {
        UObject* pAsset = kObject.GetAsset();
        if ( pAsset )
        {
            kAssetsToDelete.Add( pAsset );
            //Save Avatar On Scene To Temp Data
            UBlueprint* pBlueprintActor = Cast<UBlueprint>( pAsset );
            if ( pBlueprintActor )
            {
                for ( TActorIterator<AActor> pActorItr( pWorld, pBlueprintActor->GeneratedClass.Get() ); pActorItr; ++pActorItr )
                {
                    bool bPilotTarget = false;
                    FLevelEditorViewportClient* pLevelClient = GCurrentLevelEditingViewportClient;
                    if ( AActor* pActiveLockActor = pLevelClient->GetActiveActorLock().Get() )
                    {
                        if ( pActiveLockActor->GetUniqueID() == pActorItr->GetUniqueID() )
                        {
                            bPilotTarget = true;
                        }
                    }
                    // Before deleting an Actor, first check if it's selected Actor. 
                    // If it's the selected state, you must cancel the selection first, otherwise the UE Menu will be disabled forever.
                    if ( GEditor->GetSelectedActorCount() != 0 )
                    {
                        GEditor->SelectNone( false, true, false );
                        GEditor->NoteSelectionChange();
                    }

                    CSceneTempData kData;
                    kData.strAssetName = pActorItr->GetActorLabel();
                    kData.kTransform = pActorItr->GetTransform();
                    kData.pParentActor = pActorItr->GetAttachParentActor();
                    kData.bPilotTarget = bPilotTarget;

                    TArray<FString> kPathStringOut;
                    FString strActorPath = pActorItr->GetClass()->GetPathName();
                    strActorPath.ParseIntoArray( kPathStringOut, TEXT( "/" ), true );
                    kData.strFolderName = kPathStringOut[ kPathStringOut.Num() - 2 ];
                    // ex: strPath = RLConent/FolderName/obj.uasset 須扣除檔案本身名稱來取得Folder name
                    m_kAssetTempData.Add( kData );
                }
            }

            //Remove default clone asset
            FAssetRegistryModule::AssetDeleted( pAsset );
        }
    }
    ObjectTools::AddExtraObjectsToDelete( kAssetsToDelete );

    return kAssetsToDelete.Num() == ObjectTools::ForceDeleteObjects( kAssetsToDelete, false );
}
bool FRLLiveLinkModule::DeleteFolder( const FString& strPath )
{
    FString strFolderPath = strPath.Replace( TEXT( "/Game/" ), TEXT( "" ) );
    FString strTargetPath = FPaths::ProjectContentDir() + strFolderPath;
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if ( kPlatformFile.DirectoryExists( *strTargetPath ) )
    {
        FAssetRegistryModule& kAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>( TEXT( "AssetRegistry" ) );

        TArray<FString> kDeletePathList;
        kDeletePathList.Add( strPath );
        kAssetRegistryModule.Get().GetSubPaths( strPath, kDeletePathList, false );

        TArray<FString> kIgnorePackagePathList;
        kIgnorePackagePathList.Add( strPath + "/Motion" );

        TArray<FAssetData> kObjectList;
        //Get Asset Data
        FARFilter kFilter;
        kFilter.PackagePaths.Add( *strPath );
        kFilter.bRecursivePaths = true;

        FARFilter kIgnoreObjectFilter;
        kIgnoreObjectFilter.PackagePaths.Add( *( strPath + "/Motion" ) );
        kIgnoreObjectFilter.bRecursivePaths = true;

        GetObjectsFromPackage( kFilter, kObjectList, kIgnoreObjectFilter );

        if ( kObjectList.Num() > 0 )
        {
            //參考EditorScriptingUtils.cpp - DeleteEmptyDirectoryFromDisk()
            if ( DeleteAssets( kObjectList ) )
            {
                struct FEmptyFolderVisitor : public IPlatformFile::FDirectoryVisitor
                {
                    bool bIsEmpty;
                    FEmptyFolderVisitor()
                        : bIsEmpty( true )
                    {
                    }
                    virtual bool Visit( const TCHAR* FilenameOrDirectory, bool bIsDirectory ) override
                    {
                        if ( !bIsDirectory )
                        {
                            bIsEmpty = false;
                            return false;
                        }
                        return true;
                    }
                };

                FString strPathToDeleteOnDisk;

                for ( FString strDeletePath : kDeletePathList )
                {
                    if ( FPackageName::TryConvertLongPackageNameToFilename( strDeletePath, strPathToDeleteOnDisk ) )
                    {
                        FEmptyFolderVisitor kEmptyFolderVisitor;
                        IFileManager::Get().IterateDirectoryRecursively( *strPathToDeleteOnDisk, kEmptyFolderVisitor );
                        if ( kEmptyFolderVisitor.bIsEmpty )
                        {
                            if ( IFileManager::Get().DeleteDirectory( *strPathToDeleteOnDisk, false, true ) )
                            {
                                kAssetRegistryModule.Get().RemovePath( strDeletePath );
                            }

                        }
                    }
                }
            }
            return true;
        }
    }
    return false;
}

bool FRLLiveLinkModule::DeletePackageInContentBrowser( const FString& strPath )
{
    FAssetRegistryModule& kAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>( TEXT( "AssetRegistry" ) );

    //Get Asset Data
    TArray<FAssetData> kObjectList;

    FARFilter kFilter;
    kFilter.PackagePaths.Add( *strPath );
    kFilter.bRecursivePaths = true;

    kAssetRegistryModule.Get().GetAssets( kFilter, kObjectList );

    if ( kObjectList.Num() > 0 )
    {
        if ( DeleteAssets( kObjectList ) )
        {
            kAssetRegistryModule.Get().RemovePath( strPath );
        }

        return true;
    }
    return false;
}

bool FRLLiveLinkModule::DeleteActorInScene( const FString& strPath, const FString& strTargetName )
{
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    FString strBlueprintFilePath = FPaths::ProjectContentDir() + strPath + "/" + strTargetName + ".uasset";
    if ( kPlatformFile.FileExists( *strBlueprintFilePath ) )
    {
        FString strBlueprintLoadPath = "/Game" + strPath + "/" + strTargetName + "." + strTargetName;
        UBlueprint* pBlueprint_Temp = Cast<UBlueprint>( StaticLoadObject( UBlueprint::StaticClass(), nullptr, *( strBlueprintLoadPath ) ) );
        if ( !pBlueprint_Temp )
        {
            return false;
        }

        //Save Asset On Scene To Temp Data and Delete
        UWorld* const pWorld = GEditor->GetEditorWorldContext().World();
        for ( TActorIterator<AActor> pActorItr( pWorld, pBlueprint_Temp->GeneratedClass.Get() ); pActorItr; ++pActorItr )
        {
            // Stop Pilot
            bool bPilotTarget = false;
            FLevelEditorViewportClient* pLevelClient = GCurrentLevelEditingViewportClient;
            if ( AActor* pActiveLockActor = pLevelClient->GetActiveActorLock().Get() )
            {
                if ( pActiveLockActor->GetUniqueID() == pActorItr->GetUniqueID() )
                {
                    bPilotTarget = true;
                }
            }
            // Before deleting an Actor, first check if it's selected Actor. 
            // If it's the selected state, you must cancel the selection first, otherwise the UE Menu will be disabled forever.
            if ( GEditor->GetSelectedActorCount() != 0 )
            {
                GEditor->SelectNone( false, true, false );
                GEditor->NoteSelectionChange();
            }

            CSceneTempData kData;
            kData.strAssetName = pActorItr->GetActorLabel();
            kData.kTransform = pActorItr->GetTransform();
            kData.pParentActor = pActorItr->GetAttachParentActor();
            kData.strFolderName = strTargetName;
            kData.bPilotTarget = bPilotTarget;
            m_kAssetTempData.Add( kData );

            pActorItr->K2_DestroyActor();
            GEditor->ForceGarbageCollection( true );//GetEditorWorldContext().World()->ForceGarbageCollection( true );
        }
    }
    return true;
}

AActor* FRLLiveLinkModule::PutAssetBackToSceneAfterReplace( UBlueprint* pBlueprint )
{
    TArray<FString> kPathStringOut;
    FString strPath = pBlueprint->GetPathName();
    strPath.ParseIntoArray( kPathStringOut, TEXT( "/" ), true );
    FString strFolderName = kPathStringOut[ kPathStringOut.Num() - 2 ];
    // ex: strPath = RLConent/FolderName/obj.uasset 須扣除檔案本身名稱來取得Folder name

    //Camera & Light use BP name not folder name
    if ( strFolderName == "Camera" || strFolderName == "Light" )
    {
        strFolderName = pBlueprint->GetName();
    }

    AActor* pActor = nullptr;
    for ( int32 nIndex = 0; nIndex < m_kAssetTempData.Num(); ++nIndex )
    {
        const CSceneTempData& kTempData = m_kAssetTempData[ nIndex ];
        if ( strFolderName == kTempData.strFolderName )
        {
            //Add To Scene
            const FVector kLocation = kTempData.kTransform.GetLocation();
            const FRotator kRotation = kTempData.kTransform.Rotator();
            UClass* pClassToSpawn = Cast<UClass>( pBlueprint->GeneratedClass );
            pActor = FRLLiveLinkUtility::SpawnActorToViewport( pClassToSpawn, "", kLocation, kRotation );
            if ( pActor )
            {
                pActor->SetActorLabel( kTempData.strAssetName );
                if ( kTempData.pParentActor )
                {
                    pActor->AttachToActor( kTempData.pParentActor, FAttachmentTransformRules::KeepWorldTransform );
                }
                SetDefaultParentActor( pActor, FAttachmentTransformRules::KeepWorldTransform );
            }
            if ( kTempData.bPilotTarget )
            {
                FLevelEditorViewportClient* pLevelClient = GCurrentLevelEditingViewportClient;
                if ( pLevelClient && pLevelClient->bLockedCameraView )
                {
                    TSharedPtr<SLevelViewport> spLevelEditorViewport = StaticCastSharedPtr<SLevelViewport>( pLevelClient->GetEditorViewportWidget() );
                    if ( spLevelEditorViewport )
                    {
                        spLevelEditorViewport->OnActorLockToggleFromMenu( pActor );
                    }
                }
            }
            
            m_kAssetTempData.RemoveAt( nIndex );
            nIndex--;
        }
    }
    return pActor;
}

UTexture2D* FRLLiveLinkModule::LoadTextureFromFile( const FString& strPath, const FString& strSaveAssetPath )
{
    UTexture2D* pTexture = nullptr;
    if ( !FPlatformFileManager::Get().GetPlatformFile().FileExists( *strPath ) )
    {
        return nullptr;
    }

    UPackage* pPackage = CreatePackage( *strSaveAssetPath );
    if ( !pPackage )
    {
        return nullptr;
    }
    pPackage->FullyLoad();
    FString strTextureName = FPaths::GetBaseFilename( strSaveAssetPath );
    TArray<uint8> kRawData;
    if ( !FFileHelper::LoadFileToArray( kRawData, *strPath ) )
    {
        return nullptr;
    }
    UTextureFactory* pTexFactory = NewObject<UTextureFactory>();
    if ( !pTexFactory )
    {
        return nullptr;
    }
    kRawData.Add( 0 );
    const uint8* Ptr = &kRawData[ 0 ];
    UObject* pTexAsset = pTexFactory->FactoryCreateBinary( UTexture::StaticClass(),
                                                           pPackage,
                                                           FName( *strTextureName ),
                                                           RF_Public | RF_Standalone,
                                                           NULL,
                                                           *FPaths::GetExtension( strPath ),
                                                           Ptr,
                                                           Ptr + kRawData.Num() - 1,
                                                           GWarn );
    if ( pTexAsset )
    {
        UTexture* kTexture = Cast<UTexture>( pTexAsset );
        pTexAsset->MarkPackageDirty();
        ULevel::LevelDirtiedEvent.Broadcast();
        pTexAsset->PostEditChange();
        FAssetRegistryModule::AssetCreated( pTexAsset );
        pPackage->SetDirtyFlag( true );

        //Save
        TArray<UPackage*> kPackagesToSave;
        kPackagesToSave.Add( pPackage );
        FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );

        //Re load
        pTexture = LoadObject<UTexture2D>( nullptr, *strSaveAssetPath );
    }
    return pTexture;

}

UTextureLightProfile* FRLLiveLinkModule::LoadTextureLightProfileFromFile( const FString& strPath, const FString& strSaveAssetPath )
{
    UTextureLightProfile* pTexture = nullptr;
    if ( !FPlatformFileManager::Get().GetPlatformFile().FileExists( *strPath ) )
    {
        return nullptr;
    }

    UPackage* pPackage = CreatePackage( *strSaveAssetPath );
    if ( !pPackage )
    {
        return nullptr;
    }
    pPackage->FullyLoad();
    FString strTextureName = FPaths::GetBaseFilename( strSaveAssetPath );
    TArray<uint8> kRawData;
    if ( !FFileHelper::LoadFileToArray( kRawData, *strPath ) )
    {
        return nullptr;
    }
    UTextureFactory* pTexFactory = NewObject<UTextureFactory>();
    if ( !pTexFactory )
    {
        return nullptr;
    }
    kRawData.Add( 0 );
    const uint8* Ptr = &kRawData[ 0 ];
    UObject* pTexAsset = pTexFactory->FactoryCreateBinary( UTexture::StaticClass(),
                                                           pPackage,
                                                           FName( *strTextureName ),
                                                           RF_Public | RF_Standalone,
                                                           NULL,
                                                           *FPaths::GetExtension( strPath ),
                                                           Ptr,
                                                           Ptr + kRawData.Num() - 1,
                                                           GWarn );
    if ( pTexAsset )
    {
        UTexture* kTexture = Cast<UTexture>( pTexAsset );
        pTexAsset->MarkPackageDirty();
        ULevel::LevelDirtiedEvent.Broadcast();
        pTexAsset->PostEditChange();
        FAssetRegistryModule::AssetCreated( pTexAsset );
        pPackage->SetDirtyFlag( true );

        //Save
        TArray<UPackage*> kPackagesToSave;
        kPackagesToSave.Add( pPackage );
        FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );

        //Re load
        pTexture = LoadObject<UTextureLightProfile>( nullptr, *strSaveAssetPath );
    }
    return pTexture;

}

AActor* FRLLiveLinkModule::LoadToScene( UBlueprint* pBlueprint )
{
    if ( !pBlueprint )
    {
        return nullptr;
    }
    UClass* pClassToSpawn = Cast<UClass>( pBlueprint->GeneratedClass );
    AActor* pActor = FRLLiveLinkUtility::SpawnActorToViewport( pClassToSpawn, "" );
    if ( !pActor )
    {
        return nullptr;
    }
    SetDefaultParentActor( pActor, FAttachmentTransformRules::KeepRelativeTransform );

    //set focus view on actor
    SelectAndFocusActor( pActor, false, true );
    return pActor;
}

UTexture2D* FRLLiveLinkModule::RotateTexture2D( UTexture2D* pTexture )
{
    if ( !pTexture )
    {
        return nullptr;
    }
    // for read / write textrue
#if ENGINE_MAJOR_VERSION <= 4
    int32 nWidth = pTexture->GetSizeX();
    int32 nHeight = pTexture->GetSizeY();
#else
    int32 nWidth = pTexture->GetPlatformData()->SizeX;
    int32 nHeight = pTexture->GetPlatformData()->SizeY;
#endif
    TextureCompressionSettings kOriCompressionSettings = pTexture->CompressionSettings;
    TextureMipGenSettings kOriMipGenSettings = pTexture->MipGenSettings;
    bool bOriSRGB = pTexture->SRGB;
    pTexture->CompressionSettings = TextureCompressionSettings::TC_VectorDisplacementmap;
    pTexture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
    pTexture->SRGB = false;
    pTexture->UpdateResource();

    // read & wirte texture color
#if ( ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 4 )
    const FColor* pFormatedImageData = static_cast< const FColor* >( pTexture->GetPlatformData()->Mips[ 0 ].BulkData.Lock( LOCK_READ_ONLY ) );
#else
    const FColor* pFormatedImageData = static_cast< const FColor* >( pTexture->PlatformData->Mips[ 0 ].BulkData.Lock( LOCK_READ_ONLY ) );
#endif
    uint8* pFlipedPixels = new uint8[ nWidth * nHeight * 4 ];
    for ( int32 i = 0; i < nWidth; ++i )
    {
        for ( int32 j = 0; j < nHeight; ++j )
        {
            const FColor& kPixelColor = pFormatedImageData[ i * nWidth + j ];

            int32 nFlipedIndex = j * nWidth + ( nWidth - i );
            pFlipedPixels[ 4 * nFlipedIndex ] = kPixelColor.B;
            pFlipedPixels[ 4 * nFlipedIndex + 1 ] = kPixelColor.G;
            pFlipedPixels[ 4 * nFlipedIndex + 2 ] = kPixelColor.R;
            pFlipedPixels[ 4 * nFlipedIndex + 3 ] = kPixelColor.A;
        }
    }
#if ( ENGINE_MAJOR_VERSION >= 5 && ENGINE_MINOR_VERSION >= 4 )
    pTexture->GetPlatformData()->Mips[ 0 ].BulkData.Unlock();
#else
    pTexture->PlatformData->Mips[ 0 ].BulkData.Unlock();
#endif
    // recover texture setting
    pTexture->CompressionSettings = kOriCompressionSettings;
    pTexture->MipGenSettings = kOriMipGenSettings;
    pTexture->SRGB = bOriSRGB;
    pTexture->Source.Init( nWidth, nHeight, 1, 1, ETextureSourceFormat::TSF_BGRA8, pFlipedPixels );
    pTexture->UpdateResource();
    UPackage* pOutPackage = pTexture->GetOutermost();
    if ( pOutPackage )
    {
        pOutPackage->MarkPackageDirty();
        bool bSaved = UPackage::SavePackage( pOutPackage,
                                             pTexture,
                                             EObjectFlags::RF_Public | EObjectFlags::RF_Standalone,
                                             *pOutPackage->GetName(),
                                             GError, nullptr, true, true, SAVE_NoError );
        if ( bSaved )
        {
            TArray<UPackage*> kPackagesToSave;
            kPackagesToSave.Add( pOutPackage );
            FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
        }
    }
    return pTexture;
    }

bool FRLLiveLinkModule::BuildWrinkleBlueprint( const FString& strRootGamePath, USkeletalMesh* pMesh )
{
    if ( !pMesh )
    {
        return false;
    }
    USkeleton* pSkeleton = pMesh->Skeleton;
    if ( !pSkeleton )
    {
        return false;
    }
    FString strRootPath = strRootGamePath + "/";
    strRootPath.RemoveFromStart( TEXT( "/Game/" ) );
    strRootPath = FPaths::ProjectContentDir() + strRootPath;
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if ( !kPlatformFile.DirectoryExists( *strRootPath ) )
    {
        kPlatformFile.CreateDirectory( *strRootPath );
    }

    //1. Copy ExpSequence, ExpPoseAsset, WrinkleAnimBp
    auto strPluginPath = IPluginManager::Get().FindPlugin( TEXT( "RLLiveLink" ) )->GetBaseDir();
    FString strExpSequencePath   = strPluginPath + "/Content/" + ExpSequence + ".rluasset";
    FString strExpPosePath       = strPluginPath + "/Content/" + ExpPoseAsset + ".rluasset";
    FString strWrinkleAnimBpPath = strPluginPath + "/Content/" + WrinkleAnimBP + ".rluasset";
    // 1.1 先檢查Source檔案是否存在
    if ( !kPlatformFile.FileExists( *strExpSequencePath )
         || !kPlatformFile.FileExists( *strExpPosePath )
         || !kPlatformFile.FileExists( *strWrinkleAnimBpPath ) )
    {
        UE_LOG( LogTemp, Error, TEXT( "BuildWrinkleBlueprint Source file not found." ) );
        return false;
    }
    // 1.2 檢查Target Path是否已存在這些檔案
    FString strTargetExpSequencePath = strRootPath + ExpSequence + ".uasset";
    FString strTargetExpPosePath = strRootPath + ExpPoseAsset + ".uasset";
    FString strTargetWrinkleAnimBpPath = strRootPath + WrinkleAnimBP + ".uasset";
    if ( kPlatformFile.FileExists( *strTargetExpSequencePath )
         || kPlatformFile.FileExists( *strTargetExpPosePath )
         || kPlatformFile.FileExists( *strTargetWrinkleAnimBpPath ) )
    {
        UE_LOG( LogTemp, Error, TEXT( "BuildWrinkleBlueprint target file alrady exist." ) );
        return false;
    }
    // 1.3 開始複製
    if ( !kPlatformFile.CopyFile( *strTargetExpSequencePath, *strExpSequencePath ) != 0
         || !kPlatformFile.CopyFile( *strTargetExpPosePath, *strExpPosePath ) != 0
         || !kPlatformFile.CopyFile( *strTargetWrinkleAnimBpPath, *strWrinkleAnimBpPath ) != 0 )
    {
        UE_LOG( LogTemp, Error, TEXT( "BuildWrinkleBlueprint copy file failed." ) );
        return false;
    }

    //2. re assign skeleton
    TArray< TWeakObjectPtr< UObject > > kAssetsToRetarget;
    auto fnAddRetargetSource = [ & ]( const FString& strAssetPath )->bool
    {
        auto pObject = StaticLoadObject( UAnimationAsset::StaticClass(),
                                         NULL,
                                         *strAssetPath,
                                         NULL,
                                         LOAD_DisableDependencyPreloading | LOAD_DisableCompileOnLoad );
        if ( !pObject )
        {
            return false;
        }
        UAnimationAsset* pAnimAsset = Cast< UAnimationAsset >( pObject );
        if ( pAnimAsset )
        {
            USkeleton* pSkeletonAsset = pAnimAsset->GetSkeleton();
            if ( !pSkeletonAsset || pSkeletonAsset != pSkeleton )
            {
                kAssetsToRetarget.Add( pAnimAsset );
                return true;
            }
        }
        return false;
    };
    FString strExpSeqContentPath = strRootGamePath + ExpSequence + "." + ExpSequence;
    FString strPoseAssetContentPath = strRootGamePath + ExpPoseAsset + "." + ExpPoseAsset;
    fnAddRetargetSource( strExpSeqContentPath );
    fnAddRetargetSource( strPoseAssetContentPath );
    if ( kAssetsToRetarget.Num() != 0 )
    {
        FAnimationRetargetContext kRetargetContext( kAssetsToRetarget, true, false );
        EditorAnimUtils::RetargetAnimations( nullptr, pSkeleton, kRetargetContext, true, nullptr );
    }

    //3. Change pose asset var
    FString strAnimBlueprintPath = strRootGamePath + WrinkleAnimBP + "." + WrinkleAnimBP;
    UAnimBlueprint* pAnimBlueprint = Cast< UAnimBlueprint >( StaticLoadObject( UAnimBlueprint::StaticClass(),
                                                                               NULL,
                                                                               *( strAnimBlueprintPath ),
                                                                               NULL,
                                                                               LOAD_DisableDependencyPreloading | LOAD_DisableCompileOnLoad ) );
    if ( pAnimBlueprint )
    {
        // 3.1 retarget skeleton
        ReAssignAnimationBlueprintSkeleton( pAnimBlueprint, pSkeleton );
        for ( FBPVariableDescription& pVar : pAnimBlueprint->NewVariables )
        {
            if ( pVar.VarName == "Pose Asset" )
            {
                pVar.DefaultValue = strRootGamePath + ExpPoseAsset;
                FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pAnimBlueprint );
                //Compile
                FKismetEditorUtilities::CompileBlueprint( pAnimBlueprint );
                UPackage* const pAssetPackage = pAnimBlueprint->GetOutermost();
                pAssetPackage->SetDirtyFlag( true );

                //Save
                TArray<UPackage*> kPackagesToSave;
                kPackagesToSave.Add( pAssetPackage );
                FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
            }
        }
    }

    //4. Rename assets
    FString strAssetName = pMesh->GetName();
    auto pExpSeqObject = StaticLoadObject( UAnimationAsset::StaticClass(),
                                           NULL,
                                           *strExpSeqContentPath,
                                           NULL,
                                           LOAD_DisableDependencyPreloading | LOAD_DisableCompileOnLoad );
    if ( pExpSeqObject )
    {
        RenameAsset( pExpSeqObject, strAssetName + "_" + ExpSequence );
    }
    auto pPoseAssetObject = StaticLoadObject( UAnimationAsset::StaticClass(),
                                              NULL,
                                              *strPoseAssetContentPath,
                                              NULL,
                                              LOAD_DisableDependencyPreloading | LOAD_DisableCompileOnLoad );
    if ( pPoseAssetObject )
    {
        RenameAsset( pPoseAssetObject, strAssetName + "_" + ExpPoseAsset );
    }
    if ( pAnimBlueprint )
    {
        RenameAsset( pAnimBlueprint, strAssetName + "_" + WrinkleAnimBP );
    }

    //5. Set PostProcessAnimBP
    if ( pAnimBlueprint )
    {
        pMesh->SetPostProcessAnimBlueprint( TSubclassOf< UAnimInstance >( *pAnimBlueprint->GeneratedClass ) );
        UPackage* const pAssetPackage = pMesh->GetOutermost();
        pAssetPackage->SetDirtyFlag( true );

        //Save
        TArray<UPackage*> kPackagesToSave;
        kPackagesToSave.Add( pAssetPackage );
        FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
    }
    return true;
}

bool FRLLiveLinkModule::ReAssignAnimationBlueprintSkeleton( UAnimBlueprint* pAnimBlueprint, USkeleton* pSkeleton )
{
    if ( !pAnimBlueprint || !pSkeleton )
    {
        return false;
    }
    FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified( pAnimBlueprint );
    FAssetRegistryModule::AssetCreated( pAnimBlueprint );
    pAnimBlueprint->MarkPackageDirty();

    pAnimBlueprint->TargetSkeleton = pSkeleton;
    pAnimBlueprint->SetPreviewMesh( pSkeleton->GetPreviewMesh(), true );
    auto pMesh = pAnimBlueprint->GetPreviewMesh();
    pAnimBlueprint->Modify( true );

    //Compile
    TWeakObjectPtr<UAnimBlueprint> pWeekAnimBlueprint = pAnimBlueprint;
    TArray<TWeakObjectPtr<UObject>> kAssetsToRetarget;
    kAssetsToRetarget.Add( pWeekAnimBlueprint );
    EditorAnimUtils::RetargetAnimations( pAnimBlueprint->TargetSkeleton, pSkeleton, kAssetsToRetarget, false, NULL, false );

    FKismetEditorUtilities::CompileBlueprint( pAnimBlueprint );
    UPackage* const pAssetPackage = pAnimBlueprint->GetOutermost();
    pAssetPackage->SetDirtyFlag( true );

    //Save
    TArray<UPackage*> kPackagesToSave;
    kPackagesToSave.Add( pAssetPackage );
    FEditorFileUtils::PromptForCheckoutAndSave( kPackagesToSave, false, /*bPromptToSave=*/ false );
    return true;
}

void FRLLiveLinkModule::ResetEditorImportSetting()
{
    m_kApFps = FFrameRate( 60, 1 );
    m_kLiveLinkFps = FFrameRate( 60, 1 );
    m_kMotionFrameSize = FFrameTime( 1 );

    m_bCreateLevelSequencer = false;
    m_bIsPlaceAssets = true;
    m_kCreateLevelSequencerList.Empty();
    m_kCameraPerFrameDataMap.Empty();
    m_kSwitchCameraDataList.Empty();
    m_kDataInQueue.Empty();
}

void FRLLiveLinkModule::ResetImportTaskCount()
{
    m_nImportAmount = 1;
    m_nCurrnetImportId = 0;
}

void FRLLiveLinkModule::ProcessImportObject( const FString& strAssetName )
{
    const FString strImportObjectSetting = GetObjectImportSettingFile( strAssetName );
    ImportFbxByJson( strImportObjectSetting );
}

void FRLLiveLinkModule::ProcessImportMotion( const FString& strAssetName )
{
    const FString strImportMotionSetting = GetMotionImportSettingFile( strAssetName );
    FString strMotionPath = ImportFbxByJson( strImportMotionSetting );
    if ( strMotionPath.IsEmpty() )
    {
        return;
    }

    if ( m_bCreateLevelSequencer )
    {
        strMotionPath = strMotionPath.Replace( TEXT( ".fbx" ), TEXT( "" ) );
        int32 nMotionNameFirstWorldIndex = 0;
        strMotionPath.FindLastChar( *"/", nMotionNameFirstWorldIndex );
        FString strMotionName = strMotionPath.Mid( ++nMotionNameFirstWorldIndex );

        CCreateRLLevelSequencerData kData;
        kData.strAssetName = strAssetName;
        kData.strMotionName = strMotionName;
        m_kCreateLevelSequencerList.Add( kData );
    }
}

FString FRLLiveLinkModule::ImportFbxByJson( const FString& strJsonPath )
{
    // Import Fbx
    UAutomatedAssetImportData* pImportData = GetImportDataByJson( strJsonPath );
    FAssetToolsModule& kAssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>( "AssetTools" );
    if ( !pImportData )
    {
        return "";
    }
    kAssetToolsModule.Get().ImportAssetsAutomated( pImportData );

    //要改成直接對Folder裡的東西存檔
    TArray< UObject* > kModifiedObjects;
    FAssetRegistryModule& kAssetRegistryModule = FModuleManager::LoadModuleChecked< FAssetRegistryModule >( "AssetRegistry" );
    TArray< FAssetData > kAssetsInFile;
    kAssetRegistryModule.Get().GetAssetsByPath( FName( pImportData->DestinationPath ), kAssetsInFile, true, false );
    for ( const FAssetData& kAsset : kAssetsInFile )
    {
        UObject* pObject = kAsset.GetAsset();
        if ( pObject && pObject->GetOutermost()->IsDirty() )
        {
            kModifiedObjects.Add( pObject );
        }
    }
    UPackageTools::SavePackagesForObjects( kModifiedObjects );
    return pImportData->Filenames.Num() > 0 ? pImportData->Filenames[ 0 ] : "";
}

UAutomatedAssetImportData* FRLLiveLinkModule::GetImportDataByJson( const FString& strImportSettingFile )
{
    FString strImportSettingString;
    if ( !FFileHelper::LoadFileToString( strImportSettingString, *strImportSettingFile ) )
    {
        return nullptr;
    }

    TSharedPtr< FJsonObject > spJsonObject;
    if ( !FRLLiveLinkUtility::ParseStringToJson( strImportSettingString, spJsonObject ) )
    {
        return nullptr;
    }
    UAutomatedAssetImportData* pImportData = nullptr;
    const TArray< TSharedPtr< FJsonValue > > kImportGroupsJsonArray = spJsonObject->GetArrayField( TEXT( "ImportGroups" ) );
    for ( const TSharedPtr< FJsonValue >& spImportGroupsJson : kImportGroupsJsonArray )
    {
        const TSharedPtr< FJsonObject > spImportGroupsJsonObject = spImportGroupsJson->AsObject();
        if ( spImportGroupsJsonObject.IsValid() )
        {
            // All import data is based off of the global data defaults
            pImportData = NewObject< UAutomatedAssetImportData >();
            if ( !pImportData )
            {
                continue;
            }
            // Parse data from the json object
            if ( FJsonObjectConverter::JsonObjectToUStruct( spImportGroupsJsonObject.ToSharedRef(), UAutomatedAssetImportData::StaticClass(), pImportData, 0, 0 ) )
            {
                pImportData->Initialize( spImportGroupsJsonObject );
            }
            UFactory* pFactory = pImportData->Factory;
            const TSharedPtr< FJsonObject >* spImportSettingsJsonObject = nullptr;
            if ( pImportData->ImportGroupJsonData.IsValid() )
            {
                pImportData->ImportGroupJsonData->TryGetObjectField( TEXT( "ImportSettings" ), spImportSettingsJsonObject );
                const TSharedPtr< FJsonObject >* pSkeletalMeshImportDataJson;
                if ( spImportSettingsJsonObject->Get()->TryGetObjectField( TEXT( "SkeletalMeshImportData" ), pSkeletalMeshImportDataJson ) )
                {
                    pSkeletalMeshImportDataJson->Get()->SetNumberField( TEXT( "NormalImportMethod" ), 2 );
                }
            }

            if ( pFactory != nullptr && spImportSettingsJsonObject )
            {
                IImportSettingsParser* pImportSettings = pFactory->GetImportSettingsParser();
                if ( pImportSettings )
                {
                    pImportSettings->ParseFromJson( spImportSettingsJsonObject->ToSharedRef() );
                }
            }
        }
    }
    return pImportData;
}

void FRLLiveLinkModule::RemoveFbxFiles( const FString& strAssetName )
{
    const FString strExportFolder = m_strLiveLinkTempPath + "/" + strAssetName;
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if ( kPlatformFile.DirectoryExists( *strExportFolder ) )
    {
        kPlatformFile.DeleteDirectoryRecursively( *strExportFolder );
    }
}

void FRLLiveLinkModule::RemoveFile( const FString& strFilePath )
{
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if ( kPlatformFile.FileExists( *strFilePath ) )
    {
        kPlatformFile.DeleteFile( *strFilePath );
    }
}

FString FRLLiveLinkModule::GetObjectImportSettingFile( const FString& strAssetName )
{
    return m_strLiveLinkTempPath + "/" + strAssetName +  "/import_settings.json";
}

FString FRLLiveLinkModule::GetMotionImportSettingFile( const FString& strAssetName )
{
    return m_strLiveLinkTempPath + "/" + strAssetName + "/motion_import_settings.json";
}

bool FRLLiveLinkModule::IsImportAssetsDone() const
{
    return m_nImportAmount != 0 && m_nCurrnetImportId == m_nImportAmount;
}

void FRLLiveLinkModule::InitialProgressWidget()
{
    if ( IsRunningCommandlet() )
    {
        return;
    }
    m_spProgressStyle = MakeShareable( new FNotificationInfo( FText::FromString( "" ) ) );
    TSharedRef< SHorizontalBox > kHorizontalBox = SNew( SHorizontalBox );

    TSharedRef< FSlateStyleSet > kStyle = MakeShareable( new FSlateStyleSet( "RLLiveLinkStyle" ) );
    kStyle->SetContentRoot( IPluginManager::Get().FindPlugin( "RLLiveLink" )->GetBaseDir() / TEXT( "Resources" ) );

    TSharedRef< SHorizontalBox > kNotificationWidget = kHorizontalBox;
    kHorizontalBox->AddSlot()
        .AutoWidth()
        [
            SNew( SBox )
                [
                    SNew( SImage )
                        .Image_Lambda( [ & ]()
                    {
                        return FRLLiveLinkStyle::Get().GetBrush( "RLLiveLink.PluginAction" );
                    } )
                ]
        ];
    kHorizontalBox->AddSlot()
        .FillWidth( 4.f )
        .Padding( 10.f, 0.f, 0.f, 0.f )
        [
            SNew( SVerticalBox )
                + SVerticalBox::Slot()
                [
                    SNew( SBox )
                        .HeightOverride( 30 )
                        [
                            SNew( STextBlock )
                                .TextStyle( &FAppStyle::GetWidgetStyle<FTextBlockStyle>( "NotificationList.WidgetText" ) )
                                .Font( FAppStyle::Get().GetFontStyle( TEXT( "NotificationList.FontBold" ) ) )
                                .Text_Lambda( [ & ]()
                            {
                                int nId =  m_nCurrnetImportId < m_nImportAmount ? m_nCurrnetImportId + 1 : m_nImportAmount;
                                return FText::FromString( "Import asset from iClone...( " +
                                                          FString::FromInt( nId ) + "/" + FString::FromInt( m_nImportAmount )
                                                          + " )" );
                            } )
                        ]
                ]
                + SVerticalBox::Slot()
                [
                    SNew( SBox )
                        [
                            SNew( SProgressBar )
                                .FillColorAndOpacity( FLinearColor::Green )
                                .Percent_Lambda( [ & ]()
                            {
                                return m_nCurrnetImportId / static_cast< float >( m_nImportAmount );
                            } )
                        ]
                ]
        ];
    m_spProgressStyle.Get()->ContentWidget = MakeShared<FLiveLinkNotificationWidgetProvider>( kNotificationWidget );
    m_spProgressStyle.Get()->bFireAndForget = false;
    m_spProgressStyle.Get()->FadeInDuration = 0.f;
}

void FRLLiveLinkModule::ShowProgress()
{
    if ( m_spProgress.Get() || IsRunningCommandlet() )
    {
        return;
    }
    m_spProgress = FSlateNotificationManager::Get().AddNotification( *m_spProgressStyle.Get() );
}

void FRLLiveLinkModule::PushProgress( size_t uPushSize )
{
    if ( IsRunningCommandlet() )
    {
        return;
    }
    m_nCurrnetImportId = m_nCurrnetImportId + uPushSize <= m_nImportAmount ? m_nCurrnetImportId + uPushSize : m_nImportAmount;
    if ( IsImportAssetsDone() && m_spProgress )
    {
        m_spProgress->ExpireAndFadeout();
        m_spProgress = nullptr;
    }
}

ULevelSequence* FRLLiveLinkModule::CreateLevelSequencer()
{
    const FString strSequenceName = "RLSequence_" + FDateTime::Now().ToString( TEXT( "%Y_%m_%d-%H_%M_%S" ) );
    const FString strSaveFolder = FPaths::ProjectContentDir() + "/RLLevelSequences";
    IPlatformFile& kPlatformFile = FPlatformFileManager::Get().GetPlatformFile();

    if ( !kPlatformFile.DirectoryExists( *strSaveFolder ) )
    {
        kPlatformFile.CreateDirectory( *strSaveFolder );
    }

    const FString strPackName = TEXT( "/Game/RLLevelSequences/" ) + strSequenceName;
    UPackage* pPackage = CreatePackage( *strPackName );
    if ( !IsValid( pPackage ) )
    {
        return nullptr;
    }
    pPackage->FullyLoad();

    ULevelSequence* pLevelSequence = NewObject< ULevelSequence >( pPackage, *strSequenceName, RF_Public | RF_Standalone );
    if ( !IsValid( pLevelSequence ) )
    {
        return nullptr;
    }
    pLevelSequence->Initialize();

    UMovieScene* pMovieScene = pLevelSequence->GetMovieScene();
    if ( !IsValid( pMovieScene ) )
    {
        return nullptr;
    }

    pMovieScene->SetDisplayRate( m_kLiveLinkFps );
    const FFrameRate kTickRate = pMovieScene->GetTickResolution();
    const FFrameTime kTickResolutionFrameNumber = FFrameRate::TransformTime( m_kMotionFrameSize, m_kLiveLinkFps, kTickRate );

    const TRange< FFrameNumber > kDataRange = TRange< FFrameNumber >::Inclusive( FFrameNumber( 0 ), kTickResolutionFrameNumber.GetFrame() );
    pMovieScene->SetPlaybackRange( kDataRange );
    pMovieScene->SetPlaybackRangeLocked( false );

    FMovieSceneEditorData& kEditorData = pMovieScene->GetEditorData();
    kEditorData.ViewStart = kEditorData.WorkStart = 0.f;
    kEditorData.ViewEnd = kEditorData.WorkEnd =  m_kLiveLinkFps.AsSeconds( m_kMotionFrameSize );
    pMovieScene->SetWorkingRange( static_cast< float >( kEditorData.ViewStart ), static_cast< float >( kEditorData.ViewEnd ) );
    pMovieScene->SetViewRange( static_cast< float >( kEditorData.ViewStart ), static_cast< float >( kEditorData.ViewEnd ) );
    return pLevelSequence;
}

bool FRLLiveLinkModule::SetupLevelSequencer()
{
    ULevelSequence* pLevelSequence = CreateLevelSequencer();
    if ( !pLevelSequence )
    {
        return false;
    }

    TArray< FString > kAssetNames;
    for ( const auto& kData : m_kCreateLevelSequencerList )
    {
        const FString strAssetName = kData.strAssetName;
        const FString strMotionGamePath = kData.GetMotionGamePath();
        AddActorToSequencer( pLevelSequence, strAssetName, strMotionGamePath );
        kAssetNames.Add( strAssetName );
    }
    AddCameraToSequencer( pLevelSequence );

    UPackage* pPackage = pLevelSequence->GetOutermost();
    if ( !pPackage )
    {
        return false;
    }
    pPackage->SetDirtyFlag( true );
    UPackageTools::SavePackagesForObjects( { pLevelSequence } );

    IAssetEditorInstance* pAssetEditor = GEditor->GetEditorSubsystem< UAssetEditorSubsystem >()->FindEditorForAsset( pLevelSequence, false );
    if ( pAssetEditor )
    {
        pAssetEditor->CloseWindow();
    }

    ReassignSkeletalMeshInLevelSequencer( kAssetNames );
    return true;
}

TWeakPtr< ISequencer > FRLLiveLinkModule::GetISequencer( ULevelSequence* pLevelSequence )
{
    if ( !pLevelSequence )
    {
        return nullptr;
    }
    GEditor->GetEditorSubsystem< UAssetEditorSubsystem >()->OpenEditorForAsset( pLevelSequence );
    IAssetEditorInstance* pAssetEditor = GEditor->GetEditorSubsystem< UAssetEditorSubsystem >()->FindEditorForAsset( pLevelSequence, false );
    ILevelSequenceEditorToolkit* pLevelSequenceEditor = static_cast< ILevelSequenceEditorToolkit* >( pAssetEditor );
    TWeakPtr< ISequencer > pWeakSequencer = pLevelSequenceEditor ? pLevelSequenceEditor->GetSequencer() : nullptr;
    return pWeakSequencer;
}

void FRLLiveLinkModule::AddActorToSequencer( ULevelSequence* pLevelSequence, const FString& strAssetName, const FString& strMotionGamePath )
{
    if ( !pLevelSequence )
    {
        return;
    }

    const FString strManSkeletalGamePath = "/Game/RLContent/" + strAssetName + "/" + strAssetName + "." + strAssetName;
    USkeletalMesh* pSkeletalMesh = Cast< USkeletalMesh >( StaticLoadObject( USkeletalMesh::StaticClass(), nullptr, *( strManSkeletalGamePath ) ) );
    if ( !pSkeletalMesh )
    {
        return;
    }

    AActor* pActor = FRLLiveLinkUtility::SpawnActorToViewport( ASkeletalMeshActor::StaticClass(), strAssetName );
    ASkeletalMeshActor* pSkeletalMeshActor = Cast< ASkeletalMeshActor >( pActor );
    if ( !pSkeletalMeshActor || !pActor )
    {
        return;
    }
    pSkeletalMeshActor->GetSkeletalMeshComponent()->SetSkeletalMesh( pSkeletalMesh );
    UMovieScene* pMovieScene = pLevelSequence->GetMovieScene();
    TWeakPtr< ISequencer > pWeakSequencer = GetISequencer( pLevelSequence );
    if ( !pMovieScene || !pWeakSequencer.Pin() )
    {
        return;
    }

    TArray< FGuid > kActorTrackIds = pWeakSequencer.Pin()->AddActors( { pActor }, false );
    for ( auto kActorTrackId : kActorTrackIds )
    {
        UMovieScene3DTransformTrack* pTransformTrack = pMovieScene->FindTrack< UMovieScene3DTransformTrack >( kActorTrackId );
        AddTranslateKey( pTransformTrack, FFrameNumber( 0 ), FVector::Zero() );

        UMovieSceneSkeletalAnimationTrack* pAnimTrack = pMovieScene->FindTrack< UMovieSceneSkeletalAnimationTrack >( kActorTrackId );
        if ( pAnimTrack )
        {
            const FFrameNumber kZeroFrame( 0 );
            UAnimSequenceBase* pTransferMotion = Cast< UAnimSequenceBase >( StaticLoadObject( UAnimSequenceBase::StaticClass(), nullptr, *( strMotionGamePath ) ) );
            if ( !pTransferMotion )
            {
                continue;
            }
            pAnimTrack->AddNewAnimation( kZeroFrame, pTransferMotion );
            pAnimTrack->Modify();
        }
        FSequencerUtilities::ConvertToSpawnable( pWeakSequencer.Pin().ToSharedRef(), kActorTrackId );
    }
    pWeakSequencer.Pin()->NotifyMovieSceneDataChanged( EMovieSceneDataChangeType::MovieSceneStructureItemAdded );
}

void FRLLiveLinkModule::AddCameraToSequencer( ULevelSequence* pLevelSequence )
{
    if ( !pLevelSequence )
    {
        return;
    }
    UMovieScene* pMovieScene = pLevelSequence->GetMovieScene();
    TWeakPtr< ISequencer > pWeakSequencer = GetISequencer( pLevelSequence );
    if ( !pMovieScene || !pWeakSequencer.Pin() )
    {
        return;
    }
    const FFrameRate kTickRate = pMovieScene->GetTickResolution();
    const FFrameTime kTickResolutionFrameNumber = FFrameRate::TransformTime( m_kMotionFrameSize, m_kLiveLinkFps, kTickRate );
    const FFrameNumber kLastFrame = kTickResolutionFrameNumber.GetFrame();
    const TRange< FFrameNumber > kCameraSectionRange = TRange< FFrameNumber >::Inclusive( FFrameNumber( 0 ), kLastFrame );

    TMap< FString, FGuid > kCineCameraIdMap;
    kCineCameraIdMap.Reserve( m_kCameraPerFrameDataMap.Num() );
    for ( const auto& kCameraData : m_kCameraPerFrameDataMap )
    {
        // Spawn Cine Camera
        const FString strCameraName =  kCameraData.Key;
        AActor* pActor = FRLLiveLinkUtility::SpawnActorToViewport( ACineCameraActor::StaticClass(), strCameraName );
        ACineCameraActor* pCineCameraActor = Cast< ACineCameraActor >( pActor );
        if ( !pCineCameraActor || !pActor )
        {
            continue;
        }
        UCameraComponent* pCineCameraComponent = pCineCameraActor->GetCameraComponent();
        if ( !pCineCameraComponent )
        {
            continue;
        }
        TArray< FGuid > kActorIds = pWeakSequencer.Pin()->AddActors( { pActor }, false );
        if ( kActorIds.IsEmpty() )
        {
            continue;
        }

        // Prpare Camera Property Tracks to Add Keys
        const FGuid kCineCameraId = kActorIds[ 0 ];
        const TArray< FMovieSceneBinding >& kBindings = pMovieScene->GetBindings();
        TMap< FString, UMovieSceneTrack* > kUECameraPropertyTracks;
        for ( const FMovieSceneBinding& kBinding : kBindings )
        {
            UObject* pBindingObject = pWeakSequencer.Pin()->FindSpawnedObjectOrTemplate( kBinding.GetObjectGuid() );
            if ( !pBindingObject
                 || !Cast< UCameraComponent >( pBindingObject ) )
            {
                continue;
            }
            UCameraComponent* pCameraComponent = Cast< UCameraComponent >( pBindingObject );
            FGuid kCameraComponentId = kBinding.GetObjectGuid();
            if ( pCameraComponent->GetOwner() != pCineCameraActor )
            {
                continue;
            }
            for ( auto kCameraPropertyPair : s_kUEToICCameraPropertyNameMap )
            {
                const FName strPropertyName = *kCameraPropertyPair.Value;
                UMovieSceneFloatTrack* pPropertyTrack = Cast< UMovieSceneFloatTrack >( pMovieScene->FindTrack( UMovieSceneFloatTrack::StaticClass(), kCameraComponentId, strPropertyName ) );
                if ( !pPropertyTrack )
                {    
                    pPropertyTrack = Cast< UMovieSceneFloatTrack >( pMovieScene->AddTrack( UMovieSceneFloatTrack::StaticClass(), kCameraComponentId ) );
                    if ( !pPropertyTrack || !s_kUEPropertyNameAndPathMap.Contains( strPropertyName ) )
                    {
                        continue;
                    }
                    UMovieSceneSection* pNewSection = pPropertyTrack->CreateNewSection();
                    pNewSection->SetRange( kCameraSectionRange );
                    pPropertyTrack->AddSection( *pNewSection );
                    pPropertyTrack->SetPropertyNameAndPath( strPropertyName, s_kUEPropertyNameAndPathMap[ strPropertyName ] );
                }
                kUECameraPropertyTracks.Add( kCameraPropertyPair.Value, pPropertyTrack );
            }
            break;
        }


        // Add Camera Property key & Transform Key
        ECameraFocusMethod eFocusMethod = ECameraFocusMethod::Disable;
        UMovieScene3DTransformSection* pTransformSection = MovieSceneToolHelpers::GetTransformSection( pWeakSequencer.Pin().Get(),
                                                                                                       kCineCameraId,
                                                                                                       FTransform::Identity );
        TArray< FTransform > kInTransforms;
        TArray< FFrameNumber > kFrames;
        for ( int nFrame = 0; nFrame < kCameraData.Value.Num(); ++nFrame )
        {
            const FLiveLinkFrameData kFrameData = kCameraData.Value[ nFrame ];
            const FFrameNumber kFrameNumber = FFrameRate::TransformTime( FFrameTime( nFrame ), m_kLiveLinkFps, kTickRate ).FrameNumber;
            for ( auto kPair : kUECameraPropertyTracks )
            {
                if ( const FName* strICCameraProperty = s_kUEToICCameraPropertyNameMap.FindKey( kPair.Key ) )
                {
                    const float fPropertyValue = FCString::Atof( *kFrameData.MetaData.StringMetaData[ *strICCameraProperty ] );
                    UMovieSceneFloatTrack* pTrack = Cast< UMovieSceneFloatTrack >( kPair.Value );
                    AddFloatKey( pTrack, kFrameNumber, fPropertyValue );
                }


                const bool bIsDofEnable = FCString::Atof( *kFrameData.MetaData.StringMetaData[ FName( "Enable" ) ] ) > 0.f;
                if ( bIsDofEnable )
                {
                    eFocusMethod = ECameraFocusMethod::Manual;
                }
            }
            kInTransforms.Append( kFrameData.Transforms );
            kFrames.Add( kFrameNumber );
        }
        pCineCameraActor->GetCineCameraComponent()->FocusSettings.FocusMethod = eFocusMethod;
        kCineCameraIdMap.Add( strCameraName, kCineCameraId );
        MovieSceneToolHelpers::AddTransformKeys( pTransformSection, kFrames, kInTransforms, EMovieSceneTransformChannel::AllTransform );
    }

    UMovieSceneTrack* pCameraCutTrack = pMovieScene->GetCameraCutTrack();
    if ( !pCameraCutTrack )
    {
        pCameraCutTrack = pLevelSequence->GetMovieScene()->AddCameraCutTrack( UMovieSceneCameraCutTrack::StaticClass() );
        return;
    }
    TArray< UMovieSceneSection* > kSecitons = pCameraCutTrack->GetAllSections();
    for ( const auto pSection : kSecitons )
    {
        pCameraCutTrack->RemoveSection( *pSection );
    }

    // Set Switch Camera Key
    for ( size_t i = 0; i < m_kSwitchCameraDataList.Num(); ++i )
    {
        const auto& kData = m_kSwitchCameraDataList[ i ];
        if ( kCineCameraIdMap.Contains( kData.strCameraName ) )
        {
            UMovieSceneCameraCutSection* pCameraCutSection = Cast<UMovieSceneCameraCutSection>( pCameraCutTrack->CreateNewSection() );
            if ( !pCameraCutSection )
            {
                continue;
            }
            const FGuid kCineCameraId = kCineCameraIdMap[ kData.strCameraName ];
            const int nICFrameTime = kData.nSwitchFrame;
            const int nUrealFrameTime = ConvertFrameTimeFromeICloneToUnreal( nICFrameTime );
            const FFrameNumber kCutStartFrame = FFrameRate::TransformTime( nUrealFrameTime, m_kLiveLinkFps, kTickRate ).GetFrame();
            FFrameNumber kCutEndFrame;
            if ( i + 1 < m_kSwitchCameraDataList.Num() )
            {
                const int nICNextFrameTime = m_kSwitchCameraDataList[ i + 1 ].nSwitchFrame;
                const int nUrealNextFrameTime = ConvertFrameTimeFromeICloneToUnreal( nICNextFrameTime );
                kCutEndFrame = FFrameRate::TransformTime( nUrealNextFrameTime, m_kLiveLinkFps, kTickRate ).GetFrame();
            }
            else
            {
                kCutEndFrame = kLastFrame;
            }
            const TRange< FFrameNumber > kCutRange = TRange< FFrameNumber >::Inclusive( kCutStartFrame, kCutEndFrame );
            pCameraCutSection->SetRange( kCutRange );
            pCameraCutSection->SetCameraBindingID( UE::MovieScene::FRelativeObjectBindingID( kCineCameraId ) );
            pCameraCutTrack->AddSection( *pCameraCutSection );
        }
    }

    // ConverToSpawnable要最後做, 做完後Id會改變
    for ( const auto kPair : kCineCameraIdMap )
    {
        FSequencerUtilities::ConvertToSpawnable( pWeakSequencer.Pin().ToSharedRef(), kPair.Value );
    }
}

void FRLLiveLinkModule::AddFloatKey( UMovieSceneFloatTrack* pFloatTrack, FFrameNumber kFrameNumber, float fValue )
{
    if ( pFloatTrack )
    {
        // Add First Key
        const TArray< UMovieSceneSection* >& kSections =  pFloatTrack->GetAllSections();
        if ( kSections.IsEmpty() )
        {
            return;
        }
        TArrayView< FMovieSceneFloatChannel* > kChannels = kSections[ 0 ]->GetChannelProxy().GetChannels< FMovieSceneFloatChannel >();
        if ( kChannels.IsEmpty() )
        {
            return;
        }
        TMovieSceneChannelData< FMovieSceneFloatValue > kChannelData = kChannels[ 0 ]->GetData();
        MovieSceneToolHelpers::SetOrAddKey( kChannelData, kFrameNumber, fValue );
    }
}

void FRLLiveLinkModule::AddTranslateKey( UMovieScene3DTransformTrack* pTransformTrack, FFrameNumber kFrameNumber, FVector vTransflate )
{
    if ( pTransformTrack )
    {
        // Add First Key
        const TArray< UMovieSceneSection* >& kSections =  pTransformTrack->GetAllSections();
        if ( kSections.IsEmpty() )
        {
            return;
        }
        TArrayView< FMovieSceneDoubleChannel* > kChannels = kSections[ 0 ]->GetChannelProxy().GetChannels< FMovieSceneDoubleChannel >();
        if ( kChannels.Num() < 3 )
        {
            return;
        }
        TMovieSceneChannelData< FMovieSceneDoubleValue > kChannelData = kChannels[ 0 ]->GetData();
        MovieSceneToolHelpers::SetOrAddKey( kChannelData, kFrameNumber, vTransflate.X );
        kChannelData = kChannels[ 1 ]->GetData();
        MovieSceneToolHelpers::SetOrAddKey( kChannelData, kFrameNumber, vTransflate.Y );
        kChannelData = kChannels[ 2 ]->GetData();
        MovieSceneToolHelpers::SetOrAddKey( kChannelData, kFrameNumber, vTransflate.Z );
    }
}

void FRLLiveLinkModule::LoadCameraPerFrameDatas()
{
    const FString strCameraPerframeDataFile = m_strLiveLinkTempPath + "/" + "camera_per_frame_data";
    TArray<uint8> kCameraPerFrameRawList;
    if ( !FFileHelper::LoadFileToArray( kCameraPerFrameRawList, *strCameraPerframeDataFile ) )
    {
        return;
    }

    int nMajorVersion = 0;
    int nMinorVersion = 0;
    int nIndex = 0;

    auto fnReadInt = [ & ]() -> int
    {
        if ( nIndex < kCameraPerFrameRawList.Num() )
        {
            int nValue;
            uint8 kCharlist[ 4 ];
            for ( int i = 0; i < 4; ++i )
            {
                kCharlist[ i ] = kCameraPerFrameRawList.GetData()[ i + nIndex ];
            }
            memcpy( &nValue, kCharlist, 4 );
            nIndex += 4;
            return nValue;
        }
        return 0;
    };

    auto fnReadFloat = [ & ]() -> float
    {
        if ( nIndex < kCameraPerFrameRawList.Num() )
        {
            float fValue;
            uint8 kCharlist[ 4 ];
            for ( int i = 0; i < 4; ++i )
            {
                kCharlist[ i ] = kCameraPerFrameRawList.GetData()[ i + nIndex ];
            }
            memcpy( &fValue, kCharlist, 4 );
            nIndex += 4;
            return fValue;
        }
        return 0;
    };

    auto fnReadBool = [ & ]() -> bool
    {
        if ( nIndex < kCameraPerFrameRawList.Num() )
        {
            bool bValue;
            uint8 kCharlist[ 1 ];
            for ( int i = 0; i < 1; ++i )
            {
                kCharlist[ i ] = kCameraPerFrameRawList.GetData()[ i + nIndex ];
            }
            memcpy( &bValue, kCharlist, 1 );
            nIndex += 1;
            return bValue;
        }
        return 0;
    };

    auto fnReadString = [ & ]() -> FString
    {
        if ( nIndex < kCameraPerFrameRawList.Num() )
        {
            int nLength = fnReadInt();
            FString strValue;
            FFileHelper::BufferToString( strValue,
                                         kCameraPerFrameRawList.GetData() + nIndex,
                                         nLength );
             nIndex += nLength;
             return strValue;
        }
        return "";
    };

    auto fnReadVector = [ & ]() -> FVector
    {
        if ( nIndex < kCameraPerFrameRawList.Num() )
        {
            float fValueX = fnReadFloat();
            float fValueY = fnReadFloat();
            float fValueZ = fnReadFloat();
            return FVector( fValueX, fValueY, fValueZ );
        }
        return FVector();
    };

    auto fnReadQuat = [ & ]() -> FQuat
    {
        if ( nIndex + 3 < kCameraPerFrameRawList.Num() )
        {
            float fValueX = fnReadFloat();
            float fValueY = fnReadFloat();
            float fValueZ = fnReadFloat();
            float fValueW = fnReadFloat();
            return FQuat( fValueX, fValueY, fValueZ, fValueW );
        }
        return FQuat();
    };

    FString strVersion = fnReadString();
    if ( strVersion != "Version" )
    {
        UE_LOG( LogTemp, Error, TEXT( "(%s)" ), *strVersion );
        check( false );
        return;
    }

    nMajorVersion = fnReadInt();
    nMinorVersion = fnReadInt();

    if ( fnReadString() != "CameraPerFrameData" )
    {
        check( false );
        return;
    }

    int nCameraSize = fnReadInt();
    m_kCameraPerFrameDataMap.Reserve( nCameraSize );
    for ( int nCameraIndex = 0; nCameraIndex < nCameraSize; ++nCameraIndex )
    {
        FString strCameraName = fnReadString();
        if ( fnReadString() != "Data" )
        {
            check( false );
            return;
        }

        if ( strCameraName == "#SwitchCameras#" )
        {
            int nKeySize = fnReadInt();
            m_kSwitchCameraDataList.Reserve( nKeySize );
            for ( int nKeyIndex = 0; nKeyIndex < nKeySize; ++nKeyIndex )
            {
                FString strSwitchToCameraName = fnReadString();
                int nFrame = fnReadInt();

                CSwitchCameraData kData;
                kData.strCameraName = strSwitchToCameraName;
                kData.nSwitchFrame = nFrame;
                m_kSwitchCameraDataList.Add( kData );
            }
        }
        else
        {
            int nFrameSize = fnReadInt();
            if ( !m_kCameraPerFrameDataMap.Contains( strCameraName ) )
            {
                m_kCameraPerFrameDataMap.Add( strCameraName );
                m_kCameraPerFrameDataMap[ strCameraName ].Reserve( nFrameSize );
            }
            for ( int nFrameIndex = 0; nFrameIndex < nFrameSize; ++nFrameIndex )
            {
                //Received Data
                FVector kCameraLocation = fnReadVector();
                kCameraLocation = FVector( kCameraLocation.X, -kCameraLocation.Y, kCameraLocation.Z );

                //ROT
                FQuat kCameraRotation = fnReadQuat();
                FVector kVec = kCameraRotation.Euler();
                FVector kLeftVec = FVector( -kVec.X, kVec.Y, -kVec.Z );
                kCameraRotation = FQuat::MakeFromEuler( kLeftVec );

                //Set Camera Rotation
                FTransform kCameraTransform = FTransform( kCameraRotation, kCameraLocation );
                FTransform kICToUE = FTransform( FQuat::MakeFromEuler( FVector( -90, -90, 0 ) ), FVector::ZeroVector );
                kCameraTransform = kICToUE * kCameraTransform;

                TMap<FName, FString> kCameraMap;
                //SetFocalLength
                float fFocalLength = fnReadFloat();
                float fAngleView = fnReadFloat();

                //Set DOF
                bool bEnable = fnReadBool();
                float fFocus = fnReadFloat();
                float fRange = fnReadFloat();
                float fNearTransitionRegion = fnReadFloat();
                float fFarTransitionRegion = fnReadFloat();
                float fNearBlurScale = fnReadFloat();
                float fFarBlurScale = fnReadFloat();
                float fMinBlendDistance = fnReadFloat();
                float fCenterColorWeight = fnReadFloat();
                float fEdgeDecayPower = fnReadFloat();
                kCameraMap.Add( "FocalLength", FString::SanitizeFloat( fFocalLength ) );
                kCameraMap.Add( "AngleView", FString::SanitizeFloat( fAngleView ) );
                kCameraMap.Add( "Enable", FString::SanitizeFloat( bEnable ) );
                kCameraMap.Add( "Focus", FString::SanitizeFloat( fFocus ) );
                kCameraMap.Add( "Range", FString::SanitizeFloat( fRange * 2.f ) );
                kCameraMap.Add( "NearTransitionRegion", FString::SanitizeFloat( fNearTransitionRegion * 2.f ) );
                kCameraMap.Add( "FarTransitionRegion", FString::SanitizeFloat( fFarTransitionRegion * 2.f ) );
                kCameraMap.Add( "NearBlurScale", FString::SanitizeFloat( fNearBlurScale * 4.44f ) );
                kCameraMap.Add( "FarBlurScale", FString::SanitizeFloat( fFarBlurScale * 4.44f ) );
                kCameraMap.Add( "MinBlendDistance", FString::SanitizeFloat( fMinBlendDistance ) );
                kCameraMap.Add( "CenterColorWeight", FString::SanitizeFloat( fCenterColorWeight ) );
                kCameraMap.Add( "EdgeDecayPower", FString::SanitizeFloat( fEdgeDecayPower ) );
                kCameraMap.Add( "FocusOffset", FString::SanitizeFloat( fRange * -1.f ) );


                //Film back & Screen Size
                int nFovType = fnReadInt();
                int nScreenWidth = fnReadInt();
                int nScreenHeight = fnReadInt();
                float fFilmbackWidth = fnReadFloat();
                float fFilmbackHeight = fnReadFloat();

                float fAspectRatio = static_cast< float >( nScreenWidth ) / nScreenHeight;
                float fScreeHeight = 36.f / fAspectRatio;
                float fSensorWidth = ( nFovType == 0 ) ? fFilmbackWidth : fFilmbackHeight * fAspectRatio;
                float fSensorHeight = ( nFovType == 1 ) ? fFilmbackHeight : fFilmbackWidth / fAspectRatio;
                float fSensorAspectRatio = fSensorWidth / fSensorHeight;
                float fCurrentFocalLength = fFocalLength * fAspectRatio / fSensorAspectRatio;
                kCameraMap.Add( "ScreenWidth", "36" );
                kCameraMap.Add( "ScreenHeight", FString::SanitizeFloat( fScreeHeight ) );
                kCameraMap.Add( "AspectRatio", FString::SanitizeFloat( fAspectRatio ) );
                kCameraMap.Add( "SensorWidth", FString::SanitizeFloat( fSensorWidth ) );
                kCameraMap.Add( "SensorHeight", FString::SanitizeFloat( fSensorHeight ) );
                kCameraMap.Add( "CurrentFocalLength", FString::SanitizeFloat( fCurrentFocalLength ) );

                FLiveLinkFrameData kCameraFrameData;
                kCameraFrameData.Transforms.Add( kCameraTransform );
                kCameraFrameData.MetaData.StringMetaData = kCameraMap;
                m_kCameraPerFrameDataMap[ strCameraName ].Add( kCameraFrameData );
            }
        }
    }
    RemoveFile( strCameraPerframeDataFile );
}

void FRLLiveLinkModule::ReassignSkeletalMeshInLevelSequencer( const TArray< FString >& kAssetNames )
{
    if ( kAssetNames.IsEmpty() )
    {
        return;
    }

    const FString strAssetGamePath = "/Game/RLLevelSequences";
    FAssetRegistryModule& kAssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>( "AssetRegistry" );
    TArray< FAssetData > kAssetsInFile;
    kAssetRegistryModule.Get().GetAssetsByPath( FName( strAssetGamePath ), kAssetsInFile, true, false );

    TArray< UObject* > kModifiedObjects;
    for ( const FAssetData& kAsset : kAssetsInFile )
    {
        ULevelSequence* pLevelSequencer = Cast< ULevelSequence >( kAsset.GetAsset() );
        if ( !pLevelSequencer )
        {
            continue;
        }

        UMovieScene* pMoiveScene = pLevelSequencer->GetMovieScene();
        if ( !pMoiveScene )
        {
            continue;
        }

        for ( size_t i = 0; i < pMoiveScene->GetSpawnableCount(); ++i )
        {
            FMovieSceneSpawnable& kSpawnable = pMoiveScene->GetSpawnable( i );
            AActor* pActor = Cast< AActor >( kSpawnable.GetObjectTemplate() );
            if ( !pActor )
            {
                continue;
            }
            USkeletalMeshComponent* pSkeletalMeshComponent = pActor->FindComponentByClass< USkeletalMeshComponent >();
            if ( !pSkeletalMeshComponent )
            {
                continue;
            }

            // Check SkeletalMesh Missing
            if ( pSkeletalMeshComponent->SkeletalMesh )
            {
                continue;
            }

            // Reassign SkeletalMesh
            const FString strActorName = pActor->GetActorLabel();
            if ( !kAssetNames.Contains( strActorName ) )
            {
                continue;
            } 

            const FString strAssetPath = "/Game/RLContent/" + strActorName + "/" + strActorName + "." + strActorName;
            USkeletalMesh* pSkeletalMesh = Cast< USkeletalMesh >( StaticLoadObject( USkeletalMesh::StaticClass(), NULL, *strAssetPath ) );
            pSkeletalMeshComponent->SetSkeletalMesh( pSkeletalMesh, true );
            pLevelSequencer->GetOutermost()->SetDirtyFlag( true );
            kModifiedObjects.Add( pLevelSequencer );
        }
    }
    UPackageTools::SavePackagesForObjects( kModifiedObjects );
}

void FRLLiveLinkModule::RemoveTcpCommandData()
{
    if ( m_kDataInQueue.IsEmpty() || IsRunningCommandlet() )
    {
        return;
    }
    m_kDataInQueue.RemoveAt( 0 );
    if ( m_kDataInQueue.IsEmpty() )
    {
        if ( !FRLLiveLinkUtility::IsProcessRunning( "iClone.exe" ) && m_spProgress )
        {
            m_spProgress.Get()->ExpireAndFadeout();
            m_spProgress = nullptr;
        }
    }
}

int FRLLiveLinkModule::ConvertFrameTimeFromeICloneToUnreal( int nICFrame )
{
    return FMath::CeilToInt( static_cast< float >( nICFrame ) / m_kApFps.Numerator * m_kLiveLinkFps.Numerator );
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE( FRLLiveLinkModule, RLLiveLink )