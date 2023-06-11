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
/*
std::vector<mixImGui::gui_window*> mixImGui::gui_window::get_window_binds (window_binds bind) const
{
    if (_window_binds.count(bind))
    {
        return _window_binds.at (bind);
    }

    return {};
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
*/
void mixImGui::gui_window::set_contrainsts (window_rect constraints)
{
    _constraints = constraints;
    _has_constraints = true;
}

void mixImGui::gui_window::clear_constraints ()
{
    _has_constraints = false;
}

void mixImGui::gui_window::set_positioning (window_positioning wp)
{
    _positioning = wp;

    if (wp == window_positioning::flexible)
    {
        _flags = _flags & ~window_flags::NoResize;
    }
}

void mixImGui::gui_window::begin ()
{
    if (_has_constraints)
    {
        ImGui::SetNextWindowSizeConstraints (ImVec2 (static_cast<float> (_constraints._x),
                                                     static_cast<float> (_constraints._y)),
                                             ImVec2 (static_cast<float> (_constraints._w),
                                                     static_cast<float> (_constraints._h)));
    }

    if (_positioning == window_positioning::fixed)
    {
        _flags = _flags | window_flags::NoResize;
    }

    ImGui::SetNextWindowSize (ImVec2 (static_cast<float> (_rect._w), static_cast<float> (_rect._h)));
    ImGui::SetNextWindowPos (ImVec2 (static_cast<float> (_rect._x), static_cast<float> (_rect._y)));

    ImGui::Begin (_window_name.c_str (), &_is_open, static_cast<ImGuiWindowFlags_> (_flags));
    auto size = ImGui::GetWindowSize ();

    if (_positioning == window_positioning::flexible && (_rect._w != static_cast<int> (size.x) ||
        _rect._h != static_cast<int> (size.y)))
    {
        on_window_resized (vec2i (_rect._w, _rect._h), vec2i (size.x, size.y));
    }
    
    gui_layout::begin_vertical ();
}

void mixImGui::gui_window::end () const
{
    gui_layout::end_vertical ();
    ImGui::End ();
}

void mixImGui::gui_window::rescale (const vec2i& size)
{
    _rect._w = size.x;
    _rect._h = size.y;
}

void mixImGui::gui_window::set_position (const vec2i& pos)
{
    _rect._x = pos.x;
    _rect._y = pos.y;
}

vec2i mixImGui::gui_window::get_position () const
{
    return vec2i (_rect._x, _rect._y);
}

vec2i mixImGui::gui_window::get_size () const
{
    return vec2i (_rect._w, _rect._h);
}

void mixImGui::gui_window::on_window_resized (const vec2i& old_size, const vec2i& new_size)
{
    rescale (new_size);
}

mixImGui::window_flags mixImGui::gui_window::get_flags () const
{
    return _flags;
}
