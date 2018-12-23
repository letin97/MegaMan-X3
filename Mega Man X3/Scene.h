#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "ObjectManager.h"

class Scene
{
protected:
	ObjectManager* objManager;
public:

	Scene();
	~Scene();

	//Load Data Game
	void Init(Graphic* graphic, Sound *sound);

	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);

	//Vẽ Object lên màn hình
	void Render();
};

