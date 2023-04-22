#include "mixAsset_item.h"

namespace mix
{
    namespace assetsystem
    {
        mixAsset_item::mixAsset_item (mix::platform::mixAsset_path&& path) noexcept
        : _path{ std::move (path) }, _guid{ mix::core::mixGuid::create_new () }
        {

        }
        mix::assetsystem::mixAsset_item::mixAsset_item (const mix::platform::mixAsset_path& path) noexcept
        : _path{ path }, _guid{ mix::core::mixGuid::create_new () }
        {

        }
        std::ostream& mixAsset_item::operator<< (std::ostream& out) const
        {
            out << get_name();
            return out;
        }
        std::istream& mixAsset_item::operator>> (std::istream& in) const
        {
            auto data = get_name (); 
            in >> data;
            return in;
        }

        inline std::string to_string (const mixAsset_item& item)
        {
            return item.get_name ();
        }
    } // namespace assetsystem
} // namespace mix