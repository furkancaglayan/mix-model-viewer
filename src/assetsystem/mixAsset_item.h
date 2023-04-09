#pragma once
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "../platform/typedefs.h"
#include "../platform/mixAsset_file.h"

namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>
        
        class mixAsset_item
        {
            public:
            mixAsset_item ()
            {

            }

            virtual void construct_from (mix::platform::mixAsset_file file);
        };
    } // namespace core
} // namespace mix
