
REM Set the folder name in a variable
set name=%1
set BUILD_ROOT=.\BuildServer\WindowsServer
set Region=ap-southeast-1

if "%1"==""(
	set name=BuildServer
)

echo Start Upload
REM Upload
aws gamelift upload-build --name "BatstoiServer" --operating-system WINDOWS_2016 --server-sdk-version "5.1.0" --build-root %BUILD_ROOT% --build-version "1" --region %Region%
echo Done Upload

pause