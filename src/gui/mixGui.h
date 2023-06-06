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
        static void on_window_size_changed (const vec2i& size);

      

        template <class T>
        static mixImGui::gui_window* add_window (T* t)
        {
            auto w = std::unique_ptr<T> (t);
            auto wp = w.get ();
            _windows.emplace_back (std::move (w));
            return wp;
        }


        /* template <class T> static mixImGui::gui_window* get_window ()
        {
            auto is_same = [] (const w_ptr& w) { return std::is_same<decltype (*w.get ()), T> (); };
            auto result = std::find_if (_windows.cbegin (), _windows.cend (), is_same);

            if (result != _windows.cend ())
            {
                return (*result).get ();
            }
            return nullptr;
        }*/

        static void show_style_editor (ImGuiStyle& style);

        private:

        static std::vector<w_ptr> _windows;
        static void begin ();
        static void end ();

    };
} // namespace mixImGui
