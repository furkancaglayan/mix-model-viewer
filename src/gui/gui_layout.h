#pragma once

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <string>
#include <stack>
#include <vector>
#include <memory>
#include <functional>
#include "i_guielement.h"

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

        window_rect (int x, int y, int w, int h)
        {
            _x = x;
            _y = y;
            _w = w;
            _h = h;
        }

        window_rect ()
        {
            _x = 0;
            _y = 0;
        }

        bool operator== (const ImVec4& vec)
        {
            return _x == vec.x && _y == vec.y && _w == vec.z && _h == vec.w;
        }

        public:

        int _x, _y, _w, _h;
    };

    struct gui_layout
    {
        public:

        static void
        begin_horizontal (window_rect r = window_rect (static_cast<int> (_cursor.x), static_cast<int> (_cursor.y), 0, 0));
        static void end_horizontal ();
        static void
        begin_vertical (window_rect r = window_rect (static_cast<int> (_cursor.x), static_cast<int> (_cursor.y), 0, 0));
        static void end_vertical ();
        static void text_label (std::string s);
        static void begin_selectable_list (i_guielement* previously_selected);
        static i_guielement* end_selectable_list ();

        static void begin_child (std::string s);
        static void end_child ();
        static void add_image (void* texture, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max);
        static void slider_float (const char* label, float* value, float min, float max);
        static void horizontal_space (float space);
        static void collapsing_label (std::string s, bool* is_visible);
        static void add_selectable (i_guielement* element);
        static void render_added_selectables ();

        private:

        gui_layout (mixImGui::layout_type new_layout, window_rect r);

        static void set_global_layout (mixImGui::layout_type new_layout);
        static void add_block (gui_layout* layout);
        static void end_current_block (mixImGui::layout_type target_layout);
        static ImVec2 get_new_cursor_pos ();
        static ImVec2 _cursor;
        static mixImGui::layout_type _global_layout;
        static std::stack<std::unique_ptr<gui_layout>> _layouts;
        static bool selectable_text (std::string label, bool is_selected);

        void before_render ();
        void after_render ();
        mixImGui::layout_type get_layout () const;
        mixImGui::layout_type get_previous_layout () const;

        ImVec2 _local_cursor;
        window_rect _rect;
        mixImGui::layout_type _current_layout;
        mixImGui::layout_type _last_layout;
        int _render_index;

        //selectables
        i_guielement* _selected;
        std::vector<i_guielement*> _selectables;
        int _last_selectable_index;
    };
   
} // namespace mixImGui
