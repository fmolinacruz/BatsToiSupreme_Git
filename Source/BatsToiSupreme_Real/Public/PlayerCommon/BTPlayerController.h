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

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	UWBTMenu* CreateMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	void TurnOffMenuWidget();

	UFUNCTION(NetMulticast, Reliable, Category = "Batstoi|UI")
	void PlayCharacterSelectedAnimation(const int PlayerIndex);

	UFUNCTION(NetMulticast, Reliable, Category = "Batstoi|UI")
	void PlayCharacterDecidedAnimation(const int PlayerIndex);

	UFUNCTION(NetMulticast, Reliable, Category = "Batstoi|UI")
	void PlayCharacterRestore(const int PlayerIndex);

	UFUNCTION(NetMulticast, Reliable, Category = "Batstoi|UI")
	void ChangeCharacterSelectionTexture(const int PlayerIndex, const int CharacterChoice);
	
	UFUNCTION(Client, Reliable)
	void Client_TurnOffCharacterSelectMenu();

protected:
	virtual void BeginPlay() override;
	virtual void AcknowledgePossession(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Batstoi|UI")
	TSubclassOf<UWBTMenu> MenuUIClass;

	UPROPERTY(Transient)
	TObjectPtr<UWBTMenu> CharacterSelectionWidgetRef;

	TObjectPtr<ABTPlayerCharacter> PlayerCharacter;
	TObjectPtr<ABTInputReceiver> InputReceiver;

	bool bHasSetupInput;
};
