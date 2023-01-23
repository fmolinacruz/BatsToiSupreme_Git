// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CommonUser/Public/CommonSessionSubsystem.h"
#include "Engine/Classes/Engine/GameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCommonSessionSubsystem() {}
// Cross Module References
	COMMONUSER_API UEnum* Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode();
	UPackage* Z_Construct_UPackage__Script_CommonUser();
	COMMONUSER_API UClass* Z_Construct_UClass_UCommonSession_HostSessionRequest_NoRegister();
	COMMONUSER_API UClass* Z_Construct_UClass_UCommonSession_HostSessionRequest();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FPrimaryAssetId();
	COMMONUSER_API UClass* Z_Construct_UClass_UCommonSession_SearchResult_NoRegister();
	COMMONUSER_API UClass* Z_Construct_UClass_UCommonSession_SearchResult();
	COMMONUSER_API UFunction* Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature();
	COMMONUSER_API UClass* Z_Construct_UClass_UCommonSession_SearchSessionRequest_NoRegister();
	COMMONUSER_API UClass* Z_Construct_UClass_UCommonSession_SearchSessionRequest();
	COMMONUSER_API UClass* Z_Construct_UClass_UCommonSessionSubsystem_NoRegister();
	COMMONUSER_API UClass* Z_Construct_UClass_UCommonSessionSubsystem();
	ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController_NoRegister();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECommonSessionOnlineMode;
	static UEnum* ECommonSessionOnlineMode_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ECommonSessionOnlineMode.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ECommonSessionOnlineMode.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode, Z_Construct_UPackage__Script_CommonUser(), TEXT("ECommonSessionOnlineMode"));
		}
		return Z_Registration_Info_UEnum_ECommonSessionOnlineMode.OuterSingleton;
	}
	template<> COMMONUSER_API UEnum* StaticEnum<ECommonSessionOnlineMode>()
	{
		return ECommonSessionOnlineMode_StaticEnum();
	}
	struct Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode_Statics::Enumerators[] = {
		{ "ECommonSessionOnlineMode::Offline", (int64)ECommonSessionOnlineMode::Offline },
		{ "ECommonSessionOnlineMode::LAN", (int64)ECommonSessionOnlineMode::LAN },
		{ "ECommonSessionOnlineMode::Online", (int64)ECommonSessionOnlineMode::Online },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Specifies the online features and connectivity that should be used for a game session */" },
		{ "LAN.Name", "ECommonSessionOnlineMode::LAN" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "Offline.Name", "ECommonSessionOnlineMode::Offline" },
		{ "Online.Name", "ECommonSessionOnlineMode::Online" },
		{ "ToolTip", "Specifies the online features and connectivity that should be used for a game session" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_CommonUser,
		nullptr,
		"ECommonSessionOnlineMode",
		"ECommonSessionOnlineMode",
		Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode()
	{
		if (!Z_Registration_Info_UEnum_ECommonSessionOnlineMode.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECommonSessionOnlineMode.InnerSingleton, Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ECommonSessionOnlineMode.InnerSingleton;
	}
	void UCommonSession_HostSessionRequest::StaticRegisterNativesUCommonSession_HostSessionRequest()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCommonSession_HostSessionRequest);
	UClass* Z_Construct_UClass_UCommonSession_HostSessionRequest_NoRegister()
	{
		return UCommonSession_HostSessionRequest::StaticClass();
	}
	struct Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_OnlineMode_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnlineMode_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_OnlineMode;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bUseLobbies_MetaData[];
#endif
		static void NewProp_bUseLobbies_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseLobbies;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ModeNameForAdvertisement_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_ModeNameForAdvertisement;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MapID_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_MapID;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ExtraArgs_ValueProp;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ExtraArgs_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExtraArgs_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_ExtraArgs;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MaxPlayerCount_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_MaxPlayerCount;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CommonUser,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** A request object that stores the parameters used when hosting a gameplay session */" },
		{ "IncludePath", "CommonSessionSubsystem.h" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "A request object that stores the parameters used when hosting a gameplay session" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_OnlineMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_OnlineMode_MetaData[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Indicates if the session is a full online session or a different type */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Indicates if the session is a full online session or a different type" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_OnlineMode = { "OnlineMode", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCommonSession_HostSessionRequest, OnlineMode), Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode, METADATA_PARAMS(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_OnlineMode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_OnlineMode_MetaData)) }; // 215425728
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_bUseLobbies_MetaData[] = {
		{ "Category", "Session" },
		{ "Comment", "/** True if this request should create a player-hosted lobbies if available */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "True if this request should create a player-hosted lobbies if available" },
	};
#endif
	void Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_bUseLobbies_SetBit(void* Obj)
	{
		((UCommonSession_HostSessionRequest*)Obj)->bUseLobbies = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_bUseLobbies = { "bUseLobbies", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCommonSession_HostSessionRequest), &Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_bUseLobbies_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_bUseLobbies_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_bUseLobbies_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ModeNameForAdvertisement_MetaData[] = {
		{ "Category", "Session" },
		{ "Comment", "/** String used during matchmaking to specify what type of game mode this is */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "String used during matchmaking to specify what type of game mode this is" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ModeNameForAdvertisement = { "ModeNameForAdvertisement", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCommonSession_HostSessionRequest, ModeNameForAdvertisement), METADATA_PARAMS(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ModeNameForAdvertisement_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ModeNameForAdvertisement_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MapID_MetaData[] = {
		{ "AllowedTypes", "World" },
		{ "Category", "Session" },
		{ "Comment", "/** The map that will be loaded at the start of gameplay, this needs to be a valid Primary Asset top-level map */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "The map that will be loaded at the start of gameplay, this needs to be a valid Primary Asset top-level map" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MapID = { "MapID", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCommonSession_HostSessionRequest, MapID), Z_Construct_UScriptStruct_FPrimaryAssetId, METADATA_PARAMS(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MapID_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MapID_MetaData)) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ExtraArgs_ValueProp = { "ExtraArgs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 1, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ExtraArgs_Key_KeyProp = { "ExtraArgs_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ExtraArgs_MetaData[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Extra arguments passed as URL options to the game */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Extra arguments passed as URL options to the game" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ExtraArgs = { "ExtraArgs", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCommonSession_HostSessionRequest, ExtraArgs), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ExtraArgs_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ExtraArgs_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MaxPlayerCount_MetaData[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Maximum players allowed per gameplay session */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Maximum players allowed per gameplay session" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MaxPlayerCount = { "MaxPlayerCount", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCommonSession_HostSessionRequest, MaxPlayerCount), METADATA_PARAMS(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MaxPlayerCount_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MaxPlayerCount_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_OnlineMode_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_OnlineMode,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_bUseLobbies,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ModeNameForAdvertisement,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MapID,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ExtraArgs_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ExtraArgs_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_ExtraArgs,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::NewProp_MaxPlayerCount,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCommonSession_HostSessionRequest>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::ClassParams = {
		&UCommonSession_HostSessionRequest::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCommonSession_HostSessionRequest()
	{
		if (!Z_Registration_Info_UClass_UCommonSession_HostSessionRequest.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCommonSession_HostSessionRequest.OuterSingleton, Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCommonSession_HostSessionRequest.OuterSingleton;
	}
	template<> COMMONUSER_API UClass* StaticClass<UCommonSession_HostSessionRequest>()
	{
		return UCommonSession_HostSessionRequest::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCommonSession_HostSessionRequest);
	DEFINE_FUNCTION(UCommonSession_SearchResult::execGetPingInMs)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetPingInMs();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSession_SearchResult::execGetMaxPublicConnections)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetMaxPublicConnections();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSession_SearchResult::execGetNumOpenPublicConnections)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetNumOpenPublicConnections();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSession_SearchResult::execGetNumOpenPrivateConnections)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetNumOpenPrivateConnections();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSession_SearchResult::execGetIntSetting)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Key);
		P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_Value);
		P_GET_UBOOL_REF(Z_Param_Out_bFoundValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetIntSetting(Z_Param_Key,Z_Param_Out_Value,Z_Param_Out_bFoundValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSession_SearchResult::execGetStringSetting)
	{
		P_GET_PROPERTY(FNameProperty,Z_Param_Key);
		P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_Value);
		P_GET_UBOOL_REF(Z_Param_Out_bFoundValue);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetStringSetting(Z_Param_Key,Z_Param_Out_Value,Z_Param_Out_bFoundValue);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSession_SearchResult::execGetDescription)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetDescription();
		P_NATIVE_END;
	}
	void UCommonSession_SearchResult::StaticRegisterNativesUCommonSession_SearchResult()
	{
		UClass* Class = UCommonSession_SearchResult::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetDescription", &UCommonSession_SearchResult::execGetDescription },
			{ "GetIntSetting", &UCommonSession_SearchResult::execGetIntSetting },
			{ "GetMaxPublicConnections", &UCommonSession_SearchResult::execGetMaxPublicConnections },
			{ "GetNumOpenPrivateConnections", &UCommonSession_SearchResult::execGetNumOpenPrivateConnections },
			{ "GetNumOpenPublicConnections", &UCommonSession_SearchResult::execGetNumOpenPublicConnections },
			{ "GetPingInMs", &UCommonSession_SearchResult::execGetPingInMs },
			{ "GetStringSetting", &UCommonSession_SearchResult::execGetStringSetting },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics
	{
		struct CommonSession_SearchResult_eventGetDescription_Parms
		{
			FString ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSession_SearchResult_eventGetDescription_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::Function_MetaDataParams[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Returns an internal description of the session, not meant to be human readable */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Returns an internal description of the session, not meant to be human readable" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSession_SearchResult, nullptr, "GetDescription", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::CommonSession_SearchResult_eventGetDescription_Parms), Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics
	{
		struct CommonSession_SearchResult_eventGetIntSetting_Parms
		{
			FName Key;
			int32 Value;
			bool bFoundValue;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_Key;
		static const UECodeGen_Private::FIntPropertyParams NewProp_Value;
		static void NewProp_bFoundValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bFoundValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSession_SearchResult_eventGetIntSetting_Parms, Key), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSession_SearchResult_eventGetIntSetting_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::NewProp_bFoundValue_SetBit(void* Obj)
	{
		((CommonSession_SearchResult_eventGetIntSetting_Parms*)Obj)->bFoundValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::NewProp_bFoundValue = { "bFoundValue", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CommonSession_SearchResult_eventGetIntSetting_Parms), &Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::NewProp_bFoundValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::NewProp_Key,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::NewProp_Value,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::NewProp_bFoundValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::Function_MetaDataParams[] = {
		{ "Category", "Sessions" },
		{ "Comment", "/** Gets an arbitrary integer setting, bFoundValue will be false if the setting does not exist */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Gets an arbitrary integer setting, bFoundValue will be false if the setting does not exist" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSession_SearchResult, nullptr, "GetIntSetting", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::CommonSession_SearchResult_eventGetIntSetting_Parms), Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics
	{
		struct CommonSession_SearchResult_eventGetMaxPublicConnections_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSession_SearchResult_eventGetMaxPublicConnections_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::Function_MetaDataParams[] = {
		{ "Category", "Sessions" },
		{ "Comment", "/** The maximum number of publicly available connections that could be available, including already filled connections */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "The maximum number of publicly available connections that could be available, including already filled connections" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSession_SearchResult, nullptr, "GetMaxPublicConnections", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::CommonSession_SearchResult_eventGetMaxPublicConnections_Parms), Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics
	{
		struct CommonSession_SearchResult_eventGetNumOpenPrivateConnections_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSession_SearchResult_eventGetNumOpenPrivateConnections_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::Function_MetaDataParams[] = {
		{ "Category", "Sessions" },
		{ "Comment", "/** The number of private connections that are available */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "The number of private connections that are available" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSession_SearchResult, nullptr, "GetNumOpenPrivateConnections", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::CommonSession_SearchResult_eventGetNumOpenPrivateConnections_Parms), Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics
	{
		struct CommonSession_SearchResult_eventGetNumOpenPublicConnections_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSession_SearchResult_eventGetNumOpenPublicConnections_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::Function_MetaDataParams[] = {
		{ "Category", "Sessions" },
		{ "Comment", "/** The number of publicly available connections that are available */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "The number of publicly available connections that are available" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSession_SearchResult, nullptr, "GetNumOpenPublicConnections", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::CommonSession_SearchResult_eventGetNumOpenPublicConnections_Parms), Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics
	{
		struct CommonSession_SearchResult_eventGetPingInMs_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSession_SearchResult_eventGetPingInMs_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::Function_MetaDataParams[] = {
		{ "Category", "Sessions" },
		{ "Comment", "/** Ping to the search result, MAX_QUERY_PING is unreachable */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Ping to the search result, MAX_QUERY_PING is unreachable" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSession_SearchResult, nullptr, "GetPingInMs", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::CommonSession_SearchResult_eventGetPingInMs_Parms), Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics
	{
		struct CommonSession_SearchResult_eventGetStringSetting_Parms
		{
			FName Key;
			FString Value;
			bool bFoundValue;
		};
		static const UECodeGen_Private::FNamePropertyParams NewProp_Key;
		static const UECodeGen_Private::FStrPropertyParams NewProp_Value;
		static void NewProp_bFoundValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bFoundValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSession_SearchResult_eventGetStringSetting_Parms, Key), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSession_SearchResult_eventGetStringSetting_Parms, Value), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::NewProp_bFoundValue_SetBit(void* Obj)
	{
		((CommonSession_SearchResult_eventGetStringSetting_Parms*)Obj)->bFoundValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::NewProp_bFoundValue = { "bFoundValue", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(CommonSession_SearchResult_eventGetStringSetting_Parms), &Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::NewProp_bFoundValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::NewProp_Key,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::NewProp_Value,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::NewProp_bFoundValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::Function_MetaDataParams[] = {
		{ "Category", "Sessions" },
		{ "Comment", "/** Gets an arbitrary string setting, bFoundValue will be false if the setting does not exist */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Gets an arbitrary string setting, bFoundValue will be false if the setting does not exist" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSession_SearchResult, nullptr, "GetStringSetting", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::CommonSession_SearchResult_eventGetStringSetting_Parms), Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCommonSession_SearchResult);
	UClass* Z_Construct_UClass_UCommonSession_SearchResult_NoRegister()
	{
		return UCommonSession_SearchResult::StaticClass();
	}
	struct Z_Construct_UClass_UCommonSession_SearchResult_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCommonSession_SearchResult_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CommonUser,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCommonSession_SearchResult_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCommonSession_SearchResult_GetDescription, "GetDescription" }, // 2061285012
		{ &Z_Construct_UFunction_UCommonSession_SearchResult_GetIntSetting, "GetIntSetting" }, // 376373752
		{ &Z_Construct_UFunction_UCommonSession_SearchResult_GetMaxPublicConnections, "GetMaxPublicConnections" }, // 793585160
		{ &Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPrivateConnections, "GetNumOpenPrivateConnections" }, // 216673741
		{ &Z_Construct_UFunction_UCommonSession_SearchResult_GetNumOpenPublicConnections, "GetNumOpenPublicConnections" }, // 415406763
		{ &Z_Construct_UFunction_UCommonSession_SearchResult_GetPingInMs, "GetPingInMs" }, // 4157205568
		{ &Z_Construct_UFunction_UCommonSession_SearchResult_GetStringSetting, "GetStringSetting" }, // 1127074361
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_SearchResult_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** A result object returned from the online system that describes a joinable game session */" },
		{ "IncludePath", "CommonSessionSubsystem.h" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "A result object returned from the online system that describes a joinable game session" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCommonSession_SearchResult_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCommonSession_SearchResult>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCommonSession_SearchResult_Statics::ClassParams = {
		&UCommonSession_SearchResult::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCommonSession_SearchResult_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_SearchResult_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCommonSession_SearchResult()
	{
		if (!Z_Registration_Info_UClass_UCommonSession_SearchResult.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCommonSession_SearchResult.OuterSingleton, Z_Construct_UClass_UCommonSession_SearchResult_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCommonSession_SearchResult.OuterSingleton;
	}
	template<> COMMONUSER_API UClass* StaticClass<UCommonSession_SearchResult>()
	{
		return UCommonSession_SearchResult::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCommonSession_SearchResult);
	struct Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics
	{
		struct _Script_CommonUser_eventCommonSession_FindSessionsFinishedDynamic_Parms
		{
			bool bSucceeded;
			FText ErrorMessage;
		};
		static void NewProp_bSucceeded_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSucceeded;
		static const UECodeGen_Private::FTextPropertyParams NewProp_ErrorMessage;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::NewProp_bSucceeded_SetBit(void* Obj)
	{
		((_Script_CommonUser_eventCommonSession_FindSessionsFinishedDynamic_Parms*)Obj)->bSucceeded = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::NewProp_bSucceeded = { "bSucceeded", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(_Script_CommonUser_eventCommonSession_FindSessionsFinishedDynamic_Parms), &Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::NewProp_bSucceeded_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FTextPropertyParams Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::NewProp_ErrorMessage = { "ErrorMessage", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(_Script_CommonUser_eventCommonSession_FindSessionsFinishedDynamic_Parms, ErrorMessage), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::NewProp_bSucceeded,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::NewProp_ErrorMessage,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_CommonUser, nullptr, "CommonSession_FindSessionsFinishedDynamic__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::_Script_CommonUser_eventCommonSession_FindSessionsFinishedDynamic_Parms), Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00130000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	void UCommonSession_SearchSessionRequest::StaticRegisterNativesUCommonSession_SearchSessionRequest()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCommonSession_SearchSessionRequest);
	UClass* Z_Construct_UClass_UCommonSession_SearchSessionRequest_NoRegister()
	{
		return UCommonSession_SearchSessionRequest::StaticClass();
	}
	struct Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const UECodeGen_Private::FBytePropertyParams NewProp_OnlineMode_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OnlineMode_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_OnlineMode;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_bUseLobbies_MetaData[];
#endif
		static void NewProp_bUseLobbies_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseLobbies;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Results_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Results_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_Results;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_K2_OnSearchFinished_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_K2_OnSearchFinished;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_CommonUser,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Request object describing a session search, this object will be updated once the search has completed */" },
		{ "IncludePath", "CommonSessionSubsystem.h" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Request object describing a session search, this object will be updated once the search has completed" },
	};
#endif
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_OnlineMode_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_OnlineMode_MetaData[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Indicates if the this is looking for full online games or a different type like LAN */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Indicates if the this is looking for full online games or a different type like LAN" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_OnlineMode = { "OnlineMode", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCommonSession_SearchSessionRequest, OnlineMode), Z_Construct_UEnum_CommonUser_ECommonSessionOnlineMode, METADATA_PARAMS(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_OnlineMode_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_OnlineMode_MetaData)) }; // 215425728
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_bUseLobbies_MetaData[] = {
		{ "Category", "Session" },
		{ "Comment", "/** True if this request should look for player-hosted lobbies if they are available, false will only search for registered server sessions */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "True if this request should look for player-hosted lobbies if they are available, false will only search for registered server sessions" },
	};
#endif
	void Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_bUseLobbies_SetBit(void* Obj)
	{
		((UCommonSession_SearchSessionRequest*)Obj)->bUseLobbies = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_bUseLobbies = { "bUseLobbies", nullptr, (EPropertyFlags)0x0010000000000004, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(UCommonSession_SearchSessionRequest), &Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_bUseLobbies_SetBit, METADATA_PARAMS(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_bUseLobbies_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_bUseLobbies_MetaData)) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_Results_Inner = { "Results", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UClass_UCommonSession_SearchResult_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_Results_MetaData[] = {
		{ "Category", "Session" },
		{ "Comment", "/** List of all found sessions, will be valid when OnSearchFinished is called */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "List of all found sessions, will be valid when OnSearchFinished is called" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_Results = { "Results", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCommonSession_SearchSessionRequest, Results), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_Results_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_Results_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_K2_OnSearchFinished_MetaData[] = {
		{ "AllowPrivateAccess", "TRUE" },
		{ "Category", "Events" },
		{ "Comment", "/** Delegate called when a session search completes */" },
		{ "DisplayName", "On Search Finished" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Delegate called when a session search completes" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_K2_OnSearchFinished = { "K2_OnSearchFinished", nullptr, (EPropertyFlags)0x0040000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UCommonSession_SearchSessionRequest, K2_OnSearchFinished), Z_Construct_UDelegateFunction_CommonUser_CommonSession_FindSessionsFinishedDynamic__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_K2_OnSearchFinished_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_K2_OnSearchFinished_MetaData)) }; // 2770378033
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_OnlineMode_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_OnlineMode,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_bUseLobbies,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_Results_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_Results,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::NewProp_K2_OnSearchFinished,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCommonSession_SearchSessionRequest>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::ClassParams = {
		&UCommonSession_SearchSessionRequest::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCommonSession_SearchSessionRequest()
	{
		if (!Z_Registration_Info_UClass_UCommonSession_SearchSessionRequest.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCommonSession_SearchSessionRequest.OuterSingleton, Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCommonSession_SearchSessionRequest.OuterSingleton;
	}
	template<> COMMONUSER_API UClass* StaticClass<UCommonSession_SearchSessionRequest>()
	{
		return UCommonSession_SearchSessionRequest::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCommonSession_SearchSessionRequest);
	DEFINE_FUNCTION(UCommonSessionSubsystem::execCleanUpSessions)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->CleanUpSessions();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSessionSubsystem::execFindSessions)
	{
		P_GET_OBJECT(APlayerController,Z_Param_SearchingPlayer);
		P_GET_OBJECT(UCommonSession_SearchSessionRequest,Z_Param_Request);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->FindSessions(Z_Param_SearchingPlayer,Z_Param_Request);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSessionSubsystem::execJoinSession)
	{
		P_GET_OBJECT(APlayerController,Z_Param_JoiningPlayer);
		P_GET_OBJECT(UCommonSession_SearchResult,Z_Param_Request);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->JoinSession(Z_Param_JoiningPlayer,Z_Param_Request);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSessionSubsystem::execQuickPlaySession)
	{
		P_GET_OBJECT(APlayerController,Z_Param_JoiningOrHostingPlayer);
		P_GET_OBJECT(UCommonSession_HostSessionRequest,Z_Param_Request);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->QuickPlaySession(Z_Param_JoiningOrHostingPlayer,Z_Param_Request);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSessionSubsystem::execHostSession)
	{
		P_GET_OBJECT(APlayerController,Z_Param_HostingPlayer);
		P_GET_OBJECT(UCommonSession_HostSessionRequest,Z_Param_Request);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->HostSession(Z_Param_HostingPlayer,Z_Param_Request);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSessionSubsystem::execCreateOnlineSearchSessionRequest)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UCommonSession_SearchSessionRequest**)Z_Param__Result=P_THIS->CreateOnlineSearchSessionRequest();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UCommonSessionSubsystem::execCreateOnlineHostSessionRequest)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UCommonSession_HostSessionRequest**)Z_Param__Result=P_THIS->CreateOnlineHostSessionRequest();
		P_NATIVE_END;
	}
	void UCommonSessionSubsystem::StaticRegisterNativesUCommonSessionSubsystem()
	{
		UClass* Class = UCommonSessionSubsystem::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "CleanUpSessions", &UCommonSessionSubsystem::execCleanUpSessions },
			{ "CreateOnlineHostSessionRequest", &UCommonSessionSubsystem::execCreateOnlineHostSessionRequest },
			{ "CreateOnlineSearchSessionRequest", &UCommonSessionSubsystem::execCreateOnlineSearchSessionRequest },
			{ "FindSessions", &UCommonSessionSubsystem::execFindSessions },
			{ "HostSession", &UCommonSessionSubsystem::execHostSession },
			{ "JoinSession", &UCommonSessionSubsystem::execJoinSession },
			{ "QuickPlaySession", &UCommonSessionSubsystem::execQuickPlaySession },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UCommonSessionSubsystem_CleanUpSessions_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSessionSubsystem_CleanUpSessions_Statics::Function_MetaDataParams[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Clean up any active sessions, called from cases like returning to the main menu */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Clean up any active sessions, called from cases like returning to the main menu" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSessionSubsystem_CleanUpSessions_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSessionSubsystem, nullptr, "CleanUpSessions", nullptr, nullptr, 0, nullptr, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSessionSubsystem_CleanUpSessions_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_CleanUpSessions_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSessionSubsystem_CleanUpSessions()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSessionSubsystem_CleanUpSessions_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics
	{
		struct CommonSessionSubsystem_eventCreateOnlineHostSessionRequest_Parms
		{
			UCommonSession_HostSessionRequest* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventCreateOnlineHostSessionRequest_Parms, ReturnValue), Z_Construct_UClass_UCommonSession_HostSessionRequest_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::Function_MetaDataParams[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Creates a host session request with default options for online games, this can be modified after creation */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Creates a host session request with default options for online games, this can be modified after creation" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSessionSubsystem, nullptr, "CreateOnlineHostSessionRequest", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::CommonSessionSubsystem_eventCreateOnlineHostSessionRequest_Parms), Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics
	{
		struct CommonSessionSubsystem_eventCreateOnlineSearchSessionRequest_Parms
		{
			UCommonSession_SearchSessionRequest* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventCreateOnlineSearchSessionRequest_Parms, ReturnValue), Z_Construct_UClass_UCommonSession_SearchSessionRequest_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::Function_MetaDataParams[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Creates a session search object with default options to look for default online games, this can be modified after creation */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Creates a session search object with default options to look for default online games, this can be modified after creation" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSessionSubsystem, nullptr, "CreateOnlineSearchSessionRequest", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::CommonSessionSubsystem_eventCreateOnlineSearchSessionRequest_Parms), Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics
	{
		struct CommonSessionSubsystem_eventFindSessions_Parms
		{
			APlayerController* SearchingPlayer;
			UCommonSession_SearchSessionRequest* Request;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SearchingPlayer;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Request;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::NewProp_SearchingPlayer = { "SearchingPlayer", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventFindSessions_Parms, SearchingPlayer), Z_Construct_UClass_APlayerController_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::NewProp_Request = { "Request", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventFindSessions_Parms, Request), Z_Construct_UClass_UCommonSession_SearchSessionRequest_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::NewProp_SearchingPlayer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::NewProp_Request,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::Function_MetaDataParams[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Queries online system for the list of joinable sessions matching the search request */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Queries online system for the list of joinable sessions matching the search request" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSessionSubsystem, nullptr, "FindSessions", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::CommonSessionSubsystem_eventFindSessions_Parms), Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics
	{
		struct CommonSessionSubsystem_eventHostSession_Parms
		{
			APlayerController* HostingPlayer;
			UCommonSession_HostSessionRequest* Request;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_HostingPlayer;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Request;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::NewProp_HostingPlayer = { "HostingPlayer", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventHostSession_Parms, HostingPlayer), Z_Construct_UClass_APlayerController_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::NewProp_Request = { "Request", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventHostSession_Parms, Request), Z_Construct_UClass_UCommonSession_HostSessionRequest_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::NewProp_HostingPlayer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::NewProp_Request,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::Function_MetaDataParams[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Creates a new online game using the session request information, if successful this will start a hard map transfer */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Creates a new online game using the session request information, if successful this will start a hard map transfer" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSessionSubsystem, nullptr, "HostSession", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::CommonSessionSubsystem_eventHostSession_Parms), Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSessionSubsystem_HostSession()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSessionSubsystem_HostSession_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics
	{
		struct CommonSessionSubsystem_eventJoinSession_Parms
		{
			APlayerController* JoiningPlayer;
			UCommonSession_SearchResult* Request;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_JoiningPlayer;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Request;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::NewProp_JoiningPlayer = { "JoiningPlayer", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventJoinSession_Parms, JoiningPlayer), Z_Construct_UClass_APlayerController_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::NewProp_Request = { "Request", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventJoinSession_Parms, Request), Z_Construct_UClass_UCommonSession_SearchResult_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::NewProp_JoiningPlayer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::NewProp_Request,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::Function_MetaDataParams[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Starts process to join an existing session, if successful this will connect to the specified server */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Starts process to join an existing session, if successful this will connect to the specified server" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSessionSubsystem, nullptr, "JoinSession", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::CommonSessionSubsystem_eventJoinSession_Parms), Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics
	{
		struct CommonSessionSubsystem_eventQuickPlaySession_Parms
		{
			APlayerController* JoiningOrHostingPlayer;
			UCommonSession_HostSessionRequest* Request;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_JoiningOrHostingPlayer;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Request;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::NewProp_JoiningOrHostingPlayer = { "JoiningOrHostingPlayer", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventQuickPlaySession_Parms, JoiningOrHostingPlayer), Z_Construct_UClass_APlayerController_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::NewProp_Request = { "Request", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(CommonSessionSubsystem_eventQuickPlaySession_Parms, Request), Z_Construct_UClass_UCommonSession_HostSessionRequest_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::NewProp_JoiningOrHostingPlayer,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::NewProp_Request,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::Function_MetaDataParams[] = {
		{ "Category", "Session" },
		{ "Comment", "/** Starts a process to look for existing sessions or create a new one if no viable sessions are found */" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Starts a process to look for existing sessions or create a new one if no viable sessions are found" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UCommonSessionSubsystem, nullptr, "QuickPlaySession", nullptr, nullptr, sizeof(Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::CommonSessionSubsystem_eventQuickPlaySession_Parms), Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020400, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UCommonSessionSubsystem);
	UClass* Z_Construct_UClass_UCommonSessionSubsystem_NoRegister()
	{
		return UCommonSessionSubsystem::StaticClass();
	}
	struct Z_Construct_UClass_UCommonSessionSubsystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCommonSessionSubsystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_CommonUser,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UCommonSessionSubsystem_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UCommonSessionSubsystem_CleanUpSessions, "CleanUpSessions" }, // 3792557978
		{ &Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineHostSessionRequest, "CreateOnlineHostSessionRequest" }, // 3945123387
		{ &Z_Construct_UFunction_UCommonSessionSubsystem_CreateOnlineSearchSessionRequest, "CreateOnlineSearchSessionRequest" }, // 1589544968
		{ &Z_Construct_UFunction_UCommonSessionSubsystem_FindSessions, "FindSessions" }, // 3366590441
		{ &Z_Construct_UFunction_UCommonSessionSubsystem_HostSession, "HostSession" }, // 1172269049
		{ &Z_Construct_UFunction_UCommonSessionSubsystem_JoinSession, "JoinSession" }, // 208448601
		{ &Z_Construct_UFunction_UCommonSessionSubsystem_QuickPlaySession, "QuickPlaySession" }, // 180736470
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCommonSessionSubsystem_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/** \n * Game subsystem that handles requests for hosting and joining online games.\n * One subsystem is created for each game instance and can be accessed from blueprints or C++ code.\n * If a game-specific subclass exists, this base subsystem will not be created.\n */" },
		{ "IncludePath", "CommonSessionSubsystem.h" },
		{ "ModuleRelativePath", "Public/CommonSessionSubsystem.h" },
		{ "ToolTip", "Game subsystem that handles requests for hosting and joining online games.\nOne subsystem is created for each game instance and can be accessed from blueprints or C++ code.\nIf a game-specific subclass exists, this base subsystem will not be created." },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCommonSessionSubsystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCommonSessionSubsystem>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UCommonSessionSubsystem_Statics::ClassParams = {
		&UCommonSessionSubsystem::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCommonSessionSubsystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCommonSessionSubsystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCommonSessionSubsystem()
	{
		if (!Z_Registration_Info_UClass_UCommonSessionSubsystem.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UCommonSessionSubsystem.OuterSingleton, Z_Construct_UClass_UCommonSessionSubsystem_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UCommonSessionSubsystem.OuterSingleton;
	}
	template<> COMMONUSER_API UClass* StaticClass<UCommonSessionSubsystem>()
	{
		return UCommonSessionSubsystem::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCommonSessionSubsystem);
	struct Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_Statics::EnumInfo[] = {
		{ ECommonSessionOnlineMode_StaticEnum, TEXT("ECommonSessionOnlineMode"), &Z_Registration_Info_UEnum_ECommonSessionOnlineMode, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 215425728U) },
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UCommonSession_HostSessionRequest, UCommonSession_HostSessionRequest::StaticClass, TEXT("UCommonSession_HostSessionRequest"), &Z_Registration_Info_UClass_UCommonSession_HostSessionRequest, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonSession_HostSessionRequest), 184602280U) },
		{ Z_Construct_UClass_UCommonSession_SearchResult, UCommonSession_SearchResult::StaticClass, TEXT("UCommonSession_SearchResult"), &Z_Registration_Info_UClass_UCommonSession_SearchResult, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonSession_SearchResult), 3613704478U) },
		{ Z_Construct_UClass_UCommonSession_SearchSessionRequest, UCommonSession_SearchSessionRequest::StaticClass, TEXT("UCommonSession_SearchSessionRequest"), &Z_Registration_Info_UClass_UCommonSession_SearchSessionRequest, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonSession_SearchSessionRequest), 1483104135U) },
		{ Z_Construct_UClass_UCommonSessionSubsystem, UCommonSessionSubsystem::StaticClass, TEXT("UCommonSessionSubsystem"), &Z_Registration_Info_UClass_UCommonSessionSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UCommonSessionSubsystem), 1910292466U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_316383280(TEXT("/Script/CommonUser"),
		Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_Statics::ClassInfo),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
