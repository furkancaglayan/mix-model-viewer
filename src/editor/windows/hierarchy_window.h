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
                void on_window_size_changed (int w, int h) override;
                hierarchy_window (std::string window_name, mixImGui::window_rect r);
                ~hierarchy_window ();

                static void initialize (vec2 window_size);

                private:

                void render_entity (mix::core::mixEntity* entity, int i);
                bool _visible_entities = true;
                int _selected_entity;
            };
        } // namespace windows
    }     // namespace editor

} // namespace mix
