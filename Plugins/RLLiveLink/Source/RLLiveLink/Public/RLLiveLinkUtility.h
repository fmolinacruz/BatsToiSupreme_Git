#pragma once
#include "Templates/SharedPointer.h"

class FString;
class FJsonObject;
class FRLLiveLinkUtility
{
public:
    static bool ParseStringToJson(const FString& strJsonString, TSharedPtr<FJsonObject>& spJsonObject );
    static AActor* SpawnActorToViewport( UClass* pClass, 
                                         const FString& strActorName,
                                         const FVector& vLocation = FVector::Zero(),
                                         const FRotator& kRotation =  FRotator::ZeroRotator );
    static bool IsProcessRunning( const FString& processName );
};