
REM Copy dll to binaries
set "src=.\..\ServerBuildResource\Windows\ToBinaries"
set "des=.\..\WindowsServer\BatsToiSupreme_Real\Binaries\Win64"
echo start Copy DLL
for /r "%src%" %%f in (*) do (
  if not "%%~sf"=="%src%" (
    xcopy /y "%%f" "%des%"
  )
)


REM copy file to Root
set "src=.\..\ServerBuildResource\Windows\ToRoot"
set "des=.\..\WindowsServer"
echo start Copy DLL
for /r "%src%" %%f in (*) do (
  if not "%%~sf"=="%src%" (
    xcopy /y "%%f" "%des%"
  )
)
echo end copy

pause