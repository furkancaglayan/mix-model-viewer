#include "mixScene.h"

mix::scene_management::mixScene* mix::scene_management::mixScene::_instance = nullptr;

mix::scene_management::mixScene::mixScene () : mixScene (new mix::core::mixEntity ("New Scene"))
{
}

mix::scene_management::mixScene::mixScene (mix::core::mixEntity* r)
{
    _root = std::unique_ptr<mix::core::mixEntity> (r);
    _active_cam = std::make_unique<mix::core::mixCamera> ();
    _active_cam->_transform->set_position (vec3 (0, 0, -15));
    _instance = this;
}

void mix::scene_management::mixScene::update ()
{
    _active_cam->update ();
    _root->update ();
}

void mix::scene_management::mixScene::render (mix::rendering::rendering_context* rendering)
{
    _root->render (rendering);
}

void mix::scene_management::mixScene::set_parameters (mix::rendering::rendering_context* rendering) const
{
    rendering->set_mat4 ("_view", _active_cam->get_view_mat ());
    rendering->set_mat4 ("_projection", _active_cam->get_projection_mat ());
    rendering->set_vec3 ("_view_pos", _active_cam->_transform->get_position ());

    auto size = _lights.size ();
    rendering->set_1i ("num_lights", static_cast<int> (size));

    for (size_t i = 0; i < size; i++)
    {
        std::weak_ptr<mix::core::light::mixLight> light = _lights.at (0);
        std::string pos = "lights[" + std::to_string (i) + "].position";
        std::string diff = "lights[" + std::to_string (i) + "].diffuse";
        std::string spec = "lights[" + std::to_string (i) + "].specular";
        std::string ambient = "lights[" + std::to_string (i) + "].ambient";
        std::string intensity = "lights[" + std::to_string (i) + "].intensity";
        std::string att = "lights[" + std::to_string (i) + "].attenuation";
    
        rendering->set_vec3 (pos, light.lock ()->_transform->get_position ());
        rendering->set_vec3 (spec, vec3 (1));
        rendering->set_vec3 (ambient, vec3 (1));
        rendering->set_vec3 (diff, light.lock ()->get_color ());
        rendering->set_1f (intensity, light.lock ()->get_intensity ());
        rendering->set_1f (att, 1.0f);
    }
}

void mix::scene_management::mixScene::add_entity (const std::shared_ptr<mix::core::mixEntity>& entity)
{
    get_root ()->add_child (entity);
    if (auto light = std::dynamic_pointer_cast<mix::core::light::mixLight> (entity))
    {
        _lights.push_back (light);
    }

}

mix::core::mixCamera* mix::scene_management::mixScene::get_main_cam () const
{
    return _active_cam.get();
}

mix::core::mixEntity* mix::scene_management::mixScene::get_root () const
{
    return _root.get();
}

std::vector<std::weak_ptr<mix::core::light::mixLight>> mix::scene_management::mixScene::get_lights () const
{
    return _lights;
}

