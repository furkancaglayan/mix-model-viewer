#pragma once
#include <cstdint>
#include "mixComponent.h"
#include "../../assetsystem/assets/mixMesh.h"
#include "../../scene_management/mixScene.h"
#include "../../assetsystem/assets/mixMaterial.h"

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
            void set_material (std::shared_ptr<mix::assetsystem::mixMaterial> material);
            void update () override;
            private:

            std::weak_ptr<mix::assetsystem::mixMaterial> _material;

            std::weak_ptr<mix::assetsystem::mixMesh> _mesh;
        };
    } // namespace core
} // namespace mix
