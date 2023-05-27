#pragma once
#include "../gui/mixGui.h"

namespace mix
{
    namespace editor
    {
        namespace windows
        {
            class scene_window : public mixImGui::gui_window
            {
                public:

                void render () override;
                scene_window (std::string window_name, mixImGui::window_rect r);
            };
        } // namespace mix
    }     // namespace mix
}
