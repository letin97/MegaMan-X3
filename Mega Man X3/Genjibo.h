#pragma once
#pragma once
#include"Boss.h"

class Genjibo : public Boss
{
protected:

public:

	enum GenjiboState
	{
		Appearing,
		Attack1,
		Trans,
		Attack2,
		Attack3,
		Dying
	};
	GenjiboState state;

	Genjibo() {}
	~Genjibo() {}
	Genjibo(Sprite* sprite_boss, SpriteSheet* spriteSheet_boss, D3DXVECTOR2 pos);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
	void OnCollision();
	void ChangeAnimation(Keyboard* key);
	void New();
};