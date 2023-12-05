// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BTGraphCondition.generated.h"

UCLASS(Blueprintable, BlueprintType, abstract, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("Default"))
class BATSTOISUPREME_REAL_API UBTGraphCondition : public UObject
{
	GENERATED_BODY()

public:
	bool Verify(APlayerController* PlayerController);

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "BTGraph|Condition")
	bool VerifyCondition(APlayerController* PlayerController) const;

	virtual bool VerifyCondition_Implementation(APlayerController* PlayerController) const;

	UPROPERTY(BlueprintReadOnly, Category = "BTGraph|Condition")
	TObjectPtr<APlayerController> Controller;
};

/**
 * Condition OR
 */
UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("Default"))
class BATSTOISUPREME_REAL_API UBTGraphOrCondition : public UBTGraphCondition
{
	GENERATED_BODY()

public:
	UBTGraphOrCondition();

protected:
	virtual bool VerifyCondition_Implementation(APlayerController* PlayerController) const override;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "BTGraph|Condition")
	TArray<TObjectPtr<UBTGraphCondition>> OrConditions;
};

/**
 * Condition AND
 */
UCLASS(NotBlueprintable, BlueprintType, EditInlineNew, HideCategories = ("DoNotShow"), CollapseCategories, AutoExpandCategories = ("Default"))
class BATSTOISUPREME_REAL_API UBTGraphAndCondition : public UBTGraphCondition
{
	GENERATED_BODY()
	
public:
	UBTGraphAndCondition();

protected:
	virtual bool VerifyCondition_Implementation(APlayerController* PlayerController) const override;

	UPROPERTY(Instanced, EditDefaultsOnly, Category = "BTGraph|Condition")
	TArray<TObjectPtr<UBTGraphCondition>> AndConditions;
};
