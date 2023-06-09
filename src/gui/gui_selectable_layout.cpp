#include "gui_selectable_layout.h"

mixImGui::gui_selectable_layout::gui_selectable_layout (mixImGui::layout_type new_layout, window_rect r) : gui_layout (new_layout, r)
{
    _last_selectable_index = 0;
}
