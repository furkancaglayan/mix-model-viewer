#pragma once
#include "../../gui/mixGui.h"
#include "../mixEditor.h"
#include "../../assetsystem/assets/mixTexture.h"

namespace mix
{
    namespace editor
    {
        namespace windows
        {
            using namespace mixImGui;
            class shortcuts_window : public mixImGui::gui_window
            {
                public:

                void render () override;
                void on_editor_window_size_changed_impl (const vec2i& size) override;
                static void initialize (const vec2i& size);
                shortcuts_window (std::string window_name, mixImGui::window_rect r);

                private:

#if DEBUG
                bool _show_styles_editor = true;
                mix::assetsystem::mixTexture* _styles_editor_tex;
#endif
            };

        } // namespace windows
    }     // namespace editor
} // namespace mix
