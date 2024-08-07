// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/BTLocalInputReceiver.h"
#include "PlayerCommon/BTLocalPlayerController.h"


// Sets default values
ABTLocalInputReceiver::ABTLocalInputReceiver()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ABTLocalInputReceiver::InitializeWithPlayerController(ABTLocalPlayerController* NewPlayerController, int32 PlayerIndex)
{
	if (!NewPlayerController)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NewPlayerController is nullptr"));
		}
		return;
	}
	CurrentPlayerController = NewPlayerController;
	CurrentPlayerIndex = PlayerIndex;
}

// Called when the game starts or when spawned
void ABTLocalInputReceiver::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABTLocalInputReceiver::CreateMenuUI()
{
	if (CurrentPlayerController)
	{
		MenuWidgetRefCPP = CurrentPlayerController->CreateMenuWidget();

		// MenuWidgetRefCPP is nullptr;
		if (!MenuWidgetRefCPP)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MyMenuWidget is nullptr"));
			}
		}
	}
}
