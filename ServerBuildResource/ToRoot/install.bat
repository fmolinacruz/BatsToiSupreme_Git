VC_redist.x64.exe /q
DISM /Online /Enable-Feature /FeatureName:NetFx3 /All
Engine\Extras\Redist\en-us\UEPrereqSetup_x64.exe /q
msiexec /i "amazon-cloudwatch-agent.msi"
powershell -c "& $Env:ProgramFiles\Amazon\AmazonCloudWatchAgent\amazon-cloudwatch-agent-ctl.ps1 -m ec2 -c file:amazon-cloudwatch-agent.json -a fetch-config -s"