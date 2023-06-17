#pragma once
#include <vector>
#include <chrono>
#include <string>

#define ASSERT(...) mix::library::debug::_assert (__VA_ARGS__)
#define FAILED_ASSERT(...) mix::library::debug::_failed_assert (__VA_ARGS__)
#define DEBUG_LOG(...) mix::library::debug::_log (__VA_ARGS__)
#define LOG_ERROR(msg) mix::library::debug::_log (msg, mix::library::debug_level::error)
#define LOG_WARNING(msg) mix::library::debug::_log (msg, mix::library::debug_level::error)
#define INFO(s) mix::library::debug::_log (#s, mix::library::debug_level::info)
#define BREAK() mix::library::debug::_break ()

namespace mix
{
    namespace library
    {
        enum class debug_level
        {
            log,
            error,
            warning,
            info,
        };
        class debug
        {
            public:

            static void _failed_assert ();
            static void _failed_assert (const char* msg);
            static void _failed_assert (std::string msg);
            static void _assert (bool cond);
            static void _assert (bool cond, const char* msg);
            static void _break ();
            static void _break (const char* msg);
            static void _log (const char* msg, debug_level level = debug_level::log);
            static void _log (std::string msg, debug_level level = debug_level::log);
            static void _log (const unsigned char* msg, debug_level level = debug_level::log);
            static void _info (const char* msg);
            static void _show_warning ();
            static void initialize (const char* path);

            debug () = delete;

            private:

            static std::string get_level_string (debug_level level);
        };

    } // namespace library
} // namespace mix
