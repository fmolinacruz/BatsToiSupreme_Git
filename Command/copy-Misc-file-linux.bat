
REM Copy dll to binaries
set "src=.\..\ServerBuildResource\Linux\ToPlugin"
set "des=.\..\LinuxServer\BatsToiSupreme_Real\Plugins\GameLiftServerSDK\ThirdParty\GameLiftServerSDK\Linux\x86_64-unknown-linux-gnu"
echo start Copy DLL
for /r "%src%" %%f in (*) do (
  if not "%%~sf"=="%src%" (
    xcopy /y "%%f" "%des%"
  )
)


REM copy file to Root
set "src=.\..\ServerBuildResource\Linux\ToRoot"
set "des=.\..\LinuxServer"
echo start Copy DLL
for /r "%src%" %%f in (*) do (
  if not "%%~sf"=="%src%" (
    xcopy /y "%%f" "%des%"
  )
)
echo end copy

pause