@echo off
setlocal
if [%1] == [] goto error
set low=%1
if [%2] == [] goto error
set high=%2
if [%3] == [] goto error
set extra=%3
if [%4] == [] goto error
set comport=%4

:: low fuse

echo low =  %low%
echo high =  %high%
echo extra =  %extra%
echo comport = %comport%

echo Does this look right? crtl-c if not!!!
pause
echo .\arvdude\avrdude.exe -c arduino -p m328pb -P %comport% -b 19200 -U lfuse:w:%low%:m -U hfuse:w:%high%:m -U efuse:w:%extra%:m


goto :EOF

:error

echo Error Occurred. 
echo Check inputs. 
echo writefuses needs inputs (lowfuse highfuse extrafuse comport) in that order. Divide by space not commas.
