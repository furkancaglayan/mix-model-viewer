-- premake5.lua
workspace "Mix"
   configurations { "Debug", "Release", "Shipping" }
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
   startproject "mix-model-viewer-launcher"

   filter "system:windows"
      location ("Win64")
   filter "system:linux"
      location ("Linux")

group("mix")
project "mix-model-viewer"
   kind "StaticLib"
   language "C++"
   cppdialect "C++14"
   targetdir "../bin/%{cfg.buildcfg}"
   objdir "%{wks.location}/obj"
   location "%{wks.location}/%{prj.name}"
   architecture "x86_64"
   staticruntime "on"
   files { 
      "../src/**"
   }
   removefiles{
       "../src/test/**",
       "../src/main.cpp"
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
   defines{
      "SYSTEM_MACOSX"
   }
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
         "-Wpedantic",
         "-stdlib=libc++",
      }
   filter "system:linux"
   defines{
      "SYSTEM_LINUX"
   }
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
      defines{
         "SYSTEM_WIN64"
      }
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
      filter { "system:windows", "configurations:*" }
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

   filter "configurations:Shipping"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"
filter{}

project "mix-model-viewer-launcher"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++14"
   targetdir "../bin/%{cfg.buildcfg}"
   objdir "%{wks.location}/obj"
   location "%{wks.location}/%{prj.name}"
   architecture "x86_64"
   files { 
      "../src/main.cpp",
   }
    filter "system:windows"
      defines{
         "SYSTEM_WIN64"
      }
   staticruntime "on"
    
   includedirs {
      "../src/**",
      "../dependencies/glfw/include",
      "../dependencies/glew/include",
      "../dependencies/imgui",
      "../dependencies/stb",
      "../dependencies/glm",
   }

   links {
       "mix-model-viewer",
   }

   libdirs {
      "../dependencies/glfw/lib", 
      "../dependencies/glew/lib",
      
   }
   bindirs  {
      "../dependencies/glfw/bin", 
      "../dependencies/glew/bin/%{cfg.buildcfg}"}

      dependson { "mix-model-viewer" }


   filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"

   filter "configurations:Shipping"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"

project "mix-model-viewer-test"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++14"
   targetdir "../bin/%{cfg.buildcfg}"
   objdir "%{wks.location}/obj"
   location "%{wks.location}/%{prj.name}"
   architecture "x86_64"
   files { 
      "../src/test/**",
   }

    
   includedirs {
    "../dependencies/googletest/googletest/include",
      "../dependencies/glfw/include",
      "../dependencies/glew/include",
      "../dependencies/imgui",
      "../dependencies/stb",
      "../dependencies/glm",
      "../src/core",
   }

   links {
       "googletest",
       "mix-model-viewer",
       "glfw3_mt",
      "OpenGL32",
      "glew32",
   }

   libdirs {
      "../dependencies/glfw/lib", 
      "../dependencies/glew/lib",
      
   }
   bindirs  {
      "../dependencies/glfw/bin", 
      "../dependencies/glew/bin/%{cfg.buildcfg}"}

      dependson { "mix-model-viewer" }

   staticruntime "on"
   filter "configurations:Debug"
      defines { "DEBUG" }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"

   filter "configurations:Shipping"
      defines { "NDEBUG" }
      runtime "Release"
      optimize "On"

group "external"
include "../dependencies/dependencies.lua"