-- premake5.lua
workspace "Mix"
   configurations { "Debug", "Release" }
   language "C++"
   cppdialect "C++14"
   architecture "x86_64"
   exceptionhandling "On"
   functionlevellinking  "On"
   editAndContinue "On"
   flags { 
      "FatalCompileWarnings",
      "MultiProcessorCompile" 
   }
   filter "system:windows"
      location ("Win64")
   filter "system:linux"
      location ("Linux")

group("mix")
project "mix"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++14"
   targetdir "../bin/%{cfg.buildcfg}"
   objdir "%{wks.location}/obj/%{cfg.buildcfg}"
   location "%{wks.location}/%{prj.name}"

   files { 
      "../src/**"
   }

    
   includedirs {
      "../dependencies/glfw/include",
      "../dependencies/glew/include",
      "../dependencies/imgui",
      "../dependencies/stb",
      "../dependencies/glm",
   }

   defines{
      "STB_IMAGE_IMPLEMENTATION",
   }
   filter "system:macosx"
      links {
         "glfw",
         "glew",
         "OpenGL.framework",
         "CoreFoundation.framework",
         "imgui",
      }
      xcodebuildsettings {
         ["GCC_ENABLE_CPP_EXCEPTIONS"] = "YES",
         ["MACOSX_DEPLOYMENT_TARGET"] = "10.12"
      }
      buildoptions {
         "-Wall",
         "-Wextra",
         "-Wpedantic"
      }
      linkoptions {
         "-stdlib=libc++"
      }
   filter "system:linux"

      links {
         "glfw",
         "GL",
         "X11",
         "Xrandr",
         "Xi",
         "dl",
         "pthread",
         "GLEW",
         "imgui",
      }
      buildoptions {
         "-Wall",
         "-Wextra",
         "-Wpedantic"
      }
   filter "system:windows"

      links {
         "glfw3_mt",
         "OpenGL32",
         "glew32",
         "imgui",
      }

      libdirs {
         "../dependencies/glfw/lib", 
         "../dependencies/glew/lib"
      }
      bindirs  {
         "../dependencies/glfw/bin", 
         "../dependencies/glew/bin/%{cfg.buildcfg}"}

      -- Add common flags for Windows
      filter { "system:windows", "action:vs*" }
         buildoptions {
            "/permissive-",
            "/TP"
         }
         defines {
            "_CRT_SECURE_NO_WARNINGS",
            "_CRT_NONSTDC_NO_WARNINGS",
            "NOMINMAX",
         }
         flags {
            "MultiProcessorCompile",
            "NoMinimalRebuild",
            "NoBufferSecurityCheck"
         }
         linkoptions {
            "/ignore:4099"
         }

      -- Copy GLFW3 and GLEW DLLs to output directory for Windows
      filter { "system:windows", "configurations:Debug" }
         postbuildcommands {
            "xcopy /y /d \"%{wks.location}\\..\\..\\dependencies\\glew\\bin\\%{cfg.buildcfg}\\glew32.dll\" \"%{wks.location}\\..\\..\\bin\\%{cfg.buildcfg}\"",
         }

      filter { "system:windows", "configurations:Release" }
         postbuildcommands {
            "xcopy /y /d \"%{wks.location}\\..\\..\\dependencies\\glew\\bin\\%{cfg.buildcfg}\\glew32.dll\" \"%{wks.location}\\..\\..\\bin\\%{cfg.buildcfg}\"",
         }
   filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"
   
group "external"
include "../dependencies/dependencies.lua"