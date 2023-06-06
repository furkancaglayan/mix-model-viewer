#include "gui_window.h"


void mixImGui::gui_window::render ()
{
    ImGui::Begin (_window_name.c_str (), &_is_open, static_cast<ImGuiWindowFlags_> (_flags));
    ImGui::End ();
}

mixImGui::gui_window::gui_window (std::string name, window_rect rect, window_flags flags)
: _window_name{ name }, _rect{ rect }, _flags{ flags }
{
}

void mixImGui::gui_window::disable ()
{
    _is_open = false;
}

void mixImGui::gui_window::enable ()
{
    _is_open = true;
}

void mixImGui::gui_window::on_editor_window_size_changed (const vec2i& size)
{
    vec2i old_size = vec2i (_rect._w, _rect._h);
    on_editor_window_size_changed_impl (size);
}

void mixImGui::gui_window::set_title (std::string s)
{
    _window_name = s;
}

std::vector<mixImGui::gui_window*> mixImGui::gui_window::get_window_binds (window_binds bind) const
{
    return _window_binds.at (bind);
}

void mixImGui::gui_window::bind_with_window (mixImGui::gui_window* other, window_binds bind)
{
    auto& vec = _window_binds.at (bind);
    auto& vec_other = other->_window_binds.at (bind);
    assert (!std::count (vec.begin (), vec.end (), other));
    assert (!std::count (vec_other.begin (), vec_other.end (), this));

    vec.push_back (other);
    vec_other.push_back (this);
}

void mixImGui::gui_window::begin ()
{
    ImGui::SetNextWindowPos (ImVec2 (static_cast<float> (_rect._x), static_cast<float> (_rect._y)));
    ImGui::Begin (_window_name.c_str (), &_is_open, static_cast<ImGuiWindowFlags_> (_flags));
    auto size = ImGui::GetWindowSize ();
    ImGui::SetWindowSize (ImVec2 (static_cast<float> (_rect._w), static_cast<float> (_rect._h)));

    /* if (_rect._min_x != -1 && size.x < _rect._min_x)
    {
        size.x = _rect._min_x;
    }

    if (_rect._min_y != -1 && size.y < _rect._min_y)
    {
        size.y = _rect._min_y;
    }*/
    gui_layout::begin_vertical ();
}

void mixImGui::gui_window::end () const
{
    gui_layout::end_vertical ();
    ImGui::End ();
}

void mixImGui::gui_window::rescale (vec2i size)
{
    _rect._w = size.x;
    _rect._h = size.y;
}

void mixImGui::gui_window::set_position (vec2i pos)
{
    _rect._x = pos.x;
    _rect._y = pos.y;
}
