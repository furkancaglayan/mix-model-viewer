#pragma once
#include "../math/constants.h"
#include "../math/mat.h"
#include <string>
#include <vector>
 #include "../core/light/mixLight.h"

namespace mix
{
    namespace rendering
    {

        class scene_context
        {
            public:

            std::vector<std::weak_ptr<mix::core::light::mixLight>> _lights;
        };
    } // namespace rendering
} // namespace mix
