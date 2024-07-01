SET MapName=LVMap_TimeSquare_Multi
SET "currentPath=%~dp0"
SET ExePath="D:\UnrealEngine-5.2.1-release\Engine\Binaries\Win64\UnrealEditor.exe"
SET ProjectPath="%currentPath%BatsToiSupreme_Real.uproject"
SET epicapp=GameClientDev
SET AUTH_TYPE=developer
SET AUTH_LOGIN="localhost:6666"
SET AUTH_PASSWORD="batstoi"
SET LANHOST=192.168.35.66:7788

CALL %ExePath% %ProjectPath% -debug -game -log -AUTH_TYPE=%AUTH_TYPE% -AUTH_LOGIN=%AUTH_LOGIN% -AUTH_PASSWORD=%AUTH_PASSWORD% -epicapp=%epicapp% -LANHOST=%LANHOST% -ResX=1280 -ResY=720 -windowed
