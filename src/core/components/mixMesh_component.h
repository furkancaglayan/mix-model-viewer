#pragma once
#include <cstdint>
#include "mixComponent.h"
#include "../../assetsystem/assets/mixMesh.h"
#include "../../scene_management/mixScene.h"

namespace mix
{
    namespace components
    {

        class mixMesh_component : public mix::components::mixComponent
        {
            public:

            mixMesh_component (std::shared_ptr<mix::assetsystem::mixMesh> mesh);
            void render (/*mix::scene_management::mixScene* scene,*/ 
                         mix::rendering::rendering_context* rendering,
                         const mix::core::mixTransform* transform) override;

            private:

            std::weak_ptr<mix::assetsystem::mixMesh> _mesh;
        };
    } // namespace core
} // namespace mix
