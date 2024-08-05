// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/EOSUtils.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "OnlineSubsystemTypes.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include <Kismet/GameplayStatics.h>
#include "BTLogging.h"
#include <Utilities/BTGameFunctionLibrary.h>
#include <Utilities/BTHttpRequest.h>

// Sets default values
AEOSUtils::AEOSUtils()
{
 	
}


void AEOSUtils::Login()
{
	/*
	This function will access the EOS OSS via the OSS identity interface to log first into Epic Account Services, and then into Epic Game Services.
	It will bind a delegate to handle the callback event once login call succeeeds or fails.
	All functions that access the OSS will have this structure:
	1-Get OSS interface,
	2-Bind delegate for callback and
	3-Call OSS interface function (which will call the correspongin EOS OSS function)
	*/
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface(); // This is the generic OSS interface that will access the EOS OSS.

	// If you're logged in, don't try to login again.
	// This can happen if your player travels to a dedicated server or different maps as BeginPlay() will be called each time.
	UE_LOG(LogTemp, Log, TEXT("EOSLogin..."));
	FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);

	if (NetId != nullptr && Identity->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		UE_LOG(LogTemp, Log, TEXT("Already Login into EOS..."));
		return;
	}

	/* This binds a delegate so we can run our function when the callback completes. 0 represents the player number.
	You should parametrize this Login function and pass the parameter here for splitscreen.
	*/
	LoginDelegateHandle =
		Identity->AddOnLoginCompleteDelegate_Handle(
			0,
			FOnLoginCompleteDelegate::CreateUObject(
				this,
				&ThisClass::OnEOSLoginCompleted));

	// Grab command line parameters. If empty call hardcoded login function - Hardcoded login function useful for Play In Editor.
	FString AuthType;
	FParse::Value(FCommandLine::Get(), TEXT("AUTH_TYPE="), AuthType);
	UE_LOG(LogTemp, Log, TEXT("Start Logging ..."));
	if (!AuthType.IsEmpty()) // If parameter is NOT empty we can autologin.
	{
		/*
		In most situations you will want to automatically log a player in using the parameters passed via CLI.
		For example, using the exchange code for the Epic Games Store.
		*/
		UE_LOG(LogTemp, Log, TEXT("Logging into EOS... AuthType")); // Log to the UE logs that we are trying to log in.

		if (!Identity->AutoLogin(0))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to login... ")); // Log to the UE logs that we are trying to log in.
			// Clear our handle and reset the delegate.
			Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
			LoginDelegateHandle.Reset();
		}
	}
	else
	{
		/*
		Fallback if the CLI parameters are empty.Useful for PIE.
		The type here could be developer if using the DevAuthTool, ExchangeCode if the game is launched via the Epic Games Launcher, etc...
		*/
		FOnlineAccountCredentials Credentials("AccountPortal", "", "");

		UE_LOG(LogTemp, Log, TEXT("Logging into EOS... AuthType NULL")); // Log to the UE logs that we are trying to log in.

		if (!Identity->Login(0, Credentials))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to login... ")); // Log to the UE logs that we are trying to log in.
																   // Clear our handle and reset the delegate.
			Identity->ClearOnLoginCompleteDelegate_Handle(0, LoginDelegateHandle);
			LoginDelegateHandle.Reset();
		}
	}
}

void AEOSUtils::OnEOSLoginCompleted(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	/*
	This function handles the callback from logging in. You should not proceed with any EOS features until this function is called.
	This function will remove the delegate that was bound in the Login() function.
	*/
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Login callback completed!"));
		UE_LOG(LogTemp, Log, TEXT("Loading cloud data and searching for a session..."));

		// LoadTitleData();  // Load any game related data (in this case a string output to logs)
		// LoadPlayerData(); // Load save game data
		FindSessions(); // For convenience a session is found in sequence here. In a real game this would be done via game UI. Goal here is to show EOS functionality, not game design.
	}
	else // Login failed
	{
		// If your game is online only, you may want to return an errror to the user and return to a menu that uses a different GameMode/PlayerController.

		UE_LOG(LogTemp, Warning, TEXT("EOS login failed. %s"), *Error); // Print sign in failure in logs as a warning.
	}

	// Clear our handle and reset the delegate.
	Identity->ClearOnLoginCompleteDelegate_Handle(LocalUserNum, LoginDelegateHandle);
	LoginDelegateHandle.Reset();
}

void AEOSUtils::FindSessions(FName SearchKey, FString SearchValue) // put default value for example
{
	// This function will find our EOS Session that was created by our DedicatedServer.
	// This function will find our EOS lobby. Note that at the OSS layer we are using a Session that is marked as a lobby.  Code is similar with minor tweaks

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	TSharedRef<FOnlineSessionSearch> Search = MakeShared<FOnlineSessionSearch>();

	// Remove the default search parameters that FOnlineSessionSearch sets up.
	Search->QuerySettings.SearchParams.Empty();

	Search->QuerySettings.Set(SearchKey, SearchValue, EOnlineComparisonOp::Equals); // Seach using our Key/Value pair

	FindSessionsDelegateHandle =
		Session->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleFindSessionsCompleted,
			Search));

	UE_LOG(LogTemp, Log, TEXT("Finding session."));

	if (!Session->FindSessions(0, Search))
	{
		UE_LOG(LogTemp, Warning, TEXT("Finding session failed."));
		// Clear our handle and reset the delegate.
		Session->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsDelegateHandle);
		FindSessionsDelegateHandle.Reset();
	}
}

void AEOSUtils::HandleFindSessionsCompleted(bool bWasSuccessful, TSharedRef<FOnlineSessionSearch> Search)
{
	// This function is triggered via the callback we set in FindSession once the session is found (or there is a failure).
	// This function will triggered via the callback we set in FindSession once the lobby is found (or there is a failure). Finding the lobby here has the similar code as finding a session.

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (bWasSuccessful)
	{
		// added code here to not run into issues when searching for sessions is succesfull, but the number of sessions is 0
		if (Search->SearchResults.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session. Search session = 0"))
			return;
		}
		UE_LOG(LogTemp, Warning, TEXT("Found session. %i"), Search->SearchResults.Num());
		for (auto SessionInSearchResult : Search->SearchResults)
		{
			// Typically you want to check if the session is valid before joining. There is a bug in the EOS OSS where IsValid() returns false when the session is created on a DS.
			// Instead of customizing the engine for this tutorial, we're simply not checking if the session is valid. The code below should go in this if statement once the bug is fixed.
			/*
			if (SessionInSearchResult.IsValid())
			{


			}
			*/

			// Ensure the connection string is resolvable and store the info in ConnectString and in SessionToJoin
			if (Session->GetResolvedConnectString(SessionInSearchResult, NAME_GamePort, ConnectString))
			{
				SessionToJoin = &SessionInSearchResult;
			}

			// For this course we will join the first session found automatically. Usually you would loop through all the sessions and determine which one is best to join.
			break;
		}
		JoinSession();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Find session failed."));
	}

	// Clear our handle and reset the delegate.
	Session->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsDelegateHandle);
	FindSessionsDelegateHandle.Reset();
}

void AEOSUtils::JoinSession()
{
	// Join the session.
	// Same code is used to join the lobby - just some tweaks to the logging

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	JoinSessionDelegateHandle =
		Session->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleJoinSessionCompleted));
	UE_LOG(LogTemp, Log, TEXT("Joining session."));
	if (!Session->JoinSession(0, "SessionName", *SessionToJoin))
	{
		UE_LOG(LogTemp, Log, TEXT("Join session failed."));

		// Clear our handle and reset the delegate.
		Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionDelegateHandle);
		JoinSessionDelegateHandle.Reset();
	}
}

void AEOSUtils::HandleJoinSessionCompleted(FName FSessionName, EOnJoinSessionCompleteResult::Type Result)
{
	// This function is triggered via the callback we set in JoinSession once the session is joined (or there is a failure)

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Log, TEXT("Joined session. %s"), *FSessionName.ToString());
		if (GEngine)
		{
			FString sessionId = Session->GetNamedSession(FSessionName)->GetSessionIdStr();
			UE_LOG(LogTemp, Warning, TEXT("Session: Joined! %s"), *sessionId);
			FString url = UBTGameFunctionLibrary::GetGetSessionDataURL();
			// Get Eos Session Data
			GetEosSessionData(*url, *sessionId);

			// For the purposes of this tutorial overriding the ConnectString to point to localhost as we are testing locally. In a real game no need to override. Make sure you can connect over UDP to the ip:port of your server!
			/*ConnectString = "192.168.35.62:7788";
			FURL DedicatedServerURL(nullptr, *ConnectString, TRAVEL_Absolute);
			FString DedicatedServerJoinError;
			auto DedicatedServerJoinStatus = GEngine->Browse(GEngine->GetWorldContextFromWorldChecked(GetWorld()), DedicatedServerURL, DedicatedServerJoinError);
			if (DedicatedServerJoinStatus == EBrowseReturnVal::Failure)
			{
				UE_LOG(LogTemp, Error, TEXT("Failed to browse for dedicated server. Error is: %s"), *DedicatedServerJoinError);
			}*/

			// To be thorough here you should modify your derived UGameInstance to handle the NetworkError and TravelError events.
			// This should also be done to handle the error "FULL" returned by the server.
			// As we are testing locally, and for the purposes of keeping this tutorial simple, this is omitted.
		}
	}

	// Clear our handle and reset the delegate.
	Session->ClearOnJoinSessionCompleteDelegate_Handle(JoinSessionDelegateHandle);
	JoinSessionDelegateHandle.Reset();
}

void AEOSUtils::LoadTitleData()
{
	/*
	This function is triggered by the login callback once the player has logged in (client only).
	Files must first be enumerated before they can be read. In this course we will read from the 1st file.
	*/

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineTitleFilePtr TitleFile = Subsystem->GetTitleFileInterface();

	EnumTitleFilesDelegateHandle = TitleFile->AddOnEnumerateFilesCompleteDelegate_Handle(FOnEnumerateFilesCompleteDelegate::CreateUObject(
		this,
		&ThisClass::HandleEnumTitleFilesCompleted));

	if (!TitleFile->EnumerateFiles())
	{
		UE_LOG(LogTemp, Error, TEXT("Error enumerating title storage files."));

		// Clear our handle and reset the delegate.
		TitleFile->ClearOnEnumerateFilesCompleteDelegate_Handle(EnumTitleFilesDelegateHandle);
		EnumTitleFilesDelegateHandle.Reset();
	}
}

void AEOSUtils::HandleEnumTitleFilesCompleted(bool bWasSuccessfull, const FString& Error)
{
	// Callback function for enumerating title data storage files.
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineTitleFilePtr TitleFile = Subsystem->GetTitleFileInterface();

	if (bWasSuccessfull)
	{
		// Set an array of files we can populate
		TArray<FCloudFileHeader> TitleFiles;
		TitleFile->GetFileList(TitleFiles);

		// Get the the filenames from our array of files
		TArray<FString> TitleFileNames;
		for (const auto& File : TitleFiles)
		{
			// Add all the title storage file names to array
			TitleFileNames.Add(File.FileName);
		}

		ReadTitleFileDelegateHandle = TitleFile->AddOnReadFileCompleteDelegate_Handle(FOnReadFileCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleReadTitleFileCompleted));

		// To keep things simple we are only reading the 1st file which is a .txt file. We will output the file content to the logs.
		if (!TitleFile->ReadFile(TitleFileNames[0]))
		{
			UE_LOG(LogTemp, Error, TEXT("Error reading title storage file %s."), *TitleFileNames[0]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error enumerating title storage files. Error is: %s"), *Error);
	}

	// Clear our handle and reset the delegate.
	TitleFile->ClearOnEnumerateFilesCompleteDelegate_Handle(EnumTitleFilesDelegateHandle);
	EnumTitleFilesDelegateHandle.Reset();
}

void AEOSUtils::HandleReadTitleFileCompleted(bool bWasSuccessfull, const FString& FileName)
{
	// Callback function for reading 1st file in title data storage.
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineTitleFilePtr TitleFile = Subsystem->GetTitleFileInterface();

	if (bWasSuccessfull)
	{
		TArray<uint8> FileContents; // We need an array to output the serialized title data storage file data.
		if (TitleFile->GetFileContents(FileName, FileContents))
		{
			// Deserialize file and write to logs
			char* FileData;
			try
			{
				FileData = new char[FileContents.Num()];
			}
			catch (std::bad_alloc)
			{
				UE_LOG(LogTemp, Error, TEXT("Unable to allocate memory for title storage data"));

				// Clear our handle and reset the delegate.
				TitleFile->ClearOnReadFileCompleteDelegate_Handle(ReadTitleFileDelegateHandle);
				ReadTitleFileDelegateHandle.Reset();
				return;
			}

			// Check file contents and hardcode log outputs to prevent log injection
			std::memcpy(FileData, FileContents.GetData(), FileContents.Num());
			FString FileDataAsFString = ANSI_TO_TCHAR(FileData);
			if (FileDataAsFString.Equals("Game data"))
			{
				UE_LOG(LogTemp, Log, TEXT("File contents are: Game data"));
			}

			// Clean up memory
			delete FileData;
			FileData = nullptr;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get file contents for file named: %s."), *FileName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error reading title storage file %s."), *FileName);
	}

	// Clear our handle and reset the delegate.
	TitleFile->ClearOnReadFileCompleteDelegate_Handle(ReadTitleFileDelegateHandle);
	ReadTitleFileDelegateHandle.Reset();
}

void AEOSUtils::WritePlayerDataStorage(FString FileName, TArray<uint8> FileData)
{
	// Function called to save game. This is called when the ESC key is pressed. See the Quit() function in the character class. Only called on Clients.

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	IOnlineUserCloudPtr UserCloud = Subsystem->GetUserCloudInterface();

	// Create delagate handle
	WritePlayerDataStorageDelegateHandle =
		UserCloud->AddOnWriteUserFileCompleteDelegate_Handle(
			FOnWriteUserFileCompleteDelegate::CreateUObject(
				this,
				&ThisClass::HandleWritePlayerDataStorageCompleted));

	// Check if player is online before trying to write to player data storage
	FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);

	if (!NetId || Identity->GetLoginStatus(*NetId) != ELoginStatus::LoggedIn)
	{
		UE_LOG(LogTemp, Log, TEXT("Game won't be saved as player isn't logged in."));
		return;
	}

	if (!UserCloud->WriteUserFile(*NetId, FileName, FileData))
	{
		UE_LOG(LogTemp, Error, TEXT("Error writing file with name: %s to player data storage"), *FileName);

		// Clear our handle and reset the delegate.
		UserCloud->ClearOnWriteUserFileCompleteDelegate_Handle(WritePlayerDataStorageDelegateHandle);
		WritePlayerDataStorageDelegateHandle.Reset();
	}
}

void AEOSUtils::HandleWritePlayerDataStorageCompleted(bool bWasSuccessful, const FUniqueNetId& UserId, const FString& FileName)
{
	// callback function when file write has completed
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineUserCloudPtr UserCloud = Subsystem->GetUserCloudInterface();

	if (bWasSuccessful)
	{
		// If saving the game was a success quit
		//ConsoleCommand(TEXT("quit"));
	}
	else
	{
		// This means that the game wasn't saved. The game should notify the player and not just quit.
		UE_LOG(LogTemp, Error, TEXT("Error writing file with name: %s to player data storage"), *FileName);
	}

	// Clear our handle and reset the delegate.
	UserCloud->ClearOnWriteUserFileCompleteDelegate_Handle(WritePlayerDataStorageDelegateHandle);
	WritePlayerDataStorageDelegateHandle.Reset();
}

void AEOSUtils::LoadPlayerData()
{
	/*
	This function is triggered by the login callback once the player has logged in (client only).
	Files must first be enumerated before they can be read. In this course we will read from the 1st file only.
   */

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	IOnlineUserCloudPtr PlayerData = Subsystem->GetUserCloudInterface();

	EnumPlayerFilesDelegateHandle = PlayerData->AddOnEnumerateUserFilesCompleteDelegate_Handle(FOnEnumerateUserFilesCompleteDelegate::CreateUObject(
		this,
		&ThisClass::HandleEnumPlayerFilesCompleted));

	// Check if player is online before trying to write to player data storage
	FUniqueNetIdPtr NetId = Identity->GetUniquePlayerId(0);

	if (!NetId || Identity->GetLoginStatus(*NetId) != ELoginStatus::LoggedIn)
	{
		return;
	}

	PlayerData->EnumerateUserFiles(*NetId);
}

void AEOSUtils::HandleEnumPlayerFilesCompleted(bool bWasSuccessfull, const FUniqueNetId& NetId)
{
	// Callback function for enumerating player data storage files.
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineUserCloudPtr PlayerData = Subsystem->GetUserCloudInterface();

	if (bWasSuccessfull)
	{
		// Set an array of files we can populate
		TArray<FCloudFileHeader> PlayerFiles;
		PlayerData->GetUserFileList(NetId, PlayerFiles);

		if (PlayerFiles.Num() == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No player files in player data storage."));
			return;
		}

		TArray<FString> PlayerFileNames;

		for (const auto& File : PlayerFiles)
		{
			// Add all the player data storage file names to array
			PlayerFileNames.Add(File.FileName);
		}

		ReadPlayerDataFileDelegateHandle = PlayerData->AddOnReadUserFileCompleteDelegate_Handle(FOnReadUserFileCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleReadPlayerFileCompleted));

		// To keep things simple we are only reading the 1st file. The player's initial location will change to the location of when the player quit the last instance.

		if (!PlayerData->ReadUserFile(NetId, PlayerFileNames[0]))
		{
			UE_LOG(LogTemp, Error, TEXT("Error reading player data storage file, filename: %s."), *PlayerFileNames[0]);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error enumerating player data storage files."));
	}

	PlayerData->ClearOnEnumerateUserFilesCompleteDelegate_Handle(EnumPlayerFilesDelegateHandle);
	EnumPlayerFilesDelegateHandle.Reset();
}

void AEOSUtils::HandleReadPlayerFileCompleted(bool bWasSuccessfull, const FUniqueNetId& UserId, const FString& FileName)
{
	// Callback function for reading 1st file in player data storage.

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineUserCloudPtr PlayerData = Subsystem->GetUserCloudInterface();

	if (bWasSuccessfull)
	{
		TArray<uint8> FileContents;
		if (PlayerData->GetFileContents(UserId, FileName, FileContents))
		{
			// Should use a USaveGame
			LoadGame(FileContents);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to get file contents for file named: %s."), *FileName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error reading player data storage file %s."), *FileName);
	}
	PlayerData->ClearOnReadUserFileCompleteDelegate_Handle(ReadPlayerDataFileDelegateHandle);
	ReadPlayerDataFileDelegateHandle.Reset();
}


void AEOSUtils::UpdateSession()
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	OnUpdateSessionCompleteDelegate = FOnUpdateSessionCompleteDelegate::CreateUObject(this, &AEOSUtils::OnUpdateSessionComplete);
	HostSettings = new FOnlineSessionSettings();
	HostSettings->Set(FName(TEXT("UPDATESETTING2")), 99, EOnlineDataAdvertisementType::ViaOnlineService);
	Session->UpdateSession("SessionName", *HostSettings, true);
}

void AEOSUtils::OnUpdateSessionComplete(FName FSessionName, bool bWasSuccessful)
{
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();
	BTLOG_DISPLAY("OnUpdateSessionComplete %s bSuccess: %d", *FSessionName.ToString(), bWasSuccessful);
	Session->ClearOnUpdateSessionCompleteDelegate_Handle(OnUpdateSessionCompleteDelegateHandle);
}

void AEOSUtils::LoadGame(TArray<uint8> LoadData)
{
	// This function is part of the Login() callback callstack. It is only called on clients. LoadData is the serialized data retrieved from the Player Data Storage backend.
	// FVector is 12 bytes.
	if (LoadData.Num() != 24)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid Load data. Initial character pawn location should be of 12 bytes. Default starting location will be used."));
		return;
	}

}

void AEOSUtils::SaveGame()
{
	/*
	Called from the Quit() function in the character class. This is a "pseudo" save game function. The purpose here is to show how to use EOS Player Data Storage.
	This is not an example on how a game should be saved. You should use a derived USaveGame class and save all data that is needed for your game.
   */

	// Prepare our SaveData - serialize the FVector
	TArray<uint8> SaveData;

	// Write to player data storage
	WritePlayerDataStorage("CharacterPawnLocation", SaveData);
}

void AEOSUtils::GetEosSessionData(const FString& url, const FString& SessionId)
{
	ABTHttpRequest* HttpRequestActor = Cast<ABTHttpRequest>(UBTGameFunctionLibrary::GetOrCreateWorldActor(GetWorld(), ABTHttpRequest::StaticClass()));
	if (HttpRequestActor)
	{
		UVaRestRequestJSON* Request = HttpRequestActor->CreateRequest(EVaRestRequestVerb::GET, EVaRestRequestContentType::x_www_form_urlencoded_url);
		Request->OnRequestComplete.AddDynamic(this, &AEOSUtils::HandleGetEosSessionDataCompleted);
		Request->SetHeader(TEXT("Authorization"), UBTGameFunctionLibrary::GetAccountId());
		Request->GetRequestObject()->SetStringField(TEXT("sessionID"), SessionId);
		Request->ProcessURL(url);
	}
}

void AEOSUtils::HandleGetEosSessionDataCompleted(UVaRestRequestJSON* Request)
{
	if (Request->GetStatus() == EVaRestRequestStatus::Succeeded)
	{
		// Parse the response JSON
		FString ResponseContent = Request->GetResponseContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("HandleGetDataCompleted Response: %s"), *ResponseContent);
		UVaRestJsonObject* Data = Request->GetResponseObject()->GetObjectField(TEXT("data"));
		if (Data)
		{
			FString BEUrl = Data->GetStringField(TEXT("BEUrl"));
			BTLOG_WARNING("[ABTLobbyPlayerController] [OnGetEosSessionDataCompleted] %s", *BEUrl);

			UGameplayStatics::OpenLevel(GetWorld(), *BEUrl);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[ABTLobbyPlayerController] [OnGetEosSessionDataCompleted]: Request failed"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("OnGetCloudHostIpCompleted: Request failed"));
	}
}


void AEOSUtils::CreateSession(FName KeyName, FString KeyValue) // Dedicated Server Only
{
	// This function will create an EOS Session.
	UE_LOG(LogTemp, Warning, TEXT("ABTGameSession::CreateSession"));
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface(); // Retrieve the generic session interface.

	// Bind delegate to callback function
	CreateSessionDelegateHandle =
		Session->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleCreateSessionCompleted));

	// Set session settings
	TSharedRef<FOnlineSessionSettings> SessionSettings = MakeShared<FOnlineSessionSettings>();
	SessionSettings->NumPublicConnections = MaxNumberOfPlayersInSession; // We will test our sessions with 2 players to keep things simple
	SessionSettings->bShouldAdvertise = true;							 // This creates a public match and will be searchable. This will set the session as joinable via presence.
	SessionSettings->bUsesPresence = false;								 // No presence on dedicated server. This requires a local user.
	SessionSettings->bAllowJoinViaPresence = false;						 // superset by bShouldAdvertise and will be true on the backend
	SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;			 // superset by bShouldAdvertise and will be true on the backend
	SessionSettings->bAllowInvites = false;								 // Allow inviting players into session. This requires presence and a local user.
	SessionSettings->bAllowJoinInProgress = false;						 // Once the session is started, no one can join.
	SessionSettings->bIsDedicated = true;								 // Session created on dedicated server.
	SessionSettings->bUseLobbiesIfAvailable = false;					 // This is an EOS Session not an EOS Lobby as they aren't supported on Dedicated Servers.
	SessionSettings->bUseLobbiesVoiceChatIfAvailable = false;
	SessionSettings->bUsesStats = true; // Needed to keep track of player stats.

	// This custom attribute will be used in searches on GameClients.
	SessionSettings->Settings.Add(KeyName, FOnlineSessionSetting((KeyValue), EOnlineDataAdvertisementType::ViaOnlineService));

	// Create session.
	UE_LOG(LogTemp, Warning, TEXT("Creating session..."));

	if (!Session->CreateSession(0, SessionName, *SessionSettings))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
		Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
		CreateSessionDelegateHandle.Reset();
	}
}

void AEOSUtils::HandleCreateSessionCompleted(FName EOSSessionName, bool bWasSuccessful) // Dedicated Server Only
{
	// This function is triggered via the callback we set in CreateSession once the session is created (or there is a failure to create)
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface(); // Retrieve the generic session interface.

	// Nothing special here, simply log that the session is created.
	if (bWasSuccessful)
	{
		FString sessionId = Session->GetNamedSession(EOSSessionName)->GetSessionIdStr();
		OnSessionCreated.Broadcast(sessionId);
		OnSessionCreated.Clear();
		UE_LOG(LogTemp, Warning, TEXT("Session: %s Created 1! %s"), *EOSSessionName.ToString(), *sessionId);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
	}

	// Clear our handle and reset the delegate.
	Session->ClearOnCreateSessionCompleteDelegate_Handle(CreateSessionDelegateHandle);
	CreateSessionDelegateHandle.Reset();
}


void AEOSUtils::StartSession()
{
	// This function is called once all players are registered. It will mark the EOS Session as started.
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Bind delegate to callback function
	StartSessionDelegateHandle =
		Session->AddOnStartSessionCompleteDelegate_Handle(FOnStartSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleStartSessionCompleted));

	if (!Session->StartSession(SessionName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to start session!"));
		Session->ClearOnStartSessionCompleteDelegate_Handle(StartSessionDelegateHandle);
		StartSessionDelegateHandle.Reset();
	}
}

void AEOSUtils::HandleStartSessionCompleted(FName EOSSessionName, bool bWasSuccessful)
{
	// This function is triggered via the callback we set in StartSession once the session is started (or there is a failure).
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Just log, clear and reset delegate.
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session Started!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to start session! (From Callback)"));
	}

	Session->ClearOnStartSessionCompleteDelegate_Handle(StartSessionDelegateHandle);
	StartSessionDelegateHandle.Reset();
}

void AEOSUtils::EndSession()
{
	// This function is called once all players have left the session. It will mark the EOS Session as ended.
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Bind delegate to callback function
	EndSessionDelegateHandle =
		Session->AddOnEndSessionCompleteDelegate_Handle(FOnEndSessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleEndSessionCompleted));

	if (!Session->EndSession(SessionName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to end session!"));
		Session->ClearOnEndSessionCompleteDelegate_Handle(EndSessionDelegateHandle);
		EndSessionDelegateHandle.Reset();
	}
}

void AEOSUtils::HandleEndSessionCompleted(FName EOSSessionName, bool bWasSuccessful)
{
	// This function is triggered via the callback we set in EndSession once the session is ended (or there is a failure).
	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	// Just log, clear and reset delegate.
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session ended!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to end session! (From Callback)"));
	}

	Session->ClearOnEndSessionCompleteDelegate_Handle(EndSessionDelegateHandle);
	EndSessionDelegateHandle.Reset();
}

void AEOSUtils::DestroySession()
{
	// Called when EndPlay() is called. This will destroy the EOS Session which will remove it from the EOS backend.

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	DestroySessionDelegateHandle =
		Session->AddOnDestroySessionCompleteDelegate_Handle(FOnDestroySessionCompleteDelegate::CreateUObject(
			this,
			&ThisClass::HandleDestroySessionCompleted));

	if (!Session->DestroySession(SessionName))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session.")); // Log to the UE logs that we are trying to log in.
		Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
		DestroySessionDelegateHandle.Reset();
	}
}

void AEOSUtils::HandleDestroySessionCompleted(FName EOSSessionName, bool bWasSuccesful)
{
	// This function is triggered via the callback we set in DestroySession once the session is destroyed (or there is a failure).

	IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
	IOnlineSessionPtr Session = Subsystem->GetSessionInterface();

	if (bWasSuccesful)
	{
		//bSessionExists = false; // Mark that the session doesn't exist. This way next time BeginPlay is called a new session will be created.
		UE_LOG(LogTemp, Log, TEXT("Destroyed session succesfully."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy session."));
	}

	Session->ClearOnDestroySessionCompleteDelegate_Handle(DestroySessionDelegateHandle);
	DestroySessionDelegateHandle.Reset();
}
