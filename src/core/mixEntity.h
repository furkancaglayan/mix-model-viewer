#pragma once
#include "../math/constants.h"
#include "../math/mat.h"
#include "../math/vec.h"
#include "components/mixComponent.h"
#include "../gui/i_guielement.h"
#include "../gui/gui_layout.h"
#include <cstdint>
#include <vector>

using namespace mix::components;

namespace mix
{
    namespace core
    {

        class mixEntity : public mixImGui::i_guielement
        {
            public:

            std::unique_ptr<mixTransform> _transform;

            mixEntity ();
            mixEntity (vec3 pos);
            mixEntity (std::string name);
            mixEntity (std::string name, vec3 pos);

            void add_component (mixComponent* comp);
            /* template <class Tcomponent, class... Targs> void add_component (Targs&&... args)
            {
                add_component (std::make_unique<Tcomponent> (std::forward<Targs> (args)...));
            }*/
            void set_name (std::string name);
            void add_child (std::shared_ptr<mixEntity> ch);

            std::string get_name () const;
            mixEntity* get_parent () const;
            std::vector<std::shared_ptr<mixEntity>> get_children () const;

            virtual void update ();
            virtual void render (mix::rendering::rendering_context* rendering);
            protected:

            bool _is_enabled{ true };
            bool _is_visible{ true };

            std::string _name;
            std::weak_ptr<mixEntity> _parent;
            std::vector<std::shared_ptr<mixEntity>> _children;
            std::vector<std::unique_ptr<mixComponent>> _components;

            // Inherited via i_guielement
            virtual void on_gui () override;
            virtual void on_inspector_gui () override;
            virtual void on_scene_gui () override;
            virtual std::string get_gui_name () override;
        };
    } // namespace core
} // namespace mix
