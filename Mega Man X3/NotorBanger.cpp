#include"NotorBanger.h"

NotorBanger::NotorBanger(MegaMan *megaMan, Sprite* sprite_NotorBanger, Sprite* sprite_Item, Sprite* sprite_Explosion,
	SpriteSheet* spriteSheet_NotorBanger, SpriteSheet* spriteSheet_Item, SpriteSheet* spriteSheet_Explosion)
{
	tag = Tag::Enemys;
	this->megaMan = megaMan;
	sprite = sprite_NotorBanger;
	animationEnemy = new Animation(spriteSheet_NotorBanger);
	for (int i = 0; i < 4; i++)
	{
		bullets[i] = new Bullet(sprite_NotorBanger, spriteSheet_NotorBanger);
	}
	numBullet = 0;
	item = new Item(megaMan, sprite_Item, spriteSheet_Item);
	explosion = new Explosion(sprite_Explosion, spriteSheet_Explosion);
	collapse = new Collapse(sprite_NotorBanger, spriteSheet_NotorBanger);
}

void NotorBanger::New(D3DXVECTOR2 pos)
{
	Enemy::New(pos);
	action = NotorBanger::Standing;
	isJump = true;
	isShoot = false;
	damage = 2;
	HP = 3;
}

void NotorBanger::ChangeAnimation(Keyboard* key)
{
	SetBound(30, 30);
	switch (action)
	{
	case NotorBanger::Standing:
		animationEnemy->SetFrame(position, flipFlag, 0, 0, 0, false);
		break;
	case NotorBanger::TargetSkew:
		animationEnemy->SetFrame(position, flipFlag, 5, 0, 2, false);
		break;
	case NotorBanger::TargetVertical:
		animationEnemy->SetFrame(position, flipFlag, 5, 0, 4, false);
		break;
	case NotorBanger::BackShootingSkew:
		animationEnemy->SetFrame(position, flipFlag, 10, 7, 9, false);
		break;
	case NotorBanger::BackShootingVertical:
		animationEnemy->SetFrame(position, flipFlag, 10, 5, 9, false);
		break;
	case NotorBanger::ShootingVertical:
		animationEnemy->SetFrame(position, flipFlag, 15, 10, 11, true);
		break;
	case NotorBanger::ShootingSkew:
		animationEnemy->SetFrame(position, flipFlag, 15, 12, 13, true);
		break;
	case NotorBanger::Moving:
		animationEnemy->SetFrame(position, flipFlag, 10, 14, 18, false);
		break;
	}
}

void NotorBanger::Update(float dt, Keyboard* key)
{
	Enemy::Update(dt, key);

	if (enemyState != Dying)
	{
		if (!isJump)
		{
			if (delay <= 0)
				delay = 40;
			delay--;

			if (delay <= 0)
			{
				switch (action)
				{
				case NotorBanger::Standing:
				{
					if (abs(megaMan->GetPosition().x - position.x) < 150)
					{
						action = Moving;
						if (abs(megaMan->GetPosition().x - position.x) < 100 && !isShoot)
						{
							action = TargetSkew;
							if (abs(megaMan->GetPosition().x - position.x) < 50)
							{
								action = TargetVertical;
							}
						}
					}

					if (position.x < megaMan->GetPosition().x)
						flipFlag = true;
					else
						flipFlag = false;
					break;
				}
				case NotorBanger::TargetSkew:
				{
					isShoot = true;
					action = ShootingSkew;
					break;
				}
				case NotorBanger::TargetVertical:
				{
					isShoot = true;
					action = ShootingVertical;
					break;
				}
				case NotorBanger::ShootingSkew:
				{
					if (!bullets[numBullet]->GetAllowDraw())
					{
						bullets[numBullet]->NewBullet(position + animationEnemy->GetGun(animationEnemy->GetIndex()), flipFlag, Bullet::BulletNotorBanger);
						if (flipFlag) bullets[numBullet]->SetVelocity(2, 2);
						else bullets[numBullet]->SetVelocity(-2, 2);
						numBullet++;
						if (numBullet > 2)
						{
							numBullet = 0;
							action = BackShootingSkew;
						}
					}
					break;
				}
				case NotorBanger::ShootingVertical:
				{
					if (!bullets[numBullet]->GetAllowDraw())
					{
						bullets[numBullet]->NewBullet(position + animationEnemy->GetGun(animationEnemy->GetIndex()), flipFlag, Bullet::BulletNotorBanger);
						if (flipFlag) bullets[numBullet]->SetVelocity(1, 3);
						else bullets[numBullet]->SetVelocity(-1, 3);
						numBullet++;
						if (numBullet > 2)
						{
							numBullet = 0;
							action = BackShootingVertical;
						}
					}
					break;
				}
				case NotorBanger::BackShootingSkew:
				case NotorBanger::BackShootingVertical:
				{
					action = Standing;
					isShoot = false;
					break;
				}
				case NotorBanger::Moving:
				{
					if (flipFlag)
						SetVelocity(1.5f, 1.5f);
					else
						SetVelocity(-1.5f, 1.5f);
					isJump = true;
					break;
				}
				default:
					break;
				}
			}
		}
		else
			AddVelocity(0, -0.1);
	}

	//Update đạn
	for (int i = 0; i < 3; i++)
	{
		if (bullets[i]->GetAllowDraw())
		{
			bullets[i]->Update(dt, key);
			bullets[i]->AddVelocity(0, -0.3);
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
void NotorBanger::OnCollision(Object *obj, D3DXVECTOR2 distance)
{
	RECT board = this->GetBoard(distance);

	//Nếu other trong vùng di chuyển
	if (Collision::isCollision(board, obj->GetBound()))
	{
		if (!Collision::isNested(GetBound(), obj->GetBound()))
		{
			//Lấy cạnh va chạm
			D3DXVECTOR2 sideCollision;

			//Lấy thời gian va chạm
			float time = Collision::CollisionAABB(GetBound(), obj->GetBound(), distance, sideCollision);

			//Bé hơn 1 thì có va chạm
			if (time < 1.0f)
			{
				if (sideCollision.x != 0.0f)
				{
					position.x += distance.x * time;
					velocity.x = 0;
				}
				else if (sideCollision.y != 0)
				{
					position.y += distance.y * time;
				}

				if (sideCollision.y == 1) // va cham duoi
				{
					SetVelocity(0, 0);
					action = Standing;
					isJump = false;
				}
			}
		}	
	}

	item->OnCollision(obj);
}

void NotorBanger::OnCollision(Object *obj)
{
	HP -= obj->GetDamage();

	if (HP <= 0)
	{
		HP = 0;
		enemyState = Dying;
		//nổ
		explosion->NewExplosion(position);
		//tan rã
		collapse->NewCollapse(position, Collapse::CollapseNotorBanger);
		//item
		item->NewItem(position);
	}
}

void NotorBanger::Render(Viewport* view)
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

