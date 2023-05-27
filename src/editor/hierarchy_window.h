#pragma once
#include "../gui/mixGui.h"

namespace mix
{
    namespace editor
    {
        namespace windows
        {
            using namespace mixImGui;
            class hierarchy_window : public mixImGui::gui_window
            {
                public:

                void render () override;
                hierarchy_window (std::string window_name, mixImGui::window_rect r);
            };
        } // namespace windows
    }     // namespace editor

} // namespace mix
