param (
    [Parameter(Mandatory = $false)]
    [string]$Profile = "default",
    [Parameter(Mandatory = $false)]
    [string]$Region = "ap-southeast-1",
    [Parameter(Mandatory = $false)]
    [string]$Template = "<default>",
    [Parameter(Mandatory = $true)]
    [string]$BuildId
)

if ($Template -eq "<default>") {
    # get folder path of ps1
    $ScriptPath = $MyInvocation.MyCommand.Path
    $Template = Join-Path (Split-Path $ScriptPath) "gamelift.yaml"
}

$Name="batstoi-gamelift-deployment"
$StackStatus=aws cloudformation describe-stacks --profile $Profile --region $Region --stack-name $Name --query Stacks[].StackStatus --output text 2>Out-Null
if ($null -eq $StackStatus) {
    # create stack
    Write-Host "Stack $Name not found, creating stack"
    aws cloudformation create-stack --template-body file://$Template --stack-name $Name --profile $Profile --region $Region --parameters "ParameterKey=BuildId,ParameterValue=$BuildId" --capabilities CAPABILITY_IAM --on-failure DELETE
    # wait for stack creation
    Write-Host "Waiting for stack creation"
    aws cloudformation wait stack-create-complete --stack-name $Name --profile $Profile --region $Region
    # continue wait if timeout
} else {
    # update stack
    Write-Host "Stack $Name found, updating stack"
    aws cloudformation update-stack --template-body file://$Template --stack-name $Name --profile $Profile --region $Region --parameters "ParameterKey=BuildId,ParameterValue=$BuildId" --capabilities CAPABILITY_IAM
    # wait for stack update
    Write-Host "Waiting for stack update"
    aws cloudformation wait stack-update-complete --stack-name $Name --profile $Profile --region $Region
}
Write-Host 'Done'