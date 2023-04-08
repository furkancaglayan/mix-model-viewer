#include "mixAsset_file.h"

namespace mix
{
    namespace platform
    {
       
        bool mix::platform::mixAsset_file::open ()
        {
            auto w_string = std::wstring (_path);
            /*
            * #define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL 
            */
            auto access = GENERIC_READ;
            auto share = FILE_SHARE_READ;
            auto creation_disposition = OPEN_EXISTING;
            auto flags_and_attributes = FILE_ATTRIBUTE_NORMAL;

            _handle = CreateFileW (w_string.c_str (), access, share, NULL,
                                   creation_disposition, flags_and_attributes, NULL);

            if (_handle == INVALID_HANDLE_VALUE)
            {
                DWORD err = GetLastError ();
                HRESULT hr = HRESULT_FROM_WIN32 (err);
                return false;
            }
            else
            {
                return true;
            }
        }

        bool mixAsset_file::read ()
        {
            auto size = get_file_size ();
            _buffer = (char*) malloc (sizeof (char) * (size)); 
            unsigned long read;
            BOOL result = ReadFile (_handle, _buffer, (DWORD)size, &read, NULL);
            if (result)
            {
                _content = std::string{ _buffer, read };
            }
            else
            {
                delete _buffer;
                _buffer = nullptr;
                CloseHandle (_handle);
                _handle = nullptr;
            }
            return result;
        }

        bool mixAsset_file::close ()
        {
            assert (_handle);
            BOOL result = CloseHandle (_handle);
            _handle = nullptr;
            return result;
        }

        size_t mix::platform::mixAsset_file::get_file_size ()
        {
            LARGE_INTEGER size;
            BOOL result = GetFileSizeEx (_handle, &size);
            return result == FALSE ? -1 : size.QuadPart;
        }
    } // namespace assetsystem
} // namespace mix