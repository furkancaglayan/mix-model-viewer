#pragma once
#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>

namespace mix
{
    namespace platform
    {
        class platform_utils
        {
            public:

            enum class search_type
            {
                file,
                folder,
                all
            };
            static constexpr size_t max_len = 260;
            static std::vector<std::string> get_files (const std::string& path, search_type search_type)
            {
                std::vector<std::string> files;
                WIN32_FIND_DATA data;
                auto path_dir = path + "/*";
                std::wstring ws (path_dir.begin (), path_dir.end ());
                HANDLE hFind = FindFirstFileW (ws.c_str (), &data); // DIRECTORY

                if (hFind != INVALID_HANDLE_VALUE)
                {
                    do
                    {
                        //TODO: tidy here up...modern cpp...
                        auto cond =
                        (search_type == mix::platform::platform_utils::search_type::file &&
                         (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) ||
                        (search_type == mix::platform::platform_utils::search_type::folder &&
                         (wcscmp (data.cFileName, L".") != 0 &&
                          wcscmp (data.cFileName, L"..") != 0 &&
                          (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)) ||
                        ((wcscmp (data.cFileName, L".") != 0 &&
                          wcscmp (data.cFileName, L"..") != 0 &&
                          (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) ||
                         (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0);

                        if (cond)
                        {
                            files.emplace_back (wide_to_string(data.cFileName));
                        }
					

                       
                    } while (FindNextFileW (hFind, &data));
                    FindClose (hFind);
                }

                return files;
            }

       
            static bool is_folder (const std::string& path)
            {
                auto wide = std::wstring{path.begin(), path.end()};
                DWORD dwAttrib = GetFileAttributesW (wide.c_str());

                return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
                        (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
            }

             static bool is_file (const std::string& path)
            {
                auto wide = std::wstring{ path.begin (), path.end () };
                DWORD dwAttrib = GetFileAttributesW (wide.c_str ());

                return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
                        !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
            }

              static std::string wide_to_string (wchar_t* wide_arr)
            {
                char name[max_len];
                WideCharToMultiByte (CP_UTF8, 0, wide_arr, -1, name, max_len, NULL, NULL);
                return std::string{ name };
            }
        };

    } // namespace platform
} // namespace mix
