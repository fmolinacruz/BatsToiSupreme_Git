// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UCommonUserInfo;
enum class ECommonUserPrivilege : uint8;
enum class ECommonUserOnlineContext : uint8;
class UCommonUserSubsystem;
class UAsyncAction_CommonUserInitialize;
#ifdef COMMONUSER_AsyncAction_CommonUserInitialize_generated_h
#error "AsyncAction_CommonUserInitialize.generated.h already included, missing '#pragma once' in AsyncAction_CommonUserInitialize.h"
#endif
#define COMMONUSER_AsyncAction_CommonUserInitialize_generated_h

#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_SPARSE_DATA
#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execHandleInitializationComplete); \
	DECLARE_FUNCTION(execLoginForOnlinePlay); \
	DECLARE_FUNCTION(execInitializeForLocalPlay);


#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execHandleInitializationComplete); \
	DECLARE_FUNCTION(execLoginForOnlinePlay); \
	DECLARE_FUNCTION(execInitializeForLocalPlay);


#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAsyncAction_CommonUserInitialize(); \
	friend struct Z_Construct_UClass_UAsyncAction_CommonUserInitialize_Statics; \
public: \
	DECLARE_CLASS(UAsyncAction_CommonUserInitialize, UCancellableAsyncAction, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UAsyncAction_CommonUserInitialize)


#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_INCLASS \
private: \
	static void StaticRegisterNativesUAsyncAction_CommonUserInitialize(); \
	friend struct Z_Construct_UClass_UAsyncAction_CommonUserInitialize_Statics; \
public: \
	DECLARE_CLASS(UAsyncAction_CommonUserInitialize, UCancellableAsyncAction, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/CommonUser"), NO_API) \
	DECLARE_SERIALIZER(UAsyncAction_CommonUserInitialize)


#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAsyncAction_CommonUserInitialize(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAsyncAction_CommonUserInitialize) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAsyncAction_CommonUserInitialize); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAsyncAction_CommonUserInitialize); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAsyncAction_CommonUserInitialize(UAsyncAction_CommonUserInitialize&&); \
	NO_API UAsyncAction_CommonUserInitialize(const UAsyncAction_CommonUserInitialize&); \
public:


#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAsyncAction_CommonUserInitialize(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAsyncAction_CommonUserInitialize(UAsyncAction_CommonUserInitialize&&); \
	NO_API UAsyncAction_CommonUserInitialize(const UAsyncAction_CommonUserInitialize&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAsyncAction_CommonUserInitialize); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAsyncAction_CommonUserInitialize); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAsyncAction_CommonUserInitialize)


#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_14_PROLOG
#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_SPARSE_DATA \
	FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_RPC_WRAPPERS \
	FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_INCLASS \
	FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_SPARSE_DATA \
	FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_INCLASS_NO_PURE_DECLS \
	FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h_17_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> COMMONUSER_API UClass* StaticClass<class UAsyncAction_CommonUserInitialize>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_BatsToiSupreme_Git_Plugins_CommonUser_Source_CommonUser_Public_AsyncAction_CommonUserInitialize_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
