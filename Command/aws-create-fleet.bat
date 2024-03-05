set fleetname=%1
set buildid=%2

set path=C:\game\BatsToiSupreme_Real\Binaries\Win64\BatsToiSupreme_RealServer.exe
set instance-type=c5.large
set fleet-type=SPOT
set instance-role-arn='arn:aws:iam::458885322255:role/BatstoiInstanceRole'
set metric-groups=batstoi
set server-launch-parameters='-AbsLog=c:\game\logs\game-server.log'
set ec2-inbound-permissions='FromPort=7777,ToPort=7777,IpRange=0.0.0..0/0,Protocol=UDP'

if "%fleetname%" == "" (
	echo fleet name does not exist
  goto:eof 
)
if "%buildid%" == "" (
	echo build id does not exist
  goto:eof 
)

echo Start update-fleet-capacity

aws gamelift create-fleet --name %fleetname% --build-id %buildid% --ec2-instance-type %instance-type% --fleet-type %fleet-type%
rem aws gamelift create-fleet --name %fleetname% --build-id %buildid% --ec2-instance-type %instance-type% --fleet-type %fleet-type% --server-launch-path %path% --server-launch-parameters %server-launch-parameters% --instance-role-arn %instance-role-arn% --ec2-inbound-permissions %ec2-inbound-permissions% --metric-groups %metric-groups%

echo Done update-fleet-capacity

pause