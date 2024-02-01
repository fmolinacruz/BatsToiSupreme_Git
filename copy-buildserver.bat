
REM Set the folder name in a variable
set "src=.\..\WindowsServer"
set "des=.\BuildServer\WindowsServer"

echo start Copy
xcopy %src% %des% /E /H /I /Q /Y
echo end copy

pause