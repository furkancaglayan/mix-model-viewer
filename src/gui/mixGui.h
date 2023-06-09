#pragma once
#include "../containers/frame_buffer.h"
#include "gui_window.h"
#include "../assetsystem/assets/mixFont.h"
#include <memory>

namespace mixImGui
{
    class mixGui
    {
        using w_ptr = std::unique_ptr<mixImGui::gui_window>;

        public:

        static void init (GLFWwindow* window);
        static void render (mix::containers::frame_buffer* buffer);
        static void on_editor_window_size_changed (const vec2i& size);

      

        template <class T>
        static mixImGui::gui_window* add_window (T* t)
        {
            auto w = std::unique_ptr<T> (t);
            auto wp = w.get ();
            _windows.emplace_back (std::move (w));
            return wp;
        }


        template <class T> static mixImGui::gui_window* get_window ()
        {
            for (auto& window : _windows)
            {
                auto* p = dynamic_cast<T*> (window.get());
                if (p)
                {
                    return p;
                }
            }
            return nullptr;
        }

        static void show_style_editor (ImGuiStyle& style);
        static void add_font (mix::assetsystem::mixFont* font, bool set_default = false);
        private:

        static std::vector<w_ptr> _windows;
        static void begin ();
        static void end ();

    };
} // namespace mixImGui
