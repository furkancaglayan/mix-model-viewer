#pragma once

#include "i_guielement.h"
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <functional>
#include <memory>
#include <stack>
#include <string>
#include <vector>

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
        static void add_image (unsigned texture, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max);
        static void slider_float (const char* label, float* value, float min, float max);
        static void collapsing_label (std::string s, bool* is_visible);
        static void add_selectable (i_guielement* element);
        static void render_added_selectables ();

        static void horizontal_space (float space);
        static void vertical_space (float space);
        static void new_line ();
        static void seperator ();

        static bool button (const std::string& label, const ImVec2& size = ImVec2 (32, 32));
        static bool radio_button (const std::string& label, bool is_active);
        static bool small_button (const std::string& label);
        static bool arrow_button (const std::string& label, int dir);
        static bool image_button (const std::string& str_id,
                                  unsigned user_texture_id,
                                  const ImVec2& size = ImVec2 (32, 32),
                                  const ImVec2& uv0 = ImVec2 (0, 0),
                                  const ImVec2& uv1 = ImVec2 (1, 1),
                                  const ImVec4& bg_col = ImVec4 (0, 0, 0, 0),
                                  const ImVec4& tint_col = ImVec4 (1, 1, 1, 1));

        template <class T> static T* get_top_block ()
        {
            return static_cast<T*> (mixImGui::gui_layout::_layouts.top ().get ());
        }

        static gui_layout* get_top_block ()
        {
            return mixImGui::gui_layout::_layouts.top ().get ();
        }

        protected:

        static void
        begin_vertical_selectable (window_rect r = window_rect (static_cast<int> (_cursor.x), static_cast<int> (_cursor.y), 0, 0));
        static void end_vertical_selectable ();
        gui_layout (mixImGui::layout_type new_layout, window_rect r);

        private:

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
    };

} // namespace mixImGui
