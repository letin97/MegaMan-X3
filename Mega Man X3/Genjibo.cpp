#include"Genjibo.h"

Genjibo::Genjibo(Sprite* sprite_boss, SpriteSheet* spriteSheet_boss, D3DXVECTOR2 pos)
{
	positionStart = pos;
	transform = D3DXVECTOR2(0, 0);
	this->sprite = sprite_boss;
	this->animationBoss = new Animation(spriteSheet_boss);
	tag = Tag::Enemys;
	New();
}

void Genjibo::New()
{
	position = positionStart;
	SetBound(50, 50);
	
	allowDraw = true;
	flipFlag = false;
	state = Attack1;
	delay = 200;
	SetVelocity(-2, 0);
	HP = 20;
	damage = 4;
	stage = { 2304, 1024, 2560, 800 };
}

void Genjibo::ChangeAnimation(Keyboard* key)
{
	SetBound(50, 50);
	switch (state)
	{
	case Genjibo::Appearing:
		break;
	case Genjibo::Attack1:
		animationBoss->SetFrame(position, flipFlag, 0.5, 58, 67, true);
		break;
	case Genjibo::Trans:
		animationBoss->SetFrame(position, flipFlag, 2, 58, 67, true);
		break;
	case Genjibo::Attack2:
		animationBoss->SetFrame(position, flipFlag, 0.3, 58, 67, true);
		break;
	case Genjibo::Attack3:
		animationBoss->SetFrame(position, flipFlag, 0.2, 68, 84, true);
		break;
	case Genjibo::Dying:
		break;
	default:
		break;
	}
	
}
void Genjibo::Update(float dt, Keyboard* key)
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
		case Genjibo::Attack1:
		{
			if (velocity.y != 0)
				AddVelocity(0, -0.05f);

			if (HP < 15)
			{
				state = Trans;
			}
			break;
		}
		case Genjibo::Trans:
		{
			if (velocity.x == 0 && velocity.y == 0)
			{
				if (delay <= 0)
					delay = 200;
				delay--;

				if (delay <= 0)
				{
					SetVelocity(-2, 0);
					state = Attack2;
				}
			}
			break;
		}
		case Genjibo::Attack2:
		{
			if (velocity.x == 0 && velocity.y == 0)
			{
				if (delay <= 0)
					delay = 200;
				delay--;

				if (delay <= 0)
				{
					SetVelocity(-2, 2);
					state = Attack3;
				}
			}
			break;
		}
		case Genjibo::Attack3:
		{
			if (velocity.y != 0)
				AddVelocity(0, -0.05f);
			break;
		}
		}
	}

}
void Genjibo::OnCollision(Object *obj, D3DXVECTOR2 distance)
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

			if (sideCollision.x == -1)	//trái
			{
				if (state == Attack1 || state == Trans || state == Attack3)
				{
					velocity.x = 2;		
				}
				else if (state == Attack2)
				{
					velocity.x = 0;
					velocity.y = 2;
				}
			}
			else if (sideCollision.x == 1)	//phải
			{
				if (state == Attack1 || state == Attack3)
				{
					velocity.x = -2;
				}
				else if (state == Trans)
				{
					velocity.x = 0;
					velocity.y = -2;
				}
				else
				{
					velocity.x = 0;
					velocity.y = -2;
				}		
			}
			else if (sideCollision.y == 1)	//dưới
			{
				if (state == Attack1)
				{
					velocity.y = 0;
				}
				else if (state == Trans)
				{
					velocity.y = 0;
				}
				else if (state == Attack2)
				{
					velocity.y = 0;
				}
				else if (state == Attack3)
				{
					velocity.y = 2;
				}

			}
			else if (sideCollision.y == -1)	//trên
			{
				velocity.x = 2;
				velocity.y = 0;	
			}
			
		}
	}
}
void Genjibo::OnCollision(Object *obj)
{
	if (obj->tag == Object::Bullets)
	{
		if (state == Attack1)
		{
			if (velocity.y == 0)
				velocity.y = 2;
		}

		HP -= obj->GetDamage();

		if (HP <= 0)
		{
			HP = 0;
			state = Dying;
		}
	}	
}
void Genjibo::OnCollision()
{

}
void Genjibo::Render(Viewport* viewport)
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
}

