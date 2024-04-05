// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class BATSTOISUPREME_REAL_API VaRestHttpRequest
{
public:
	VaRestHttpRequest();
	~VaRestHttpRequest();

	void MatchMakingCreate();
	void MatchMakingGetStatus();

	UVaRestSubsystem* GetVARestSub();

private:
	FString HostURL;
};
