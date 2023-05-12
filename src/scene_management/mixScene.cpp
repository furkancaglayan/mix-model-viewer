#include "mixScene.h"


mix::scene_management::mixScene::mixScene () : mixScene (new mix::core::mixEntity ("Root"))
{
}

mix::scene_management::mixScene::mixScene (mix::core::mixEntity* r)
{
    _root = std::unique_ptr<mix::core::mixEntity> (r);
}

void mix::scene_management::mixScene::update ()
{
    _root->update ();
}

void mix::scene_management::mixScene::render ()
{
    _root->render ();
}
