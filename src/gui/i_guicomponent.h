#pragma once
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

#include <memory>
#include <string>
#include <vector>
namespace mixImGui
{
    class i_guicomponent
    {
        public:

        virtual void gui_impl () = 0;
        virtual std::string get_name () = 0;

        private:
    };
} // namespace mixImGui
