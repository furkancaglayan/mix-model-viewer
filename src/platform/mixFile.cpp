#include "mixFile.h"

mix::platform::mixFile::mixFile (mixAsset_path&& path) : _path{ std::move (path) }, _handle{ INVALID_HANDLE_VALUE }
{
}

mix::platform::mixFile::mixFile (const mixAsset_path& path) : _path{ path }, _handle{ INVALID_HANDLE_VALUE }
{
}

mix::platform::mixFile::mixFile (std::string&& path)
: _path{ mixAsset_path{ std::move (path) } }, _handle{ INVALID_HANDLE_VALUE }
{
}

mix::platform::mixFile::~mixFile ()
{
    _handle = INVALID_HANDLE_VALUE;
}

bool mix::platform::mixFile::open ()
{
    auto w_string = std::wstring (_path);
    auto access = GENERIC_READ;
    auto share = FILE_SHARE_READ;
    // TODO: If not exists, create new
    auto creation_disposition = OPEN_EXISTING;
    if (!platform::platform_utils::file_exists (_path))
    {
        creation_disposition = CREATE_NEW;
        access = GENERIC_WRITE;
    }
    auto flags_and_attributes = FILE_ATTRIBUTE_NORMAL;

    assert (_handle == INVALID_HANDLE_VALUE);
    _handle = CreateFileW (w_string.c_str (), access, share, NULL, creation_disposition, flags_and_attributes, NULL);

    if (_handle == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError ();
        HRESULT hr = HRESULT_FROM_WIN32 (err);
        assert (false);
        return false;
    }
    else
    {
        is_open = true;
        return true;
    }
}

bool mix::platform::mixFile::write (std::string content, bool leave_open)
{
    assert (is_open);
    assert (_handle != INVALID_HANDLE_VALUE);
    // Write data to the file
    auto w_string = std::wstring (_path);
    DWORD bytesWritten;
    BOOL result = WriteFile (_handle, content.c_str (), (DWORD) content.size (), &bytesWritten, nullptr);
    if (!leave_open)
    {
        close ();
    }
    return result;
}

bool mix::platform::mixFile::read (char* ptr)
{
    assert (is_open);
    auto size = get_file_size ();
    //_buffer = (char*) malloc (sizeof (char) * (size));
    unsigned long read;
    BOOL result = ReadFile (_handle, ptr, (DWORD) size, &read, NULL);
    if (!result)
    {
        close ();
    }

    return result;
}

std::string mix::platform::mixFile::read_all_text ()
{
    assert (!is_open);
    open ();
    // Change this to store the text read
    auto size = get_file_size ();
    char* buffer = (char*) malloc (sizeof (char) * (size));
    read (buffer);
    std::string val{ buffer, size };
    free (buffer);
    close ();
    return val;
}

bool mix::platform::mixFile::close ()
{
    assert (_handle);
    assert (is_open);
    BOOL result = CloseHandle (_handle);
    _handle = INVALID_HANDLE_VALUE;
    is_open = false;
    return result;
}

size_t mix::platform::mixFile::get_file_size ()
{
    assert (is_open);
    LARGE_INTEGER size;
    BOOL result = GetFileSizeEx (_handle, &size);
    return result == FALSE ? -1 : size.QuadPart;
}

bool mix::platform::mixFile::exists ()
{
    return platform::platform_utils::file_exists (_path);
}
