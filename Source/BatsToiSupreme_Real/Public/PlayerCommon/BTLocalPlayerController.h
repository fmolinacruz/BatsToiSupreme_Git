// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularGameplayActors/GSCModularPlayerController.h"
#include "BTLocalPlayerController.generated.h"

class ABTLocalOfflineGameMode;
class ABTLocalInputReceiver;
class ABTLocalPlayerCharacter;
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

	//UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	//UWBTMenu* CreateMenuWidget();

	//UFUNCTION(BlueprintCallable, Category = "Batstoi|UI")
	//UWBTMenu* GetMenuWidgetFromGameMode();

	void SetCharacterSelectionWidgetRef(UWBTMenu* MenuWidget);

	UFUNCTION(Category = "Batstoi|UI")
	void PlayCharacterSelectedAnimation(const int PlayerIndex);

	UFUNCTION(Category = "Batstoi|UI")
	void PlayCharacterDecidedAnimation(const int PlayerIndex);

	UFUNCTION(Category = "Batstoi|UI")
	void PlayCharacterRestore(const int PlayerIndex);

	UFUNCTION(Category = "Batstoi|UI")
	void ChangeCharacterSelectionTexture(const int PlayerIndex, const int CharacterChoice);

protected:
	virtual void BeginPlay() override;
	virtual void AcknowledgePossession(APawn* InPawn) override;
	
private:
	//UPROPERTY(EditDefaultsOnly, Category = "Batstoi|UI")
	//TSubclassOf<UWBTMenu> MenuUIClass;

	UPROPERTY(Transient)
	TObjectPtr<UWBTMenu> CharacterSelectionWidgetRef;

	TObjectPtr<ABTLocalPlayerCharacter> PlayerCharacter;
	TObjectPtr<ABTLocalInputReceiver> InputReceiver;

	bool bHasSetupInput;
	
	ABTLocalOfflineGameMode* GetGameMode() const;
};
