#pragma once
#include "../math/constants.h"
#include "../math/mat.h"
#include "../math/vec.h"
#include "../platform/typedefs.h"
#include "mixTransform.h"
#include <cstdint>
#include <vector>
#include "components/mixComponent.h"

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

            void add_component (std::unique_ptr<mixComponent> comp);
            void add_component (mixComponent* comp);
            void set_name (std::string name);
            void add_child (std::shared_ptr<mixEntity> ch);

            std::string get_name () const;
            mixEntity* get_parent () const;
            std::vector<std::shared_ptr<mixEntity>> get_children () const;

            virtual void update ();
            virtual void render ();
            protected:

            bool _is_enabled{ true };
            bool _is_visible{ true };

            std::string _name;
            std::weak_ptr<mixEntity> _parent;
            std::vector<std::shared_ptr<mixEntity>> _children;
            std::vector<std::unique_ptr<mixComponent>> _components;
        };
    } // namespace core
} // namespace mix
