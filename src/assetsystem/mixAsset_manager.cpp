#include "mixAsset_manager.h"

namespace mix
{
    namespace assetsystem
    {
        template <class T> inline bool mixAsset_manager::load_asset (const mix::platform::mixAsset_file& file) noexcept
        {
            T asset = resolve_asset (file);
            if (!asset)
            {
                return false;
            }

            /* auto index = std::type_index{ typeid (T) };
            if (_maps.count (index))
            {
                mixAsset_map t = static_cast<mixAsset_map> ((_maps[index])->get ());
                t->add (t);
            }
            else
            {
                add_asset_map<T> ();
                load_asset (t);
            }*/
        }

    

      
      
    } // namespace assetsystem
} // namespace mix