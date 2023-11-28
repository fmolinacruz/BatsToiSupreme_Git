// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameplayActors/GSCModularCharacter.h"
#include "BTBaseCharacter.generated.h"

class UBTCharacterMovement;

UCLASS()
class BATSTOISUPREME_REAL_API ABTBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABTBaseCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintCallable, Category = "BatstoiCharacter|Actions")
	void MoveCharacter(const FVector2D& MovementVector); 
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BatstoiCharacter|Enemy")
	TObjectPtr<ABTBaseCharacter> BTEnemy;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter")
	bool bIsTurningRight;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BatstoiCharacter")
	bool bIsTurningLeft;
	
private:
	void RotateTowardEnemy(float DeltaSeconds);
};
