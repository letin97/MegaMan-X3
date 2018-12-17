#pragma once
#include "Boss.h"
#include "Explosion.h"

class Byte : public Boss
{
protected:
	int numSmoke;
public:

	enum ByteState
	{
		Standing,
		Shooting,
		Gliding,
		Dying
	};
	ByteState state;

	Bullet* bullet;
	Smoke* smokes[6];
	Explosion* explosion;

	Byte() {}
	~Byte() {}
	Byte(Sprite* sprite_Byte, Sprite* sprite_Smoke, Sprite* sprite_Explosion,
		SpriteSheet* spriteSheet_Byte, SpriteSheet* spriteSheet_Smoke, SpriteSheet* spriteSheet_Explosion, D3DXVECTOR2 pos);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
	void OnCollision();
	void ChangeAnimation(Keyboard* key);
};