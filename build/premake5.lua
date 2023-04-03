
workspace "MixModelViewer"
   configurations { "Debug", "Release" }
   language "C++"
	cppdialect "C++14"
   platforms {"Win64"}
   location "mix-model-viewer"
   targetdir "../bin/%{cfg.system}/%{cfg.buildcfg}"
   architecture "x86_64"
   exceptionhandling "On"
   functionlevellinking  "On"
   editAndContinue "On"
   flags { "FatalCompileWarnings", "MultiProcessorCompile" }

   filter { "platforms:Win64" }
      system "Windows"

project "MixModelViewer"
   kind "ConsoleApp"
   location "mix-model-viewer"
   
   includedirs {"../dependencies/*/include", "../dependencies/*" }
   libdirs {"../dependencies/*/lib", "../dependencies/*/lib/%{cfg.buildcfg}" }
   bindirs  {"../dependencies/*/bin", "../dependencies/*/bin/%{cfg.buildcfg}"}
   targetdir "../bin/%{cfg.buildcfg}"

   files { "mix-model-viewer/src/**.h", "mix-model-viewer/src/**.cpp" }
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "Full"
		optimize "Off"
      links {"glew32", "freeglutd", "glfw3"}

   filter "configurations:Release"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"
      libdirs {"../dependencies/**/lib", "../dependencies/*/lib/Release" }
      bindirs  {"../dependencies/*/bin", "../dependencies/*/bin/Release"}
      links {"glew32", "freeglut", "glfw3"}

   filter "configurations"
      defines {"TARGET_SYSTEM_WIN64"}

   
	filter { "system:windows" }
      links { "OpenGL32" }

   filter { "system:not windows" }
      links { "GL" }


include "../dependencies/dependencies.lua"
