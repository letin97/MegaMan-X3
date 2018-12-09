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
	delay = 40;
	SetVelocity(-1, 0);
	HP = 20;
	damage = 4;
}

void Genjibo::ChangeAnimation(Keyboard* key)
{
	SetBound(50, 50);
	switch (state)
	{
	case Attack1:
		animationBoss->SetFrame(position, flipFlag, 1, 58, 67, true);
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
		allowDraw = false;
	}
	else
	{
		switch (state)
		{
		case Genjibo::Attack1:
		{
			if (velocity.y != 0)
				AddVelocity(0, -0.015f);

			if (HP < 10)
			{
				SetVelocity(-1, -1);
				state = Attack2;
			}
		}
		case Genjibo::Attack2:
		{
			
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
				position.x += distance.x*time;
			else if (sideCollision.y != 0)
				position.y += distance.y*time;

			if (sideCollision.x == -1)	//trái
			{
				if (state == Attack1)
				{
					velocity.x = 1;		
				}
				else
				{
					velocity.x = 0;
					velocity.y = 1;
				}
			}
			else if (sideCollision.x == 1)	//phải
			{
				if (state == Attack1)
				{
					velocity.x = -1;
				}
				else
				{
					velocity.x = 0;
					velocity.y = -1;
				}		
			}
			else if (sideCollision.y == 1)	//dưới
			{
				if (state == Attack1)
				{
					velocity.x = 1;
					velocity.y = 0;
				}
				else
				{
					velocity.x = -1;
					velocity.y = 0;
				}		
			}
			else if (sideCollision.y == -1)	//trên
			{
				velocity.x = 1;
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
			velocity.y = 1;
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

