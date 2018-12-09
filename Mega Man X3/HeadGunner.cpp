﻿#include"HeadGunner.h"

HeadGunner::HeadGunner(MegaMan *megaMan, Sprite* sprite_enemy, Sprite* sprite_Item, SpriteSheet* spriteSheet_Enemy, SpriteSheet* spriteSheet_Item)
{
	tag = Tag::Enemys;
	this->megaMan = megaMan;
	sprite = sprite_enemy;
	animationEnemy = new Animation(spriteSheet_Enemy);
	for (int i = 0; i < 4; i++)
	{
		bullets[i] = new Bullet(sprite_enemy, spriteSheet_Enemy);
	}
	numBullet = 0;

	item = new Item(megaMan, sprite_Item, spriteSheet_Item);

	explosion = new Explosion(sprite_enemy, spriteSheet_Enemy);
	
	collapse = new Collapse(sprite_enemy, spriteSheet_Enemy);
}

void HeadGunner::New(D3DXVECTOR2 pos)
{
	Enemy::New(pos);
	action = HeadGunner::Standing;
	isShoot = false;
	damage = 2;
	HP = 3;
}

void HeadGunner::ChangeAnimation(Keyboard* key)
{
	SetBound(30, 40);
	switch (action)
	{
	case HeadGunner::Standing:
		animationEnemy->SetFrame(position, flipFlag, 0, 8, 8, false);
		break;
	case HeadGunner::Shooting:
		animationEnemy->SetFrame(position, flipFlag, 15, 9, 12, true);
		break;
	}
}

void HeadGunner::Update(float dt, Keyboard* key)
{
	Enemy::Update(dt, key);

	if (enemyState != Dying)
	{
		if (delay <= 0)
			delay = 40;
		delay--;

		if (delay <= 0)
		{
			switch (action)
			{
			case HeadGunner::Standing:
			{
				if (abs(megaMan->GetPosition().x - position.x) < 150 && !isShoot)
				{
					isShoot = true;
					action = Shooting;
				}
				break;
			}
			case HeadGunner::Shooting:
			{
				if (!bullets[numBullet]->GetAllowDraw())
				{
					bullets[numBullet]->NewBullet(position + animationEnemy->GetGun(animationEnemy->GetIndex()), false, Bullet::BulletHeadGunner);
					if (flipFlag) bullets[numBullet]->SetVelocity(2, 0);
					else bullets[numBullet]->SetVelocity(-2, 0);
					numBullet++;
					if (numBullet > 0)
					{
						numBullet = 0;
						action = Standing;
						isShoot = false;
					}	
				}
				break;
			}
			}
		}
	}

	//Update đạn
	for (int i = 0; i < 3; i++)
	{
		if (bullets[i]->GetAllowDraw())
		{
			bullets[i]->Update(dt, key);

			if (megaMan->GetPosition().y > position.y)
				bullets[i]->SetVelocityY(0.1f);
			else
				bullets[i]->SetVelocityY(-0.1f);

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
void HeadGunner::OnCollision(Object *obj, D3DXVECTOR2 distance)
{
	item->OnCollision(obj);
}

void HeadGunner::OnCollision(Object *obj)
{
	HP -= obj->GetDamage();

	if (HP <= 0)
	{
		HP = 0;

		enemyState = Dying;

		//nổ
		explosion->NewExplosion(position);

		//tan rã
		collapse->NewCollapse(position, Collapse::CollapseHeadGunner);

		//item
		item->NewItem(position);
	}
}

void HeadGunner::Render(Viewport* view)
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

		for (int i = 0; i < 3; i++)
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
			New(positionStart);
		}
	}
}
