#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "../core/mixWindow.h"
#include "../core/mixEntity.h"
#include "../core/light/mixLight.h"

namespace mix
{
    namespace gui
    {

        class test_gui
        {
            public:

            void init (mix::core::mixWindow* window);
            void new_frame (mix::core::mixEntity* root,
                            std::vector<std::weak_ptr<mix::core::light::mixLight>> lights,
                            mix::core::mixWindow* w);
        };
    } // namespace core
} // namespace mix
