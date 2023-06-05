#pragma once
#include "../gui/mixGui.h"
#include "mixEditor.h"

namespace mix
{
    namespace editor
    {
        namespace windows
        {
            using namespace mixImGui;
            class scene_window : public mixImGui::gui_window
            {
                public:

                void render () override;
                static void initialize (vec2 w_size);
                scene_window (std::string window_name, mixImGui::window_rect r);
            };

        } // namespace mix
    }     // namespace mix
}
