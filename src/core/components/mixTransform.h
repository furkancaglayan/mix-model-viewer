#pragma once
#include "../../math/vec.h"
#include <memory>
#include <string>

namespace mix
{
    namespace components
    {
        struct mixTransform
        {
            public:

            void translate (vec3 v);
            vec3 position;
            vec3 rotation;

            private:
        };
    } // namespace components
} // namespace mix
