
os.mkdir("mix-model-viewer")

workspace "MixModelViewer"
   configurations { "Debug", "Release" }
   platforms {"Win64", "Linux"}
   location "mix-model-viewer"
   targetdir "mix-model-viewer"
   filter { "platforms:Win64" }
      system "Windows"
      architecture "x86_64"
 

project "MixModelViewer"
   kind "ConsoleApp"
   language "C++"
   location "mix-model-viewer"
   
   libdirs {"../dependencies/lib" }
   includedirs {"../dependencies/include"}


   filter "configurations"
      defines {"TARGET_SYSTEM_WIN64"}

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      targetdir "mix-model-viewer/Debug"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      targetdir "mix-model-viewer/Release"

   files { "../src/*.h", "../src/*.cpp" }

