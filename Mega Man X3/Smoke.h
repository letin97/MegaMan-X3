#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
using namespace Define;

class Smoke : public Object
{
protected:

	Animation* animationSmoke;

public:

	Smoke();
	Smoke(Sprite* sprite_smoke, SpriteSheet* sprite_sheet);
	~Smoke();

	void NewSmoke(D3DXVECTOR2 position, bool flipflag);

	void ChangeAnimation();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
};
