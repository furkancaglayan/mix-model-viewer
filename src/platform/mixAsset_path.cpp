#include "mixAsset_path.h"
#include <iostream>

mix::platform::mixAsset_path::mixAsset_path (const std::string& path) : _path{ path }
{
    _name = _path.substr (_path.find_last_of ("/\\") + 1);
    std::string::size_type const p (_name.find_last_of ('.'));
    if (platform_utils::is_file (_path))
    {
        _extension = _name.substr (p + 1);
    }
    else
    {
        _extension = std::string ();
    }
    _base_name = _name.substr (0, p);
}
