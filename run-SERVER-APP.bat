set mode=%1

REM Set the folder name in a variable
set "src=.\BuildServer\WindowsServer\BatsToiSupreme_Real\Binaries\Win64\BatsToiSupreme_RealServer.exe"

%src% -log -mode=%mode%

pause