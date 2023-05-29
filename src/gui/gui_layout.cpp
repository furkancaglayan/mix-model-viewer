#include "gui_layout.h"

ImVec2 mixImGui::gui_layout::_cursor = ImVec2 ();
std::stack<std::unique_ptr<mixImGui::gui_layout>> mixImGui::gui_layout::_layouts;
mixImGui::layout_type mixImGui::gui_layout::_global_layout = mixImGui::layout_type::vertical;

mixImGui::gui_layout::gui_layout (mixImGui::layout_type new_layout, window_rect r)
{
    _local_cursor = ImVec2();
    _rect = r;
    _current_layout = new_layout;
    _last_layout = _global_layout;
    _cursor = ImGui::GetCursorPos ();
}

void mixImGui::gui_layout::begin_horizontal (window_rect r)
{
    add_block (new mixImGui::gui_layout (mixImGui::layout_type::horizontal, r));
}

void mixImGui::gui_layout::end_horizontal ()
{
    end_current_block (mixImGui::layout_type::horizontal);
}

void mixImGui::gui_layout::begin_vertical (window_rect r)
{
    add_block (new mixImGui::gui_layout (mixImGui::layout_type::vertical, r));
}

void mixImGui::gui_layout::end_vertical ()
{
    end_current_block (mixImGui::layout_type::vertical);
}

void mixImGui::gui_layout::text_label (std::string s)
{
    auto block = mixImGui::gui_layout::_layouts.top ().get();
    block->add_gui_element ([=] () { ImGui::Text (s.c_str ()); });
}

void mixImGui::gui_layout::slider_float (const char* label, float* value, float min, float max)
{
    auto block = mixImGui::gui_layout::_layouts.top ().get ();
    block->add_gui_element ([=] () { ImGui::SliderFloat (label, value, min, max); });
}

void mixImGui::gui_layout::add_gui_element (const std::function<void ()>& command)
{
    _commands.push_back (command);
}

void mixImGui::gui_layout::render_layout ()
{
    for (size_t i = 0; i < _commands.size(); i++)
    {
        render_gui_element (_commands.at(i));
    }
}

void mixImGui::gui_layout::render_gui_element (const std::function<void ()>& command)
{
    auto w_size = ImGui::GetWindowSize ();
    auto w_pos = ImGui::GetWindowPos ();
    auto element_count = _commands.size ();
    auto eq_size = w_size.x / element_count;

    auto cursor_pos = ImGui::GetCursorPos ();

    ImGui::SetCursorPos (ImVec2 (_local_cursor.x + _cursor.x, _local_cursor.y + _cursor.y));

    if (_global_layout == mixImGui::layout_type::horizontal)
    {
        _local_cursor.x += eq_size;
    }

    command ();
}

mixImGui::layout_type mixImGui::gui_layout::get_layout () const
{
    return _current_layout;
}

mixImGui::layout_type mixImGui::gui_layout::get_previous_layout () const
{
    return _last_layout;
}

void mixImGui::gui_layout::set_global_layout (mixImGui::layout_type new_layout)
{
    _global_layout = new_layout;
}

void mixImGui::gui_layout::add_block (mixImGui::gui_layout* layout)
{
    mixImGui::gui_layout::_layouts.push (std::unique_ptr<mixImGui::gui_layout> (layout));
    set_global_layout (layout->get_layout());
}

void mixImGui::gui_layout::end_current_block (mixImGui::layout_type target_layout)
{
    auto block = mixImGui::gui_layout::_layouts.top ().get();
    assert (block->get_layout () == target_layout);
    block->render_layout ();
    auto cursor_pos = ImGui::GetCursorPos ();

    _cursor = ImVec2 (cursor_pos.x, cursor_pos.y + block->_rect._h);
    ImGui::SetCursorPos (_cursor);
    set_global_layout (block->get_previous_layout ());
    mixImGui::gui_layout::_layouts.pop ();

    if (_layouts.size () == 0)
    {
        _cursor = ImVec2 ();
    }
}

ImVec2 mixImGui::gui_layout::get_new_cursor_pos ()
{
    return ImVec2 ();
}
