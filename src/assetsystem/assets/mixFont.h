#pragma once
#include "../../math/vertex.h"
#include "mixAsset_item.h"
#include "mixMaterial.h"
#include <memory>
#include <string>
#include <vector>
#include "../../rendering/rendering_context.h"
using namespace mix::math;

namespace mix
{
    namespace assetsystem
    {

        class mixFont : public mix::assetsystem::mixAsset_item
        {
            public:

            mixFont (const mix::platform::mixAsset_path& path);
            ~mixFont ();

            private:
        };
    } // namespace assetsystem
} // namespace mix
