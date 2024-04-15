param (
    [Parameter(Mandatory = $false)]
    [string]$Profile = "default",
    [Parameter(Mandatory = $false)]
    [string]$Region = "ap-northeast-1",


    [Parameter(Mandatory = $true)]
    [string]$ExecutePath,
    [Parameter(Mandatory = $false)]
    [string]$ServerParams = "-Log",
    [Parameter(Mandatory = $false)]
    [string]$IP = "127.0.0.1",
    [Parameter(Mandatory = $false)]
    [string]$Port = "7777",


    [Parameter(Mandatory = $false)]
    [string]$FleetId = "<default>",
    [Parameter(Mandatory = $false)]
    [string]$ComputerName = "<default>",
    [Parameter(Mandatory = $false)]
    [string]$Location = "custom-local-1",
    [Parameter(Mandatory = $false)]
    [string]$Stack = "batstoi-gamelift",
    [Parameter(Mandatory = $false)]
    [string]$AnyWhereFleetIDOuput = "AnyWhereFleetID"
)

if ($ComputerName -eq "<default>") {
    # Get computer name
    $ComputerName = (Get-WmiObject -Class Win32_ComputerSystem).Name
    # replace . by -
    $IPStr = $IP -replace "\.", "-"
    $ComputerName = "$ComputerName-$IPStr"
}

if ($FleetId -eq "<default>") {
    # Get fleet id
    Write-Host "Getting fleet id"
    $FleetId = aws cloudformation describe-stacks --region $Region --profile $Profile --query "Stacks[?StackName=='$Stack'][].Outputs[?OutputKey=='$AnyWhereFleetIDOuput'].OutputValue" --output text
    Write-Host "Fleet id: $FleetId"
}

# Register local computer
$Computer = aws --profile $Profile --region $Region gamelift register-compute --fleet-id $FleetId --compute-name $ComputerName --location $Location --ip-address $IP | ConvertFrom-Json

# Get auth token
$Auth = aws --profile $Profile --region $Region gamelift get-compute-auth-token --fleet-id $FleetId --compute-name $ComputerName | ConvertFrom-Json

# Execute process
$AuthToken = $Auth.AuthToken
$Wss = $Computer.Compute.GameLiftServiceSdkEndpoint
&$ExecutePath $ServerParams -Port="$Port" -mode=anywhere --authtoken="$AuthToken" -hostid="$ComputerName" -fleetid="$FleetId" -websocketurl="$Wss"