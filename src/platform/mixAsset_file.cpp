#include "mixAsset_file.h"

namespace mix
{
    namespace platform
    {

        bool mix::platform::mixAsset_file::open ()
        {
            auto w_string = std::wstring (_path);
            auto access = GENERIC_READ;
            auto share = FILE_SHARE_READ;
            auto creation_disposition = OPEN_EXISTING;
            auto flags_and_attributes = FILE_ATTRIBUTE_NORMAL;

            assert (_handle == INVALID_HANDLE_VALUE);
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
                is_open = true;
                return true;
            }
        }

        bool mixAsset_file::read (char* ptr)
        {
            assert (is_open);
            auto size = get_file_size ();
            //_buffer = (char*) malloc (sizeof (char) * (size));
            unsigned long read;
            BOOL result = ReadFile (_handle, ptr, (DWORD) size, &read, NULL);
            if (!result)
            {
                CloseHandle (_handle);
                is_open = false;
                _handle = INVALID_HANDLE_VALUE;
                //_content = std::string{ _buffer, read };
            }

            return result;
        }

        std::string mixAsset_file::read_all_text ()
        {
            assert (!is_open);
            open ();
            //Change this to store the text read
            auto size = get_file_size ();
            char* buffer = (char*) malloc (sizeof (char) * (size));
            read (buffer);
            std::string val{ buffer, size };
            free (buffer);
            close ();
            return val;
        }

        bool mixAsset_file::close ()
        {
            assert (_handle);
            assert (is_open);
            BOOL result = CloseHandle (_handle);
            _handle = INVALID_HANDLE_VALUE;
            is_open = false;
            return result;
        }

        size_t mix::platform::mixAsset_file::get_file_size ()
        {
            assert (is_open);
            LARGE_INTEGER size;
            BOOL result = GetFileSizeEx (_handle, &size);
            return result == FALSE ? -1 : size.QuadPart;
        }
    } // namespace platform
} // namespace mix