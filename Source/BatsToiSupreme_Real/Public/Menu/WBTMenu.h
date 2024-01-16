// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/UniformGridPanel.h"
#include "WBTMenu.generated.h"

/**
 * 
 */
class UWBTCharacterSelect;

UCLASS()
class BATSTOISUPREME_REAL_API UWBTMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// Initialize animations
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Batstoi|Menu")
	UWBTCharacterSelect* AddCharacterSelect(int32 PlayerIndex);

public:
	UPROPERTY(Transient, BlueprintReadWrite, meta = (BindWidgetAnim))
	UWidgetAnimation* CharacterIn1;

	UPROPERTY(Transient, BlueprintReadWrite, meta = (BindWidgetAnim))
	UWidgetAnimation* CharacterIn2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Animations")
	TArray<UWidgetAnimation*> CharacterAnimationsCPP;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* UniformGridPanel_59;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PlayerImage1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* PlayerImage2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Animations")
	TArray<UImage*> PlayerImagesCPP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|CharacterSelectMenu")
	TSubclassOf<UWBTCharacterSelect> CharacterSelectMenuTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Textures")
	UTexture2D* Image1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Textures")
	UTexture2D* Image2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Textures")
	UTexture2D* Image3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Textures")
	UTexture2D* Image4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Textures")
	UTexture2D* Image5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Textures")
	UTexture2D* Image6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Textures")
	UTexture2D* Image7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Batstoi|Textures")
	UTexture2D* Image8;

	TArray<UTexture2D*> ImagesSourcecCPP;

protected:

	void AddToImagesSourcec();
};
