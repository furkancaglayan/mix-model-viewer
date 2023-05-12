#pragma once

#include <memory>
#include <string>
namespace mix
{
    namespace components
    {
        class mixComponent
        {
            public:

            virtual void update () = 0;
            virtual void render () = 0;
        };
    } // namespace assetsystem
} // namespace mix
