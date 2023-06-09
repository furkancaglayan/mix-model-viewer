#pragma once

#include "mixGui.h"
#include "../math/color.h"
namespace mixImGui
{
    enum class rounding
    {
        none,
        medium,
        all
    };

    enum class theme
    {
        dark,
        light
    };

    struct gui_color
    {
        public:

        gui_color () = default;
        mix::math::color _disabled;
        mix::math::color _active;
        mix::math::color _hovered;
    };

    struct gui_style
    {
        public:

        gui_style ();
        
        bool enable_borders = true;
        rounding _rounding = rounding::all;
        theme _theme = theme::dark;
        gui_color _text_color;
        gui_color _button_color;
        gui_color _frame_color;
        gui_color _seperator_color;
        gui_color _tab_color;
        gui_color _title_color;
        gui_color _header_color;
        mix::math::color _border_color;
        mix::math::color _checkmark_color, _slidergrab_color;
        ImVec2 _window_title_align;
        ImGuiStyle to_imgui_style (ImGuiStyle& style);
        static ImGuiStyle get_default_dark_style (ImGuiStyle& imgui_style);
        static ImGuiStyle get_default_light_style ();
    };

} // namespace mixImGui
