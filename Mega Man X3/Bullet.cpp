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
		bulletType = BulletHeadGunner;
		damage = 4;
		break;
	}
	case 4:
	{
		bulletType = BulletNotorBanger;
		damage = 4;
		break;
	}
	case 5:
	{
		bulletType = BulletHelit;
		damage = 4;
		break;
	}
	case 6:
	{
		bulletType = BulletByte;
		damage = 0;
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
	case Bullet::BulletHeadGunner:
	{
		SetBound(8, 4);
		animationBullet->SetFrame(position, flipFlag, 10, 5, 6, true);
		break;
	}
	case Bullet::BulletNotorBanger:
	{
		SetBound(2, 2);
		animationBullet->SetFrame(position, flipFlag, 0, 19, 19, false);
		break;
	}
	case Bullet::BulletHelit:
	{
		SetBound(8, 4);
		animationBullet->SetFrame(position, flipFlag, 10, 5, 6, true);
		break;
	}
	case Bullet::BulletByte:
	{
		switch (bulletState)
		{
		case Bullet::Firing:
			SetBound(7, 7);
			animationBullet->SetFrame(position, flipFlag, 10, 9, 15, true);
			break;
		case Bullet::Cling:
			SetBound(7, 7);
			animationBullet->SetFrame(position, flipFlag, 10, 16, 17, false);
			break;
		}
		
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

void Bullet::OnCollision(Object *obj, D3DXVECTOR2 distance)
{
	RECT board = this->GetBoard(distance);

	//Nếu other trong vùng di chuyển
	if (Collision::isCollision(board, obj->GetBound()))
	{
		//Lấy cạnh va chạm
		D3DXVECTOR2 sideCollision;

		//lấy thời gian va chạm
		float time = Collision::CollisionAABB(GetBound(), obj->GetBound(), distance, sideCollision);

		//bé hơn 1 thì có va chạm
		if (time < 1.0f)
		{
			this->SetVelocity(0, 0);
			bulletState = BulletState::Cling;
		}
	}
}

void Bullet::OnCollision()
{
	this->SetVelocity(0, 0);
	bulletState = BulletState::Bursting;
}