
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

   libdirs {"../dependencies/*/lib" }
   includedirs {"../dependencies/*/include"}
   bindirs  {"../dependencies/*/bin"}

   files { "../src/**.h", "../src/**.cpp", "../src/dummy_file.cpp" }

   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      targetdir "mix-model-viewer/Debug"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      targetdir "mix-model-viewer/Release"

   filter "configurations"
      defines {"TARGET_SYSTEM_WIN64"}



