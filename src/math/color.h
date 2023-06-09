#pragma once
#include "vec.h"
#include <string>

namespace mix
{
    namespace math
    {
        struct color
        {
            public:

            color ();
            color (float r, float g, float b);
            color (float r, float g, float b, float a);
            color (vec4 col);
            color (vec3 col);
            color (int r, int g, int b);
            color (int r, int g, int b, int a);
            color (unsigned col);
            static color from_uint (unsigned u);
            unsigned to_uint ();

            vec4 get_value ();
            private:

            vec4 _color;
        };
    } // namespace core
} // namespace mix
