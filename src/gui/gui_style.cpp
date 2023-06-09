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
    colors[ImGuiCol_FrameBgHovered] = from_color (_frame_color._disabled);
    colors[ImGuiCol_FrameBgActive] = from_color (_frame_color._disabled);

    colors[ImGuiCol_Separator] = from_color (_seperator_color._disabled);
    colors[ImGuiCol_SeparatorHovered] = from_color (_seperator_color._disabled);
    colors[ImGuiCol_SeparatorActive] = from_color (_seperator_color._disabled);

    colors[ImGuiCol_CheckMark] = from_color (_checkmark_color);
    colors[ImGuiCol_SliderGrab] = from_color (_slidergrab_color);
    colors[ImGuiCol_SliderGrabActive] = from_color (_slidergrab_color);

    colors[ImGuiCol_Border] = from_color (_border_color);
    colors[ImGuiCol_BorderShadow] = from_color (_border_color);

    bool enable_borders = true;
    rounding _rounding = rounding::all;
    theme _theme = theme::dark;

    if (enable_borders)
    {
        style.ChildBorderSize = 1.f;
        style.FrameBorderSize = 1.f;
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

    switch (_rounding)
    {
    case mixImGui::rounding::none:
        style.FrameRounding = 0.0f;
        style.IndentSpacing = 0.0f;
        style.WindowRounding = 0.0f;
        style.ChildRounding = 0.0f;
        style.PopupRounding = 0.0f;
        style.TabRounding = 0.0f;
        style.ScrollbarRounding = 0.0f;
        break;
    case mixImGui::rounding::medium:
        break;
        style.FrameRounding = 4;
        style.IndentSpacing = 12.0f;
        style.WindowRounding = 4.0f;
        style.ChildRounding = 4.0f;
        style.PopupRounding = 2.0f;
        style.TabRounding = 4.0f;
        style.ScrollbarRounding = 4.0f;
    case mixImGui::rounding::all:
        break;
        style.FrameRounding = 12.0f;
        style.IndentSpacing = 12.0f;
        style.WindowRounding = 12.0f;
        style.ChildRounding = 12.0f;
        style.PopupRounding = 12.0f;
        style.TabRounding = 12.0f;
        style.ScrollbarRounding = 12.0f;
    default: break;
    }

    style.WindowTitleAlign = _window_title_align;
    return style;
}

ImGuiStyle mixImGui::gui_style::get_default_dark_style (ImGuiStyle& imgui_style)
{
    auto style = gui_style ();
    style.enable_borders = true;
    style._rounding = rounding::all;
    style._theme = theme::dark;

    style._text_color = gui_color ();
    style._text_color._active = mix::math::color (212, 212, 212);
    style._text_color._hovered = mix::math::color ();
    style._text_color._disabled = mix::math::color (89, 89, 89);

    // also set checkmark color
    style._button_color = gui_color ();
    style._button_color._active = mix::math::color (61, 129, 211, 255);
    style._button_color._hovered = mix::math::color (45, 176, 247, 255);
    style._button_color._disabled = mix::math::color (132, 248, 112, 102);

    style._frame_color = gui_color ();
    style._frame_color._active = mix::math::color (85, 169, 129, 166);
    style._frame_color._hovered = mix::math::color (85, 169, 129, 166);
    style._frame_color._disabled = mix::math::color (0, 0, 0);

    style._seperator_color = gui_color ();
    style._seperator_color._active = mix::math::color (161, 161, 161, 255);
    style._seperator_color._hovered = mix::math::color (161, 161, 161, 255);
    style._seperator_color._disabled = mix::math::color (161, 161, 161, 255);


    style._border_color = mix::math::color (217, 212, 212, 128);
    style._checkmark_color = mix::math::color (77, 185, 214, 255);
    style._slidergrab_color = mix::math::color (77, 185, 214, 255);

    style._window_title_align = ImVec2 (0.5f, 0.0f);
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
