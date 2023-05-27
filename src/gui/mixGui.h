#pragma once

#include "gui_window.h"
#include <GLFW/glfw3.h>
#include <memory>

namespace mixImGui
{
    class mixGui
    {
        using w_ptr = std::unique_ptr<mixImGui::gui_window>;

        public:

        static void init (GLFWwindow* window);
        static void render ();

        template <class T>
        static mixImGui::gui_window* add_window (T* t)
        {
            auto w = std::unique_ptr<T> (t);
            auto wp = w.get ();
            _windows.emplace_back (std::move (w));
            return wp;
        }

        private:

        static std::vector<w_ptr> _windows;

        static void begin ();
        static void end ();

    };
} // namespace mixImGui
