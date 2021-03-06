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

	//Sound
	GSound *soundBulletLv1;
	GSound *soundBulletLv2;
	GSound *soundBulletLv3;

public:
	enum BulletType
	{
		BulletLv1,
		BulletLv2,
		BulletLv3,
		BulletHeadGunner,
		BulletNotorBanger,
		BulletHelit,
		BulletByte
	};
	BulletType bulletType;

	enum BulletState
	{
		Firing,
		Bursting,
		Cling
	};
	BulletState bulletState;

	Bullet();
	Bullet(Sprite* sprite_bullet, SpriteSheet* sprite_sheet, Sound* sound);
	~Bullet();

	BulletType GetBulletType();
	void SetBulletType(BulletType bulletType);

	BulletState GetBulletState();
	void SetBulletState(BulletState state);

	void NewBullet(D3DXVECTOR2 position, bool flipflag, int energyLevel);

	void ChangeAnimation();
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision();
};
