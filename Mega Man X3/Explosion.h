#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
using namespace Define;

class Explosion : public Object
{
protected:

	Animation* animationExplosion;

public:
	Explosion();
	Explosion(Sprite* sprite, SpriteSheet* sprite_sheet);
	~Explosion();

	void NewExplosion(D3DXVECTOR2 position);

	void ChangeAnimation();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
};