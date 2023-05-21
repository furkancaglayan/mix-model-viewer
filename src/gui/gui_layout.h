#pragma once

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <string>

namespace mixImGui
{

    class gui_layout
    {
        public:

        static void begin_horizontal ();
        static void end_horizontal ();
        static void begin_vertical ();
        static void end_vertical ();
        static void text_label (std::string s);

        private:

        gui_layout () = delete;
        static float _x;
        static float _y;
    };
} // namespace mixImGui
