#include "mixAsset_manager.h"

namespace mix
{
    namespace assetsystem
    {
        template <typename T>
        void mix::assetsystem::mixAsset_manager::add_asset_map ()
        {
            _maps[typeid (T)] = mixAsset_map{};
        }
        template <typename T>
        void mix::assetsystem::mixAsset_manager::add_asset (T t)
        {
            if (_maps.count (typeid(T)))
            {
                mixAsset_map t =
                static_cast<mixAsset_map> ((_maps[typeid (T)])->get ());
                t->add (t);
            }
            else
            {
                add_asset_map<T> ();
                add_asset (t);
            }
        }
        template <typename T>
        T mixAsset_manager::get_asset (const std::string& name) const
        {
            mixAsset_map t =
            static_cast<mixAsset_map> ((_maps[typeid (T)])->get ());
            return t.get (name);
        }
        void mixAsset_manager::load ()
        {
            _root->collect ();
        }
        void mixAsset_manager::load_async ()
        {
        }
    } // namespace assetsystem
} // namespace mix