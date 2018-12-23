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
	int delay;
	
	float dta;
public:
	MegaMan() {}
	MegaMan(Sprite* sprite_MegaMan, Sprite* sprite_LightEnergy, Sprite* sprite_Spark,
		Sprite* sprite_Smoke, Sprite* sprite_Weapons_And_Items,
		SpriteSheet* spriteSheet_MegaMan, SpriteSheet* spriteSheet_LightEnergy, SpriteSheet* spriteSheet_Spark,
		SpriteSheet* spriteSheet_Smoke, SpriteSheet* spriteSheet_Weapons_And_Items,
		Sound *sound);
	~MegaMan();

	Bullet* bullets[3];
	Smoke* smokes[8];

	const char* pathPNG;

	MegaManState* GetMegaManState();

	void ChangeAnimation(float dt, Keyboard* key);

	void OnCollision(Object *obj, D3DXVECTOR2 distance, D3DXVECTOR2 disMan);
	void Update(float dt, Keyboard* key);
	void Render(Viewport *viewport);

};

