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

void mix::editor::windows::scene_window::on_editor_window_size_changed_impl (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.05f;
    auto WINDOW_SIZE = 0.7f;
    auto width = size.x * WINDOW_SIZE;
    rescale (vec2i (width, static_cast<float> (size.y)));
    set_position (vec2i (size.x * WINDOW_BEGIN_POS, 0));
}

void mix::editor::windows::scene_window::initialize (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.05f;
    auto WINDOW_SIZE = 0.7f;

    auto rect = mixImGui::window_rect ((int) (size.x * WINDOW_BEGIN_POS), 0, (int) (size.x * WINDOW_SIZE), size.y);
    mixImGui::mixGui::add_window (new editor::windows::scene_window (std::string ("Viewport"), rect));
}

mix::editor::windows::scene_window::scene_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::NoCollapse |
                        mixImGui::window_flags::NoMove/*| | mixImGui::window_flags::NoResize*/)
{
}
