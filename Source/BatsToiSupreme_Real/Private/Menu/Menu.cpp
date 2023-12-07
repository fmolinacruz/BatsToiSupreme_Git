// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/Menu.h"


// Constructor
UMenu::UMenu(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set any default values or initialization code here
}

// Called when the widget is constructed in the game
void UMenu::NativeConstruct()
{
	Super::NativeConstruct();

	// Add your widget initialization code here
}

// Called every frame
void UMenu::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Add your per-frame update code here
}
