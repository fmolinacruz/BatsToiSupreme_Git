// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTLocalOfflineGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/BTBaseCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "PlayerCommon/BTLocalPlayerController.h"
#include "Utilities/BTLogging.h"


ABTLocalOfflineGameMode::ABTLocalOfflineGameMode(const FObjectInitializer& ObjectInitializer)
{
}

void ABTLocalOfflineGameMode::BeginPlay()
{
	Super::BeginPlay();
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

            // Spawn InputReceiver tr??c
			// ABTInputReceiver* InputReceiver = GetWorld()->SpawnActor<ABTInputReceiver>(InputReceiverClass, Location, Rotation);
			ABTLocalInputReceiver* InputReceiver = GetWorld()->SpawnActor<ABTLocalInputReceiver>(InputReceiverClass, Location, Rotation);
			if (InputReceiver)
			{
				PC->Possess(InputReceiver);
				InputReceiver->InitializeWithPlayerController(PC, Index);

				// T?o UI Menu cho ng??i ch?i ??u tiên
				if (!bIsMenuCreated)
				{
					InputReceiver->CreateMenuUI();
					bIsMenuCreated = true;
				}
			}

			ABTBaseCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABTBaseCharacter>(CharacterClass, Location, Rotation);
			if (SpawnedCharacter != nullptr)
			{
				PC->Possess(SpawnedCharacter);
				PC->SetViewTarget(MainCameraRef);

				PlayerCharacters.Add(SpawnedCharacter);
				SpawnedCharacter->SetPlayerIndex(Index);
				SpawnedCharacter->SetCharacterID(Index);

				// Set enemies if there are at least 2 players
				// (Assuming PlayerCharacters array is sorted by player index)
				if (PlayerCharacters.Num() >= 2)
				{
					PlayerCharacters[0]->BTEnemy = PlayerCharacters[1];
					PlayerCharacters[1]->BTEnemy = PlayerCharacters[0];
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

