#pragma once
#include "../platform/typedefs.h"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>
#if defined(SYSTEM_WIN64)
#include <combaseapi.h>
#endif

namespace mix
{
	namespace core
	{
        class mixGuid
        {
            public:

            static mixGuid create_new ();

            bool operator== (const mixGuid& p)
            {
                return !_internal.compare (p._internal);
            }

            bool operator!= (const mixGuid& p)
            {
                return _internal.compare (p._internal);
            }

            private:

            mixGuid (std::string& val) : _internal{ std::move (val) }
            {
            
            }
            std::string _internal;
		};
	}
}
