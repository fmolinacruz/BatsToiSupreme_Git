set mode=%1

REM Set the folder name in a variable
set "src=.\..\WindowsServer\BatsToiSupreme_Real\Binaries\Win64\BatsToiSupreme_RealServer.exe"

%src% -log -epicapp="Tekfall Supreme Dev" -mode=anywhere -Port=7788

pause