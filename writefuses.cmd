@echo off
setlocal
set low=%1
set high=%2
set extra=%3
set comport=%4

:: low fuse

echo low =  %low%
echo high =  %high%
echo extra =  %extra%
echo comport = %comport%

echo Does this look right? crtl-c if not!!!
pause
echo .\arvdude\avrdude.exe -c arduino -p m328pb -P %comport% -b 19200 -U lfuse:w:%low%:m

:: high fuse

echo .\arvdude\avrdude.exe -c arduino -p m328pb -P %comport% -b 19200 -U hfuse:w:%high%:m

:: extra fuse

echo .\arvdude\avrdude.exe -c arduino -p m328pb -P %comport% -b 19200 -U efuse:w:%extra%:m