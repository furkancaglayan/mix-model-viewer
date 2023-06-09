#include "event.h"

void mix::library::event_base::add_listener (ievent_callback_base* action)
{
    typename _action_list_base::iterator position = std::find (_actions.begin (), _actions.end (), action);

    if (position == _actions.end ())
    {
        _actions.push_back (action);
    }
}

void mix::library::event_base::remove_listener (ievent_callback_base* action)
{
    typename _action_list_base::iterator position = std::find (_actions.begin (), _actions.end (), action);

    if (position != _actions.end ())
    {
        _actions.erase (position);
    }
}

void mix::library::event_base::dispatch ()
{
    for (ievent_callback_base* action : _actions)
    {
        (*action) ();
    }
}
