#pragma once
#include "../math/mat.h"
#include "../math/vec.h"
#include "../math/constants.h"
#include "../platform/typedefs.h"
#include <cstdint>

namespace mix
{
    namespace core
    {

        enum class projection_mode : std::uint8_t
        {
            perspective,
            orthogonal
        };
        class mixCamera
        {
            using uint = unsigned int;

            public:

            mixCamera ()
            {
            }
            mat4 get_view_mat () const;
            mat4 get_projection_mat () const;
            void change_projection (projection_mode p);
            void refresh ();

            private:

            float _fov{ 75.0f };
            float _yaw{};
            float _pitch{};
            float movement_speed{ 2.0f };
            float _sensitivity{ 2.0f };
            float _zoom{ 1.0f };
            float _near{ 0.01f };
            float _far{ 1000.0f };
            float _aspect{ 16.0f / 9.0f };

            //TODO: replace with entity and transform
            vec3 _forward{ 0 };
            vec3 _up{ 0 };
            vec3 _right{ 0 };
            vec4 _eye{ 0 };
            vec4 _at{ 0 };

            projection_mode _projection{ projection_mode ::perspective };
        };
    } // namespace core
} // namespace mix
