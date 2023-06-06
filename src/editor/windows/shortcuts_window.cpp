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

void mix::editor::windows::shortcuts_window::on_editor_window_size_changed_impl (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.0f;
    auto WINDOW_SIZE = 0.05f;
    auto width = size.x * WINDOW_SIZE;
    rescale (vec2i (width, static_cast<float> (size.y)));
    set_position (vec2i (size.x * WINDOW_BEGIN_POS, 0));
}

void mix::editor::windows::shortcuts_window::initialize (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.0f;
    auto WINDOW_SIZE = 0.05f;
    auto rect = mixImGui::window_rect ((int) (size.x * WINDOW_BEGIN_POS), 0, (int) (size.x * WINDOW_SIZE), size.y);

    mixImGui::mixGui::add_window (new editor::windows::shortcuts_window (std::string ("Shortcuts"), rect));
}

mix::editor::windows::shortcuts_window::shortcuts_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::MenuBar | mixImGui::window_flags::NoCollapse /*|
                         mixImGui::window_flags::NoMove | mixImGui::window_flags::NoResize*/)
{
}
