#pragma once
#include "../core/mixEntity.h"
#include <memory>


namespace mix
{
    namespace scene_management
    {

        class mixScene
        {
            public:

            mixScene ();
            mixScene (mix::core::mixEntity* r);

            void update ();
            void render ();

            private:

            std::unique_ptr<mix::core::mixEntity> _root;
        };
    } // namespace scene_management
} // namespace mix
