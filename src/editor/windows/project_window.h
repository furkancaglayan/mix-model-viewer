#pragma once
#include "../../gui/mixGui.h"
#include "../mixEditor.h"
#include "../../assetsystem/assets/mixTexture.h"
#include "../../assetsystem/mixAsset_manager.h"

namespace mix
{
    namespace editor
    {
        namespace windows
        {
            using namespace mixImGui;
            class project_window : public mixImGui::gui_window
            {
                public:

                project_window (std::string window_name, mixImGui::window_rect r);

                void render () override;
                void on_editor_window_size_changed_impl (const vec2i& size) override;
                static void initialize (const vec2i& size);

                private:

                mix::assetsystem::mixTexture *_folder_icon, *_empty_folder_icon;
                mix::assetsystem::mixAsset_folder* _selected_folder;
                mix::assetsystem::asset_tree_ptr _root_node;
            };

        } // namespace windows
    }     // namespace editor
} // namespace mix
