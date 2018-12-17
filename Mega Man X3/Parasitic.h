#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
#include"Collision.h"

using namespace Define;

class Parasitic : public Object
{
protected:
	Animation* animation;
	float timeExist;
	

public:

	enum ParasiticState
	{
		Flying,
		Cling
	};
	ParasiticState state;
	bool isCling;
	bool appear;

	Parasitic();
	Parasitic(Sprite* sprite_Parasitic, SpriteSheet* spriteSheet_Parasitic);
	~Parasitic();

	void New(D3DXVECTOR2 position);

	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
};
