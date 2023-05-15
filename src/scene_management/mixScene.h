#pragma once

#include "../core/light/mixLight.h"
#include <memory>
#include <vector>


namespace mix
{
    namespace scene_management
    {

        class mixScene
        {
            public:

            mixScene ();
            mixScene (mix::core::mixEntity* r);

            void update ();
            void render (mix::rendering::rendering_context* rendering);
            void set_parameters (mix::rendering::rendering_context* rendering) const;

            private:


            std::vector<std::weak_ptr<mix::core::light::mixLight>> _lights;
            std::unique_ptr<mix::core::mixEntity> _root;
        };
    } // namespace scene_management
} // namespace mix
