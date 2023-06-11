#pragma once
#include "../core/mixWindow.h"
#include "../scene_management/mixScene.h"
#include <memory>
#include "windows/scene_window.h"
#include "windows/hierarchy_window.h"
#include "windows/shortcuts_window.h"
#include "../containers/frame_buffer.h"
#include "../assetsystem/mixAsset_manager.h"

namespace mix
{
    class editor_config
    {
        public:

        void deserialize ();
        void serialize () const;

        vec2i _editor_window_size;
    };
} // namespace mix
