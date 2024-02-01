
REM Set the folder name in a variable
set "src=.\Misc"
set "des=.\BuildServer\WindowsServer\BatsToiSupreme_Real\Binaries\Win64"

echo start Copy
for /r "%src%" %%f in (*) do (
  if not "%%~sf"=="%src%" (
    xcopy /y "%%f" "%des%"
  )
)
echo end copy

pause