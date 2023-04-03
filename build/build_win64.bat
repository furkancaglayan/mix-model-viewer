pushd "%~dp0"
mkdir "mix-model-viewer"
mklink /J "mix-model-viewer/src" "../src"
"../tools/premake5/premake5.exe" --file=premake5.lua vs2022

@echo off
popd
if NOT ["%errorlevel%"]==["0"] pause

