#pragma once
#include "mixAsset_path.h"
#include <memory>
#include <string>
#include <vector>

namespace mix
{
    namespace platform
    {
        class mixAsset_folder
        {
            public:


            mixAsset_folder (mixAsset_path&& path /*, std::shared_ptr<mixAsset_folder> parent*/)
            : _path{ std::move (path) }/*, _parent{ parent }*/
            {
            }

            mixAsset_folder (std::string&& path /*, std::shared_ptr<mixAsset_folder> parent*/)
            : _path{ mixAsset_path{ std::move (path) } }/*, _parent{ parent } */
            {
            }
            const std::string get_name ()
            {
                return _path.get_name_without_extension ();
            }

            private:

            mixAsset_path _path;
            //std::weak_ptr<mixAsset_folder> _parent;
            std::vector<std::weak_ptr<mixAsset_folder>> _children;
        };
    }; // namespace platform
} // namespace mix
