#include"Byte.h"

Byte::Byte(Sprite* sprite_Byte, Sprite* sprite_Smoke, Sprite* sprite_Explosion,
	SpriteSheet* spriteSheet_Byte, SpriteSheet* spriteSheet_Smoke, SpriteSheet* spriteSheet_Explosion, Sound* sound, D3DXVECTOR2 pos)
{
	positionStart = pos;
	transform = D3DXVECTOR2(0, 0);
	this->sprite = sprite_Byte;
	this->animationBoss = new Animation(spriteSheet_Byte);
	tag = Tag::Enemys;
	position = positionStart;
	SetBound(60, 84);
	allowDraw = true;
	flipFlag = false;
	state = Standing;
	delay = 200;
	HP = 24;
	HPMax = 24;
	damage = 4;
	bullet = new Bullet(sprite_Byte, spriteSheet_Byte, sound);
	for (int i = 0; i < 6; i++)
	{
		smokes[i] = new Smoke(sprite_Smoke, spriteSheet_Smoke);
	}
	numSmoke = 0;
	explosion = new Explosion(sprite_Explosion, spriteSheet_Explosion);
	stage = { 5632, 1024, 5888, 800 };
}

void Byte::ChangeAnimation(Keyboard* key)
{
	SetBound(60, 84);
	switch (state)
	{
	case Byte::Standing:
		animationBoss->SetFrame(position, flipFlag, 10, 0, 1, true);
		break;
	case Byte::Shooting:
		animationBoss->SetFrame(position, flipFlag, 5, 2, 5, false);
		break;
	case Byte::Gliding:
		animationBoss->SetFrame(position, flipFlag, 10, 6, 8, false);
		break;
	case Byte::Dying:
		break;
	default:
		break;
	}
}
void Byte::Update(float dt, Keyboard* key)
{
	if (!allowDraw)
		return;

	ChangeAnimation(key);
	Object::Update(dt, key);
	animationBoss->Update(dt, key);

	if (state == Dying)
	{
		SetVelocity(0, 0);
		delay--;
		if (delay < 0)
			stage = { 0, 0, 0, 0 };
	}
	else
	{
		switch (state)
		{
		case Byte::Standing:
		{
			if (delay <= 0)
				delay = 150;
			delay--;
			if (delay <= 0)
			{
				if (!bullet->GetAllowDraw())
				{
					state = Shooting;
				}
				else
				{
					if (flipFlag)
						velocity.x = 2;
					else
						velocity.x = -2;
					state = Gliding;
				}
			}
			break;
		}
		case Byte::Shooting:
		{
			if (delay <= 0)
				delay = 20;
			delay--;
			if (delay <= 0)
			{
				if (!bullet->GetAllowDraw())
				{
					bullet->NewBullet(position + animationBoss->GetGun(animationBoss->GetIndex()), false, Bullet::BulletByte);
					if (flipFlag) bullet->SetVelocity(2, 0);
					else bullet->SetVelocity(-2, 0);
					state = Standing;
				}
			}
			break;
		}
		case Byte::Gliding:
		{
			if (velocity.x == 0)
			{
				delay--;
				if (delay <= 0)
				{
					flipFlag = !flipFlag;
					state = Standing;
				}			
			}
			else
			{
				if (delay <= 0)
					delay = 5;
				delay--;
				if (delay <= 0)
				{
					smokes[numSmoke]->NewSmoke(position + animationBoss->GetSmoke(animationBoss->GetIndex()), flipFlag);
					numSmoke++;
					if (numSmoke > 5)
						numSmoke = 0;
				}
			}
			break;
		}
		}
	}

	if (bullet->GetAllowDraw())
		bullet->Update(dt, key);

	for (int i = 0; i < 6; i++)
	{
		smokes[i]->Update(dt, key);
	}

	explosion->Update(dt, key);
}

void Byte::OnCollision(Object *obj, D3DXVECTOR2 distance)
{
	RECT board = this->GetBoard(distance);

	if (Collision::isCollision(board, obj->GetBound()))
	{
		//Lấy cạnh va chạm
		D3DXVECTOR2 sideCollision;

		//lấy thời gian va chạm
		float time = Collision::CollisionAABB(GetBound(), obj->GetBound(), distance, sideCollision);

		//bé hơn 1 thì có va chạm
		if (time < 1.0f)
		{
			if (sideCollision.x != 0)
				position.x += distance.x * time;
			else if (sideCollision.y != 0)
				position.y += distance.y * time;

			if (sideCollision.x != 0)
			{
				velocity.x = 0;
				explosion->NewExplosion(bullet->GetPosition());
				bullet->SetAllowDraw(false);
				delay = 100;
			}
		}
	}
}

void Byte::OnCollision(Object *obj)
{
	if (obj->tag == Object::Bullets)
	{
		HP -= obj->GetDamage();

		if (HP <= 0)
		{
			HP = 0;
			state = Dying;
		}
	}
}

void Byte::OnCollision()
{

}

void Byte::Render(Viewport* viewport)
{
	if (!allowDraw)
		return;

	this->sprite->SetData(
		animationBoss->GetRect(),
		animationBoss->GetCenter(),
		animationBoss->GetPosition(),
		animationBoss->GetScale(),
		animationBoss->GetTransform(),
		animationBoss->GetAngle()
	);
	this->sprite->Render(viewport);

	if (bullet->GetAllowDraw())
		bullet->Render(viewport);

	for (int i = 0; i < 6; i++)
	{
		smokes[i]->Render(viewport);
	}

	explosion->Render(viewport);
}

