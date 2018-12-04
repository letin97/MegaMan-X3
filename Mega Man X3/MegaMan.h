#pragma once
#include "Object.h"
#include "Define.h"
#include "MegaManAnimation.h"
#include "MegaManState.h"
#include "Viewport.h"
#include "Bullet.h"
#include "LightEnergy.h"
#include "Spark.h"
#include "Smoke.h"

using namespace Define;

class MegaMan : public Object
{
protected:
	MegaManAnimation *animationMegaMan;
	MegaManState *stateMegaMan;
	MegaManState::State state;

	LightEnergy* lightEnergy;
	Spark* spark;

	int numBullet;
	int numSmoke;
	
public:
	MegaMan() {}
	MegaMan(Sprite* sprite_MegaMan, Sprite* sprite_Effect,Sprite* sprite_Weapons_And_Items,
		SpriteSheet* spriteSheet_MegaMan, SpriteSheet* spriteSheet_Effect, SpriteSheet* spriteSheet_Weapons_And_Items);
	~MegaMan();

	Bullet* bullets[3];
	Smoke* smokes[6];

	const char* pathPNG;

	MegaManState* GetMegaManState();

	void ChangeAnimation(float dt, Keyboard* key);

	void OnCollision(Object *obj, D3DXVECTOR2 distance, D3DXVECTOR2 disMan);
	void Update(float dt, Keyboard* key);
	void Render(Viewport *viewport);

};

