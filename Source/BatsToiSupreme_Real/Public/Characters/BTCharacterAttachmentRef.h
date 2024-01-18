// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BTCharacterAttachmentRef.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATSTOISUPREME_REAL_API UBTCharacterAttachmentRef : public USceneComponent
{
	GENERATED_BODY()

public:
	UBTCharacterAttachmentRef();

protected:
	virtual void BeginPlay() override;
};
