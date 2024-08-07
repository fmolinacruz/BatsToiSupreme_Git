// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameplayActors/GSCModularPlayerController.h"
#include "BTLocalPlayerController.generated.h"

class ABTPlayerCharacter;
class UWBTMenu;
/**
 * 
 */
UCLASS()
class BATSTOISUPREME_REAL_API ABTLocalPlayerController : public AGSCModularPlayerController
{
	GENERATED_BODY()
	
public:
	ABTLocalPlayerController();

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	UWBTMenu* CreateMenuWidget();

protected:
	virtual void BeginPlay() override;
	virtual void AcknowledgePossession(APawn* InPawn) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Batstoi|UI")
	TSubclassOf<UWBTMenu> MenuUIClass;

	UPROPERTY(Transient)
	TObjectPtr<UWBTMenu> CharacterSelectionWidgetRef;

	TObjectPtr<ABTPlayerCharacter> PlayerCharacter;

	bool bHasSetupInput;
	
};
