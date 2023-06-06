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

void mixImGui::gui_window::on_window_size_changed (int w, int h)
{
    _rect._w = static_cast<float>(w);
    _rect._h = static_cast<float> (h);
}

void mixImGui::gui_window::set_title (std::string s)
{
    _window_name = s;
}

void mixImGui::gui_window::begin ()
{
    ImGui::SetNextWindowPos (ImVec2 (_rect._x, _rect._y));
    ImGui::Begin (_window_name.c_str (), &_is_open, static_cast<ImGuiWindowFlags_> (_flags));
    auto size = ImGui::GetWindowSize ();
    ImGui::SetWindowSize (ImVec2 (_rect._w, _rect._h));

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

void mixImGui::gui_window::rescale (float w, float h)
{
    _rect._w = w;
    _rect._h = h;
}

void mixImGui::gui_window::set_position (float x, float y)
{
    _rect._x = x;
    _rect._y = y;
}
