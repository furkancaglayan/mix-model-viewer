#include "mixAsset_loader_base.h"

namespace mix
{
    namespace assetsystem
    {
       
        template <class T>
        void mixAsset_loader_base::add_resolver (std::string s, std::function<T (const mix::platform::mixAsset_file&)> func) noexcept
        {
            _resolvers[s] = func;
        }

    } // namespace assetsystem
} // namespace mix