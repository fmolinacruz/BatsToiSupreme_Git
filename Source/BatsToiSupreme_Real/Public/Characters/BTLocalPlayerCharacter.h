// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BTBaseCharacter.h"
#include "BTLocalPlayerCharacter.generated.h"

class UBTLocalPlayerInput;

UCLASS()
class BATSTOISUPREME_REAL_API ABTLocalPlayerCharacter : public ABTBaseCharacter
{
	GENERATED_BODY()

public:
	ABTLocalPlayerCharacter();

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Component")
	UBTLocalPlayerInput* GetBTLocalInputComponent() const { return BTLocalInputComponent; }

protected:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Component")
	TObjectPtr<UBTLocalPlayerInput> BTLocalInputComponent;
};


