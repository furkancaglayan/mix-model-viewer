#pragma once
#include <string>
#include <memory>
#include "mixFolder.h"

namespace mix
{
    namespace core
    {
        class mixFile
        {
            public:

            mixFile (std::string&& path, std::shared_ptr<mixFolder> parent)
            : _path{ std::move (path) }, _parent{ parent }
            {
            
            }
            mixFile () = default;

            private:

            std::string _path;
            std::string _name;
            std::string _extension;

            std::weak_ptr<mixFolder> _parent;
        };
    } // namespace core
} // namespace mix
