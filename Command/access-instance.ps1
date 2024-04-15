param (
    [Parameter(Mandatory = $false)]
    [string]$Profile = "default",

    [Parameter(Mandatory = $false)]
    [string]$Region = "ap-northeast-1"
)

# Get Fleet list
$FleetList = aws --profile $Profile --region $Region --output json gamelift describe-fleet-attributes | ConvertFrom-Json

# check fleet found
if ($FleetList.FleetAttributes.Count -eq 0) {
    Write-Host "No fleet found"
    exit
}

# Show result id and name
Write-Host "Fleet list"
$FleetList.FleetAttributes | Select-Object FleetId, Name | Format-List
# choose fleet
if ($FleetList.FleetAttributes.Count -eq 1) {
    $FleetId = $FleetList.FleetAttributes[0].FleetId
    Write-Host "Only one fleet found, using fleet: $FleetId"
}
else {
    # Require user choose one by input or tab
    $FleetId = Read-Host "Choose fleet id"
}

$ComputeList = aws --profile $Profile --region $Region --output json gamelift list-compute --fleet-id $FleetId | ConvertFrom-Json

# print result
if ($ComputeList.ComputeList.Count -eq 0) {
    Write-Host "No instance found"
    exit
}

# list all instances
Write-Host "Instance list"
$ComputeList.ComputeList


$ActiveComputelist = $ComputeList.ComputeList | Where-Object { $_.ComputeStatus -eq "Active" } | Measure-Object

if ($ActiveComputelist.Count -eq 0) {
    Write-Host "No active instance found"
    exit
}

if ($ActiveComputelist.Count -eq 1) {
    $ComputeName = $ComputeList.ComputeList[0].ComputeName
    Write-Host "Only one active instance found, using compute: $ComputeName"
}
else {
    # Require user choose one
    $ComputeName = Read-Host "Choose compute name"
}

$Access = aws --profile $Profile --region $Region --output json gamelift get-compute-access --fleet-id $FleetId --compute-name $ComputeName | ConvertFrom-Json

# Store initial values of environment variables
$initial_AWS_ACCESS_KEY_ID = $env:AWS_ACCESS_KEY_ID
$initial_AWS_SECRET_ACCESS_KEY = $env:AWS_SECRET_ACCESS_KEY
$initial_AWS_SESSION_TOKEN = $env:AWS_SESSION_TOKEN

# ssm start session and run the command inside the instance
$env:AWS_ACCESS_KEY_ID = $Access.Credentials.AccessKeyId
$env:AWS_SECRET_ACCESS_KEY = $Access.Credentials.SecretAccessKey
$env:AWS_SESSION_TOKEN = $Access.Credentials.SessionToken
aws --region $Region --output json ssm start-session --target $Access.ComputeName

# Restore initial values of environment variables
$env:AWS_ACCESS_KEY_ID = $initial_AWS_ACCESS_KEY_ID
$env:AWS_SECRET_ACCESS_KEY = $initial_AWS_SECRET_ACCESS_KEY
$env:AWS_SESSION_TOKEN = $initial_AWS_SESSION_TOKEN