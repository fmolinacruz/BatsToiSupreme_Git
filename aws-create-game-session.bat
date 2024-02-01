
REM Set the folder name in a variable
set id=%1
set BUILD_ROOT=.\BuildServer\WindowsServer
set Region=ap-southeast-1

if "%1"==""(
	echo input fleet id
)
else (
	echo Create game session
	aws gamelift create-game-session --fleet-id %id% --maximum-player-session-count 2 --location %Region%
	echo Done 

)

pause