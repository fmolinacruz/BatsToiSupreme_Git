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
	
	if (LocalCharacterSelectMenu == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("LocalCharacterSelectMenu NULL"));
	}
	if (CameraRef == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraRef NULL"));
	}


	World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("BTLocalMultiGameMode BeginPlay World NULL"));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode BeginPlay"));
	// SetSkipAssigningGamepadToPlayer1
	UGameMapsSettings* GameMapsSettings = UGameMapsSettings::GetGameMapsSettings();
	if (GameMapsSettings != nullptr)
	{
		GameMapsSettings->SetSkipAssigningGamepadToPlayer1(true);
	}
	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode GameMapsSettings"));
	//Get All Actors Of Class
	/*TArray<AActor*> AllCamera;
	UGameplayStatics::GetAllActorsOfClass(World, ABTCamera::StaticClass(), AllCamera);
	if (AllCamera.IsValidIndex(0))
	{
		CameraRef = Cast<ABTCamera>(AllCamera[0]);
		UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode CameraRef"));
	}*/
	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode GetAllActorsOfClass"));

	//Get Player Start Points
	GetPlayerStartPoints();
	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode GetPlayerStartPoints"));
	//Create WBP Menu Widget

	MenuWidgetRef = CreateWidget<ULocalCharacterSelectMenu>(World, LocalCharacterSelectMenu->GetClass());
	////Add to Viewport
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
	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode MenuWidgetRef"));

	////Delay until next tick
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SpawnInputReceivers"));
	// Set up a timer to call the delegate on the next tick
	GetWorld()->GetTimerManager().SetTimerForNextTick(TimerDelegate);
	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode TimerDelegate"));
	// Completed
}

void ABTLocalMultiGameMode::GetPlayerStartPoints()
{
	UClass* PlayerStartClass = APlayerStart::StaticClass();

	// Get all player start points in the world and store them in the array
	UGameplayStatics::GetAllActorsOfClass(World, PlayerStartClass, PlayerStartArray);
	if (!PlayerStartArray.IsValidIndex(0))
	{
		UE_LOG(LogTemp, Warning, TEXT("GetPlayerStartPoints PlayerStartArray NULL"));
	}
}

void ABTLocalMultiGameMode::SpawnInputReceivers()
{
	/*for (AActor* Actor : PlayerStartArray)
	{
		if (Actor && !Actor->IsPendingKill())
		{
			int index = NameToInt(Actor);
		}
	}*/

	int32 Index = 0;
	for (AActor* Actor : PlayerStartArray)
	{

		if (NameToInt(Actor) == Index)
		{
			CreateLocalPlayerDebug(Index);

			if (World != nullptr)
			{
				// Spawn the actor
				FActorSpawnParameters SpawnParams;
				//SpawnParams.PlayerIn
				//TODO: missing Player Index param
				AInputReceive* SpawnedActor = World->SpawnActor<AInputReceive>(AInputReceive::StaticClass(), Actor->GetActorTransform(), SpawnParams);
				if (SpawnedActor)
				{
					PlayerInputReceiverArray.Add(SpawnedActor);

					APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, Index);
					PlayerController->Possess(SpawnedActor);

					//Player Index 0
					APlayerController* PlayerController0 = UGameplayStatics::GetPlayerController(World, 0);
					PlayerController0->SetViewTargetWithBlend(CameraRef);
				}
			}
			
		}
		// Increment the index counter
		Index++;
	}
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
	AGameStateBase* State = UGameplayStatics::GetGameState(World);

	// Check if the game state is valid before using it
	if (State != nullptr)
	{
		ABTGameState* BtGameState = Cast<ABTGameState>(State);
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
	UGameplayStatics::GetAllActorsOfClass(World, CameraActorClass, CameraActorArray);

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
	if (ControllerId != 0)
	{
		if (World != nullptr)
		{
			APlayerController* PlayerController = UGameplayStatics::CreatePlayer(World, ControllerId, true);
		}
	}
}
