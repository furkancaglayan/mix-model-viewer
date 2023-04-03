
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
   
   links {"glew32"}
   links {"glfw3"}
 
   includedirs {"../dependencies/*/include", "../dependencies/*" }
   files { "mix-model-viewer/src/**.h", "mix-model-viewer/src/**.cpp", "mix-model-viewer/src/dummy_file.cpp" }

   
   filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "Full"
		optimize "Off"
      targetdir "mix-model-viewer/Debug"
      libdirs {"../dependencies/*/lib", "../dependencies/*/lib/Debug" }
      bindirs  {"../dependencies/*/bin", "../dependencies/*/bin/Debug"}
      links {"freeglutd"}

   filter "configurations:Release"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"
      targetdir "mix-model-viewer/Release"
      libdirs {"../dependencies/**/lib", "../dependencies/*/lib/Release" }
      bindirs  {"../dependencies/*/bin", "../dependencies/*/bin/Release"}
      links {"freeglut"}

   filter "configurations"
      defines {"TARGET_SYSTEM_WIN64"}

   
	filter { "system:windows" }
      links { "OpenGL32" }

   filter { "system:not windows" }
      links { "GL" }



