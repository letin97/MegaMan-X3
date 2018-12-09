#pragma once
#include "Animation.h"
#include "MegaMan.h"
#include "Define.h"
#include "Item.h"
#include "Collision.h"
#include "Explosion.h"
#include "Collapse.h"

using namespace Define;

class Enemy : public Object
{
protected:
	Animation *animationEnemy;
	SpriteSheet* spriteSheetEnemy;

	//Đạn quái
	Bullet* bullets[3];
	int numBullet;
	
	//Vật phẩm rơi khi quái chết
	Item* item;

	//Player
	MegaMan *megaMan;

	//Vụ nổ khi quái chết
	Explosion* explosion;

	//Tan rã
	Collapse* collapse;

public:

	enum EnemyState
	{
		Aliving,
		Dying
	};
	EnemyState enemyState;

	Enemy();
	~Enemy();

	EnemyState GetEnemyState();
	void SetEnemyState(EnemyState state);

	virtual void New(D3DXVECTOR2 pos);
	virtual void ChangeAnimation(Keyboard* key);
	virtual void Update(float dt, Keyboard* key);
	virtual void Render(Viewport* viewport);
	virtual void OnCollision(Object *obj, D3DXVECTOR2 distance);
	virtual void OnCollision(Object *obj);
};

