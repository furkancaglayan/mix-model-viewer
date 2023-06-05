#pragma once
#include "../containers/frame_buffer.h"
#include "gui_window.h"
#include <memory>

namespace mixImGui
{
    class mixGui
    {
        using w_ptr = std::unique_ptr<mixImGui::gui_window>;

        public:

        static void init (GLFWwindow* window);
        static void render (mix::containers::frame_buffer* buffer);
        static void on_window_size_changed (int w, int h, int w_sizex, int w_sizey);

      

        template <class T>
        static mixImGui::gui_window* add_window (T* t)
        {
            auto w = std::unique_ptr<T> (t);
            auto wp = w.get ();
            _windows.emplace_back (std::move (w));
            return wp;
        }
        static void show_style_editor (ImGuiStyle& style);

        private:

        static std::vector<w_ptr> _windows;
        static void begin ();
        static void end ();

    };
} // namespace mixImGui
