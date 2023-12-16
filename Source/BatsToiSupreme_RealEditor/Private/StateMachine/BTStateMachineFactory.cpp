// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/BTStateMachineFactory.h"

#include "StateMachine/BTStateMachine.h"

UBTStateMachineFactory::UBTStateMachineFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UBTStateMachine::StaticClass();
}

UObject* UBTStateMachineFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UObject>(InParent, InClass, InName, Flags);
}

FName UBTStateMachineFactory::GetNewAssetThumbnailOverride() const
{
	return "";
}

FText UBTStateMachineFactory::GetDisplayName() const
{
	return FText::FromString("Batstoi State Machine");
}

FText UBTStateMachineFactory::GetToolTip() const
{
	return FText::FromString("Create a new State Machine");
}

FString UBTStateMachineFactory::GetDefaultNewAssetName() const
{
	return "New State Machine";
}
