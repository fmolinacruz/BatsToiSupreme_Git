SET MapName=LVMap_TimeSquare_Multi
SET "currentPath=%~dp0"
SET ExePath="D:\UnrealEngine-5.2.1-release\Engine\Binaries\Win64\UnrealEditor.exe"
SET ProjectPath="%currentPath%BatsToiSupreme_Real.uproject"
SET epicapp=DedicatedServerDev
SET Port=7788
SET GameliftMode=anywhere

CALL %ExePath% %ProjectPath% %MapName% -server -log -epicapp=%epicapp% -MAPNAME=%MapName% -mode=%GameliftMode% -Port=%Port%