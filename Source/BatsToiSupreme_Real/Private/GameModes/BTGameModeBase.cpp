// Fill out your copyright notice in the Description page of Project Settings.

#include "GameModes/BTGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/BTBaseCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "PlayerCommon/BTPlayerController.h"
#include "Utilities/BTLogging.h"

ABTGameModeBase::ABTGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), MainCameraRef(nullptr)
{
}

void ABTGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void ABTGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	BTLOG_DISPLAY("[ABTGameModeBase] - OnPostLogin: Login New Player %s", *NewPlayer->GetName());
	if (MainCameraRef == nullptr)
	{
		GetMainCameraRef();
	}
	if (StartSpots.Num() == 0)
	{
		GetStartSpots();
	}

	ABTPlayerController* PC = Cast<ABTPlayerController>(NewPlayer);
	if (!PC)
	{
		BTLOG_WARNING("[ABTGameModeBase] - OnPostLogin: This is not a Player!");
		return;
	}
	
	const FVector& Location = StartSpots[CurrentPlayerIndex]->GetActorLocation();
	const FRotator& Rotation = StartSpots[CurrentPlayerIndex]->GetActorRotation();
	ABTBaseCharacter* SpawnedCharacter = GetWorld()->SpawnActor<ABTBaseCharacter>(CharacterClass, Location, Rotation);
	PC->Possess(SpawnedCharacter);
	PC->ClientSetViewTarget(MainCameraRef);

	PlayerCharacters.Add(SpawnedCharacter);

	// Check if there are at least 2 players, then set enemy
	if (PlayerCharacters.Num() >= 2)
	{
		PlayerCharacters[0]->BTEnemy = PlayerCharacters[1];
		PlayerCharacters[1]->BTEnemy = PlayerCharacters[0];
	}		

	CurrentPlayerIndex++;
}

void ABTGameModeBase::GetMainCameraRef()
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

void ABTGameModeBase::GetStartSpots()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), StartSpots);
}
