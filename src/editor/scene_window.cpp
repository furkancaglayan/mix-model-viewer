#include "scene_window.h"

void mix::editor::windows::scene_window::render ()
{
    begin ();
    auto editor = mix::mixEditor::_instance.get ();
    if (editor)
    {
        auto texture = editor->get_rendered_texture ();
        auto size = editor->get_window ()->get_window_size ();

        gui_layout::begin_child ("Render");

        float width = ImGui::GetContentRegionAvail ().x;
        float height = ImGui::GetContentRegionAvail ().y;

        gui_layout::text_label ("OpenGL Texture Text");

        ImVec2 pos = ImGui::GetCursorScreenPos ();
        gui_layout::add_image ((void*) (intptr_t) (texture), ImVec2 (pos.x, pos.y),
                               ImVec2 (pos.x + width, pos.y + height), ImVec2 (0, 1), ImVec2 (1, 0));
        gui_layout::end_child ();
    }

    end ();
}

void mix::editor::windows::scene_window::initialize (vec2 w_size)
{
    auto WINDOW_BEGIN_POS = 0.15f;
    auto WINDOW_SIZE = 0.65f;
    mixImGui::mixGui::add_window (new editor::windows::scene_window (std::string ("Viewport"), mixImGui::window_rect (w_size.x * WINDOW_BEGIN_POS, 0,
                                                                                        w_size.x * WINDOW_SIZE, w_size.y)));
}

mix::editor::windows::scene_window::scene_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::MenuBar | mixImGui::window_flags::NoCollapse /*|
                         mixImGui::window_flags::NoMove | mixImGui::window_flags::NoResize*/)
{
}
