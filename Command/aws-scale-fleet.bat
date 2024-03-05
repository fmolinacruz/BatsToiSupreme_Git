
set fleetid=%1
set max=%2
set instances=%3

if "%fleetid%" == "" (
	echo fleet id does not exist
  goto:eof 
)
if "%max%" == "" (
	echo --max-size does not exist
  goto:eof 
)
if "%instances%" == "" (
	echo desired-instances does not exist
  goto:eof 
)

echo Start update-fleet-capacity
aws gamelift update-fleet-capacity --fleet-id %feetid% --min-size 0 --max-size %max% --desired-instances %instances%
echo Done update-fleet-capacity

pause