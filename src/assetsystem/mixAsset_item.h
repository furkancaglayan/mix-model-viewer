#pragma once
#include "../core/mixGuid.h"
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

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

            mixAsset_item (std::string&& name) noexcept;
            mixAsset_item (const std::string& name) noexcept;

            mix::core::mixGuid _guid;
           
            protected:

            std::string _name;

        };
    } // namespace assetsystem
} // namespace mix
