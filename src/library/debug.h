#pragma once
#include "ievent_callback_base.h"
#include <vector>

#define ASSERT(...) mix::library::debug::_assert (__VA_ARGS__)
#define FAILED_ASSERT(...) mix::library::debug::_failed_assert (__VA_ARGS__)
#define LOG(...) mix::library::debug::_log (__VA_ARGS__)
#define LOG_ERROR(msg) mix::library::debug::_log (msg, mix::library::debug_level::error)
#define LOG_WARNING(msg) mix::library::debug::_log (msg, mix::library::debug_level::error)
#define INFO(msg) mix::library::debug::_log (msg, mix::library::debug_level::info)
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
            static void _assert (bool cond);
            static void _assert (bool cond, const char* msg);
            static void _break ();
            static void _break (const char* msg);
            static void _log (const char* msg, debug_level level = debug_level::log);
            static void _info (const char* msg);
            static void _show_warning ();
            static void initialize (const char* path);

            debug () = delete;
        };

    } // namespace library
} // namespace mix
