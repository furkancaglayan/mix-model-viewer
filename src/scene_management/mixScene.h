#pragma once

#include <memory>
#include <vector>
#include "../core/mixCamera.h"
#include "../rendering/scene_context.h"

namespace mix
{
    namespace scene_management
    {

        class mixScene
        {
            public:

            mixScene ();
            mixScene (mix::core::mixEntity* r);
            static std::unique_ptr<mixScene> _instance;

            void update ();
            void render (mix::rendering::rendering_context* rendering);
            void set_parameters (mix::rendering::rendering_context* rendering) const;
            void add_light (std::shared_ptr<mix::core::light::mixLight> l);
            mix::core::mixCamera* get_main_cam () const;
            mix::core::mixEntity* get_root () const;
            std::vector<std::weak_ptr<mix::core::light::mixLight>> get_lights() const;

            private:

            std::shared_ptr<mix::core::mixCamera> _active_cam;
            std::vector<std::weak_ptr<mix::core::light::mixLight>> _lights;
            std::unique_ptr<mix::core::mixEntity> _root;
        };
    } // namespace scene_management
} // namespace mix
