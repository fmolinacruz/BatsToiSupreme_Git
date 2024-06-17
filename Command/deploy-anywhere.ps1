
param (
    [Parameter(Mandatory = $false)]
    [string]$Profile = "default",
    [Parameter(Mandatory = $false)]
    [string]$Region = "ap-northeast-1",
    [Parameter(Mandatory = $false)]
    [string]$Template = "<default>",
    [Parameter(Mandatory = $true)]
    [string]$EnvName = "<default>",
)

if ($Template -eq "<default>") {
    # get folder path of ps1
    $ScriptPath = $MyInvocation.MyCommand.Path
    $Template = Join-Path (Split-Path $ScriptPath) "gamelift-anywhere.yaml"
}

if ($EnvName -eq "<default>") {
    Write-Host "Missing EnvName"
    exit
ì

$Name = "batstoi-gamelift-debug-$EnvName"
$StackStatus = aws cloudformation describe-stacks --profile $Profile --region $Region --stack-name $Name --query Stacks[].StackStatus --output text 2>$null
if ($null -eq $StackStatus) {
    # create stack
    Write-Host "Stack $Name not found, creating stack"
    aws cloudformation create-stack --template-body file://$Template --stack-name $Name --profile $Profile --region $Region --parameters "ParameterKey=EnvName,ParameterValue=$EnvName" --on-failure DELETE
    # wait for stack creation
    Write-Host "Waiting for stack creation (up to 45 minutes)"
    aws cloudformation wait stack-create-complete --stack-name $Name --profile $Profile --region $Region
}
else {
    # update stack
    Write-Host "Stack $Name found, updating stack"
    aws cloudformation update-stack --template-body file://$Template --stack-name $Name --profile $Profile --region $Region --parameters "ParameterKey=EnvName,ParameterValue=$EnvName"
    # wait for stack update
    Write-Host "Waiting for stack update (up to 45 minutes if the fleet is updated)"
    aws cloudformation wait stack-update-complete --stack-name $Name --profile $Profile --region $Region
}
Write-Host 'Done'