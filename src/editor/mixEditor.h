#pragma once
#include "../core/mixWindow.h"
#include "../scene_management/mixScene.h"
#include <memory>
#include "scene_window.h"
#include "hierarchy_window.h"

namespace mix
{
    class mixEditor
    {
        public:

        static std::unique_ptr<mixEditor> _instance;
        static void create_new ();

        bool _should_run = false;
        void run ();
        inline void select_monitor (int num);
        
        mixEditor ();
     
        mix::core::mixWindow* get_window () const;
        mix::scene_management::mixScene* get_active_scene () const;
        std::unique_ptr<mix::core::mixWindow> _window;
        private:

        void render ();
        void gui_pass ();
        std::unique_ptr<mix::rendering::rendering_context> _rendering;
        std::unique_ptr<mix::scene_management::mixScene> _active_scene;
        void start ();
    };
} // namespace mix
