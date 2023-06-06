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
    class i_guielement
    {
        public:

        virtual void on_gui () = 0;

        private:
    };
} // namespace mixImGui
