#include "Bullet.h"


Bullet::Bullet()
{
}

Bullet::Bullet(Sprite* sprite_bullet, SpriteSheet* sprite_sheet)
{
	tag = Object::Bullets;

	sprite = sprite_bullet;
	animationBullet = new Animation(sprite_sheet);
	allowDraw = false;

	bulletType = BulletType::BulletLv1;
	bulletState = BulletState::Firing;

	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);
}

Bullet::~Bullet()
{
	delete animationBullet;
}

//Tạo thông số cho viên đạn khi bắn
void Bullet::NewBullet(D3DXVECTOR2 position, bool flipflag, int energyLevel)
{
	switch (energyLevel)
	{
	case 0:
	{
		bulletType = BulletLv1;
		damage = 1;
		break;
	}
	case 1:
	{
		bulletType = BulletLv2;
		damage = 2;
		break;
	}
	case 2:
	{
		bulletType = BulletLv3;
		damage = 3;
		break;
	}
	case 3:
	{
		bulletType = Rocket;
		damage = 4;
		break;
	}
	default:
		break;
	}

	bulletState = BulletState::Firing;
	timeBurst = 0;
	this->allowDraw = true;
	this->position = position;
	this->flipFlag = flipflag;
	
	if (flipFlag)
	{
		if (bulletType == Rocket) SetVelocity(2, 0);
		else SetVelocity(-BulletSpeed, 0);
	}
	else
	{
		if (bulletType == Rocket) SetVelocity(-2, 0);
		else SetVelocity(BulletSpeed, 0);
	}
}

Bullet::BulletType Bullet::GetBulletType()
{
	return bulletType;
}

void Bullet::SetBulletType(Bullet::BulletType bulletType)
{
	this->bulletType = bulletType;
}

Bullet::BulletState Bullet::GetBulletState()
{
	return bulletState;
}

void Bullet::SetBulletState(BulletState state)
{
	bulletState = state;
}

void Bullet::ChangeAnimation()
{
	switch (bulletType)
	{
	case Bullet::BulletLv1:
	{
		SetBound(4, 4);
		switch (bulletState)
		{
		case Bullet::Firing:
		{
			animationBullet->SetFrame(position, flipFlag, 0, 0, 0, true);
			break;
		}
		case Bullet::Bursting:
			animationBullet->SetFrame(position, flipFlag, 1, 1, 3, false);
			break;
		}
		break;
	}
	case Bullet::BulletLv2:
	{
		SetBound(8, 4);
		switch (bulletState)
		{
		case Bullet::Firing:
		{	
			animationBullet->SetFrame(position, flipFlag, 2, 6, 11, true);
			break;
		}
		case Bullet::Bursting:
			animationBullet->SetFrame(position, flipFlag, 1, 12, 13, false);
			break;
		}
		break;
	}
	case Bullet::BulletLv3:
	{
		SetBound(8, 8);
		switch (bulletState)
		{
		case Bullet::Firing:
		{
			animationBullet->SetFrame(position, flipFlag, 2, 16, 18, true);
			break;
		}
		case Bullet::Bursting:
			animationBullet->SetFrame(position, flipFlag, 1, 19, 20, false);
			break;
		}
		break;
	}
	case Bullet::Rocket:
	{
		SetBound(8, 4);
		animationBullet->SetFrame(position, flipFlag, 10, 17, 18, true);
		break;
	}
	}
}

void Bullet::Update(float dt, Keyboard* key)
{
	if (allowDraw)
	{
		ChangeAnimation();
		Object::Update(dt, key);
		animationBullet->Update(dt, key);

		if (bulletState == BulletState::Bursting)
		{
			timeBurst += dt;
			SetVelocity(0, 0);
			if (timeBurst > 0.1f)
			{
				bound = { 0, 0, 0, 0 };
				timeBurst = 0.0f;
				allowDraw = false;
			}
		}
	}
}

void Bullet::Render(Viewport* viewport)
{
	//Vẽ đạn
	if (allowDraw)
	{
		if (viewport->isContains(bound))
		{
			sprite->SetData(
				animationBullet->GetRect(),
				animationBullet->GetCenter(),
				animationBullet->GetPosition(),
				animationBullet->GetScale(),
				animationBullet->GetTransform(),
				animationBullet->GetAngle()
			);
			sprite->Render(viewport);
		}
		else
		{
			bound = { 0, 0, 0, 0 };
			allowDraw = false;
		}
	}
}
void Bullet::OnCollision()
{
	this->SetVelocity(0, 0);
	bulletState = BulletState::Bursting;
}