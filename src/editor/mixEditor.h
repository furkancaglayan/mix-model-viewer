#pragma once
#include "../core/mixWindow.h"
#include "../scene_management/mixScene.h"
#include <memory>
#include "windows/scene_window.h"
#include "windows/hierarchy_window.h"
#include "windows/shortcuts_window.h"
#include "../containers/frame_buffer.h"
#include "../assetsystem/mixAsset_manager.h"
#include "editor_config.h"

namespace mix
{
    class mixEditor
    {
        public:

        static std::unique_ptr<mixEditor> _instance;
        static void create_new (editor_config config);
        static void initialize_asset_manager (std::string path);
        static void initialize_gui ();

        static mix::assetsystem::mixAsset_manager* get_asset_manager ();
        bool _should_run = false;
        void run ();
        mixEditor ();

        void render ();
        void init_render_buffers ();
        unsigned get_rendered_texture () const;
        void on_window_size_changed (const vec2i& size);
     
        mix::core::mixWindow* get_window () const;
        mix::scene_management::mixScene* get_active_scene () const;
        private:

        void gui_pass ();
        void start (editor_config config);
        
        std::unique_ptr<mix::core::mixWindow> _window;
        std::unique_ptr<mix::containers::frame_buffer> _frame_buffer;
        std::unique_ptr<mix::rendering::rendering_context> _rendering;
        std::unique_ptr<mix::scene_management::mixScene> _active_scene;
        std::unique_ptr<mix::assetsystem::mixAsset_manager> _asset_manager;
    };
} // namespace mix
