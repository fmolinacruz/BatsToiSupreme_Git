// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameplayActors/GSCModularPlayerController.h"
#include "BTPlayerController.generated.h"

class ABTPlayerCharacter;
class ABTInputReceiver;
class UWBTMenu;

UCLASS()
class BATSTOISUPREME_REAL_API ABTPlayerController : public AGSCModularPlayerController
{
	GENERATED_BODY()

public:
	ABTPlayerController();

	UWBTMenu* CreateMenuWidget();

protected:
	virtual void BeginPlay() override;

	virtual void AcknowledgePossession(APawn* InPawn) override;

private:
	TObjectPtr<ABTPlayerCharacter> PlayerCharacter;
	bool bHasSetupInput;

	// InputReceiver
	TObjectPtr<ABTInputReceiver> InputReceiver;

	UPROPERTY(EditDefaultsOnly, Category = "Batstoi|UI")
	TSubclassOf<UWBTMenu> MenuUIClass;
};
