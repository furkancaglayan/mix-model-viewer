-- dependencies.lua
project "imgui"
   kind "StaticLib"
   language "C++"
   cppdialect "C++14"
   location ("%{wks.location}/external")
   targetdir "%{wks.location}/../../bin/%{cfg.buildcfg}"

   files { 
    "src/*.cpp",
    "src/*.h" 
  }

   includedirs { 
    "imgui"
 }

   -- imgui-specific settings
   files { 
    "imgui/*.cpp", 
    "imgui/*.h" 
    }

	filter "system:windows"
      systemversion "latest"
	  staticruntime "On"

	
    filter "system:windows"
      systemversion "latest"
	  staticruntime "On"
      defines 
      { 
          "_IMGUI_WIN32",
      }

      files { 
        "imgui/backends/imgui_impl_win32.cpp", 
        "imgui/backends/imgui_impl_opengl3.cpp", 
    }
    filter "system:macosx"
      files { 
        "imgui/backends/imgui_impl_glfw.cpp", 
        "imgui/backends/imgui_impl_opengl3.cpp" 
    }
    
    filter "system:linux"
      pic "On"
      systemversion "latest"
      staticruntime "On"

      defines
      {
            "_IMGUI_X11"
      }

   filter {}
