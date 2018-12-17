#include"BlastHornet.h"

BlastHornet::BlastHornet(MegaMan *megaMan, Sprite* sprite_BlastHornet,
	SpriteSheet* spriteSheet_BlastHornet, D3DXVECTOR2 pos)
{
	positionStart = pos;
	transform = D3DXVECTOR2(0, 0);
	this->sprite = sprite_BlastHornet;
	this->animationBoss = new Animation(spriteSheet_BlastHornet);
	tag = Tag::Enemys;
	this->megaMan = megaMan;
	position = positionStart;
	posStartSwoop = D3DXVECTOR2(0, 0);
	isLaunch = false;
	SetBound(60, 84);
	SetVelocity(0, 0);
	allowDraw = true;
	flipFlag = false;
	state = Flying;
	delay = 50;
	HP = 20;
	damage = 4;
	numRound = 0;

	numBee = 0;
	for (int i = 0; i < 5; i++)
		listBee[i] = new Bee(sprite_BlastHornet, spriteSheet_BlastHornet);

	parasitic = new Parasitic(sprite_BlastHornet, spriteSheet_BlastHornet);
}

void BlastHornet::ChangeAnimation(Keyboard* key)
{
	SetBound(50, 80);
	switch (state)
	{
	case BlastHornet::Flying:
	case BlastHornet::FlyingRound:
		animationBoss->SetFrame(position, flipFlag, 0.5, 0, 3, true);
		break;
	case BlastHornet::Pricking:
		animationBoss->SetFrame(position, flipFlag, 0.5, 7, 45, false);
		break;
	case BlastHornet::Swooping:
		animationBoss->SetFrame(position, flipFlag, 0.5, 4, 6, true);
		break;
	case BlastHornet::Launching:
		animationBoss->SetFrame(position, flipFlag, 0.5, 46, 63, false);
		break;
	case BlastHornet::Dying:
		break;
	default:
		break;
	}
}
void BlastHornet::Update(float dt, Keyboard* key)
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
		case BlastHornet::Flying:
		{
			if (position.x < megaMan->GetPosition().x)
				flipFlag = true;
			else
				flipFlag = false;

			if (posStartSwoop.x != 0)
			{
				if (position.x < posStartSwoop.x)
					velocity.x = 0.5;
				else
					velocity.x = -0.5;
			}

			AddVelocity(0, 0.05f);
			break;
		}
		case BlastHornet::FlyingRound:
		{
			if (position.x < megaMan->GetPosition().x)
				flipFlag = true;
			else
				flipFlag = false;

			if (velocity.y >= 1)
				isUp = false;
			else if (velocity.y <= -1)
				isUp = true;

			if (isUp)
				AddVelocity(0, 0.05f);
			else
				AddVelocity(0, -0.05f);

			if (isLeft)
				AddVelocity(-0.01f, 0);
			else
				AddVelocity(0.01f, 0);

			if (HP <= 10)
			{
				if (!parasitic->appear)
					parasitic->New(position);

				if (parasitic->isCling)
				{
					if (delay <= 0)
						delay = 100;
					delay--;

					if (delay <= 0)
					{
						if (!listBee[numBee]->GetAllowDraw())
						{
							listBee[numBee]->New(position, !flipFlag);
							numBee++;
							if (numBee > 2)
							{
								numBee = 0;
							}
						}
					}
				}
			}
			else
			{
				if (numRound == 4)
				{
					if (velocity.y <= -1)
					{
						numRound = 0;
						state = Flying;
					}		
				}
			}
			break;
		}
		case BlastHornet::Pricking:
		{
			if (delay <= 0)
				delay = 50;
			delay--;
			if (delay <= 0)
			{
				velocity.y = -1.5f;
				posStartSwoop = position;
				state = Swooping;
			}
			break;
		}
		case BlastHornet::Swooping:
		{
			if (position.x < megaMan->GetPosition().x)
				AddVelocity(0.05f, 0);
			else
				AddVelocity(-0.05f, 0);
			break;
		}
		case BlastHornet::Launching:
		{
			if (delay <= 0)
				delay = 20;
			delay--;

			if (delay <= 0)
			{
				for (int i = 0; i < 5; i++)
				{
					if (!listBee[i]->GetAllowDraw())
					{
						listBee[i]->New(position, !flipFlag);
						if (flipFlag)
							listBee[i]->SetVelocity(1, 0.5 - 0.4*i);
						else
							listBee[i]->SetVelocity(-1, 0.5 - 0.4*i);
					}
				}
				state = FlyingRound;
			}	
			break;
		}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (listBee[i]->GetAllowDraw())
		{
			listBee[i]->Update(dt, key);

			if (parasitic->isCling)
			{
				if (listBee[i]->GetPosition().x < megaMan->GetPosition().x)
				{
					listBee[i]->SetVelocityX(1.5f);
					listBee[i]->SetFlipFlag(false);
				}
				else
				{
					listBee[i]->SetVelocityX(-1.5f);
					listBee[i]->SetFlipFlag(true);
				}

				if (listBee[i]->GetPosition().y < megaMan->GetPosition().y)
					listBee[i]->SetVelocityY(1.0f);
				else
					listBee[i]->SetVelocityY(-1.0f);
			}
		}
	}

	if (parasitic->appear)
	{
		parasitic->Update(dt, key);

		if (parasitic->isCling)
		{
			parasitic->SetPosition(megaMan->GetPosition());
		}
		else
		{
			if (parasitic->GetPosition().x < megaMan->GetPosition().x)
				parasitic->SetVelocityX(1.0f);
			else
				parasitic->SetVelocityX(-1.0f);

			if (parasitic->GetPosition().y < megaMan->GetPosition().y)
				parasitic->SetVelocityY(1.0f);
			else
				parasitic->SetVelocityY(-1.0f);

			if (Collision::isCollision(parasitic->GetBound(), megaMan->GetBound()))
			{
				parasitic->isCling = true;
			}
		}
	}
}

void BlastHornet::OnCollision(Object *obj, D3DXVECTOR2 distance)
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
				numRound++;
				velocity.x = 0;
				isLeft = false;
			}

			if (sideCollision.x == 1)
			{
				numRound++;
				velocity.x = 0;
				isLeft = true;
			}

			if (sideCollision.y == -1) // trên
			{
				velocity.x = 0;
				velocity.y = 0;

				if (state == Flying)
				{
					if (isLaunch)
					{
						isLaunch = false;
						state = Launching;
					}
					else
					{
						isLaunch = true;
						state = Pricking;
					}
				}			
			}

			if (sideCollision.y == 1) // dưới
			{
				velocity.x = 0;
				state = Flying;
			}
		}
	}
}

void BlastHornet::OnCollision(Object *obj)
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

void BlastHornet::OnCollision()
{

}

void BlastHornet::Render(Viewport* viewport)
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

	for (int i = 0; i < 5; i++)
		listBee[i]->Render(viewport);

	if (parasitic->GetAllowDraw())
		parasitic->Render(viewport);
}

