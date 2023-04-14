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

            mixAsset_item (std::string&& name) noexcept
            : _name{ std::move (name) }, _guid{ mix::core::mixGuid::create_new () }
            {
            }

            mixAsset_item (const std::string& name) noexcept : _name{ name }, _guid{ mix::core::mixGuid::create_new () }
            {
            }
            /*
            mixAsset_item (mixAsset_item&& other) noexcept : mixAsset_item{ other._name }
            {
                std::cout << "Move constructor is called." << std::endl;
            }

            mixAsset_item (const mixAsset_item& other) = default;

            mixAsset_item () : _guid{ mix::core::mixGuid::create_new () }
            {
            }
            */
            protected:

            std::string _name;

            public:

            mix::core::mixGuid _guid;
        };
    } // namespace assetsystem
} // namespace mix
