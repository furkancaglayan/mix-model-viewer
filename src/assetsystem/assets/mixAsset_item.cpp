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
        const std::string mixAsset_item::get_shortened_name () const
        {
            std::string name = get_full_name ();
            if (name.size () > 8)
            {
                name = name.substr (0, 8);
                name.append ("...");
            }

            return name;
        }

        std::ostream& mixAsset_item::operator<< (std::ostream& out) const
        {
            out << get_base_name ();
            return out;
        }
        std::istream& mixAsset_item::operator>> (std::istream& in) const
        {
            auto data = get_base_name ();
            in >> data;
            return in;
        }

        inline std::string to_string (const mixAsset_item& item)
        {
            return item.get_base_name ();
        }
    } // namespace assetsystem
} // namespace mix