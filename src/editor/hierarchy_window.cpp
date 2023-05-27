#include "hierarchy_window.h"

void mix::editor::windows::hierarchy_window::render ()
{
    begin ();

    gui_layout::begin_vertical ();


    gui_layout::begin_horizontal ();
    gui_layout::text_label ("Text1");
    gui_layout::text_label ("Text2");
    gui_layout::text_label ("Text3");
    gui_layout::end_horizontal ();

    gui_layout::begin_horizontal ();
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
