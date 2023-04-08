#pragma once
#include <vector>
#include <memory>
#include <string>
#include "typedefs.h"

namespace mix
{
    namespace platform
    {
        class mixAsset_folder
        {
            public:

            mixAsset_folder (std::string&& path, std::shared_ptr<mixAsset_folder> parent)
            : _path{ std::move (path) }, _parent{ parent }
            {
            }
            void collect ();

            private:

            std::string _path;
            std::weak_ptr<mixAsset_folder> _parent;
            std::vector<std::shared_ptr<mixAsset_folder>> _children;
        };
    };
} // namespace mix
