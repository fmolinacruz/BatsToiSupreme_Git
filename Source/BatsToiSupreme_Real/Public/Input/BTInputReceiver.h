// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BTInputReceiver.generated.h"

UCLASS()
class BATSTOISUPREME_REAL_API ABTInputReceiver : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABTInputReceiver();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
