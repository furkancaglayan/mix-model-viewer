#pragma once

#include "../../rendering/rendering_context.h"
#include "../mixTransform.h"

namespace mix
{
    namespace components
    {
        class mixComponent
        {
            public:

            virtual void update () = 0;
            virtual void render (/* mix::scene_management::mixScene* scene,*/
                                 mix::rendering::rendering_context* rendering,
                                 const mix::core::mixTransform* transform) = 0;
        };
    } // namespace assetsystem
} // namespace mix
