#include "shortcuts_window.h"

void mix::editor::windows::shortcuts_window::render ()
{
    begin ();
    auto editor = mix::mixEditor::_instance.get ();
    if (editor)
    {
        gui_layout::text_label ("OpenGL Texture Text");
    }

    end ();
}

void mix::editor::windows::shortcuts_window::on_window_size_changed (int w, int h)
{
    auto WINDOW_BEGIN_POS = 0.0f;
    auto WINDOW_SIZE = 0.05f;
    auto width = w * WINDOW_SIZE;
    rescale (width, static_cast<float> (h));
    set_position (w * WINDOW_BEGIN_POS, 0);
}

void mix::editor::windows::shortcuts_window::initialize (vec2 w_size)
{
    auto WINDOW_BEGIN_POS = 0.0f;
    auto WINDOW_SIZE = 0.05f;
    mixImGui::mixGui::add_window (new editor::windows::shortcuts_window (
    std::string ("Shortcuts"), mixImGui::window_rect (w_size.x * WINDOW_BEGIN_POS, 0,
                                                                                        w_size.x * WINDOW_SIZE, w_size.y)));
}

mix::editor::windows::shortcuts_window::shortcuts_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::MenuBar | mixImGui::window_flags::NoCollapse /*|
                         mixImGui::window_flags::NoMove | mixImGui::window_flags::NoResize*/)
{
}
