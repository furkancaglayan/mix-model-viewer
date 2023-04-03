
os.mkdir("mix-model-viewer")

workspace "MixModelViewer"
   configurations { "Debug", "Release" }
   platforms {"Win64"}
   location "mix-model-viewer"
   targetdir "mix-model-viewer"
   filter { "platforms:Win64" }
      system "Windows"
      architecture "x86_64"

project "MixModelViewer"
   kind "ConsoleApp"
   language "C++"
   location "mix-model-viewer"
   
   links {"glew32"}
   links {"glfw3"}

 
   includedirs {"../dependencies/*/include", "../dependencies/*" }

   files { "../src/**.h", "../src/**.cpp", "../src/dummy_file.cpp" }

   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      targetdir "mix-model-viewer/Debug"
      libdirs {"../dependencies/*/lib", "../dependencies/*/lib/Debug" }
      bindirs  {"../dependencies/*/bin", "../dependencies/*/bin/Debug"}
      links {"freeglutd"}

   filter "configurations:Release"
      defines { "NDEBUG" }
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



