// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "RLPlugin/Private/CCImportUI.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeCCImportUI() {}
// Cross Module References
	RLPLUGIN_API UClass* Z_Construct_UClass_UCCImportUI_NoRegister();
	RLPLUGIN_API UClass* Z_Construct_UClass_UCCImportUI();
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	UPackage* Z_Construct_UPackage__Script_RLPlugin();
// End Cross Module References
	void UCCImportUI::StaticRegisterNativesUCCImportUI()
	{
	}
	UClass* Z_Construct_UClass_UCCImportUI_NoRegister()
	{
		return UCCImportUI::StaticClass();
	}
	struct Z_Construct_UClass_UCCImportUI_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UCCImportUI_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_RLPlugin,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UCCImportUI_Statics::Class_MetaDataParams[] = {
		{ "AutoExpandCategories", "FTransform" },
		{ "Comment", "/**\n * TODO:\n */" },
		{ "HideCategories", "Object" },
		{ "IncludePath", "CCImportUI.h" },
		{ "ModuleRelativePath", "Private/CCImportUI.h" },
		{ "ObjectInitializerConstructorDeclared", "" },
		{ "ToolTip", "TODO:" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UCCImportUI_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UCCImportUI>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UCCImportUI_Statics::ClassParams = {
		&UCCImportUI::StaticClass,
		"EditorPerProjectUserSettings",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x000800A0u,
		METADATA_PARAMS(Z_Construct_UClass_UCCImportUI_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UCCImportUI_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UCCImportUI()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UCCImportUI_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UCCImportUI, 3432315647);
	template<> RLPLUGIN_API UClass* StaticClass<UCCImportUI>()
	{
		return UCCImportUI::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UCCImportUI(Z_Construct_UClass_UCCImportUI, &UCCImportUI::StaticClass, TEXT("/Script/RLPlugin"), TEXT("UCCImportUI"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UCCImportUI);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
