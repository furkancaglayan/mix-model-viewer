#include "gui_layout.h"
#include "gui_selectable_layout.h"

ImVec2 mixImGui::gui_layout::_cursor = ImVec2 ();
std::stack<std::unique_ptr<mixImGui::gui_layout>> mixImGui::gui_layout::_layouts;
mixImGui::layout_type mixImGui::gui_layout::_global_layout = mixImGui::layout_type::vertical;


mixImGui::gui_layout::gui_layout (mixImGui::layout_type new_layout, window_rect r)
{
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

void mixImGui::gui_layout::begin_vertical_selectable (window_rect r)
{
    add_block (new mixImGui::gui_selectable_layout (mixImGui::layout_type::vertical, r));
}

void mixImGui::gui_layout::end_vertical_selectable ()
{
    end_vertical ();
}


void mixImGui::gui_layout::text_label (std::string s)
{
    auto block = mixImGui::gui_layout::get_top_block ();
    block->before_render ();
    ImGui::Text (s.c_str ());
    block->after_render ();
}

void mixImGui::gui_layout::begin_selectable_list (i_guielement* previously_selected)
{
    begin_vertical_selectable ();
    auto block = mixImGui::gui_layout::get_top_block<mixImGui::gui_selectable_layout> ();
    block->_selected = previously_selected;
}

mixImGui::i_guielement* mixImGui::gui_layout::end_selectable_list ()
{
    auto block = mixImGui::gui_layout::get_top_block<mixImGui::gui_selectable_layout> ();

    if (block->_last_selectable_index != block->_selectables.size ())
    {
        render_added_selectables ();
    }

    i_guielement* selected = block->_selected;
    end_vertical_selectable ();

    return selected;
}


void mixImGui::gui_layout::begin_child (std::string s)
{
    ImGui::BeginChild (s.c_str ());
}

void mixImGui::gui_layout::begin_child (std::string s, const ImVec2& size, bool border, int flags)
{
    ImGui::BeginChild (s.c_str (), size, border, flags);
}

void mixImGui::gui_layout::end_child ()
{
    ImGui::EndChild ();
}

void mixImGui::gui_layout::add_image (unsigned texture_id,
                                      const ImVec2& size,
                                      const ImVec2& uv_min,
                                      const ImVec2& uv_max,
                                      const ImVec4& tint_color,
                                      const ImVec4& border_color)
{
    auto block = mixImGui::gui_layout::get_top_block ();
    block->before_render ();
    ImGui::Image ((void*) (intptr_t) texture_id, size, uv_min, uv_max, tint_color, border_color);
    block->after_render ();
}


bool mixImGui::gui_layout::selectable_text (std::string label, bool is_selected)
{
    auto block = mixImGui::gui_layout::_layouts.top ().get ();
    block->before_render ();
    bool pressed = ImGui::Selectable (label.c_str (), is_selected,
                                      ImGuiSelectableFlags_DontClosePopups | ImGuiSelectableFlags_AllowDoubleClick);
    block->after_render ();
    return pressed;
}

bool mixImGui::gui_layout::is_double_clicked ()
{
    return ImGui::IsItemHovered () && ImGui::IsMouseDoubleClicked (0);
}

bool mixImGui::gui_layout::is_left_clicked ()
{
    return ImGui::IsItemHovered () && ImGui::IsMouseClicked (0);
}


bool mixImGui::gui_layout::is_right_clicked ()
{
    return ImGui::IsItemHovered () && ImGui::IsMouseClicked (1);
}

void mixImGui::gui_layout::selectable_image (std::string id, const ImVec2& size, unsigned image, bool& pressed, bool& double_clicked, bool& right_clicked)
    {
    auto block = mixImGui::gui_layout::_layouts.top ().get ();
    block->before_render ();
    auto cursor = ImGui::GetCursorPos ();

    auto header_hover_col = ImGui::GetStyleColorVec4 (ImGuiCol_HeaderHovered);
    auto header_active_col = ImGui::GetStyleColorVec4 (ImGuiCol_HeaderActive);
    auto header_normal_col = ImGui::GetStyleColorVec4 (ImGuiCol_Header);
    ImGui::PushStyleColor (ImGuiCol_HeaderHovered, ImVec4 ());
    ImGui::PushStyleColor (ImGuiCol_HeaderActive, ImVec4 ());

    pressed = ImGui::Selectable ((std::string ("##") + id).c_str (), false,
                                      ImGuiSelectableFlags_DontClosePopups | ImGuiSelectableFlags_AllowDoubleClick, size);
    double_clicked = is_double_clicked ();
    right_clicked = is_right_clicked ();
    ImGui::PopStyleColor (2);
    ImGui::SetCursorPos (cursor);
    {
        add_image (image, size, ImVec2 (0, 1), ImVec2 (1, 0));
    }
    block->after_render ();
}


void mixImGui::gui_layout::add_selectable (i_guielement* element)
{
    auto block = mixImGui::gui_layout::get_top_block<mixImGui::gui_selectable_layout> ();
    block->_selectables.push_back (element);
}

void mixImGui::gui_layout::render_added_selectables ()
{
    auto block = mixImGui::gui_layout::get_top_block<mixImGui::gui_selectable_layout> ();
    auto start_index = block->_last_selectable_index;
    size_t i;
    for (i = start_index; i < block->_selectables.size (); i++)
    {
        auto element = block->_selectables.at (i);
        //gui_layout::horizontal_space (20);
        bool selected = element == block->_selected;

        if (gui_layout::selectable_text (element->get_gui_name (), selected))
        {
            block->_selected = element;
        }
    }
    block->_last_selectable_index = static_cast<int> (i);
}

void mixImGui::gui_layout::progress_bar (float r)
{
    auto block = mixImGui::gui_layout::get_top_block ();
    block->before_render ();
    ImGui::ProgressBar (r);
    block->after_render ();
}

bool mixImGui::gui_layout::button (const std::string& label, const ImVec2& size)
{
    auto block = mixImGui::gui_layout::get_top_block ();
    block->before_render ();
    bool result = ImGui::Button (label.c_str (), size);
    block->after_render ();
    return result;
}

bool mixImGui::gui_layout::arrow_button (const std::string& label, int dir)
{
    auto block = mixImGui::gui_layout::get_top_block ();
    block->before_render ();
    bool result = ImGui::ArrowButton (label.c_str (), dir);
    block->after_render ();
    return result;
}

bool mixImGui::gui_layout::small_button (const std::string& label)
{
    auto block = mixImGui::gui_layout::get_top_block ();
    block->before_render ();
    bool result = ImGui::SmallButton (label.c_str ());
    block->after_render ();
    return result;
}

bool mixImGui::gui_layout::radio_button (const std::string& label, bool is_active)
{
    auto block = mixImGui::gui_layout::get_top_block ();
    block->before_render ();
    bool result = ImGui::RadioButton (label.c_str (), is_active);
    block->after_render ();
    return result;
}

bool mixImGui::gui_layout::image_button (const std::string& str_id,
                                         unsigned user_texture_id,
                                         const ImVec2& size,
                                         const ImVec2& uv0,
                                         const ImVec2& uv1,
                                         const ImVec4& bg_col,
                                         const ImVec4& tint_col)
{
    auto block = mixImGui::gui_layout::get_top_block ();
    block->before_render ();
    bool result = ImGui::ImageButton (str_id.c_str (), (void*) (intptr_t) (user_texture_id), size, uv0, uv1, bg_col, tint_col);
    block->after_render ();
    return result;
}

void mixImGui::gui_layout::begin_context_menu (const std::string& id)
{
    ImGui::OpenPopup (id.c_str ());
}

void mixImGui::gui_layout::end_context_menu ()
{
    ImGui::EndPopup ();
}

bool mixImGui::gui_layout::tree_node (const char* label, int index, bool is_selected, bool is_framed, bool is_leaf)
{
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow;

    if (is_selected)
    {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    if (is_framed)
    {
        flags |= ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_CollapsingHeader;
    }

    if (is_leaf)
    {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }

    return ImGui::TreeNodeEx ((void*) (intptr_t) index, flags, label);
}

bool mixImGui::gui_layout::tree_node (const char* label)
{
    return ImGui::TreeNode (label);
}

void mixImGui::gui_layout::tree_pop ()
{
    ImGui::TreePop();
}

bool mixImGui::gui_layout::begin_drag_drop_source ()
{
    return ImGui::BeginDragDropSource ();
}

void mixImGui::gui_layout::end_drag_drop_source ()
{
    ImGui::EndDragDropSource ();
}

bool mixImGui::gui_layout::set_drag_drop_payload (const char* label, const void* data, size_t size)
{
    return ImGui::SetDragDropPayload (label, data, size);
}

bool mixImGui::gui_layout::begin_drag_drop_target ()
{
    return ImGui::BeginDragDropTarget();
}

void mixImGui::gui_layout::end_drag_drop_target ()
{
    ImGui::EndDragDropTarget ();
}

void* mixImGui::gui_layout::accept_drag_drop_payload (const char* label)
{
    auto payload = ImGui::AcceptDragDropPayload (label);
    if (payload != nullptr)
    {
        return payload->Data;
    }
    return nullptr;
}

void mixImGui::gui_layout::set_background_color (mix::math::color& color)
{
    vec4 c = color.get_value();
    ImVec4 imgui_color = ImVec4 (c.x, c.y, c.z, c.w);
    ImGui::PushStyleColor (ImGuiCol_WindowBg, imgui_color);
}

void mixImGui::gui_layout::pop_style_vars ()
{
    ImGui::PopStyleColor ();
}


ImVec2 mixImGui::gui_layout::get_cursor ()
{
    return _cursor;
}

void mixImGui::gui_layout::collapsing_label (std::string s, bool* is_visible)
{
    auto block = mixImGui::gui_layout::get_top_block ();

    block->before_render ();
    *is_visible = ImGui::CollapsingHeader (s.c_str (), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen);
    block->after_render ();
}

void mixImGui::gui_layout::slider_float (const char* label, float* value, float min, float max)
{
    auto block = mixImGui::gui_layout::get_top_block ();

    block->before_render ();
    ImGui::SliderFloat (label, value, min, max);
    block->after_render ();
}

void mixImGui::gui_layout::horizontal_space (float space)
{
    _cursor = ImVec2 (_cursor.x + space, _cursor.y);
    ImGui::SetCursorPos (_cursor);
}

void mixImGui::gui_layout::vertical_space (float space)
{
    ImGui::Dummy (ImVec2 (0.0f, space));
}

void mixImGui::gui_layout::new_line ()
{
    ImGui::NewLine ();
}

void mixImGui::gui_layout::seperator ()
{
    ImGui::Separator ();
}

void mixImGui::gui_layout::before_render ()
{
    auto w_size = ImGui::GetWindowSize ();
    auto w_pos = ImGui::GetWindowPos ();

    auto cursor_pos = ImGui::GetCursorPos ();

    // ImGui::SetCursorPos (ImVec2 (_local_cursor.x + _cursor.x, _local_cursor.y + _cursor.y));
    if (_global_layout == mixImGui::layout_type::horizontal)
    {
        if (_render_index > 0)
        {
            auto last_item_size = ImGui::GetItemRectSize ();
            _cursor.x += (int) last_item_size.x;
            ImGui::SetCursorPos (_cursor);
        }
    }

    // command ();
}

void mixImGui::gui_layout::after_render ()
{
    _render_index++;
    auto last_item_size = ImGui::GetItemRectSize ();

    if (_current_layout == layout_type::vertical)
    {
        _rect._h += (int) last_item_size.y;
        _rect._w = std::max ((int) last_item_size.y, _rect._w);
        _cursor.y += (int) last_item_size.y; 
    }
    else
    {
        _rect._w += (int) last_item_size.x;
        _rect._h = std::max ((int) last_item_size.x, _rect._h);
        _cursor.x += (int) last_item_size.x;
    }
    ImGui::SetCursorPos (_cursor);
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
    auto block = mixImGui::gui_layout::get_top_block ();

    assert (block->get_layout () == target_layout);
    auto cursor_pos = ImGui::GetCursorPos ();

    if (block->_last_layout == layout_type::horizontal)
    {
        _cursor = ImVec2 ((float) block->_rect._x + block->_rect._w, (float) block->_rect._y);
    }
    else
    {
        _cursor = ImVec2 ((float) block->_rect._x, (float) block->_rect._y + block->_rect._h);
    }
    ImGui::SetCursorPos (_cursor);

    set_global_layout (block->get_previous_layout ());
    mixImGui::gui_layout::_layouts.pop ();

    if (_layouts.size () == 0)
    {
        _cursor = ImVec2 ();
    }
}
