#pragma once
#include "../math/constants.h"
#include "../math/mat.h"
#include <memory>
#include <string>

namespace mix
{
    class transform
    {
        public:

        constexpr static vec3 forward{ vec3 (0, 0, 1) };
        constexpr static vec3 right{ vec3 (1, 0, 0) };
        constexpr static vec3 up{ vec3 (0, 1, 0) };
    };

    namespace core
    {
        struct mixTransform
        {
            public:

            mixTransform ();
            mixTransform (vec3 pos);
            mixTransform (vec3 pos, vec3 rot);
            mixTransform (vec3 pos, vec3 rot, vec3 scale);
            ~mixTransform ();

            mixTransform (mixTransform&& move) = delete;
            mixTransform (const mixTransform& copy) = delete;

            void set_position (vec3 v);
            void set_local_position (vec3 v);
            void set_rotation (vec3 v);
            void set_scale (vec3 v);
            void translate (vec3 v);
            void scale (vec3 v);
            void look_at (const vec3& pos);
            // void rotate (vec3 v);
            void rotate_around (float x, float y, float z);
            void update ();

            mat4 get_model_mat () const;

            inline vec3 up () const
            {
                return _up;
            }

            inline vec3 forward () const
            {
                return _forward;
            }

            inline vec3 right () const
            {
                return _right;
            }

            inline float yaw () const
            {
                return _rotation.x;
            }

            inline float pitch () const
            {
                return _rotation.y;
            }

            inline float roll () const
            {
                return _rotation.z;
            }

            inline vec3 get_position () const
            {
                return _position;
            }

            inline vec3 get_local_position () const
            {
                return _local_position;
            }

            inline vec3 get_rotation () const
            {
                return _rotation;
            }

            inline vec3 get_scale () const
            {
                return _scale;
            }

            private:

            void update_vectors ();

            vec3 _position;
            vec3 _local_position;
            // yaw, pitch, roll
            vec3 _rotation;
            vec3 _scale;

            vec3 _forward;
            vec3 _up;
            vec3 _right;

            bool _is_dirty;
        };
    } // namespace core
} // namespace mix
