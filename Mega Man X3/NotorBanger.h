#pragma once
#include "Enemy.h"

class NotorBanger :public Enemy
{
protected:
	int delay;
	bool isJump;
	bool isShoot;
public:

	enum NotorBangerAction
	{
		Standing,
		TargetSkew,
		TargetVertical,
		ShootingSkew,
		ShootingVertical,
		BackShootingSkew,
		BackShootingVertical,
		Moving
	};

	NotorBangerAction action;

	NotorBanger() {}
	~NotorBanger() {}
	NotorBanger(MegaMan *megaMan, Sprite* sprite_enemy, Sprite* sprite_Item, SpriteSheet* spriteSheet_Enemy, SpriteSheet* spriteSheet_Item);

	void New(D3DXVECTOR2 pos);
	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
};