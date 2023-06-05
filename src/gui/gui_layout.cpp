#include "gui_layout.h"

ImVec2 mixImGui::gui_layout::_cursor = ImVec2 ();
std::stack<std::unique_ptr<mixImGui::gui_layout>> mixImGui::gui_layout::_layouts;
mixImGui::layout_type mixImGui::gui_layout::_global_layout = mixImGui::layout_type::vertical;

mixImGui::gui_layout::gui_layout (mixImGui::layout_type new_layout, window_rect r)
{
    _local_cursor = ImVec2 ();
    _rect = r;
    _current_layout = new_layout;
    _last_layout = _global_layout;
    _cursor = ImGui::GetCursorPos ();
    _render_index = 0;
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
    auto block = mixImGui::gui_layout::_layouts.top ().get ();
    block->before_render ();
    ImGui::Text (s.c_str ());
    block->after_render ();
}

void mixImGui::gui_layout::begin_child (std::string s)
{
    ImGui::BeginChild (s.c_str ());
}

void mixImGui::gui_layout::end_child ()
{
    ImGui::EndChild ();
}

void mixImGui::gui_layout::add_image (void* texture, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max)
{
    ImGui::GetWindowDrawList ()->AddImage (texture, p_min, p_max, uv_min, uv_max);
}


bool mixImGui::gui_layout::selectable (std::string label, bool is_selected)
{
    auto block = mixImGui::gui_layout::_layouts.top ().get ();
    block->before_render ();
    bool pressed = ImGui::Selectable (label.c_str (), is_selected, ImGuiSelectableFlags_DontClosePopups);
    block->after_render ();
    return pressed;
}

void mixImGui::gui_layout::collapsing_label (std::string s, bool* is_visible)
{
    auto block = mixImGui::gui_layout::_layouts.top ().get ();
    block->before_render ();
    *is_visible = ImGui::CollapsingHeader (s.c_str (), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen);
    block->after_render ();
}


void mixImGui::gui_layout::slider_float (const char* label, float* value, float min, float max)
{
    auto block = mixImGui::gui_layout::_layouts.top ().get ();
    block->before_render ();
    ImGui::SliderFloat (label, value, min, max);
    block->after_render ();
}

void mixImGui::gui_layout::horizontal_space (float space)
{
    auto cursor_pos = ImGui::GetCursorPos ();
    ImGui::SetCursorPos (ImVec2 (cursor_pos.x + space, cursor_pos.y));
}

void mixImGui::gui_layout::before_render ()
{
    auto w_size = ImGui::GetWindowSize ();
    auto w_pos = ImGui::GetWindowPos ();

    auto cursor_pos = ImGui::GetCursorPos ();
    auto last_item_size = ImGui::GetItemRectSize ();

    // ImGui::SetCursorPos (ImVec2 (_local_cursor.x + _cursor.x, _local_cursor.y + _cursor.y));
    if (_global_layout == mixImGui::layout_type::horizontal)
    {
        _local_cursor.x += last_item_size.x;
        if (_render_index > 0)
        {
            ImGui::SameLine ();
        }
    }

    // command ();
}

void mixImGui::gui_layout::after_render ()
{
    _render_index++;
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
    set_global_layout (layout->get_layout ());
}

void mixImGui::gui_layout::end_current_block (mixImGui::layout_type target_layout)
{
    auto block = mixImGui::gui_layout::_layouts.top ().get ();
    assert (block->get_layout () == target_layout);
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
