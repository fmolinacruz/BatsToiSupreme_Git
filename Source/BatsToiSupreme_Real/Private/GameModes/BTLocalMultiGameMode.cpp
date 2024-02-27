// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTLocalMultiGameMode.h"
#include <GameMapsSettings.h>
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"
#include "Camera/CameraActor.h"
#include <GameModes/BTGameState.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ABTLocalMultiGameMode::ABTLocalMultiGameMode()
{
	// Create and assign the InputComponent
	//InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("InputComponent"));
}

// Called when the game starts
void ABTLocalMultiGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode BeginPlay"));
	
	if (LocalCharacterSelectMenuTemplate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("LocalCharacterSelectMenuTemplate NULL"));
	}
	if (CameraTemplate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CameraTemplate NULL"));
	}


	World = GetWorld();
	if (World == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("BTLocalMultiGameMode BeginPlay World NULL"));
		return;
	}

	// SetSkipAssigningGamepadToPlayer1
	UGameMapsSettings* GameMapsSettings = UGameMapsSettings::GetGameMapsSettings();
	if (GameMapsSettings != nullptr)
	{
		GameMapsSettings->SetSkipAssigningGamepadToPlayer1(true);
	}
	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode GameMapsSettings"));

	//Get BT Camera
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, CameraTemplate);
	CameraRef = Cast<ABTCamera>(FoundActor);

	//Get Player Start Points
	GetPlayerStartPoints();
	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode GetPlayerStartPoints"));
	//Create WBP Menu Widget

	if (LocalCharacterSelectMenuTemplate != nullptr)
	{
		MenuWidgetRef = CreateWidget<ULocalCharacterSelectMenu>(World, LocalCharacterSelectMenuTemplate);
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
	}

	//InitializeInputComponent(InputComponent);
	////Delay until next tick
	//GetWorldTimerManager().SetTimerForNextTick(this, &ABTLocalMultiGameMode::SpawnInputReceivers);
    
	UE_LOG(LogTemp, Warning, TEXT("BTLocalMultiGameMode TimerDelegate"));
	// Completed
}

void ABTLocalMultiGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	InitializeInputComponent(InputComponent);
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
	UE_LOG(LogTemp, Warning, TEXT("SpawnInputReceivers "));
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
	if (CameraRef != nullptr)
	{
		CameraRef->GameStarted(Players);
	}

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

void ABTLocalMultiGameMode::InitializeInputComponent(UInputComponent* MenuInputComponent)
{
	if (MenuInputComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("MenuInputComponent == nullptr "));
	}
	else
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(MenuInputComponent);
		EnhancedInputComponent->BindAction(CharacterSelectInputAction, ETriggerEvent::Triggered, this, &ABTLocalMultiGameMode::CharacterSelect);
	}
}

void ABTLocalMultiGameMode::CharacterSelect(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Error, TEXT("CharacterSelect "));
}

bool ABTLocalMultiGameMode::StartGame1()
{
	AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, ThirdPersionPlayerAITemplate);
	AGSCModularCharacter* CharacterAI = Cast<AGSCModularCharacter>(FoundActor);
	if (CharacterAI == nullptr)
	{
		if (CharacterAI != nullptr || Players.Num() >= MinPlayers)
		{
			GameStarted();
			return true;
		}
	}
	return false;
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
