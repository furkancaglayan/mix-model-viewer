#pragma once
#include "../math/mat.h"
#include "../math/vec.h"
#include "../math/constants.h"
#include "../platform/typedefs.h"
#include "mixEntity.h"
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
        class mixCamera : public mixEntity
        {
            public:

            mixCamera ()
            {
            }
            mat4 get_view_mat () const;
            mat4 get_projection_mat () const;
            void change_projection (projection_mode p);

            void update () override;
            void debug_input (vec3 v);
            private:

            float _fov{ 75.0f };
            float movement_speed{ 2.0f };
            float _sensitivity{ 2.0f };
            float _zoom{ 1.0f };
            float _near{ 0.1f };
            float _far{ 100.0f };
            float _aspect{ 1024.0f / 768.0f };

            projection_mode _projection{ projection_mode ::perspective };
        };
    } // namespace core
} // namespace mix
