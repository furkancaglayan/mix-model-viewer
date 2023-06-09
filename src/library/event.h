#pragma once
#include "ievent_callback_base.h"
#include <vector>
namespace mix
{
    namespace library
    {

        class event_base
        {
            public:

            typedef std::vector<ievent_callback_base*> _action_list_base;

            virtual void add_listener (ievent_callback_base* action);
            virtual void remove_listener (ievent_callback_base* action);
            virtual void dispatch ();

            protected:

           _action_list_base _actions;
        };

        template <class U> class event
        {
            public:

            typedef std::vector<ievent_callback_base_with_args<U>*> _action_list;
            virtual void add_listener (ievent_callback_base_with_args<U>* action)
            {
                typename _action_list::iterator position =
                std::find (_actions.begin (), _actions.end (), action);

                if (position == _actions.end ())
                {
                    _actions.push_back (action);
                }
            }
            virtual void remove_listener (ievent_callback_base_with_args<U>* action)
            {
                typename _action_list::iterator position =
                std::find (_actions.begin (), _actions.end (), action);

                if (position != _actions.end ())
                {
                    _actions.erase (position);
                }
            }
            virtual void dispatch (U* obj)
            {
                for (ievent_callback_base_with_args<U>* action : _actions)
                {
                    (*action) (obj);
                }
            }

            protected:

            _action_list _actions;
        };
    } // namespace library
} // namespace mix
