// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Styling/BTEditorStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

#define DEFAULT_FONT(...) FCoreStyle::GetDefaultFontStyle(__VA_ARGS__)
#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( Style, RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( Style->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )
#define JPG_IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush(Style->RootToContentDir( RelativePath, TEXT(".jpg")), __VA_ARGS__ )

TSharedPtr<FSlateStyleSet> FBTEditorStyle::StyleInstance = nullptr;

void FBTEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBTEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

void FBTEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FBTEditorStyle::Get()
{
	return *StyleInstance;
}

FName FBTEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("BTEditorStyle"));
	return StyleSetName;
}

TSharedRef<FSlateStyleSet> FBTEditorStyle::Create()
{
	TSharedRef<FSlateStyleSet> Style = CreateStyle("BTEditorStyle");
	return Style;
}

TSharedRef<FSlateStyleSet> FBTEditorStyle::CreateStyle(FName StyleSetName)
{
	TSharedRef<FSlateStyleSet> Style = MakeShareable(new FSlateStyleSet(StyleSetName));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("BatsToiSupreme_Real")->GetBaseDir() / TEXT("Resources"));
	return Style;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT
#undef JPG_IMAGE_BRUSH
