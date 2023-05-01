#pragma once
#include "../math/constants.h"
#include "../math/mat.h"
#include "../math/vec.h"
#include "../platform/typedefs.h"
#include "components/mixTransform.h"
#include <cstdint>
using namespace mix::components;

namespace mix
{
    namespace core
    {

        class mixEntity
        {
            public:

            std::unique_ptr<mixTransform> _transform;

            mixEntity ();
            mixEntity (vec3 pos);
            mixEntity (std::string name);
            mixEntity (std::string name, vec3 pos);

            void set_name (std::string name);
            virtual void update ();
            protected:

            bool _is_enabled{ true };
            bool _is_visible{ true };

            std::string _name;
        };
    } // namespace core
} // namespace mix
