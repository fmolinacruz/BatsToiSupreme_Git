// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BTBaseCharacter.h"
#include "BTPlayerCharacter.generated.h"

class UBTPlayerInput;

UCLASS()
class BATSTOISUPREME_REAL_API ABTPlayerCharacter : public ABTBaseCharacter
{
	GENERATED_BODY()

public:
	ABTPlayerCharacter();

	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Component")
	UBTPlayerInput* GetBTInputComponent() const { return BTInputComponent; }

protected:
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter|Component")
	TObjectPtr<UBTPlayerInput> BTInputComponent;
};
