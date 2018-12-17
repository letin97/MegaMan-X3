#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
#include"Collision.h"

using namespace Define;

class Bee : public Object
{
protected:
	Animation* animation;
	bool isCollision;
	float timeBurst;
	float timeExist;

public:

	enum BeeState
	{
		Aliving,
		Dying
	};
	BeeState state;

	Bee();
	Bee(Sprite* sprite_BlastHornet, SpriteSheet* spriteSheet_BlastHornet);
	~Bee();

	void New(D3DXVECTOR2 position, bool flipflag);

	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
};
