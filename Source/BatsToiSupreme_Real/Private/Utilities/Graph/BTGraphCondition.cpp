// Fill out your copyright notice in the Description page of Project Settings.

#include "Utilities/Graph/BTGraphCondition.h"

bool UBTGraphCondition::Verify(APlayerController* PlayerController)
{
	Controller = PlayerController;
	return VerifyCondition(PlayerController);
}

bool UBTGraphCondition::VerifyCondition_Implementation(APlayerController* PlayerController) const
{
	return true;
}

/* Condition OR *****************************************************/

UBTGraphOrCondition::UBTGraphOrCondition() {}

bool UBTGraphOrCondition::VerifyCondition_Implementation(APlayerController* PlayerController) const
{
	for(UBTGraphCondition* Condition : OrConditions)
	{
		if (Condition->Verify(Controller))
		{
			return true;
		}
	}
	return false;
}

/* Condition AND *****************************************************/

UBTGraphAndCondition::UBTGraphAndCondition() {}

bool UBTGraphAndCondition::VerifyCondition_Implementation(APlayerController* PlayerController) const
{
	for(UBTGraphCondition* Condition : AndConditions)
	{
		if (!Condition->Verify(Controller))
		{
			return false;
		}
	}
	return true;
}
