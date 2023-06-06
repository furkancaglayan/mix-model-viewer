#pragma once
#include "../../gui/mixGui.h"
#include "../mixEditor.h"

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
                void on_editor_window_size_changed_impl (const vec2i& size) override;
                void on_window_resized (const vec2i& old_size, const vec2i& new_size) override;
                static void initialize (const vec2i& size);
                scene_window (std::string window_name, mixImGui::window_rect r);
            };

        } // namespace mix
    }     // namespace mix
}
