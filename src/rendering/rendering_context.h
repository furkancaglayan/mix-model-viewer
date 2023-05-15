#pragma once
#include "../math/constants.h"
#include "../math/mat.h"
#include <vector>
#include <string>
namespace mix
{
    namespace rendering
    {

        class rendering_context
        {
            public:

            void set_1f (int loc, float f);
            void set_1i (int loc, int f);
            void set_vec3 (int loc, vec3 vec);
            void set_mat3 (int loc, mat3 mat);
            void set_vec4 (int loc, vec4 vec);
            void set_mat4 (int loc, mat4 mat);

            void set_1f (const std::string& s, float f);
            void set_1i (const std::string& s, int f);
            void set_vec3 (const std::string& s, vec3 vec);
            void set_mat3 (const std::string& s, mat3 mat);
            void set_vec4 (const std::string& s, vec4 vec);
            void set_mat4 (const std::string& s, mat4 mat);

            void initialize () const;
            void finalize () const;
            unsigned _active_program;

        };
    } // namespace rendering
} // namespace mix
