// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "CommonUser/Public/CommonUserTypes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCommonUserTypes() {}
// Cross Module References
	COMMONUSER_API UEnum* Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext();
	UPackage* Z_Construct_UPackage__Script_CommonUser();
	COMMONUSER_API UEnum* Z_Construct_UEnum_CommonUser_ECommonUserInitializationState();
	COMMONUSER_API UEnum* Z_Construct_UEnum_CommonUser_ECommonUserPrivilege();
	COMMONUSER_API UEnum* Z_Construct_UEnum_CommonUser_ECommonUserAvailability();
	COMMONUSER_API UEnum* Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult();
// End Cross Module References
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECommonUserOnlineContext;
	static UEnum* ECommonUserOnlineContext_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserOnlineContext.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ECommonUserOnlineContext.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext, Z_Construct_UPackage__Script_CommonUser(), TEXT("ECommonUserOnlineContext"));
		}
		return Z_Registration_Info_UEnum_ECommonUserOnlineContext.OuterSingleton;
	}
	template<> COMMONUSER_API UEnum* StaticEnum<ECommonUserOnlineContext>()
	{
		return ECommonUserOnlineContext_StaticEnum();
	}
	struct Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext_Statics::Enumerators[] = {
		{ "ECommonUserOnlineContext::Game", (int64)ECommonUserOnlineContext::Game },
		{ "ECommonUserOnlineContext::Default", (int64)ECommonUserOnlineContext::Default },
		{ "ECommonUserOnlineContext::Service", (int64)ECommonUserOnlineContext::Service },
		{ "ECommonUserOnlineContext::ServiceOrDefault", (int64)ECommonUserOnlineContext::ServiceOrDefault },
		{ "ECommonUserOnlineContext::Platform", (int64)ECommonUserOnlineContext::Platform },
		{ "ECommonUserOnlineContext::PlatformOrDefault", (int64)ECommonUserOnlineContext::PlatformOrDefault },
		{ "ECommonUserOnlineContext::Invalid", (int64)ECommonUserOnlineContext::Invalid },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Enum specifying where and how to run online queries */" },
		{ "Default.Comment", "/** The default engine online system, this will always exist and will be the same as either Service or Platform */" },
		{ "Default.Name", "ECommonUserOnlineContext::Default" },
		{ "Default.ToolTip", "The default engine online system, this will always exist and will be the same as either Service or Platform" },
		{ "Game.Comment", "/** Called from game code, this uses the default system but with special handling that could merge results from multiple contexts */" },
		{ "Game.Name", "ECommonUserOnlineContext::Game" },
		{ "Game.ToolTip", "Called from game code, this uses the default system but with special handling that could merge results from multiple contexts" },
		{ "Invalid.Comment", "/** Invalid system */" },
		{ "Invalid.Name", "ECommonUserOnlineContext::Invalid" },
		{ "Invalid.ToolTip", "Invalid system" },
		{ "ModuleRelativePath", "Public/CommonUserTypes.h" },
		{ "Platform.Comment", "/** Explicitly ask for the platform system, which may not exist */" },
		{ "Platform.Name", "ECommonUserOnlineContext::Platform" },
		{ "Platform.ToolTip", "Explicitly ask for the platform system, which may not exist" },
		{ "PlatformOrDefault.Comment", "/** Looks for platform system first, then falls back to default */" },
		{ "PlatformOrDefault.Name", "ECommonUserOnlineContext::PlatformOrDefault" },
		{ "PlatformOrDefault.ToolTip", "Looks for platform system first, then falls back to default" },
		{ "Service.Comment", "/** Explicitly ask for the external service, which may not exist */" },
		{ "Service.Name", "ECommonUserOnlineContext::Service" },
		{ "Service.ToolTip", "Explicitly ask for the external service, which may not exist" },
		{ "ServiceOrDefault.Comment", "/** Looks for external service first, then falls back to default */" },
		{ "ServiceOrDefault.Name", "ECommonUserOnlineContext::ServiceOrDefault" },
		{ "ServiceOrDefault.ToolTip", "Looks for external service first, then falls back to default" },
		{ "ToolTip", "Enum specifying where and how to run online queries" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_CommonUser,
		nullptr,
		"ECommonUserOnlineContext",
		"ECommonUserOnlineContext",
		Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserOnlineContext.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECommonUserOnlineContext.InnerSingleton, Z_Construct_UEnum_CommonUser_ECommonUserOnlineContext_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ECommonUserOnlineContext.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECommonUserInitializationState;
	static UEnum* ECommonUserInitializationState_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserInitializationState.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ECommonUserInitializationState.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CommonUser_ECommonUserInitializationState, Z_Construct_UPackage__Script_CommonUser(), TEXT("ECommonUserInitializationState"));
		}
		return Z_Registration_Info_UEnum_ECommonUserInitializationState.OuterSingleton;
	}
	template<> COMMONUSER_API UEnum* StaticEnum<ECommonUserInitializationState>()
	{
		return ECommonUserInitializationState_StaticEnum();
	}
	struct Z_Construct_UEnum_CommonUser_ECommonUserInitializationState_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_CommonUser_ECommonUserInitializationState_Statics::Enumerators[] = {
		{ "ECommonUserInitializationState::Unknown", (int64)ECommonUserInitializationState::Unknown },
		{ "ECommonUserInitializationState::DoingInitialLogin", (int64)ECommonUserInitializationState::DoingInitialLogin },
		{ "ECommonUserInitializationState::DoingNetworkLogin", (int64)ECommonUserInitializationState::DoingNetworkLogin },
		{ "ECommonUserInitializationState::FailedtoLogin", (int64)ECommonUserInitializationState::FailedtoLogin },
		{ "ECommonUserInitializationState::LoggedInOnline", (int64)ECommonUserInitializationState::LoggedInOnline },
		{ "ECommonUserInitializationState::LoggedInLocalOnly", (int64)ECommonUserInitializationState::LoggedInLocalOnly },
		{ "ECommonUserInitializationState::Invalid", (int64)ECommonUserInitializationState::Invalid },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_CommonUser_ECommonUserInitializationState_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/** Enum describing the state of initialization for a specific user */" },
		{ "DoingInitialLogin.Comment", "/** Player is in the process of acquiring a user id with local login */" },
		{ "DoingInitialLogin.Name", "ECommonUserInitializationState::DoingInitialLogin" },
		{ "DoingInitialLogin.ToolTip", "Player is in the process of acquiring a user id with local login" },
		{ "DoingNetworkLogin.Comment", "/** Player is performing the network login, they have already logged in locally */" },
		{ "DoingNetworkLogin.Name", "ECommonUserInitializationState::DoingNetworkLogin" },
		{ "DoingNetworkLogin.ToolTip", "Player is performing the network login, they have already logged in locally" },
		{ "FailedtoLogin.Comment", "/** Player failed to log in at all */" },
		{ "FailedtoLogin.Name", "ECommonUserInitializationState::FailedtoLogin" },
		{ "FailedtoLogin.ToolTip", "Player failed to log in at all" },
		{ "Invalid.Comment", "/** Invalid state or user */" },
		{ "Invalid.Name", "ECommonUserInitializationState::Invalid" },
		{ "Invalid.ToolTip", "Invalid state or user" },
		{ "LoggedInLocalOnly.Comment", "/** Player is logged in locally (either guest or real user), but cannot perform online actions */" },
		{ "LoggedInLocalOnly.Name", "ECommonUserInitializationState::LoggedInLocalOnly" },
		{ "LoggedInLocalOnly.ToolTip", "Player is logged in locally (either guest or real user), but cannot perform online actions" },
		{ "LoggedInOnline.Comment", "/** Player is logged in and has access to online functionality */" },
		{ "LoggedInOnline.Name", "ECommonUserInitializationState::LoggedInOnline" },
		{ "LoggedInOnline.ToolTip", "Player is logged in and has access to online functionality" },
		{ "ModuleRelativePath", "Public/CommonUserTypes.h" },
		{ "ToolTip", "Enum describing the state of initialization for a specific user" },
		{ "Unknown.Comment", "/** User has not started login process */" },
		{ "Unknown.Name", "ECommonUserInitializationState::Unknown" },
		{ "Unknown.ToolTip", "User has not started login process" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CommonUser_ECommonUserInitializationState_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_CommonUser,
		nullptr,
		"ECommonUserInitializationState",
		"ECommonUserInitializationState",
		Z_Construct_UEnum_CommonUser_ECommonUserInitializationState_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserInitializationState_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_CommonUser_ECommonUserInitializationState_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserInitializationState_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_CommonUser_ECommonUserInitializationState()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserInitializationState.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECommonUserInitializationState.InnerSingleton, Z_Construct_UEnum_CommonUser_ECommonUserInitializationState_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ECommonUserInitializationState.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECommonUserPrivilege;
	static UEnum* ECommonUserPrivilege_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserPrivilege.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ECommonUserPrivilege.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CommonUser_ECommonUserPrivilege, Z_Construct_UPackage__Script_CommonUser(), TEXT("ECommonUserPrivilege"));
		}
		return Z_Registration_Info_UEnum_ECommonUserPrivilege.OuterSingleton;
	}
	template<> COMMONUSER_API UEnum* StaticEnum<ECommonUserPrivilege>()
	{
		return ECommonUserPrivilege_StaticEnum();
	}
	struct Z_Construct_UEnum_CommonUser_ECommonUserPrivilege_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_CommonUser_ECommonUserPrivilege_Statics::Enumerators[] = {
		{ "ECommonUserPrivilege::CanPlay", (int64)ECommonUserPrivilege::CanPlay },
		{ "ECommonUserPrivilege::CanPlayOnline", (int64)ECommonUserPrivilege::CanPlayOnline },
		{ "ECommonUserPrivilege::CanCommunicateViaTextOnline", (int64)ECommonUserPrivilege::CanCommunicateViaTextOnline },
		{ "ECommonUserPrivilege::CanCommunicateViaVoiceOnline", (int64)ECommonUserPrivilege::CanCommunicateViaVoiceOnline },
		{ "ECommonUserPrivilege::CanUseUserGeneratedContent", (int64)ECommonUserPrivilege::CanUseUserGeneratedContent },
		{ "ECommonUserPrivilege::CanUseCrossPlay", (int64)ECommonUserPrivilege::CanUseCrossPlay },
		{ "ECommonUserPrivilege::Invalid_Count", (int64)ECommonUserPrivilege::Invalid_Count },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_CommonUser_ECommonUserPrivilege_Statics::Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "CanCommunicateViaTextOnline.Comment", "/** Whether the user can use text chat */" },
		{ "CanCommunicateViaTextOnline.Name", "ECommonUserPrivilege::CanCommunicateViaTextOnline" },
		{ "CanCommunicateViaTextOnline.ToolTip", "Whether the user can use text chat" },
		{ "CanCommunicateViaVoiceOnline.Comment", "/** Whether the user can use voice chat */" },
		{ "CanCommunicateViaVoiceOnline.Name", "ECommonUserPrivilege::CanCommunicateViaVoiceOnline" },
		{ "CanCommunicateViaVoiceOnline.ToolTip", "Whether the user can use voice chat" },
		{ "CanPlay.Comment", "/** Whether the user can play at all, online or offline */" },
		{ "CanPlay.Name", "ECommonUserPrivilege::CanPlay" },
		{ "CanPlay.ToolTip", "Whether the user can play at all, online or offline" },
		{ "CanPlayOnline.Comment", "/** Whether the user can play in online modes */" },
		{ "CanPlayOnline.Name", "ECommonUserPrivilege::CanPlayOnline" },
		{ "CanPlayOnline.ToolTip", "Whether the user can play in online modes" },
		{ "CanUseCrossPlay.Comment", "/** Whether the user can ever participate in cross-play */" },
		{ "CanUseCrossPlay.Name", "ECommonUserPrivilege::CanUseCrossPlay" },
		{ "CanUseCrossPlay.ToolTip", "Whether the user can ever participate in cross-play" },
		{ "CanUseUserGeneratedContent.Comment", "/** Whether the user can access content generated by other users */" },
		{ "CanUseUserGeneratedContent.Name", "ECommonUserPrivilege::CanUseUserGeneratedContent" },
		{ "CanUseUserGeneratedContent.ToolTip", "Whether the user can access content generated by other users" },
		{ "Comment", "/** Enum specifying different privileges and capabilities available to a user */" },
		{ "Invalid_Count.Comment", "/** Invalid privilege (also the count of valid ones) */" },
		{ "Invalid_Count.Hidden", "" },
		{ "Invalid_Count.Name", "ECommonUserPrivilege::Invalid_Count" },
		{ "Invalid_Count.ToolTip", "Invalid privilege (also the count of valid ones)" },
		{ "ModuleRelativePath", "Public/CommonUserTypes.h" },
		{ "ToolTip", "Enum specifying different privileges and capabilities available to a user" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CommonUser_ECommonUserPrivilege_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_CommonUser,
		nullptr,
		"ECommonUserPrivilege",
		"ECommonUserPrivilege",
		Z_Construct_UEnum_CommonUser_ECommonUserPrivilege_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserPrivilege_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_CommonUser_ECommonUserPrivilege_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserPrivilege_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_CommonUser_ECommonUserPrivilege()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserPrivilege.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECommonUserPrivilege.InnerSingleton, Z_Construct_UEnum_CommonUser_ECommonUserPrivilege_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ECommonUserPrivilege.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECommonUserAvailability;
	static UEnum* ECommonUserAvailability_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserAvailability.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ECommonUserAvailability.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CommonUser_ECommonUserAvailability, Z_Construct_UPackage__Script_CommonUser(), TEXT("ECommonUserAvailability"));
		}
		return Z_Registration_Info_UEnum_ECommonUserAvailability.OuterSingleton;
	}
	template<> COMMONUSER_API UEnum* StaticEnum<ECommonUserAvailability>()
	{
		return ECommonUserAvailability_StaticEnum();
	}
	struct Z_Construct_UEnum_CommonUser_ECommonUserAvailability_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_CommonUser_ECommonUserAvailability_Statics::Enumerators[] = {
		{ "ECommonUserAvailability::Unknown", (int64)ECommonUserAvailability::Unknown },
		{ "ECommonUserAvailability::NowAvailable", (int64)ECommonUserAvailability::NowAvailable },
		{ "ECommonUserAvailability::PossiblyAvailable", (int64)ECommonUserAvailability::PossiblyAvailable },
		{ "ECommonUserAvailability::CurrentlyUnavailable", (int64)ECommonUserAvailability::CurrentlyUnavailable },
		{ "ECommonUserAvailability::AlwaysUnavailable", (int64)ECommonUserAvailability::AlwaysUnavailable },
		{ "ECommonUserAvailability::Invalid", (int64)ECommonUserAvailability::Invalid },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_CommonUser_ECommonUserAvailability_Statics::Enum_MetaDataParams[] = {
		{ "AlwaysUnavailable.Comment", "/** This feature will never be available for the rest of this session due to hard account or platform restrictions */" },
		{ "AlwaysUnavailable.Name", "ECommonUserAvailability::AlwaysUnavailable" },
		{ "AlwaysUnavailable.ToolTip", "This feature will never be available for the rest of this session due to hard account or platform restrictions" },
		{ "BlueprintType", "true" },
		{ "Comment", "/** Enum specifying the general availability of a feature or privilege, this combines information from multiple sources */" },
		{ "CurrentlyUnavailable.Comment", "/** This feature is not available now because of something like network connectivity but may be available in the future */" },
		{ "CurrentlyUnavailable.Name", "ECommonUserAvailability::CurrentlyUnavailable" },
		{ "CurrentlyUnavailable.ToolTip", "This feature is not available now because of something like network connectivity but may be available in the future" },
		{ "Invalid.Comment", "/** Invalid feature */" },
		{ "Invalid.Name", "ECommonUserAvailability::Invalid" },
		{ "Invalid.ToolTip", "Invalid feature" },
		{ "ModuleRelativePath", "Public/CommonUserTypes.h" },
		{ "NowAvailable.Comment", "/** This feature is fully available for use right now */" },
		{ "NowAvailable.Name", "ECommonUserAvailability::NowAvailable" },
		{ "NowAvailable.ToolTip", "This feature is fully available for use right now" },
		{ "PossiblyAvailable.Comment", "/** This might be available after the completion of normal login procedures */" },
		{ "PossiblyAvailable.Name", "ECommonUserAvailability::PossiblyAvailable" },
		{ "PossiblyAvailable.ToolTip", "This might be available after the completion of normal login procedures" },
		{ "ToolTip", "Enum specifying the general availability of a feature or privilege, this combines information from multiple sources" },
		{ "Unknown.Comment", "/** State is completely unknown and needs to be queried */" },
		{ "Unknown.Name", "ECommonUserAvailability::Unknown" },
		{ "Unknown.ToolTip", "State is completely unknown and needs to be queried" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CommonUser_ECommonUserAvailability_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_CommonUser,
		nullptr,
		"ECommonUserAvailability",
		"ECommonUserAvailability",
		Z_Construct_UEnum_CommonUser_ECommonUserAvailability_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserAvailability_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_CommonUser_ECommonUserAvailability_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserAvailability_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_CommonUser_ECommonUserAvailability()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserAvailability.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECommonUserAvailability.InnerSingleton, Z_Construct_UEnum_CommonUser_ECommonUserAvailability_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ECommonUserAvailability.InnerSingleton;
	}
	static FEnumRegistrationInfo Z_Registration_Info_UEnum_ECommonUserPrivilegeResult;
	static UEnum* ECommonUserPrivilegeResult_StaticEnum()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserPrivilegeResult.OuterSingleton)
		{
			Z_Registration_Info_UEnum_ECommonUserPrivilegeResult.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult, Z_Construct_UPackage__Script_CommonUser(), TEXT("ECommonUserPrivilegeResult"));
		}
		return Z_Registration_Info_UEnum_ECommonUserPrivilegeResult.OuterSingleton;
	}
	template<> COMMONUSER_API UEnum* StaticEnum<ECommonUserPrivilegeResult>()
	{
		return ECommonUserPrivilegeResult_StaticEnum();
	}
	struct Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult_Statics
	{
		static const UECodeGen_Private::FEnumeratorParam Enumerators[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[];
#endif
		static const UECodeGen_Private::FEnumParams EnumParams;
	};
	const UECodeGen_Private::FEnumeratorParam Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult_Statics::Enumerators[] = {
		{ "ECommonUserPrivilegeResult::Unknown", (int64)ECommonUserPrivilegeResult::Unknown },
		{ "ECommonUserPrivilegeResult::Available", (int64)ECommonUserPrivilegeResult::Available },
		{ "ECommonUserPrivilegeResult::UserNotLoggedIn", (int64)ECommonUserPrivilegeResult::UserNotLoggedIn },
		{ "ECommonUserPrivilegeResult::LicenseInvalid", (int64)ECommonUserPrivilegeResult::LicenseInvalid },
		{ "ECommonUserPrivilegeResult::VersionOutdated", (int64)ECommonUserPrivilegeResult::VersionOutdated },
		{ "ECommonUserPrivilegeResult::NetworkConnectionUnavailable", (int64)ECommonUserPrivilegeResult::NetworkConnectionUnavailable },
		{ "ECommonUserPrivilegeResult::AgeRestricted", (int64)ECommonUserPrivilegeResult::AgeRestricted },
		{ "ECommonUserPrivilegeResult::AccountTypeRestricted", (int64)ECommonUserPrivilegeResult::AccountTypeRestricted },
		{ "ECommonUserPrivilegeResult::AccountUseRestricted", (int64)ECommonUserPrivilegeResult::AccountUseRestricted },
		{ "ECommonUserPrivilegeResult::PlatformFailure", (int64)ECommonUserPrivilegeResult::PlatformFailure },
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult_Statics::Enum_MetaDataParams[] = {
		{ "AccountTypeRestricted.Comment", "/** Account does not have a required subscription or account type */" },
		{ "AccountTypeRestricted.Name", "ECommonUserPrivilegeResult::AccountTypeRestricted" },
		{ "AccountTypeRestricted.ToolTip", "Account does not have a required subscription or account type" },
		{ "AccountUseRestricted.Comment", "/** Another account/user restriction such as being banned by the service */" },
		{ "AccountUseRestricted.Name", "ECommonUserPrivilegeResult::AccountUseRestricted" },
		{ "AccountUseRestricted.ToolTip", "Another account/user restriction such as being banned by the service" },
		{ "AgeRestricted.Comment", "/** Parental control failure */" },
		{ "AgeRestricted.Name", "ECommonUserPrivilegeResult::AgeRestricted" },
		{ "AgeRestricted.ToolTip", "Parental control failure" },
		{ "Available.Comment", "/** This privilege is fully available for use */" },
		{ "Available.Name", "ECommonUserPrivilegeResult::Available" },
		{ "Available.ToolTip", "This privilege is fully available for use" },
		{ "BlueprintType", "true" },
		{ "Comment", "/** Enum giving specific reasons why a user may or may not use a certain privilege */" },
		{ "LicenseInvalid.Comment", "/** User does not own the game or content */" },
		{ "LicenseInvalid.Name", "ECommonUserPrivilegeResult::LicenseInvalid" },
		{ "LicenseInvalid.ToolTip", "User does not own the game or content" },
		{ "ModuleRelativePath", "Public/CommonUserTypes.h" },
		{ "NetworkConnectionUnavailable.Comment", "/** No network connection, this may be resolved by reconnecting */" },
		{ "NetworkConnectionUnavailable.Name", "ECommonUserPrivilegeResult::NetworkConnectionUnavailable" },
		{ "NetworkConnectionUnavailable.ToolTip", "No network connection, this may be resolved by reconnecting" },
		{ "PlatformFailure.Comment", "/** Other platform-specific failure */" },
		{ "PlatformFailure.Name", "ECommonUserPrivilegeResult::PlatformFailure" },
		{ "PlatformFailure.ToolTip", "Other platform-specific failure" },
		{ "ToolTip", "Enum giving specific reasons why a user may or may not use a certain privilege" },
		{ "Unknown.Comment", "/** State is unknown and needs to be queried */" },
		{ "Unknown.Name", "ECommonUserPrivilegeResult::Unknown" },
		{ "Unknown.ToolTip", "State is unknown and needs to be queried" },
		{ "UserNotLoggedIn.Comment", "/** User has not fully logged in */" },
		{ "UserNotLoggedIn.Name", "ECommonUserPrivilegeResult::UserNotLoggedIn" },
		{ "UserNotLoggedIn.ToolTip", "User has not fully logged in" },
		{ "VersionOutdated.Comment", "/** The game needs to be updated or patched before this will be available */" },
		{ "VersionOutdated.Name", "ECommonUserPrivilegeResult::VersionOutdated" },
		{ "VersionOutdated.ToolTip", "The game needs to be updated or patched before this will be available" },
	};
#endif
	const UECodeGen_Private::FEnumParams Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult_Statics::EnumParams = {
		(UObject*(*)())Z_Construct_UPackage__Script_CommonUser,
		nullptr,
		"ECommonUserPrivilegeResult",
		"ECommonUserPrivilegeResult",
		Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult_Statics::Enumerators,
		UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult_Statics::Enumerators),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EEnumFlags::None,
		(uint8)UEnum::ECppForm::EnumClass,
		METADATA_PARAMS(Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult_Statics::Enum_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult_Statics::Enum_MetaDataParams))
	};
	UEnum* Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult()
	{
		if (!Z_Registration_Info_UEnum_ECommonUserPrivilegeResult.InnerSingleton)
		{
			UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ECommonUserPrivilegeResult.InnerSingleton, Z_Construct_UEnum_CommonUser_ECommonUserPrivilegeResult_Statics::EnumParams);
		}
		return Z_Registration_Info_UEnum_ECommonUserPrivilegeResult.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonUserTypes_h_Statics
	{
		static const FEnumRegisterCompiledInInfo EnumInfo[];
	};
	const FEnumRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonUserTypes_h_Statics::EnumInfo[] = {
		{ ECommonUserOnlineContext_StaticEnum, TEXT("ECommonUserOnlineContext"), &Z_Registration_Info_UEnum_ECommonUserOnlineContext, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2680643188U) },
		{ ECommonUserInitializationState_StaticEnum, TEXT("ECommonUserInitializationState"), &Z_Registration_Info_UEnum_ECommonUserInitializationState, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2411757713U) },
		{ ECommonUserPrivilege_StaticEnum, TEXT("ECommonUserPrivilege"), &Z_Registration_Info_UEnum_ECommonUserPrivilege, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3520582230U) },
		{ ECommonUserAvailability_StaticEnum, TEXT("ECommonUserAvailability"), &Z_Registration_Info_UEnum_ECommonUserAvailability, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 152116938U) },
		{ ECommonUserPrivilegeResult_StaticEnum, TEXT("ECommonUserPrivilegeResult"), &Z_Registration_Info_UEnum_ECommonUserPrivilegeResult, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1617272912U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonUserTypes_h_468864327(TEXT("/Script/CommonUser"),
		nullptr, 0,
		nullptr, 0,
		Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonUserTypes_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonUserTypes_h_Statics::EnumInfo));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
