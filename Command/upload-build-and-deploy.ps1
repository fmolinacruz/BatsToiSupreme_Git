param (
    [Parameter(Mandatory = $false)]
    [string]$Profile = "default",
    [Parameter(Mandatory = $false)]
    [string]$Region = "ap-southeast-1",
    [Parameter(Mandatory = $false)]
    [string]$Path = ".\"
)

# timetamp
$Timestamp = Get-Date -Format "yyyyMMdd.HHmmss"
$Version = "v$Timestamp"

# upload build
$RealPath = Resolve-Path $Path
Write-Host "Uploading build in $RealPath as version $Version"
aws --profile $Profile --region $Region gamelift upload-build --name "BatsToi Game Server (version $Version)" --operating-system WINDOWS_2016 --server-sdk-version "5.1.2" --build-root $Path --build-version $Version

# Get the build version for fleet deployment
$query = "Builds[?Version==``$Version``].BuildId"
$BuildId = aws --profile $Profile --region $Region gamelift list-builds --query $query --output text
if ($null -eq $BuildId -or $BuildId -eq "None") {
    Write-Host "Build not found"
    exit
}

# deploy fleet
Write-Host "Deploying fleet with build $BuildId"
$ScriptPath = $MyInvocation.MyCommand.Path
$Deploy = Join-Path (Split-Path $ScriptPath) "deploy.ps1"
. $Deploy -Profile $Profile -Region $Region -BuildId $BuildId