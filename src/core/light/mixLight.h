#pragma once
#include "../mixEntity.h"
#include <cstdint>

namespace mix
{
    namespace core
    {
        namespace light
        {
            enum class light_type
            {
                directional,
                spot,
                point
            };
            class mixLight : public mix::core::mixEntity
            {
                public:

                mixLight ();
                mixLight (light_type type);
                mixLight (light_type type, vec3 color);
                light_type get_type () const;
                void set_type (light_type t);

                float get_intensity () const;
                void set_intensity (float f);
                
                vec3 get_color () const;
                void set_color (vec3 color);

                private:

                light_type _type;
                float _intensity;
                vec3 _color;
            };
        } // namespace light
    }     // namespace components
} // namespace mix
