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
        gui_layout::add_image (texture, ImVec2 (width, height), ImVec2 (0, 1), ImVec2 (1, 0));
        gui_layout::end_child ();
    }

    end ();
}

void mix::editor::windows::scene_window::on_editor_window_size_changed_impl (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.20f;
    auto WINDOW_SIZE = 0.65f;
    auto width = size.x * WINDOW_SIZE;
    rescale (vec2i (width, static_cast<int> (size.y * 0.75f)));
    set_position (vec2i (size.x * WINDOW_BEGIN_POS, 0));
}

void mix::editor::windows::scene_window::on_window_resized (const vec2i& old_size, const vec2i& new_size)
{
    mixImGui::gui_window::on_window_resized (old_size, new_size);
    auto WINDOW_BEGIN_POS = 0.20f;
    auto WINDOW_SIZE = 0.65f;

    auto editor_window_size = mixEditor::_instance->get_window ()->get_window_size ();
    auto width = editor_window_size.x * WINDOW_SIZE;

    auto constraints = mixImGui::window_rect ((int) (width / 2), (int) editor_window_size.y, (int) width, (int) editor_window_size.y);
    set_contrainsts (constraints);
}

void mix::editor::windows::scene_window::initialize (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.05f;
    auto WINDOW_SIZE = 0.7f;

    auto rect = mixImGui::window_rect ((int) (size.x * WINDOW_BEGIN_POS), 0, (int) (size.x * WINDOW_SIZE),
                                       static_cast<int> (size.y * 0.75));
    mixImGui::mixGui::add_window (new editor::windows::scene_window (std::string ("Viewport"), rect));
}

mix::editor::windows::scene_window::scene_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::NoCollapse | mixImGui::window_flags::NoMove |
                        mixImGui::window_flags::NoResize | mixImGui::window_flags::NoScrollbar)
{
}
