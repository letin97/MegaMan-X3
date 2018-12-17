#include "Bee.h"

Bee::Bee(Sprite* sprite_BlastHornet, SpriteSheet* spriteSheet_BlastHornet)
{
	sprite = sprite_BlastHornet;
	animation = new Animation(spriteSheet_BlastHornet);
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);
	tag = Object::Bullets;
	allowDraw = false;
	SetBound(20, 20);
	damage = 4;
}

void Bee::New(D3DXVECTOR2 pos, bool flipflag)
{
	allowDraw = true;
	position = pos;
	this->flipFlag = flipflag;
	SetBound(20, 20);
	isCollision = false;
	timeExist = 0;
	timeBurst = 0;
	state = Aliving;
}

void Bee::OnCollision(Object *obj, D3DXVECTOR2 distance)
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
			isCollision = true;
			bound = { 0, 0, 0, 0 };
		}
	}
}

void Bee::OnCollision(Object *obj)
{
	this->SetVelocity(0, 0);
	state = Dying;
}

void Bee::ChangeAnimation(Keyboard* key)
{
	switch (state)
	{
	case BeeState::Aliving:
	{
		animation->SetFrame(position, flipFlag, 1, 64, 66, true);
		break;
	}
	case BeeState::Dying:
	{
		animation->SetFrame(position, flipFlag, 1, 67, 72, false);
		break;
	}
	}
	
}

void Bee::Update(float dt, Keyboard* key)
{
	ChangeAnimation(key);
	Object::Update(dt, key);
	animation->Update(dt, key);

	if (isCollision)
	{
		timeExist += dt;
		if (timeExist > 5.0f)
		{
			state = Dying;		
		}
	}

	if (state == Dying)
	{
		timeBurst += dt;
		if (timeBurst > 0.3f)
		{
			bound = { 0, 0, 0, 0 };
			timeBurst = 0.0f;
			timeExist = 0.0f;
			allowDraw = false;
		}
	}
}

void Bee::Render(Viewport* viewport)
{
	if (!allowDraw) return;

	sprite->SetData(
		animation->GetRect(),
		animation->GetCenter(),
		animation->GetPosition(),
		animation->GetScale(),
		animation->GetTransform(),
		animation->GetAngle()
	);
	sprite->Render(viewport);
}