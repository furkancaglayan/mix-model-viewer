#include "debug.h"
#include <iostream>
#define ENABLE_ASSERTS

void mix::library::debug::_failed_assert ()
{
    _assert (false);
}

void mix::library::debug::_failed_assert (const char* msg)
{
    _assert (false, msg);
}

void mix::library::debug::_assert (bool cond)
{
    if (!cond)
    {
        _break ();
    }
}

void mix::library::debug::_assert (bool cond, const char* msg)
{
    if (!cond)
    {
        _log (msg, debug_level::error);
        _break ();
    }
}

void mix::library::debug::_break ()
{
#ifdef ENABLE_ASSERTS
    __debugbreak ();
#endif
}

void mix::library::debug::_break (const char* msg)
{
    _log (msg, debug_level::error);
    _break ();
}

void mix::library::debug::_log (const char* msg, debug_level level)
{
    std::time_t time = std::chrono::system_clock::to_time_t (std::chrono::system_clock::now());
    char* time_string = std::ctime (&time);
    size_t length = strlen (time_string);
    if ((length > 0) && (time_string[length - 1] == '\n'))
    {
        time_string[length - 1] = '\0';
    }

    printf ("[%s][%s] %s\n", time_string, get_level_string (level).c_str (), msg);
}

void mix::library::debug::_log (std::string msg, debug_level level)
{
    _log (msg.c_str(), level);
}

void mix::library::debug::_log (const unsigned char* msg, debug_level level)
{
    _log ((const char*) msg, level);
}

void mix::library::debug::_info (const char* msg)
{
    _log (msg, debug_level::info);
}

void mix::library::debug::_show_warning ()
{
}

void mix::library::debug::initialize (const char* path)
{
}

std::string mix::library::debug::get_level_string (debug_level level)
{
    switch (level)
    {
    case mix::library::debug_level::log: return "Log";
    case mix::library::debug_level::error: return "Error";
    case mix::library::debug_level::warning: return "Warning";
    case mix::library::debug_level::info: return "Info";
    default: break;
    }

    return "Log";
}
