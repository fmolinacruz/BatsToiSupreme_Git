// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RLPlugin/Private/CCFbxFactory.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCCFbxFactory() {}
// Cross Module References
	RLPLUGIN_API UClass* Z_Construct_UClass_UCCFbxFactory_NoRegister();
	RLPLUGIN_API UClass* Z_Construct_UClass_UCCFbxFactory();
	UNREALED_API UClass* Z_Construct_UClass_UFbxFactory();
	UPackage* Z_Construct_UPackage__Script_RLPlugin();
// End Cross Module References
	void UCCFbxFactory::StaticRegisterNativesUCCFbxFactory()
	{
	}
	UClass* Z_Construct_UClass_UCCFbxFactory_NoRegister()
	{
		return UCCFbxFactory::StaticClass();
	}
	struct Z_Construct_UClass_UCCFbxFactory_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCCFbxFactory_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UFbxFactory,
		(UObject* (*)())Z_Construct_UPackage__Script_RLPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCCFbxFactory_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Object Object" },
		{ "IncludePath", "CCFbxFactory.h" },
		{ "ModuleRelativePath", "Private/CCFbxFactory.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCCFbxFactory_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCCFbxFactory>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCCFbxFactory_Statics::ClassParams = {
		&UCCFbxFactory::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCCFbxFactory_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCCFbxFactory_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCCFbxFactory()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCCFbxFactory_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCCFbxFactory, 295642347);
	template<> RLPLUGIN_API UClass* StaticClass<UCCFbxFactory>()
	{
		return UCCFbxFactory::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCCFbxFactory(Z_Construct_UClass_UCCFbxFactory, &UCCFbxFactory::StaticClass, TEXT("/Script/RLPlugin"), TEXT("UCCFbxFactory"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCCFbxFactory);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
