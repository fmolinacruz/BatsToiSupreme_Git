// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/BTLocalBaseGameMode.h"

#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

ABTLocalBaseGameMode::ABTLocalBaseGameMode()
{
}

void ABTLocalBaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	//World = GetWorld();
	//if (World == nullptr)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("BTLocalMultiGameMode BeginPlay World NULL"));
	//	return;
	//}

	UE_LOG(LogTemp, Warning, TEXT("World Done"));

	//// Get BT Camera
	//AActor* FoundActor = UGameplayStatics::GetActorOfClass(World, CameraTemplate);
	//CameraRef = Cast<ABTCamera>(FoundActor);

	UE_LOG(LogTemp, Warning, TEXT("CameraRef Done"));

	//GetPlayerStartPoints();
	FindMainCameraRef();
	SpawnInputReceivers();
}

//void ABTLocalBaseGameMode::GetPlayerStartPoints()
//{
//	UClass* PlayerStartClass = APlayerStart::StaticClass();
//
//	// Get all player start points in the world and store them in the array
//	UGameplayStatics::GetAllActorsOfClass(World, PlayerStartClass, PlayerStartArray);
//	if (!PlayerStartArray.IsValidIndex(0))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("GetPlayerStartPoints PlayerStartArray NULL"));
//	}
//
//	UE_LOG(LogTemp, Warning, TEXT("PlayerStartArray Done"));
//}

void ABTLocalBaseGameMode::FindMainCameraRef()
{
	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), MainCameraClass, FoundCameras);
	if (FoundCameras.Num() != 0)
	{
		MainCameraRef = FoundCameras[0]; // Always have one main camera in our current example.
	}
}

void ABTLocalBaseGameMode::SpawnInputReceivers()
{
	const UWorld* CurrentWorld = GetWorld();

	int PlayerIndex = 0;
	UClass* ActorClass = APlayerStart::StaticClass();
	for (TActorIterator<AActor> It(CurrentWorld, ActorClass); It; ++It)
	//for (AActor* Actor : PlayerStartArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerStartTag: %d"), PlayerIndex);

		//if (NameToInt(Actor) == Index)
		//{
		//	//// Print Index log use GEngine
		//	UE_LOG(LogTemp, Warning, TEXT("NameToInt: %d"), Index);

		if (PlayerIndex >= 2)
			break;

		// Get Player Controller
		APlayerController* PC = UGameplayStatics::GetPlayerController(CurrentWorld, PlayerIndex);
		if (PC == nullptr)
		{
			PC = UGameplayStatics::CreatePlayer(CurrentWorld, PlayerIndex, true);
		}

		UE_LOG(LogTemp, Warning, TEXT("CreatePlayer Done"));

		const AActor* Start = *It;
		const FVector& Location = Start->GetActorLocation();
		const FRotator& Rotation = Start->GetActorRotation();

		ABTBaseCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABTBaseCharacter>(CharacterClass, Location, Rotation);
		if (SpawnedCharacter != nullptr)
		{
			PC->Possess(SpawnedCharacter);
			PC->SetViewTarget(MainCameraRef);

			PlayerCharacters.Add(SpawnedCharacter);
			SpawnedCharacter->SetPlayerIndex(PlayerIndex);
			SpawnedCharacter->SetCharacterID(PlayerIndex);

			// Set enemies if there are at least 2 players
			// (Assuming PlayerCharacters array is sorted by player index)
			if (PlayerCharacters.Num() >= 2)
			{
				PlayerCharacters[0]->BTEnemy = PlayerCharacters[1];
				PlayerCharacters[1]->BTEnemy = PlayerCharacters[0];
			}
		}
		//	//const FVector& Location = Actor->GetActorLocation();
		//	//const FRotator& Rotation = Actor->GetActorRotation();

		//	//ABTBaseCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABTBaseCharacter>(CharacterClass, Location, Rotation);
		//	//if (SpawnedCharacter)
		//	//{
		//	//	// PC->UnPossess();
		//	//	PC->Possess(SpawnedCharacter);
		//	//	PC->ClientSetViewTarget(CameraRef);

		//	//	PlayerCharacters.Add(SpawnedCharacter);
		//	//	SpawnedCharacter->SetPlayerIndex(Index);
		//	//	SpawnedCharacter->SetCharacterID(Index);

		//	//	// Set enemies if there are at least 2 players
		//	//	// (Assuming PlayerCharacters array is sorted by player index)
		//	//	if (PlayerCharacters.Num() >= 2)
		//	//	{
		//	//		PlayerCharacters[0]->BTEnemy = PlayerCharacters[1];
		//	//		PlayerCharacters[1]->BTEnemy = PlayerCharacters[0];
		//	//	}
		//	//}
		//}
		// Increment the index counter
		PlayerIndex++;
	}
}

//int ABTLocalBaseGameMode::NameToInt(AActor* Player)
//{
//	APlayerStart* PlayerStart = Cast<APlayerStart>(Player);
//
//	// Get the custom tag assigned to the PlayerStart actor
//	FName PlayerStartTag = PlayerStart->PlayerStartTag;
//
//	// Convert the tag to a string
//	FString PlayerStartTagString = PlayerStartTag.ToString();
//
//	// Remove any non-numeric characters from the string
//	PlayerStartTagString.RemoveFromStart(TEXT("PlayerStart")); // Remove a prefix if needed
//
//	// Parse the remaining string as an integer
//	int32 PlayerIndex = FCString::Atoi(*PlayerStartTagString);
//
//	return PlayerIndex;
//}
