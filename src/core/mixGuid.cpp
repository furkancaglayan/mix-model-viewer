#include "mixGuid.h"

mix::core::mixGuid::mixGuid (std::string& val) : _internal{ std::move (val) }
{

}

mix::core::mixGuid mix::core::mixGuid::create_new ()
{
    GUID guid;
    HRESULT hCreateGuid = CoCreateGuid (&guid);
    // DATA1: refers to first 8 digits
    // DATA2: refers to first group of 4 digits
    // DATA3: refers to second group of 4 digits:
    // DATA4:

    OLECHAR* guidString;
    HRESULT result = StringFromCLSID (guid, &guidString);
    std::string str = mix::platform::platform_utils::wide_to_string (guidString);
    CoTaskMemFree (guidString);
    return mixGuid{ str };
}
