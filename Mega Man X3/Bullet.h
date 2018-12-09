#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
#include "Collision.h"

using namespace Define;

class Bullet : public Object
{
protected:
	Animation* animationBullet;
	float timeBurst;

public:
	enum BulletType
	{
		BulletLv1,
		BulletLv2,
		BulletLv3,
		BulletHeadGunner,
		BulletNotorBanger,
		BulletHelit
	};
	BulletType bulletType;

	enum BulletState
	{
		Firing,
		Bursting,
	};
	BulletState bulletState;

	Bullet();
	Bullet(Sprite* sprite_bullet, SpriteSheet* sprite_sheet);
	~Bullet();

	BulletType GetBulletType();
	void SetBulletType(BulletType bulletType);

	BulletState GetBulletState();
	void SetBulletState(BulletState state);

	void NewBullet(D3DXVECTOR2 position, bool flipflag, int energyLevel);

	void ChangeAnimation();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision();
};
