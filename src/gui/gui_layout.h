#pragma once

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <string>
#include <stack>
#include <vector>
#include <memory>
#include <functional>

namespace mixImGui
{
    enum class layout_type
    {
        none,
        horizontal,
        vertical
    };

     struct window_rect
    {
        window_rect (float x, float y, float min_x, float min_y, float w, float h)
        {
            _x = x;
            _y = y;
            _min_x = min_x;
            _min_y = min_y;
            _w = w;
            _h = h;
        }

        window_rect (float x, float y, float w, float h)
        {
            _x = x;
            _y = y;
            _min_x = -1;
            _min_y = -1;
            _w = w;
            _h = h;
        }

        window_rect ()
        {
            _x = 0;
            _y = 0;
        }

        public:

        float _x, _y, _min_x, _min_y, _w, _h;
    };

    struct gui_layout
    {
        public:

        static void begin_horizontal (window_rect r = window_rect(_cursor.x, _cursor.y, 0, 0));
        static void end_horizontal ();
        static void begin_vertical (window_rect r = window_rect (_cursor.x, _cursor.y, 0, 0));
        static void end_vertical ();
        static void text_label (std::string s);

     
        private:

        gui_layout (mixImGui::layout_type new_layout, window_rect r);

        static void set_global_layout (mixImGui::layout_type new_layout);
        static void add_block (gui_layout* layout);
        static void end_current_block (mixImGui::layout_type target_layout);
        static ImVec2 get_new_cursor_pos ();
        static ImVec2 _cursor;
        static mixImGui::layout_type _global_layout;
        static std::stack<std::unique_ptr<gui_layout>> _layouts;

        void add_gui_element (const std::function<void ()>& command);
        void render_layout ();
        void render_gui_element (const std::function<void ()>& command);
        mixImGui::layout_type get_layout () const;
        mixImGui::layout_type get_previous_layout () const;

        std::vector<std::function<void()>> _commands;
        ImVec2 _local_cursor;
        window_rect _rect;
        mixImGui::layout_type _current_layout;
        mixImGui::layout_type _last_layout;
    };
} // namespace mixImGui
