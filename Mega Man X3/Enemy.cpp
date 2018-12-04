#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(MegaMan *obj, Sprite* sprite_enemy, Sprite* sprite_Item, SpriteSheet* spriteSheet_Enemy, SpriteSheet* spriteSheet_Item)
{
	tag = Tag::Enemys;
	megaMan = obj;
	sprite = sprite_enemy;
	animationEnemy = new Animation(spriteSheet_Enemy);
	for (int i = 0; i < 4; i++)
	{
		bullets[i] = new Bullet(sprite_enemy, spriteSheet_Enemy);
	}
	numBullet = 0;

	item = new Item(obj, sprite_Item, spriteSheet_Item);

	explosion = new Explosion(sprite_enemy, spriteSheet_Enemy);
	
	collapse = new Collapse(sprite_enemy, spriteSheet_Enemy);
}

Enemy::~Enemy()
{
	delete animationEnemy;
	delete item;
}

Enemy::EnemyType Enemy::GetEnemyType()
{
	return enemyType;
}

void Enemy::SetEnemyType(EnemyType type)
{
	enemyType = type;
}

Enemy::EnemyState Enemy::GetEnemyState()
{
	return enemyState;
}

void Enemy::SetEnemyState(EnemyState state)
{
	enemyState = state;
}

void Enemy::NewEnemy(D3DXVECTOR2 pos, EnemyType type)
{
	allowDraw = true;
	enemyState = EnemyState::Moving;
	velocity = D3DXVECTOR2(0, 0);
	positionStart = pos;
	position = pos;

	enemyType = type;

	switch (enemyType)
	{
	case Enemy::HeadGunner:
	{
		damage = 2;
		HP = 3;
		break;
	}
	};;
}

Enemy::EnemyType Enemy::GetEnemyType(string name)
{
	if (name == "HeadGunner")
	{
		return HeadGunner;
	}
		
}

void Enemy::ChangeAnimation(Keyboard * key)
{
	switch (enemyType)
	{
	case Enemy::HeadGunner:
	{
		SetBound(38, 46);
		switch (enemyState)
		{
		case Enemy::Moving:
			animationEnemy->SetFrame(position, flipFlag, 0, 8, 8);
			break;
		case Enemy::Attacking:
			animationEnemy->SetFrame(position, flipFlag, 15, 9, 12, false);
			break;
		}
	}
	}
}

//Update
void Enemy::Update(float dt, Keyboard * key)
{
	ChangeAnimation(key);
	Object::Update(dt, key);
	animationEnemy->Update(dt, key);

	if (enemyState != EnemyState::Dying)
	{
		if (fabs(megaMan->GetPosition().x - position.x) < 150 || fabs(megaMan->GetPosition().y - position.y) < 150)
			isSeePlayer = true;
		else
			isSeePlayer = false;

		if (enemyState == EnemyState::Moving && isSeePlayer)
		{
			timeDelayShoot += dt;
			if (timeDelayShoot > 1.5f)
			{
				enemyState = EnemyState::Attacking;
				timeDelayShoot = 0;
			}
		}

		if (enemyState == EnemyState::Attacking)
		{
			timeDelayShoot += dt;
			if (timeDelayShoot > 0.5f)
			{
				if (!bullets[numBullet]->GetAllowDraw())
				{
					bullets[numBullet]->NewBullet(position + animationEnemy->GetGun(animationEnemy->GetIndex()), false, Bullet::Rocket);
					numBullet++;
					if (numBullet > 1)
						numBullet = 0;
				}
				timeDelayShoot = 0;
				enemyState = EnemyState::Moving;
			}
		}	
	}
	else if (enemyState == Dying)
	{
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
	
	//Update đạn
	for (int i = 0; i < 2; i++)
	{
		if (bullets[i]->GetAllowDraw())
		{
			if (megaMan->GetPosition().y > position.y)
				bullets[i]->SetVelocityY(0.1f);
			else
				bullets[i]->SetVelocityY(-0.1f);
			bullets[i]->Update(dt, key);

			if (Collision::isCollision(bullets[i]->GetBound(), megaMan->GetBound()))
			{
				int side;
				if (position.x > megaMan->GetPosition().x)
					side = 1;
				else
					side = -1;
				megaMan->GetMegaManState()->BleedState(side, damage);
				bullets[i]->OnCollision();
			}
		}		
	}
}

//Vẽ
void Enemy::Render(Viewport * view)
{
	if (view->isContains(bound))
	{
		if (allowDraw)
		{
			sprite->SetData(
				animationEnemy->GetRect(),
				animationEnemy->GetCenter(),
				animationEnemy->GetPosition(),
				animationEnemy->GetScale(),
				animationEnemy->GetTransform(),
				animationEnemy->GetAngle()
			);
			sprite->Render(view);
		}

		for (int i = 0; i < 2; i++)
			if (bullets[i]->GetAllowDraw())
				bullets[i]->Render(view);

		if (enemyState == Dying)
		{
			explosion->Render(view);
			collapse->Render(view);
			item->Render(view);
		}
	}
	else
	{
		if (!Collision::isCollision(positionStart.x, positionStart.y, view->GetBound()) && !item->GetAppear())
		{
			NewEnemy(positionStart, enemyType);
		}
	}
}

//Va chạm tường
void Enemy::OnCollision(Object *obj, D3DXVECTOR2 distance)
{
	RECT board = Collision::GetBoard(bound, distance);
	
	if (Collision::isCollision(board, obj->GetBound()))
	{
		//Lấy cạnh va chạm
		D3DXVECTOR2 sideCollision;

		//Lấy thời gian va chạm
		float time = Collision::CollisionAABB(bound, obj->GetBound(), distance, sideCollision);

		//bé hơn 1 thì có va chạm
		if (time < 1.0f)
		{
			if (sideCollision.x != 0)
				position.x += distance.x * time;
			else if (sideCollision.y != 0)
				position.y += distance.y * time;
		}
	}

	item->OnCollision(obj);

}

//Va chạm đạn Megaman
void Enemy::OnCollision(Object *obj)
{
	HP -= obj->GetDamage();

	if (HP <= 0)
	{
		HP = 0;
		enemyState = Dying;

		//nổ
		explosion->NewExplosion(position);

		//tan rã
		collapse->NewCollapse(position, enemyType);

		//item
		item->NewItem(position);
	}
}