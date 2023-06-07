#pragma once
#include "../mixEditor.h"

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
                void on_editor_window_size_changed_impl (const vec2i& size) override;
                hierarchy_window (std::string window_name, mixImGui::window_rect r);
                ~hierarchy_window ();

                static void initialize (const vec2i& size);

                private:

                bool _visible_entities = true;
                bool _visible_lights = true;
                bool _visible_cameras = true;
                i_guielement* _selected_entity;
            };
        } // namespace windows
    }     // namespace editor

} // namespace mix
