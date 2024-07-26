#pragma once
#include "RLLiveLinkUtility.h"
#include "Containers/UnrealString.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "Editor.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

bool FRLLiveLinkUtility::ParseStringToJson( const FString& strJsonString, TSharedPtr<FJsonObject>& spJsonObject )
{
    TSharedRef< TJsonReader<> > kJsonReader = TJsonReaderFactory<>::Create( strJsonString );
    return FJsonSerializer::Deserialize( kJsonReader, spJsonObject );
}

AActor* FRLLiveLinkUtility::SpawnActorToViewport( UClass* pClass,
                                                  const FString& strActorName, 
                                                  const FVector& vLocation,
                                                  const FRotator& kRotation )
{
    UWorld* pWorld = GEditor->GetEditorWorldContext().World();
    if ( !pWorld || !pClass )
    {
        return nullptr;
    }
    AActor* pActor = pWorld->SpawnActor< AActor >( pClass, vLocation, kRotation );
    if ( pActor )
    {
        pActor->SetActorLabel( strActorName );
    }
    return pActor;
}

bool FRLLiveLinkUtility::IsProcessRunning( const FString& strProcessName )
{
    // Create a snapshot of all processes in the system
    HANDLE pSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if ( pSnapshot == INVALID_HANDLE_VALUE )
    {
        return false;
    }

    PROCESSENTRY32 kProcessEntry;
    kProcessEntry.dwSize = sizeof( PROCESSENTRY32 );

    if ( Process32First( pSnapshot, &kProcessEntry ) )
    {
        do
        {
            // Compare the process name with the target process name
            if ( _wcsicmp( kProcessEntry.szExeFile, *strProcessName ) == 0 )
            {
                // Check the process state
                DWORD nExitCode;
                GetExitCodeProcess( OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, kProcessEntry.th32ProcessID ), &nExitCode );

                if ( nExitCode == STILL_ACTIVE )
                {
                    // The process is still running
                    CloseHandle( pSnapshot );
                    return true;
                }
                else
                {
                    // The process has terminated
                    CloseHandle( pSnapshot );
                    return false;
                }
            }
        } while ( Process32Next( pSnapshot, &kProcessEntry ) );
    }

    CloseHandle( pSnapshot );
    return false; // The process is not running
}