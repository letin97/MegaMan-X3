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
	Sprite* sprite_Bullet;

	//Time
	float timeDelayShoot = 0;
	bool isSeePlayer;
	
	//Vật phẩm rơi khi quái chết
	Item* item;

	//Player
	MegaMan *megaMan;

	//Vụ nổ khi quái chết
	Explosion* explosion;

	//Tan rã
	Collapse* collapse;

public:
	enum EnemyType
	{
		HeadGunner
	};
	EnemyType enemyType;

	enum EnemyState
	{
		Moving,
		Attacking,
		Dying
	};
	EnemyState enemyState;

	Enemy();
	Enemy(MegaMan *megaMan, Sprite* sprite_enemy, Sprite* sprite_Item, SpriteSheet* spriteSheet_Enemy, SpriteSheet* spriteSheet_Item);
	~Enemy();

	EnemyType GetEnemyType();
	EnemyType GetEnemyType(string name);
	void SetEnemyType(EnemyType type);

	EnemyState GetEnemyState();
	void SetEnemyState(EnemyState state);

	void NewEnemy(D3DXVECTOR2 pos, EnemyType enemyType);
	void ChangeAnimation(Keyboard* key);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
};

