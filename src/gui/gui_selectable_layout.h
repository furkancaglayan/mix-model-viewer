#pragma once
#include "gui_layout.h"

namespace mixImGui
{
    struct gui_selectable_layout: public gui_layout 
    {
        gui_selectable_layout (mixImGui::layout_type new_layout, window_rect r);
        i_guielement* _selected;
        std::vector<i_guielement*> _selectables;
        int _last_selectable_index;
    };
   
} // namespace mixImGui
