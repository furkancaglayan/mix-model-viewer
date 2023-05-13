#pragma once
#include <Windows.h>
#include <functional>
#include <string>
#include <tchar.h>
#include <vector>

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
                char p[max_len];
                sprintf (p, "%s\\*", path.c_str ());
                std::wstring ws = convert_utf8_to_wide (p);

                WIN32_FIND_DATA data;
                HANDLE hFind = FindFirstFileW (ws.c_str (), &data); // DIRECTORY

                if (hFind != INVALID_HANDLE_VALUE)
                {
                    do
                    {
                        // TODO: tidy here up...modern cpp...
                        // TODO2: arrange folder creation. Store them as weak ptr in somewhere.
                        auto cond = (search_type == mix::platform::platform_utils::search_type::file &&
                                     (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) ||
                                    (search_type == mix::platform::platform_utils::search_type::folder &&
                                     (wcscmp (data.cFileName, L".") != 0 && wcscmp (data.cFileName, L"..") != 0 &&
                                      (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)) ||
                                    (wcscmp (data.cFileName, L".") != 0 && wcscmp (data.cFileName, L"..") != 0);

                        if (cond)
                        {
                            auto p = path + "/" + convert_wide_to_utf8 (data.cFileName);
                            files.emplace_back (p);
                        }


                    } while (FindNextFileW (hFind, &data));
                    FindClose (hFind);
                }

                return files;
            }

            static void get_all_dfs (const std::string& root, std::vector<std::string>& list)
            {
                char p[max_len];
                sprintf (p, "%s\\*", root.c_str ());
                std::wstring ws = convert_utf8_to_wide (p);

                WIN32_FIND_DATA data;
                HANDLE hFind = FindFirstFileW (ws.c_str (), &data); // DIRECTORY

                if (hFind != INVALID_HANDLE_VALUE)
                {
                    do
                    {
                        auto is_folder = (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
                        auto path = root + "/" + convert_wide_to_utf8 (data.cFileName);

                        if ((data.dwFileAttributes & INVALID_FILE_ATTRIBUTES) != 0 &&
                            wcscmp (data.cFileName, L".") != 0 && wcscmp (data.cFileName, L"..") != 0)
                        {
                            if (is_folder)
                            {
                                list.push_back (path);
                                get_all_dfs (path, list);
                            }
                            else
                            {
                                list.push_back (path);
                            }
                        }

                    } while (FindNextFileW (hFind, &data));
                    FindClose (hFind);
                }
            }

            static bool is_folder (const std::string& path)
            {
                auto wide = convert_utf8_to_wide (path.c_str ());
                DWORD dwAttrib = GetFileAttributesW (wide.c_str ());

                return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
            }
            static bool file_exists (const std::string& path)
            {
                return is_file (path);
            }

            static bool folder_exists (const std::string& path)
            {
                return is_folder (path);
            }

            static bool is_file (const std::string& path)
            {
                auto wide = std::wstring{ path.begin (), path.end () };
                DWORD dwAttrib = GetFileAttributesW (wide.c_str ());

                return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
            }

            static std::wstring convert_utf8_to_wide (const char* str)
            {
                std::wstring wstr;
                int result = MultiByteToWideChar (CP_UTF8, 0, str, (int) strlen (str), NULL, 0);
                if (result <= 0)
                {
                    auto error = GetLastError ();
                }
                else
                {
                    wstr.resize (result);
                    result = MultiByteToWideChar (CP_UTF8, 0, str, (int) strlen (str), &wstr[0], result);
                }
                return wstr;
            }


            static std::string convert_wide_to_utf8 (const wchar_t* wstr)
            {
                std::string str;
                int result = WideCharToMultiByte (CP_UTF8, 0, wstr, (int) wcslen (wstr), NULL, 0, NULL, NULL);
                if (result <= 0)
                {
                    auto error = GetLastError ();
                }
                else
                {
                    str.resize (result);
                    result = WideCharToMultiByte (CP_UTF8, 0, wstr, (int) wcslen (wstr), &str[0], result, NULL, NULL);
                    // CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0)
                }

                return str;
            }


            static std::string convert_wide_to_ansi (const wchar_t* wstr)
            {
                std::string str;
                int result = WideCharToMultiByte (CP_ACP, 0, wstr, (int) wcslen (wstr), NULL, 0, NULL, NULL);
                if (result <= 0)
                {
                    auto error = GetLastError ();
                }
                else
                {
                    str.resize (result);
                    result = WideCharToMultiByte (CP_ACP, 0, wstr, (int) wcslen (wstr), &str[0], result, NULL, NULL);
                }

                return str;
            }

            static std::wstring convert_ansi_to_wide (const char* str)
            {
                std::wstring wstr;
                int result = MultiByteToWideChar (CP_ACP, 0, str, (int) strlen (str), NULL, 0);
                if (result <= 0)
                {
                    auto error = GetLastError ();
                }
                else
                {
                    wstr.resize (result);
                    result = MultiByteToWideChar (CP_ACP, 0, str, (int) strlen (str), &wstr[0], result);
                }
                return wstr;
            }
        };

    } // namespace platform
} // namespace mix
