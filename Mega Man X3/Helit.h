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
	Helit(MegaMan *megaMan, Sprite* sprite_Helit, Sprite* sprite_Item, Sprite* sprite_Explosion,
		SpriteSheet* spriteSheet_Helit, SpriteSheet* spriteSheet_Item, SpriteSheet* spriteSheet_Explosion, Sound* sound);

	void New(D3DXVECTOR2 pos);
	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
};