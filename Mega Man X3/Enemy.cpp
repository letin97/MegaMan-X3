#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	delete animationEnemy;
	delete item;
}


Enemy::EnemyState Enemy::GetEnemyState()
{
	return enemyState;
}

void Enemy::SetEnemyState(EnemyState state)
{
	enemyState = state;
}

void Enemy::New(D3DXVECTOR2 pos)
{
	allowDraw = true;
	enemyState = EnemyState::Aliving;
	velocity = D3DXVECTOR2(0, 0);
	positionStart = pos;
	position = pos;
}

void Enemy::ChangeAnimation(Keyboard * key)
{

}

//Update
void Enemy::Update(float dt, Keyboard * key)
{
	ChangeAnimation(key);
	Object::Update(dt, key);
	animationEnemy->Update(dt, key);

	if (enemyState == Dying)
	{
		SetVelocity(0, 0);

		allowDraw = false;

		if (item->GetAppear())
			item->OnCollision(megaMan);

		//nổ
		explosion->Update(dt, key);

		//tan rã
		collapse->Update(dt, key);

		//item
		item->Update(dt, key);
	}
	
}

//Vẽ
void Enemy::Render(Viewport * view)
{
	
}

//Va chạm tường
void Enemy::OnCollision(Object *obj, D3DXVECTOR2 distance)
{

}

//Va chạm đạn Megaman
void Enemy::OnCollision(Object *obj)
{
	
}