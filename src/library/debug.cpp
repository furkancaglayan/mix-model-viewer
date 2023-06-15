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
    std::cout << msg << std::endl;
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
