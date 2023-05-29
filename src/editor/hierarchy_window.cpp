#include "hierarchy_window.h"

void mix::editor::windows::hierarchy_window::render ()
{
    begin ();

    float c1 = 0.0f;
    gui_layout::slider_float ("Slider", &c1, 0.0f, 10.0f);

    gui_layout::begin_vertical ();


    gui_layout::begin_horizontal (mixImGui::window_rect(0, 0, 100, 200));
    gui_layout::text_label ("Value: ");
    float c = 0.0f;
    gui_layout::slider_float ("Slider", &c, 0.0f, 10.0f);
    gui_layout::end_horizontal ();

    gui_layout::begin_horizontal (mixImGui::window_rect (0, 0, 100, 200));
    gui_layout::text_label ("Text1");
    gui_layout::text_label ("Text2");
    gui_layout::text_label ("Text3");
    gui_layout::end_horizontal ();

    gui_layout::end_vertical ();
    end ();
}

mix::editor::windows::hierarchy_window::hierarchy_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::AlwaysUseWindowPadding | mixImGui::window_flags::MenuBar |
                        mixImGui::window_flags::NoCollapse |
                        mixImGui::window_flags::NoMove)
{
}
