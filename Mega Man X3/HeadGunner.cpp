#include"HeadGunner.h"

HeadGunner::HeadGunner(MegaMan *megaMan, Sprite* sprite_HeadGunner, Sprite* sprite_Item, Sprite* sprite_Explosion,
	SpriteSheet* spriteSheet_HeadGunner, SpriteSheet* spriteSheet_Item, SpriteSheet* spriteSheet_Explosion, Sound* sound)
{
	tag = Tag::Enemys;
	this->megaMan = megaMan;
	sprite = sprite_HeadGunner;
	animationEnemy = new Animation(spriteSheet_HeadGunner);
	for (int i = 0; i < 4; i++)
	{
		bullets[i] = new Bullet(sprite_HeadGunner, spriteSheet_HeadGunner,sound);
	}
	numBullet = 0;

	item = new Item(megaMan, sprite_Item, spriteSheet_Item);

	explosion = new Explosion(sprite_Explosion, spriteSheet_Explosion);
	
	collapse = new Collapse(sprite_HeadGunner, spriteSheet_HeadGunner);
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
		animationEnemy->SetFrame(position, flipFlag, 0, 0, 0, false);
		break;
	case HeadGunner::Shooting:
		animationEnemy->SetFrame(position, flipFlag, 15, 1, 4, true);
		break;
	}
}

void HeadGunner::Update(float dt, Keyboard* key)
{
	Enemy::Update(dt, key);

	if (enemyState != Dying)
	{
		if (delay <= 0)
			delay = 20;
		delay--;

		if (delay <= 0)
		{
			switch (action)
			{
			case HeadGunner::Standing:
			{
				if (abs(megaMan->GetPosition().x - position.x) < 200 && !isShoot)
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
					bullets[numBullet]->NewBullet(position + animationEnemy->GetGun(animationEnemy->GetIndex()), flipFlag, Bullet::BulletHeadGunner);
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

