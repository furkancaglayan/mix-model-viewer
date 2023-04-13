#pragma once
#include "../platform/mixAsset_file.h"
#include "mixAsset_item.h"
#include <functional>
#include <string>
#include <unordered_map>
namespace mix
{
    namespace assetsystem
    {
        /// <summary>
        /// Support multiple extensions
        /// </summary>

        class mixAsset_loader_base
        {
            public:

            template <class T> T resolve (const mix::platform::mixAsset_file& file)
            {
                std::string ext = file.get_extension ();
                mixAsset_item item = _resolvers[ext](file);
                T t = static_cast<T> (t);
                return t;
            }
            template <class T>
            void add_resolver (std::string s, std::function<T (const mix::platform::mixAsset_file&)> func) noexcept;

            private:

            std::unordered_map<std::string, std::function<mixAsset_item (const mix::platform::mixAsset_file&)>> _resolvers;
        };

    } // namespace assetsystem
} // namespace mix
