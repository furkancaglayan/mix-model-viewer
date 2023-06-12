#include "shortcuts_window.h"

void mix::editor::windows::shortcuts_window::render ()
{
    begin ();
    auto editor = mix::mixEditor::_instance.get ();
    if (editor)
    {
        gui_layout::text_label ("OpenGL Texture Text");
        if (_styles_editor_tex)
        {
            float width = 64;
            float height = 64;
            ImVec2 pos = ImGui::GetCursorScreenPos ();
            //gui_layout::add_image (_styles_editor_tex->get_id(), ImVec2 (pos.x, pos.y), ImVec2 (pos.x + width, pos.y + height), ImVec2 (0, 1), ImVec2 (1, 0));
            if (gui_layout::image_button ("shortcuts-imgui-button", _styles_editor_tex->get_id ()))
            {
                _show_styles_editor = !_show_styles_editor;
            }
            gui_layout::seperator ();
            gui_layout::button ("Label");
            gui_layout::seperator ();
            gui_layout::arrow_button ("Label", 30);
            gui_layout::seperator ();
            gui_layout::small_button ("Label");
            gui_layout::seperator ();
            gui_layout::radio_button ("Label", true);

            if (_show_styles_editor)
            {
                mixGui::show_style_editor (ImGui::GetStyle());
            }

            gui_layout::progress_bar (0.25f);
        }
    }

    end ();
}

void mix::editor::windows::shortcuts_window::on_editor_window_size_changed_impl (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.0f;
    auto WINDOW_SIZE = 0.20f;
    auto width = size.x * WINDOW_SIZE;
    rescale (vec2i (width, static_cast<int> (size.y)));
    set_position (vec2i (size.x * WINDOW_BEGIN_POS, 0));
}

void mix::editor::windows::shortcuts_window::initialize (const vec2i& size)
{
    auto WINDOW_BEGIN_POS = 0.0f;
    auto WINDOW_SIZE = 0.20f;
    auto rect = mixImGui::window_rect ((int) (size.x * WINDOW_BEGIN_POS), 0, (int) (size.x * WINDOW_SIZE),
                                       static_cast<int> (size.y));

    mixImGui::mixGui::add_window (new editor::windows::shortcuts_window (std::string ("Shortcuts"), rect));
}

mix::editor::windows::shortcuts_window::shortcuts_window (std::string window_name, mixImGui::window_rect r)
: mixImGui::gui_window (window_name,
                        r,
                        mixImGui::window_flags::MenuBar | mixImGui::window_flags::NoCollapse |
                         mixImGui::window_flags::NoMove | mixImGui::window_flags::NoResize)
{
    _styles_editor_tex = mixEditor::get_asset_manager ()->get_asset_with_full_name<mix::assetsystem::mixTexture> ("default_other.png").get();
    assert (_styles_editor_tex);
}
