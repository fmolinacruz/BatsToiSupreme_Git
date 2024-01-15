// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/WBTMenu.h"



void UWBTMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (CharacterIn1)
	{
		CharacterAnimationsCPP.Add(CharacterIn1);
	}
	if (CharacterIn2)
	{
		CharacterAnimationsCPP.Add(CharacterIn2);
	}
}
