#include "mixEntity.h"
#include "mixCamera.h"


mix::core::mixEntity::mixEntity () : mixEntity ("Entity", vec3 (0))
{
}

mix::core::mixEntity::mixEntity (vec3 pos) : mixEntity ("Entity", pos)
{
}

mix::core::mixEntity::mixEntity (std::string name) : mixEntity (name, vec3(0))
{
}

mix::core::mixEntity::mixEntity (std::string name, vec3 pos) : _name{ "Entity" }
{
    _transform = std::make_unique<mix::components::mixTransform> (pos);
    _transform->set_position (pos);
}

void mix::core::mixEntity::set_name (std::string name)
{
    _name = name;
}

void mix::core::mixEntity::update ()
{
    _transform->update ();
}
