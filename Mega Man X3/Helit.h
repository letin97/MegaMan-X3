#pragma once
#include "Enemy.h"

class Helit :public Enemy
{
protected:
	int delay;
	bool isShoot;
public:

	enum HelitAction
	{
		Flying,
		Shooting
	};

	HelitAction action;

	Helit() {}
	~Helit() {}
	Helit(MegaMan *megaMan, Sprite* sprite_enemy, Sprite* sprite_Item, SpriteSheet* spriteSheet_Enemy, SpriteSheet* spriteSheet_Item);

	void New(D3DXVECTOR2 pos);
	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
};