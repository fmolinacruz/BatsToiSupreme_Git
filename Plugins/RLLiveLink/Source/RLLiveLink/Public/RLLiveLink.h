// Copyright 2022 The Reallusion Authors. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Templates/SharedPointer.h"
#include "Engine/EngineTypes.h"
#include "Widgets/SWidget.h"
/// Tcp Connection
#include "Modules/ModuleManager.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4SubnetMask.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Interfaces/IPv4/IPv4Endpoint.h"
#include "Interfaces/IPv4/IPv4Subnet.h"
#include "Interfaces/Steam/SteamEndpoint.h"
#include "Interfaces/INetworkingModule.h"
#include "Common/TcpSocketBuilder.h"
#include "Common/TcpListener.h"
#include "HAL/ThreadSafeBool.h"

#include "Engine/MeshMerging.h"

class FJsonValue;
class FToolBarBuilder;
class FMenuBuilder;
class UBlueprint;
class UTexture2D;

struct FMergeComponentData
{
    FMergeComponentData( UPrimitiveComponent* InPrimComponent )
        : PrimComponent( InPrimComponent )
        , bShouldIncorporate( true )
    {
    }

    /** Component extracted from selected actors */
    TWeakObjectPtr<UPrimitiveComponent> PrimComponent;
    /** Flag determining whether or not this component should be incorporated into the merge */
    bool bShouldIncorporate;
};

struct ExportFbxSetting 
{
    UObject* pObjectToExport;
    FString strSaveFilePath;
};

class CSceneTempData
{
    public:
        FString strAssetName;
        FTransform kTransform;
        AActor* pParentActor;
        FString strFolderName;
        bool bPilotTarget;
};

enum class ETransferMode : int
{
    Merge,
    Simplify,
    BatchMerge,
    BatchSimplify,
    Batch
};
class FRLLiveLinkModule : public IModuleInterface, public FRunnable
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

    // Begin FRunnable Interface
    virtual bool Init() override { return true; }
    virtual uint32 Run() override;
    void Start();
    virtual void Stop() override;
    virtual void Exit() override {}
    // End FRunnable Interface

    void HandleReceivedData( TSharedPtr<TArray<uint8>, ESPMode::ThreadSafe> spReceivedData );

private:
    void InitSocket();
    FString GetCommandletExePath();

    void ProcessObjectData( const TSharedPtr<FJsonValue>& spJsonValue, bool bPlaceAsset );
    void ProcessCameraData( const TSharedPtr<FJsonValue>& spJsonValue, bool bPlaceAsset );
    void ProcessLightData( const TSharedPtr<FJsonValue>& spJsonValue, bool bPlaceAsset );
    void ProcessRequireFromIC( const TSharedPtr<FJsonValue>& spJsonValue );
    void CheckAndDeleteDuplicatedAsset( const TSharedPtr<FJsonValue>& spJsonValue );
    void CheckSkeletonAssetExist( const TSharedPtr<FJsonValue>& spJsonValue );
    void CheckAssetExist( const TSharedPtr<FJsonValue>& spJsonValue );
    void CheckICVersion( const TSharedPtr< FJsonValue >& spJsonValue );

    void CreateEmptyNodeForiClone();
    void CreateCamera();
    void CreateCineCamera();
    void CreateDirectionalLight();
    void CreateSpotLight();
    void CreatePointLight();
    void CreateRectLight();
    void SetUpAllCharacterToBlueprint();
    void SetUpAllCameraToBlueprint();
    void SetUpAllLightToBlueprint();
    bool SetupCineCamera( UBlueprint* pCameraBlueprint );
    void LiveLinkHelpMenu( FString strWebID );

    void AddToolBar( FToolBarBuilder& kBuilder );
    bool BuildBlueprint( const FString& strAssetFolder, const FString& strAssetName, bool bToScene = true );
    TSharedRef<SWidget> FillComboButton( TSharedPtr<class FUICommandList> Commands );

    bool DeleteFolder( const FString& strPath );
    bool DeleteActorInScene( const FString& strPath, const FString& strTargetName );
    AActor* PutAssetBackToSceneAfterReplace( UBlueprint* pBlueprint );

    UBlueprint* CreateLiveLinkBlueprint( const FString& strPath,
                                         const FString& strSource,
                                         const FString& strSubjectName,
                                         bool bCheckSerialNumber );
    UBlueprint* CreateLiveLinkBlueprintFromActor( AActor* pActor,
                                                  const FString& strPath,
                                                  const FString& strSource,
                                                  const FString& strSubjectName,
                                                  const FString& strDataText = "LiveLinkCode" );
    TArray<AActor*> GetSelectedActorByType( const FString& strType );
    void SetDefaultParentActor( AActor* pActor, FAttachmentTransformRules eAttachmentRules );
    bool CheckPluginInstalled( const FString& strPluginName );
    void SelectAndFocusActor( AActor* pActor, bool bFocus, bool bSelect );
    UTexture2D* LoadTextureFromFile( const FString& strPath, const FString& strSaveAssetPath );
    UTextureLightProfile* LoadTextureLightProfileFromFile( const FString& strPath, const FString& strSaveAssetPath );
    AActor* LoadToScene( UBlueprint* pBlueprint );

    UTexture2D* RotateTexture2D( UTexture2D* pTexture );

    // wrinkle BP setup
    bool BuildWrinkleBlueprint( const FString& strRootGamePath, USkeletalMesh* pMesh );
    bool ReAssignAnimationBlueprintSkeleton( UAnimBlueprint* pAnimBlueprint, USkeleton* pSkeleton );

    //Transfer Scene to IC
    void TransferSceneToIC( ETransferMode iMode = ETransferMode::Merge );
    void CheckICVersionBeforeTransferScene( const ETransferMode iMode );
    bool BatchTransferSceneToIClone( ETransferMode iMergeMode, TSet<UStaticMesh*>& kStaticMeshList );
    bool CheckAssetExist( const FString& strAssetPath );
    bool RunMergeFromSelection( ETransferMode iMergeMode, FString& strPackageName );
    bool RunSimplify( const FString& strPackageName, const TArray<TSharedPtr<FMergeComponentData>>& kSelectedComponents );
    void BuildActorsListFromMergeComponentsData( const TArray<TSharedPtr<FMergeComponentData>>& InComponentsData, TArray<AActor*>& OutActors, TArray<ULevel*>* OutLevels /* = nullptr */ );
    bool RunMerge( const FString& strPackageName, const TArray<TSharedPtr<FMergeComponentData>>& kSelectedComponents );
    bool GetPackageNameForMergeAction( const FString& strDefaultPackageName, FString& strOutPackageName );
    bool BuildMergeComponentDataFromSelection( TArray<TSharedPtr<FMergeComponentData>>& kOutComponentsData );
    bool HasAtLeastOneStaticMesh( const TArray<TSharedPtr<FMergeComponentData>>& kComponentsData );
    FString GetDefaultPackageName() const;
    bool ExportFbx( const struct ExportFbxSetting& kExportFbxSetting );
    bool ExportFbx( const TArray<struct ExportFbxSetting>& kExportFbxSettings );
    bool ExportAssetsInternal( const TArray<struct ExportFbxSetting>& kExportFbxSettings, bool bPromptIndividualFilenames = true ) const;
    bool ExportSelected( const FString& strSaveFilePath );
    void EditorGetUnderlyingActors( AActor* pActor, TSet<AActor*>& kOutUnderlyingActors ) const;
    bool DeletePackageInContentBrowser( const FString& strPath );

    void SendJsonToIC( const TSharedPtr<FJsonObject>& spReturnJson );

    //for outliner and viewport right click
    void AddMenuEntryInRightClick();
    TSharedRef<FExtender> OutlinerMenuExtend( const TSharedRef<FUICommandList> CommandList, const TArray<AActor*> Actors );
    void FillTransferSceneMenu( FMenuBuilder& kMenuBuilder );

    void GetObjectsFromPackage( const FARFilter& kFilter, TArray<FAssetData>& kObjectList, const FARFilter& kIgnoreObjectFilter );
    bool DeleteAssets( const TArray<FAssetData>& kObjectList );

    void ProcessAvatarMotionNameAndPath( const FString& strAssetPath, const FString& strAssetName );
    void ProcessPropMotionNameAndPath( const FString& strAssetPath, const FString& strAssetName );
    void MoveAsset( const FString& strFromAssetPath, const FString& strToAssetPath );
    void MoveMotionAssetPath( const TSharedPtr<FJsonValue>& spJsonValue, bool bIsProp );
    void ReAssignMotionSkeleton( const FString& strCurrentPath );

#if ENGINE_MAJOR_VERSION <= 4
    void ReplaceMissingSkeleton( const TArray<UObject*>& kAnimAssetsToRetarget, UObject* kSkeletonAsset ) const;
#else
    void ReplaceMissingSkeleton( const TArray<TObjectPtr<UObject>>& kAnimAssetsToRetarget, const TObjectPtr<UObject>& kSkeletonAsset ) const;
#endif
    bool DeselectNonStaticMeshActors( TSet<AActor*>& kDeselectedActors );
    void RenameAsset( UObject* pAsset, const FString& strNewAssetName );
private:
    FString m_strCurUProjectPath;
    FString m_strCurEngineCmdexePath;
    TSharedPtr< class FUICommandList > m_kPluginCommands;

    FIPv4Address m_kDeviceIPAddr = FIPv4Address::Any;
    uint32 m_uDevicePort = 54322;
    ISocketSubsystem* m_pSocketSubsystem;
    FRunnableThread* m_pThread;
    FString m_strThreadName;
    FTimespan m_kWaitTime;
    FThreadSafeBool m_bStopping = false;
    // Buffer to receive socket data into
    TArray<uint8> m_kRecvBuffer;

    // Tcp Server
    FSocket* m_pListenerSocket;
    FSocket* m_pConnectionSocket;
    FIPv4Endpoint m_kRemoteAddressForConnection;

    // Blueprint file name
    FString m_strCineCameraBlueprint = "";
    FString m_strCharacterBlueprint  = "";
    FString m_strPointLightBlueprint = "";
    FString m_strDirLightBlueprint   = "";
    FString m_strSpotLightBlueprint  = "";
    FString m_strRectLightBlueprint = "";

    // Save Asset Data In Scene
    TArray< CSceneTempData > m_kAssetTempData;

    ////Transfer Scene to IC
    FTimerHandle m_kCountdownRecheckICVersionTimerHandle;
    ETransferMode m_iMergeMode = ETransferMode::Merge;
    //merge actors
    FMeshMergingSettings m_kMeshMergeSettings;
    FMeshProxySettings m_kMeshProxySetting; // simplify
    bool bReplaceSourceActors = false;

};