#pragma once

#include "gui_window.h"
#include <GLFW/glfw3.h>

namespace mixImGui
{

    class mixGui
    {
        friend class mixImGui::gui_window;
        using w_ptr = std::unique_ptr<mixImGui::gui_window>;

        public:

        static void init (GLFWwindow* window);
        static void render ();
        template <class Comp, class... Args> static mixImGui::gui_window* add_window_with_component (Args&&... args)
        {
            return std::unique_ptr<mixImGui::gui_window> (new mixImGui::gui_window (std::forward<Args> (args)...));
        }

        private:

        static void begin ();
        static void end ();
        static std::vector<w_ptr> _windows;
    };
} // namespace mixImGui
