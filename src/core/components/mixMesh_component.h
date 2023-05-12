#pragma once
#include <cstdint>
#include "mixComponent.h"
#include "../../assetsystem/assets/mixMesh.h"
using namespace mix::assetsystem;

namespace mix
{
    namespace components
    {

        class mixMesh_component : public mixComponent
        {
            public:

            mixMesh_component (std::shared_ptr<mixMesh> mesh);
            void render () override;

            private:

            std::weak_ptr<mixMesh> _mesh;
        };
    } // namespace core
} // namespace mix
