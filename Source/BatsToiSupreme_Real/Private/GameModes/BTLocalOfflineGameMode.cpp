// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTLocalOfflineGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/BTBaseCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "PlayerCommon/BTLocalPlayerController.h"
#include "Utilities/BTLogging.h"
#include "Menu/WBTMenu.h"


ABTLocalOfflineGameMode::ABTLocalOfflineGameMode(const FObjectInitializer& ObjectInitializer)
{
}

void ABTLocalOfflineGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Create Menu UI
	CreateMenuUI();

	SpawnInputReceivers();
}

void ABTLocalOfflineGameMode::SpawnInputReceivers()
{
	// BTLOG_DISPLAY("[ABTGameModeBase] - OnPostLogin: Login New Player %s", *NewPlayer->GetName());
	if (MainCameraRef == nullptr)
	{
		GetMainCameraRef();
	}
	if (StartSpots.Num() == 0)
	{
		GetStartSpots();
	}

	const UWorld* CurrentWorld = GetWorld();

	int32 Index = 0;
	for (AActor* Actor : StartSpots)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerStartTag: %d"), Index);
		if (NameToInt(Actor) == Index)
		{
			UE_LOG(LogTemp, Warning, TEXT("Done: %d"), Index);

			// Get Player Controller
			ABTLocalPlayerController* PC = Cast<ABTLocalPlayerController>(UGameplayStatics::GetPlayerController(CurrentWorld, Index));
			if (PC == nullptr)
			{
				PC = Cast<ABTLocalPlayerController>(UGameplayStatics::CreatePlayer(CurrentWorld, Index, true));
			}

			const FVector& Location = StartSpots[Index]->GetActorLocation();
			const FRotator& Rotation = StartSpots[Index]->GetActorRotation();

            // Spawn InputReceiver
			ABTLocalInputReceiver* InputReceiver = GetWorld()->SpawnActor<ABTLocalInputReceiver>(InputReceiverClass, Location, Rotation);
			if (InputReceiver)
			{
				PC->Possess(InputReceiver);

				// Initialize the InputReceiver with the player controller and current player index
				InputReceivers.Add(InputReceiver);
				InputReceiver->InitializeWithPlayerController(PC, Index);
				InputReceiver->SetMenuWidget(MenuWidgetRefCPP);

				if (InputReceivers.Num() >= 2)
				{
					InputReceivers[0]->OtherPlayerController = InputReceivers[1]->CurrentPlayerController;
					InputReceivers[1]->OtherPlayerController = InputReceivers[0]->CurrentPlayerController;
				}
			}
		}
		Index++;
	}
}

int ABTLocalOfflineGameMode::NameToInt(AActor* Player)
{
	APlayerStart* PlayerStart = Cast<APlayerStart>(Player);

	// Get the custom tag assigned to the PlayerStart actor
	FName PlayerStartTag = PlayerStart->PlayerStartTag;

	// Convert the tag to a string
	FString PlayerStartTagString = PlayerStartTag.ToString();

	// Remove any non-numeric characters from the string
	PlayerStartTagString.RemoveFromStart(TEXT("PlayerStart")); // Remove a prefix if needed

	// Parse the remaining string as an integer
	int32 PlayerIndex = FCString::Atoi(*PlayerStartTagString);

	return PlayerIndex;
}

void ABTLocalOfflineGameMode::CheckForSpawningPlayerCharacter(ABTLocalPlayerController* PC, int CharacterID, int PlayerIndex)
{
	BTLOG_DISPLAY("[ABTGameModeBase] - CheckForSpawningPlayerCharacter: ");
	if (!PC)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SpawnPlayerCharacter is nullptr"));
		}
		return;
	}

	// Add player data to the map
	PlayerMap.Add(PlayerIndex, { CharacterID, PC });

	// Check if there are at least 2 players
	if (PlayerMap.Num() >= 2)
	{
		for (const auto& Pair : PlayerMap)
		{
			StartSpawningPlayerCharacter(Pair.Value.Controller, Pair.Value.CharacterID, Pair.Key);
		}

		// Hide the menu UI
		HideMenuUI();
	}
}

void ABTLocalOfflineGameMode::StartSpawningPlayerCharacter(ABTLocalPlayerController * PC, int CharacterID, int PlayerIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("SpawnPlayerCharacter with PlayerIndex: %d"), PlayerIndex));
	}

	// Retrieve the spawn location and rotation from the start spots array
	const FVector& Location = StartSpots[PlayerIndex]->GetActorLocation();
	const FRotator& Rotation = StartSpots[PlayerIndex]->GetActorRotation();

	// Spawn the player character using the selected CharacterID
	// For simplicity, this example uses the same CharacterClass for all IDs
	ABTBaseCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABTBaseCharacter>(CharacterClass, Location, Rotation);
	if (SpawnedCharacter)
	{
		// PC->UnPossess();
		PC->Possess(SpawnedCharacter);
		PC->ClientSetViewTarget(MainCameraRef);

		PlayerCharacters.Add(SpawnedCharacter);
		SpawnedCharacter->SetPlayerIndex(PlayerIndex);
		SpawnedCharacter->SetCharacterID(CharacterID);

		// Set enemies if there are at least 2 players
		// (Assuming PlayerCharacters array is sorted by player index)
		if (PlayerCharacters.Num() >= 2)
		{
			PlayerCharacters[0]->BTEnemy = PlayerCharacters[1];
			PlayerCharacters[1]->BTEnemy = PlayerCharacters[0];
		}
	}
}

void ABTLocalOfflineGameMode::RestorePlayerCharacter(int PlayerIndex)
{
	// Remove player data to the map
	PlayerMap.Remove(PlayerIndex);
}

void ABTLocalOfflineGameMode::GetMainCameraRef()
{
	TArray<AActor*> AllCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CameraClass, AllCameras);
	if (AllCameras.Num() == 0)
	{
		BTLOG_ERROR("[ABTGameModeBase] - BeginPlay: There's no main camera setup!");
		return;
	}

	MainCameraRef = AllCameras[0];
}

void ABTLocalOfflineGameMode::GetStartSpots()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), StartSpots);
}

void ABTLocalOfflineGameMode::CreateMenuUI()
{
	if (MenuWidgetRefCPP == nullptr && MenuUIClass)
	{
		MenuWidgetRefCPP = CreateWidget<UWBTMenu>(GetWorld(), MenuUIClass);
		if (MenuWidgetRefCPP)
		{
			MenuWidgetRefCPP->AddToViewport();
		}
	}
}

void ABTLocalOfflineGameMode::HideMenuUI()
{
	if (MenuWidgetRefCPP)
	{
		MenuWidgetRefCPP->SetVisibility(ESlateVisibility::Hidden);
	}
}

UWBTMenu* ABTLocalOfflineGameMode::GetMenuWidgetRef() const
{
	return MenuWidgetRefCPP;
}
