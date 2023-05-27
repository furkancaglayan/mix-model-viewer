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

void mixImGui::gui_window::begin ()
{
    ImGui::SetNextWindowPos (ImVec2 (_rect._x, _rect._y));
    ImGui::Begin (_window_name.c_str (), &_is_open, static_cast<ImGuiWindowFlags_> (_flags));
    auto size = ImGui::GetWindowSize ();

    if (_rect._min_x != -1 && size.x < _rect._min_x)
    {
        size.x = _rect._min_x;
    }

    if (_rect._min_y != -1 && size.y < _rect._min_y)
    {
        size.y = _rect._min_y;
    }
    ImGui::SetWindowSize (size);
}

void mixImGui::gui_window::end () const
{
    ImGui::End ();
}
