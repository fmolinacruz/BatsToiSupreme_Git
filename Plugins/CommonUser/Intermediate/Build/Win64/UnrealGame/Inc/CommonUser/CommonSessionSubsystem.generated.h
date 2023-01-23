// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class APlayerController;
class UCommonSession_SearchSessionRequest;
class UCommonSession_SearchResult;
class UCommonSession_HostSessionRequest;
#ifdef COMMONUSER_CommonSessionSubsystem_generated_h
#error "CommonSessionSubsystem.generated.h already included, missing '#pragma once' in CommonSessionSubsystem.h"
#endif
#define COMMONUSER_CommonSessionSubsystem_generated_h

#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_SPARSE_DATA
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_RPC_WRAPPERS
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCommonSession_HostSessionRequest(); \
	friend struct Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics; \
public: \
	DECLARE_CLASS(UCommonSession_HostSessionRequest, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UCommonSession_HostSessionRequest)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_INCLASS \
private: \
	static void StaticRegisterNativesUCommonSession_HostSessionRequest(); \
	friend struct Z_Construct_UClass_UCommonSession_HostSessionRequest_Statics; \
public: \
	DECLARE_CLASS(UCommonSession_HostSessionRequest, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UCommonSession_HostSessionRequest)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCommonSession_HostSessionRequest(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCommonSession_HostSessionRequest) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCommonSession_HostSessionRequest); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonSession_HostSessionRequest); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCommonSession_HostSessionRequest(UCommonSession_HostSessionRequest&&); \
	NO_API UCommonSession_HostSessionRequest(const UCommonSession_HostSessionRequest&); \
public:


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCommonSession_HostSessionRequest(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCommonSession_HostSessionRequest(UCommonSession_HostSessionRequest&&); \
	NO_API UCommonSession_HostSessionRequest(const UCommonSession_HostSessionRequest&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCommonSession_HostSessionRequest); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonSession_HostSessionRequest); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCommonSession_HostSessionRequest)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_45_PROLOG
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_SPARSE_DATA \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_RPC_WRAPPERS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_INCLASS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_SPARSE_DATA \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_INCLASS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_48_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COMMONUSER_API UClass* StaticClass<class UCommonSession_HostSessionRequest>();

#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_SPARSE_DATA
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetPingInMs); \
	DECLARE_FUNCTION(execGetMaxPublicConnections); \
	DECLARE_FUNCTION(execGetNumOpenPublicConnections); \
	DECLARE_FUNCTION(execGetNumOpenPrivateConnections); \
	DECLARE_FUNCTION(execGetIntSetting); \
	DECLARE_FUNCTION(execGetStringSetting); \
	DECLARE_FUNCTION(execGetDescription);


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetPingInMs); \
	DECLARE_FUNCTION(execGetMaxPublicConnections); \
	DECLARE_FUNCTION(execGetNumOpenPublicConnections); \
	DECLARE_FUNCTION(execGetNumOpenPrivateConnections); \
	DECLARE_FUNCTION(execGetIntSetting); \
	DECLARE_FUNCTION(execGetStringSetting); \
	DECLARE_FUNCTION(execGetDescription);


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCommonSession_SearchResult(); \
	friend struct Z_Construct_UClass_UCommonSession_SearchResult_Statics; \
public: \
	DECLARE_CLASS(UCommonSession_SearchResult, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UCommonSession_SearchResult)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_INCLASS \
private: \
	static void StaticRegisterNativesUCommonSession_SearchResult(); \
	friend struct Z_Construct_UClass_UCommonSession_SearchResult_Statics; \
public: \
	DECLARE_CLASS(UCommonSession_SearchResult, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UCommonSession_SearchResult)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCommonSession_SearchResult(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCommonSession_SearchResult) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCommonSession_SearchResult); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonSession_SearchResult); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCommonSession_SearchResult(UCommonSession_SearchResult&&); \
	NO_API UCommonSession_SearchResult(const UCommonSession_SearchResult&); \
public:


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCommonSession_SearchResult(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCommonSession_SearchResult(UCommonSession_SearchResult&&); \
	NO_API UCommonSession_SearchResult(const UCommonSession_SearchResult&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCommonSession_SearchResult); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonSession_SearchResult); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCommonSession_SearchResult)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_94_PROLOG
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_SPARSE_DATA \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_RPC_WRAPPERS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_INCLASS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_SPARSE_DATA \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_INCLASS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_97_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COMMONUSER_API UClass* StaticClass<class UCommonSession_SearchResult>();

#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_144_DELEGATE \
struct _Script_CommonUser_eventCommonSession_FindSessionsFinishedDynamic_Parms \
{ \
	bool bSucceeded; \
	FText ErrorMessage; \
}; \
static inline void FCommonSession_FindSessionsFinishedDynamic_DelegateWrapper(const FMulticastScriptDelegate& CommonSession_FindSessionsFinishedDynamic, bool bSucceeded, const FText& ErrorMessage) \
{ \
	_Script_CommonUser_eventCommonSession_FindSessionsFinishedDynamic_Parms Parms; \
	Parms.bSucceeded=bSucceeded ? true : false; \
	Parms.ErrorMessage=ErrorMessage; \
	CommonSession_FindSessionsFinishedDynamic.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_SPARSE_DATA
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_RPC_WRAPPERS
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCommonSession_SearchSessionRequest(); \
	friend struct Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics; \
public: \
	DECLARE_CLASS(UCommonSession_SearchSessionRequest, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UCommonSession_SearchSessionRequest)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_INCLASS \
private: \
	static void StaticRegisterNativesUCommonSession_SearchSessionRequest(); \
	friend struct Z_Construct_UClass_UCommonSession_SearchSessionRequest_Statics; \
public: \
	DECLARE_CLASS(UCommonSession_SearchSessionRequest, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UCommonSession_SearchSessionRequest)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCommonSession_SearchSessionRequest(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCommonSession_SearchSessionRequest) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCommonSession_SearchSessionRequest); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonSession_SearchSessionRequest); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCommonSession_SearchSessionRequest(UCommonSession_SearchSessionRequest&&); \
	NO_API UCommonSession_SearchSessionRequest(const UCommonSession_SearchSessionRequest&); \
public:


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCommonSession_SearchSessionRequest(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCommonSession_SearchSessionRequest(UCommonSession_SearchSessionRequest&&); \
	NO_API UCommonSession_SearchSessionRequest(const UCommonSession_SearchSessionRequest&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCommonSession_SearchSessionRequest); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonSession_SearchSessionRequest); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCommonSession_SearchSessionRequest)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_147_PROLOG
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_SPARSE_DATA \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_RPC_WRAPPERS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_INCLASS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_SPARSE_DATA \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_INCLASS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_150_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COMMONUSER_API UClass* StaticClass<class UCommonSession_SearchSessionRequest>();

#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_SPARSE_DATA
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execCleanUpSessions); \
	DECLARE_FUNCTION(execFindSessions); \
	DECLARE_FUNCTION(execJoinSession); \
	DECLARE_FUNCTION(execQuickPlaySession); \
	DECLARE_FUNCTION(execHostSession); \
	DECLARE_FUNCTION(execCreateOnlineSearchSessionRequest); \
	DECLARE_FUNCTION(execCreateOnlineHostSessionRequest);


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execCleanUpSessions); \
	DECLARE_FUNCTION(execFindSessions); \
	DECLARE_FUNCTION(execJoinSession); \
	DECLARE_FUNCTION(execQuickPlaySession); \
	DECLARE_FUNCTION(execHostSession); \
	DECLARE_FUNCTION(execCreateOnlineSearchSessionRequest); \
	DECLARE_FUNCTION(execCreateOnlineHostSessionRequest);


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUCommonSessionSubsystem(); \
	friend struct Z_Construct_UClass_UCommonSessionSubsystem_Statics; \
public: \
	DECLARE_CLASS(UCommonSessionSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UCommonSessionSubsystem)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_INCLASS \
private: \
	static void StaticRegisterNativesUCommonSessionSubsystem(); \
	friend struct Z_Construct_UClass_UCommonSessionSubsystem_Statics; \
public: \
	DECLARE_CLASS(UCommonSessionSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UCommonSessionSubsystem)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UCommonSessionSubsystem(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UCommonSessionSubsystem) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCommonSessionSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonSessionSubsystem); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCommonSessionSubsystem(UCommonSessionSubsystem&&); \
	NO_API UCommonSessionSubsystem(const UCommonSessionSubsystem&); \
public:


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UCommonSessionSubsystem(UCommonSessionSubsystem&&); \
	NO_API UCommonSessionSubsystem(const UCommonSessionSubsystem&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UCommonSessionSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UCommonSessionSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UCommonSessionSubsystem)


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_186_PROLOG
#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_SPARSE_DATA \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_RPC_WRAPPERS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_INCLASS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_SPARSE_DATA \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_INCLASS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h_189_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COMMONUSER_API UClass* StaticClass<class UCommonSessionSubsystem>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_BatsToiSupreme_Tortoise_Plugins_CommonUser_Source_CommonUser_Public_CommonSessionSubsystem_h


#define FOREACH_ENUM_ECOMMONSESSIONONLINEMODE(op) \
	op(ECommonSessionOnlineMode::Offline) \
	op(ECommonSessionOnlineMode::LAN) \
	op(ECommonSessionOnlineMode::Online) 

enum class ECommonSessionOnlineMode : uint8;
template<> COMMONUSER_API UEnum* StaticEnum<ECommonSessionOnlineMode>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
