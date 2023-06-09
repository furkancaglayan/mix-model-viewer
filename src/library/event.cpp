#include "event.h"

mix::library::event::event ()
{
}

mix::library::event::~event ()
{
}

void mix::library::event::add_listener (ievent_callback_base* action)
{
    std::vector<ievent_callback_base*>::iterator position = std::find (_actions.begin (), _actions.end (), action);

    if (position == _actions.end ())
    {
        _actions.push_back (action);
    }
}

void mix::library::event::remove_listener (ievent_callback_base* action)
{
    std::vector<ievent_callback_base*>::iterator position = std::find (_actions.begin (), _actions.end (), action);

    if (position != _actions.end ())
    {
        _actions.erase (position);
    }
}

void mix::library::event::dispatch ()
{
    for (ievent_callback_base* action : _actions)
    {
        (*action) ();
    }
}
