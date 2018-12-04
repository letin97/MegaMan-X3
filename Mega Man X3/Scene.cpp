#include "Scene.h"


Scene::Scene()
{

}

Scene::~Scene()
{
	delete objManager;
}

//Load Data Game
void Scene::Init(Graphic* graphic)
{
	objManager = new ObjectManager();
	objManager->Init(graphic);
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