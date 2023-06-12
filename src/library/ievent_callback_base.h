#pragma once
#include <memory>
#include <cassert>
namespace mix
{
    namespace library
    {
        /* class ievent_callback_base
        {
            public:

            virtual void operator() () = 0;
        };
        */
        template <class T> class ievent_callback_base_with_args// : public ievent_callback_base
        {
            public:

            virtual void operator() (T* t) = 0;
            /* void operator() () override
            {
                assert (false);
            }*/
        };
    } // namespace library
} // namespace mix
