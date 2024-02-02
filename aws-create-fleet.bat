
set fleetname=%1
set buildid=%2
set path=C:\game\BatsToiSupreme_Real\Binaries\Win64\BatsToiSupreme_RealServer.exe

if "%fleetname%" == "" (
	echo fleet name does not exist
  goto:eof 
)
if "%buildid%" == "" (
	echo build id does not exist
  goto:eof 
)

echo Start update-fleet-capacity

aws gamelift create-fleet --name %fleetname% --build-id %buildid% --ec2-instance-type c5.large --fleet-type SPOT --server-launch-path %path%

echo Done update-fleet-capacity

pause