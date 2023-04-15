pushd "%~dp0"

"%~dp0/../tools/premake5/premake5.exe" --file=%~dp0/mix.lua vs2022
@echo off
popd
if NOT ["%errorlevel%"]==["0"] pause
pause
