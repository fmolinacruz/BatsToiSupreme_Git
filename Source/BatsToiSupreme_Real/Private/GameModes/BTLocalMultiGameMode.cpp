// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTLocalMultiGameMode.h"
#include <GameMapsSettings.h>
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include <GameModes/BTGameState.h>

// Called when the game starts
void ABTLocalMultiGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode BeginPlay"));
	// SetSkipAssigningGamepadToPlayer1
	UGameMapsSettings* GameMapsSettings = UGameMapsSettings::GetGameMapsSettings();
	if (GameMapsSettings)
	{
		GameMapsSettings->SetSkipAssigningGamepadToPlayer1(true);
	}

	//Get All Actors Of Class
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), BP_Camera, OutActors);

	//Get Player Start Points
	GetPlayerStartPoints();

	//Create WBP Menu Widget
	UMenu* MenuWidgetRef = CreateWidget<UMenu>(this, UMenu::StaticClass());

	//Add to Viewport
	if (MenuWidgetRef)
	{
		// Add the widget to the viewport
		MenuWidgetRef->AddToViewport(1);
	}
	else
	{
		// Handle the case where widget creation failed
		UE_LOG(LogTemp, Error, TEXT("Widget creation failed"));
	}

	//Delay until next tick
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SpawnInputReceivers"));
	// Set up a timer to call the delegate on the next tick
	GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
	//Completed
}

void ABTLocalMultiGameMode::GetPlayerStartPoints()
{
	UClass* PlayerStartClass = APlayerStart::StaticClass();

	// Get all player start points in the world and store them in the array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerStartClass, PlayerStartArray);
}

void ABTLocalMultiGameMode::SpawnInputReceivers()
{
}

int ABTLocalMultiGameMode::NameToInt(AActor* Player)
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

void ABTLocalMultiGameMode::GameStarted()
{
	bIsInGame = true;
	CameraRef->GameStarted(Players);

	// Get the game state
	AGameStateBase* GameState = UGameplayStatics::GetGameState(GetWorld());

	// Check if the game state is valid before using it
	if (GameState != nullptr)
	{
		ABTGameState* BtGameState = Cast<ABTGameState>(GameState);
		if (BtGameState != nullptr)
		{
			bIsInGame = true;
			BtGameState->InitializePlayer();
		}
	}
}

void ABTLocalMultiGameMode::RemoveUnusedCameras()
{
	UClass* CameraActorClass = ACameraActor::StaticClass();

	// Create an array to store all camera actors
	TArray<AActor*> CameraActorArray;

	// Get all camera actors in the world and store them in the array
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CameraActorClass, CameraActorArray);

	for (AActor* CameraActor : CameraActorArray)
	{
		if (CameraActor && !CameraActor->IsPendingKill())
		{
			// Destroy the actor
			CameraActor->Destroy();
			// Optionally, set the pointer to nullptr to avoid using it after destruction
			CameraActor = nullptr;
		}
	}
}

void ABTLocalMultiGameMode::CreateLocalPlayerDebug(int ControllerId)
{
}
