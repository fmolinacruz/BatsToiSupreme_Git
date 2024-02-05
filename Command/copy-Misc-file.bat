
REM Set the folder name in a variable
set "src=.\..\Misc"
set "des=.\..\WindowsServer\BatsToiSupreme_Real\Binaries\Win64"

echo start Copy DLL
for /r "%src%" %%f in (*) do (
  if not "%%~sf"=="%src%" (
    xcopy /y "%%f" "%des%"
  )
)

echo start Install.bat
set "src=.\..\Misc\install.bat"
set "des=.\..\WindowsServer\install.bat"
copy /y "%src%" "%des%"

echo start VC_redist.x64.exe
set "src=.\..\Misc\VC_redist.x64.exe"
set "des=.\..\WindowsServer\VC_redist.x64.exe"
copy /y "%src%" "%des%"

echo end copy

pause