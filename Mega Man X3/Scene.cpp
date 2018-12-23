#include "Scene.h"


Scene::Scene()
{

}

Scene::~Scene()
{
	delete objManager;
}

//Load Data Game
void Scene::Init(Graphic* graphic, Sound *sound)
{
	objManager = new ObjectManager();
	objManager->Init(graphic, sound);
}

//Update Game sau khoảng thời gian dt
void Scene::Update(float dt, Keyboard* key)
{
	objManager->Update(dt, key);
}


//Vẽ Object lên màn hình
void Scene::Render()
{
	objManager->Render();
}