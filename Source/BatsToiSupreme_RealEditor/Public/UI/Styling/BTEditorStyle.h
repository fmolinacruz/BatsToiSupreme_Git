// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class BATSTOISUPREME_REALEDITOR_API FBTEditorStyle
{
public:
	static void Initialize();
	static void Shutdown();

	static void ReloadTextures();
	static const ISlateStyle& Get();
	static FName GetStyleSetName();

private:
	static TSharedRef<FSlateStyleSet> CreateDefault();
	static TSharedRef<FSlateStyleSet> CreateStyle(const FName StyleSetName);

	static TSharedPtr<FSlateStyleSet> StyleInstance;
};
