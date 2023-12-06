// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BTLocalMultiGameMode.h"
#include <GameMapsSettings.h>
#include <Kismet/GameplayStatics.h>
#include "Blueprint/UserWidget.h"

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

void ABTLocalMultiGameMode::GetPlayerStartPoints(AActor* Actor)
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), PlayerStart, PlayerStartArray);
}

//TODO
void ABTLocalMultiGameMode::GetPlayerStartPoints()
{
}

void ABTLocalMultiGameMode::SpawnInputReceivers()
{
}
