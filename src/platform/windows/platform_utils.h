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

            static std::vector<std::wstring> get_directories (const std::string& path)
            {
                std::vector<std::wstring> folders;
                WIN32_FIND_DATA data;
                auto path_dir = path + "/*";
                std::wstring ws (path_dir.begin (), path_dir.end ());
                HANDLE hFind = FindFirstFileW (ws.c_str (), &data); // DIRECTORY

                if (hFind != INVALID_HANDLE_VALUE)
                {
                    do
                    {
                        if (wcscmp (data.cFileName, L".") != 0 &&
                            wcscmp (data.cFileName, L"..") != 0 &&
                            (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
                        {
                            folders.emplace_back (data.cFileName);
                        }
                    } while (FindNextFileW (hFind, &data));
                    FindClose (hFind);
                }

                return folders;
            }

       

            static std::vector<std::wstring> get_files (const std::string& path)
            {
                std::vector<std::wstring> files;
                WIN32_FIND_DATA data;
                auto path_dir = path + "/*";
                std::wstring ws (path_dir.begin (), path_dir.end ());
                HANDLE hFind = FindFirstFileW (ws.c_str (), &data); // DIRECTORY

                if (hFind != INVALID_HANDLE_VALUE)
                {
                    do
                    {
                        if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
                        {
                            files.emplace_back (data.cFileName);
                        }
                    } while (FindNextFileW (hFind, &data));
                    FindClose (hFind);
                }

                return files;
            }
        };

    } // namespace platform
} // namespace mix
