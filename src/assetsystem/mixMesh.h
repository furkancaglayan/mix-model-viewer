#pragma once
#include "mixAsset_base.h"
#include <memory>
#include <string>

namespace mix
{
    namespace assetsystem
    {
        class mixMesh : public mixAsset_base
        {
            public:

            using mixAsset_base::read;

            mixMesh (std::string&& path)
            : mixAsset_base (std::move (path))
            {
            }
        };
    } // namespace assetsystem
} // namespace mix
