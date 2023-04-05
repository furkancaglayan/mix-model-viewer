pushd "%~dp0"
mkdir "%~dp0/mix-model-viewer"
mklink /J "%~dp0/mix-model-viewer/src" "%~dp0/../src"
"%~dp0/../tools/premake5/premake5.exe" --file=%~dp0/premake5.lua vs2022

@echo off
popd
if NOT ["%errorlevel%"]==["0"] pause
pause
