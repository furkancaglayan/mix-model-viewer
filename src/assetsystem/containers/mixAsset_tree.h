#pragma once

#include <map>
#include <memory>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include "../../platform/mixFolder.h"

namespace mix
{
    namespace assetsystem
    {
        class mixAsset_tree
        {
            public:
            private:

            std::unique_ptr<mix::platform::mixFolder> _root;
        };


    } // namespace assetsystem
} // namespace mix
