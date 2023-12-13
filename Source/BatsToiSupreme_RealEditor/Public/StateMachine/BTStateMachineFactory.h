// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "BTStateMachineFactory.generated.h"

UCLASS()
class BATSTOISUPREME_REALEDITOR_API UBTStateMachineFactory : public UFactory
{
	GENERATED_BODY()

public:
	UBTStateMachineFactory();

	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName InName,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn) override;

	virtual FName GetNewAssetThumbnailOverride() const override;
	virtual FText GetDisplayName() const override;
	virtual FText GetToolTip() const override;
	virtual FString GetDefaultNewAssetName() const override;
};
