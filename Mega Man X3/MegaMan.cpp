﻿#include "MegaMan.h"


MegaMan::MegaMan(Sprite* sprite_MegaMan, Sprite* sprite_Effect, Sprite* sprite_Weapons_And_Items,
	SpriteSheet* spriteSheet_MegaMan, SpriteSheet* spriteSheet_Effect, SpriteSheet* spriteSheet_Weapons_And_Items)
{
	tag = Object::Player;
	pathPNG = MegaManPNG;
	sprite = sprite_MegaMan;

	//Tạo Animation MegaMan
	animationMegaMan = new MegaManAnimation(spriteSheet_MegaMan);

	//Tạo Animation Effect
	lightEnergy = new LightEnergy(sprite_Effect, spriteSheet_Effect);
	spark = new Spark(sprite_Effect, spriteSheet_Effect);
	for (int i = 0; i < 6; i++)
	{
		smokes[i] = new Smoke(sprite_Effect, spriteSheet_Effect);
	}
	numSmoke = 0;

	//Tạo đạn
	for (int i = 0; i < 3; i++)
	{
		bullets[i] = new Bullet(sprite_Weapons_And_Items, spriteSheet_Weapons_And_Items);
	}
	numBullet = 0;

	//Tạo StateSamus lấy state
	stateMegaMan = new MegaManState(this);

	// 500, 1280
	// 2880 1280
	position = D3DXVECTOR2(16, 1280);
	velocity = D3DXVECTOR2(0, -1);
	allowDraw = true;
	SetBound(30, 34);

	HP = 20;
	HPMax = 20;
}

MegaMan::~MegaMan()
{
	
}

MegaManState* MegaMan::GetMegaManState()
{
	return stateMegaMan;
}


void MegaMan::ChangeAnimation(float dt, Keyboard* keyboard)
{
	stateMegaMan->CheckSide(keyboard);

	switch (stateMegaMan->GetState())
	{
	case MegaManState::Standing:
	{
		stateMegaMan->StandState(keyboard);
		if (!stateMegaMan->GetIsDelayShoot()) animationMegaMan->StandAnimation();
		else animationMegaMan->StandShootAnimation();
		break;
	}
	case MegaManState::Running:
	{
		stateMegaMan->RunState(keyboard);
		if(!stateMegaMan->GetIsDelayShoot()) animationMegaMan->RunAnimation();
		else animationMegaMan->RunShootAnimation();
		break;
	}
	case MegaManState::Jumping:
	{
		stateMegaMan->JumpState(keyboard);
		if (!stateMegaMan->GetIsDelayShoot()) animationMegaMan->JumpAnimation();
		else animationMegaMan->JumpShootAnimation();
		//SetBound(24, 46);
		break;
	}
	case MegaManState::Falling:
	{
		stateMegaMan->FallState(keyboard);
		if (!stateMegaMan->GetIsDelayShoot()) animationMegaMan->FallAnimation();
		else animationMegaMan->FallShootAnimation();
		break;
	}
	case MegaManState::Gliding:
	{
		stateMegaMan->GlideState(keyboard);
		if (!stateMegaMan->GetIsDelayShoot()) animationMegaMan->GlideAnimation();
		else animationMegaMan->GlideShootAnimation();
		break;
	}
	case MegaManState::Clamping:
	{
		stateMegaMan->ClampState(keyboard);
		if (!stateMegaMan->GetIsDelayShoot()) animationMegaMan->ClampAnimation();
		else animationMegaMan->ClampShootAnimation();
		break;
	}
	case MegaManState::Kicking:
	{
		stateMegaMan->KickState(keyboard);
		if (!stateMegaMan->GetIsDelayShoot()) animationMegaMan->KickAnimation();
		else animationMegaMan->KickShootAnimation();
		break;
	}
	case MegaManState::StandingShoot:
	{
		stateMegaMan->ShootState(keyboard);
		if (stateMegaMan->GetEnergyLevel() != 1) animationMegaMan->StandAnimation();
		else animationMegaMan->StandShootAnimation();
		break;
	}
	case MegaManState::RunningShoot:
	{
		stateMegaMan->ShootState(keyboard);
		if (stateMegaMan->GetEnergyLevel() != 1) animationMegaMan->RunAnimation();
		else animationMegaMan->RunShootAnimation();
		break;
	}
	case MegaManState::JumpingShoot:
	{
		stateMegaMan->ShootState(keyboard);
		if (stateMegaMan->GetEnergyLevel() != 1) animationMegaMan->JumpAnimation();
		else animationMegaMan->JumpShootAnimation();
		break;
	}
	case MegaManState::FallingShoot:
	{
		stateMegaMan->ShootState(keyboard);
		if (stateMegaMan->GetEnergyLevel() != 1) animationMegaMan->FallAnimation();
		else animationMegaMan->FallShootAnimation();
		break;
	}
	case MegaManState::GlidingShoot:
	{
		stateMegaMan->ShootState(keyboard);
		if (stateMegaMan->GetEnergyLevel() != 1) animationMegaMan->GlideAnimation();
		else animationMegaMan->GlideShootAnimation();
		break;
	}
	case MegaManState::ClampingShoot:
	{
		stateMegaMan->ShootState(keyboard);
		if (stateMegaMan->GetEnergyLevel() != 1) animationMegaMan->ClampAnimation();
		else animationMegaMan->ClampShootAnimation();
		break;
	}
	case MegaManState::KickingShoot:
	{
		stateMegaMan->ShootState(keyboard);
		if (stateMegaMan->GetEnergyLevel() != 1) animationMegaMan->KickAnimation();
		else animationMegaMan->KickShootAnimation();
		break;
	}
	}

	//Bị thương
	if (stateMegaMan->IsBleeding())
		animationMegaMan->BleedAnimation();

	stateMegaMan->Update(dt, keyboard);

	//SetBound(animationMegaMan->GetWidthFrame(), animationMegaMan->GetHeightFrame());
}

//Kiểm tra va chạm 
void MegaMan::OnCollision(Object *other, D3DXVECTOR2 distance, D3DXVECTOR2 disMan)
{
	RECT board = this->GetBoard(distance);

	//Nếu other trong vùng di chuyển
	if (Collision::isCollision(board, other->GetBound()))
	{
		if (!Collision::isNested(GetBound(), other->GetBound()))
		{
			//Lấy cạnh va chạm
			D3DXVECTOR2 sideCollision;

			//Lấy thời gian va chạm
			float time = Collision::CollisionAABB(GetBound(), other->GetBound(), distance, sideCollision);

			//Bé hơn 1 thì có va chạm
			if (time < 1.0f)
			{
				if (sideCollision.x != 0.0f)
				{
					position.x += disMan.x * time;
					velocity.x = 0;

					switch (stateMegaMan->GetState())
					{
					case MegaManState::Running:
					case MegaManState::RunningShoot:
					case MegaManState::Gliding:
					case MegaManState::GlidingShoot:
						stateMegaMan->SetState(MegaManState::State::Standing);
						break;
					case MegaManState::Jumping:
					case MegaManState::JumpingShoot:
					case MegaManState::Falling:
					case MegaManState::FallingShoot:
						stateMegaMan->SetState(MegaManState::State::Clamping);
						break;
					default:
						break;
					}	
				}
				else if (sideCollision.y == -1.0f)	//va chạm trên
				{
					position.y += disMan.y * time;
					velocity.y = -Gravity;
					stateMegaMan->SetState(MegaManState::State::Falling);
				}
				else if (sideCollision.y == 1.0f)	//va chạm dưới
				{
					position.y += disMan.y * time;
					velocity.y = 0;
				}

				//Enemy
				if (other->tag == Object::Enemys)
				{
					int side;
					if (position.x < other->GetPosition().x)
						side = 1;
					else
						side = -1;
					if (other->GetDamage() > 0)
					{
						stateMegaMan->BleedState(side, other->GetDamage());
					}
				}
			}
		}
	}
}

void MegaMan::Update(float dt, Keyboard* key)
{
	//Chỉnh lại vị trí sau khi xét va chạm
	Object::Update(dt, key);

	//Update Animation
	animationMegaMan->SetFlipFlag(GetFlipFlag());
	animationMegaMan->Update(dt, key);

	//Tạo tia lửa
	if (stateMegaMan->GetAllowDrawSpark())
	{
		bool k = spark->GetIsDone();
		if (!spark->GetIsDone() && !spark->GetAllowDraw())
		{
			spark->NewSpark(position + animationMegaMan->GetSpark(animationMegaMan->GetIndex()) / 2, flipFlag);
		}		
	}
	else
	{
		spark->SetIsDone(false);
	}
	
	//Update tia lửa
	if (spark->GetAllowDraw())
		spark->Update(dt, key);

	//Tạo khói khi lướt
	if (stateMegaMan->GetAllowDrawSpark())
	{
		if ((int)stateMegaMan->GetGlideWidth() % 20 == 0 || (int)stateMegaMan->GetClampHeight() % 10 == 0)
		{
			smokes[numSmoke]->NewSmoke(position + animationMegaMan->GetSpark(animationMegaMan->GetIndex()), flipFlag);
			numSmoke++;
			if (numSmoke > 5)
				numSmoke = 0;
		}
	}

	//Update khói
	for (int i = 0; i < 6; i++)
	{
		if (smokes[i]->GetAllowDraw())
			smokes[i]->Update(dt, key);
	}
	
	//Tạo ánh sáng năng lượng
	lightEnergy->NewLight(position, flipFlag, stateMegaMan->GetEnergyLevel());

	//Update ánh sáng năng lượng
	if (lightEnergy->GetAllowDraw())
		lightEnergy->Update(dt, key);

	//Tạo chớp nhân vật
	if (GetAllowDraw())
	{
		sprite->SetColor(D3DCOLOR_XRGB(255, 255, 255));	
	}
	else
	{ 
		sprite->SetColor(D3DCOLOR_XRGB(120, 180, 255));
	}
	
	//Tạo đạn
	if (stateMegaMan->IsShoot())
	{
		if (!bullets[numBullet]->GetAllowDraw())
		{
			bool flipBullet = stateMegaMan->IsClamping() ? !flipFlag : flipFlag;
			bullets[numBullet]->NewBullet(position + animationMegaMan->GetGun(animationMegaMan->GetIndex()), flipBullet, stateMegaMan->GetEnergyLevel());
			numBullet++;
			if (numBullet > 2)
				numBullet = 0;
		}	
	}

	//Update đạn
	for (int i = 0; i < 3; i++)
	{
		if (bullets[i]->GetAllowDraw())
			bullets[i]->Update(dt, key);
	}
	
}

void MegaMan::Render(Viewport *viewport)
{
	sprite->SetData(
		animationMegaMan->GetRect(),
		animationMegaMan->GetCenter(),
		animationMegaMan->GetPosition(),
		animationMegaMan->GetScale(),
		animationMegaMan->GetTransform(),
		animationMegaMan->GetAngle()
	);
	sprite->SetPosition(position);
	sprite->Render(viewport);

	lightEnergy->Render(viewport);

	spark->Render(viewport);

	for (int i = 0; i < 6; i++)
	{
		smokes[i]->Render(viewport);
	}
	
	for (int i = 0; i < 3; i++)
	{
		bullets[i]->Render(viewport);
	}
}