#include"Helit.h"

Helit::Helit(MegaMan *megaMan, Sprite* sprite_Helit, Sprite* sprite_Item, Sprite* sprite_Explosion,
	SpriteSheet* spriteSheet_Helit, SpriteSheet* spriteSheet_Item, SpriteSheet* spriteSheet_Explosion, Sound* sound)
{
	tag = Tag::Enemys;
	this->megaMan = megaMan;
	sprite = sprite_Helit;
	animationEnemy = new Animation(spriteSheet_Helit);
	for (int i = 0; i < 4; i++)
	{
		bullets[i] = new Bullet(sprite_Helit, spriteSheet_Helit, sound);
	}
	numBullet = 0;

	item = new Item(megaMan, sprite_Item, spriteSheet_Item);

	explosion = new Explosion(sprite_Explosion, spriteSheet_Explosion);

	collapse = new Collapse(sprite_Helit, spriteSheet_Helit);
}

void Helit::New(D3DXVECTOR2 pos)
{
	Enemy::New(pos);
	action = Helit::Flying;
	isShoot = false;
	damage = 2;
	HP = 3;
}

void Helit::ChangeAnimation(Keyboard* key)
{
	SetBound(40, 30);
	animationEnemy->SetFrame(position, flipFlag, 5, 0, 4, true);
}

void Helit::Update(float dt, Keyboard* key)
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
			case Helit::Flying:
			{
				if (abs(megaMan->GetPosition().x - position.x) < 150 && !isShoot)
				{
					isShoot = true;
					action = Shooting;
				}
				break;
			}
			case Helit::Shooting:
			{
				if (!bullets[numBullet]->GetAllowDraw())
				{
					bullets[numBullet]->NewBullet(position + animationEnemy->GetGun(animationEnemy->GetIndex()), flipFlag, Bullet::BulletHelit);
					if (flipFlag) bullets[numBullet]->SetVelocity(2, 0);
					else bullets[numBullet]->SetVelocity(-2, 0);
					numBullet++;
					if (numBullet > 0)
					{
						numBullet = 0;
						action = Flying;
						isShoot = false;
					}
				}
				break;
			}
			}
		}

		if (position.y < megaMan->GetPosition().y + 17)
		{
			SetVelocity(0, 0.5f);
		}
		else
		{
			SetVelocity(0, -0.5f);
		}
	}

	//Update đạn
	for (int i = 0; i < 3; i++)
	{
		if (bullets[i]->GetAllowDraw())
		{
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
void Helit::OnCollision(Object *obj, D3DXVECTOR2 distance)
{
	item->OnCollision(obj);
}

void Helit::OnCollision(Object *obj)
{
	HP -= obj->GetDamage();

	if (HP <= 0)
	{
		HP = 0;

		enemyState = Dying;

		//nổ
		explosion->NewExplosion(position);

		//tan rã
		collapse->NewCollapse(position, Collapse::CollapseHelit);

		//item
		item->NewItem(position);
	}
}

void Helit::Render(Viewport* view)
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

