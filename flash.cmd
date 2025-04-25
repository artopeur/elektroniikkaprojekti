@echo off

setlocal

if [%1] == [] goto error

set comport=%1
if [%2] == [] goto skip
set file=%2
echo .\avrdude\avrdude.exe -c stk500v1 -p ATMEGA328P -P %comport% -b 19200 -U flash:w:%file%:i
pause
.\avrdude\avrdude.exe -c stk500v1 -p ATMEGA328P -P %comport% -b 19200 -U flash:w:%file%:i
goto EOF

:skip
echo using default debug folder
echo .\avrdude\avrdude.exe -c stk500v1 -p ATMEGA328P -P %comport% -b 19200 -e -U flash:w:.\rfScanner\rfScanner\Debug\rfScanner.hex:i
pause
.\avrdude\avrdude.exe -c stk500v1 -p ATMEGA328P -P %comport% -b 19200 -e -U flash:w:.\rfScanner\rfScanner\Debug\rfScanner.hex:i
goto EOF
:error
echo "no comport set."

:EOF