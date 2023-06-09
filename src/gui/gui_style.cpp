#include "gui_style.h"

ImVec4 from_color (mix::math::color color);

mixImGui::gui_style::gui_style ()
{
}

ImGuiStyle mixImGui::gui_style::to_imgui_style (ImGuiStyle& style)
{
    auto colors = style.Colors;

    colors[ImGuiCol_Text] = from_color (_text_color._active);
    colors[ImGuiCol_TextDisabled] = from_color (_text_color._disabled);

    colors[ImGuiCol_Button] = from_color (_button_color._disabled);
    colors[ImGuiCol_ButtonHovered] = from_color (_button_color._hovered);
    colors[ImGuiCol_ButtonActive] = from_color (_button_color._active);

    colors[ImGuiCol_FrameBg] = from_color (_frame_color._disabled);
    colors[ImGuiCol_FrameBgHovered] = from_color (_frame_color._hovered);
    colors[ImGuiCol_FrameBgActive] = from_color (_frame_color._active);

    colors[ImGuiCol_Separator] = from_color (_seperator_color._disabled);
    colors[ImGuiCol_SeparatorHovered] = from_color (_seperator_color._disabled);
    colors[ImGuiCol_SeparatorActive] = from_color (_seperator_color._disabled);

    colors[ImGuiCol_Header] = from_color (_header_color._active);
    colors[ImGuiCol_HeaderHovered] = from_color (_header_color._hovered);
    colors[ImGuiCol_HeaderActive] = from_color (_header_color._disabled);

    colors[ImGuiCol_TitleBg] = from_color (_title_color._active);
    colors[ImGuiCol_TitleBgActive] = from_color (_title_color._active);
    colors[ImGuiCol_TitleBgCollapsed] = from_color (_title_color._disabled);

    colors[ImGuiCol_Tab] = from_color (_tab_color._active);
    colors[ImGuiCol_TabHovered] = from_color (_tab_color._hovered);
    colors[ImGuiCol_TabActive] = from_color (_tab_color._disabled);

    colors[ImGuiCol_CheckMark] = from_color (_checkmark_color);
    colors[ImGuiCol_SliderGrab] = from_color (_slidergrab_color);
    colors[ImGuiCol_SliderGrabActive] = from_color (_slidergrab_color);

    colors[ImGuiCol_Border] = from_color (_border_color);
    colors[ImGuiCol_BorderShadow] = from_color (_border_color);

    if (enable_borders)
    {
        style.ChildBorderSize = 1.f;
        style.FrameBorderSize = 0.f;
        style.PopupBorderSize = 1.f;
        style.SeparatorTextBorderSize = 1.f;
        style.TabBorderSize = 1.f;
        style.WindowBorderSize = 1.f;
    }
    else
    {
        style.ChildBorderSize = 0.f;
        style.FrameBorderSize = 0.f;
        style.PopupBorderSize = 0.f;
        style.SeparatorTextBorderSize = 0.f;
        style.TabBorderSize = 0.f;
        style.WindowBorderSize = 0.f;
    }

    if (_rounding == mixImGui::rounding::none)
    {
        style.FrameRounding = 0.0f;
        style.IndentSpacing = 0.0f;
        style.WindowRounding = 0.0f;
        style.ChildRounding = 0.0f;
        style.PopupRounding = 0.0f;
        style.TabRounding = 0.0f;
        style.ScrollbarRounding = 0.0f;
        style.GrabRounding = 0.0f;
    }
    else if (_rounding == mixImGui::rounding::medium)
    {
        style.FrameRounding = 4;
        style.IndentSpacing = 12.0f;
        style.WindowRounding = 4.0f;
        style.ChildRounding = 4.0f;
        style.PopupRounding = 2.0f;
        style.TabRounding = 4.0f;
        style.ScrollbarRounding = 4.0f;
        style.GrabRounding = 6.0f;
    }
    else if (_rounding == mixImGui::rounding::all)
    {
        style.FrameRounding = 12.0f;
        style.IndentSpacing = 12.0f;
        style.WindowRounding = 12.0f;
        style.ChildRounding = 12.0f;
        style.PopupRounding = 12.0f;
        style.TabRounding = 12.0f;
        style.ScrollbarRounding = 12.0f;
        style.GrabRounding = 12.0f;
    }

    style.WindowTitleAlign = _window_title_align;
    return style;
}

ImGuiStyle mixImGui::gui_style::get_default_dark_style (ImGuiStyle& imgui_style)
{
    auto style = gui_style ();
    style.enable_borders = true;
    style._rounding = rounding::medium;
    style._theme = theme::dark;


    auto primary_active = mix::math::color (204, 64, 64, 140);
    auto primary_hovered = mix::math::color (249, 146, 146, 114);
    auto primary_normal = mix::math::color (255, 94, 94, 102);

    auto secondary_active = primary_active;
    auto secondary_hovered = primary_hovered;
    auto secondary_normal = primary_normal;


    style._text_color = gui_color ();
    style._text_color._active = mix::math::color (212, 212, 212);
    style._text_color._hovered = mix::math::color ();
    style._text_color._disabled = mix::math::color (89, 89, 89);

    // also set checkmark color
    style._button_color = gui_color ();
    style._button_color._active = primary_active;
    style._button_color._hovered = primary_hovered;
    style._button_color._disabled = primary_normal;

    style._frame_color = gui_color ();
    style._frame_color._active = mix::math::color (56, 56, 56);
    style._frame_color._hovered = mix::math::color (56, 56, 56);
    style._frame_color._disabled = mix::math::color (56, 56, 56);

    style._seperator_color = gui_color ();
    style._seperator_color._active = mix::math::color (161, 161, 161, 255);
    style._seperator_color._hovered = mix::math::color (161, 161, 161, 255);
    style._seperator_color._disabled = mix::math::color (161, 161, 161, 255);

    style._title_color = gui_color ();
    style._title_color._active = secondary_active;
    style._title_color._hovered = secondary_hovered;
    style._title_color._disabled = secondary_normal;

    style._header_color = style._button_color;

    style._tab_color = style._button_color;

    style._border_color = secondary_normal;
    style._checkmark_color = secondary_normal;
    style._slidergrab_color = secondary_normal;

    style._window_title_align = ImVec2 (0.5f, 0.3f);
    // gui_color _button_color;
    // mix::math::color _border_color;
    return style.to_imgui_style (imgui_style);
}

ImGuiStyle mixImGui::gui_style::get_default_light_style ()
{
    return ImGuiStyle ();
}

ImVec4 from_color (mix::math::color color)
{
    auto values = color.get_value ();
    return ImVec4 (values.x, values.y, values.z, values.w);
}
