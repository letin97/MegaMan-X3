#include "MegaManState.h"


MegaManState::MegaManState(Object* megaman)
{
	this->megaMan = megaman;
	state = State::Standing;
}

MegaManState::MegaManState()
{
}

MegaManState::~MegaManState()
{
}

MegaManState::State MegaManState::GetState()
{
	return state;
}

//Set trạng thái
void MegaManState::SetState(State state)
{
	this->state = state;
}

bool MegaManState::GetAllowDrawSpark()
{
	return allowDrawSpark;
}

void MegaManState::SetAllowDrawSpark(bool b)
{
	this->allowDrawSpark = b;
}

bool MegaManState::GetAllowDrawSmoke()
{
	return allowDrawSmoke;
}

bool MegaManState::IsShoot()
{
	return isShoot;
}

bool MegaManState::IsClamping()
{
	if (state == State::Clamping || state == State::ClampingShoot)
		return true;
	return false;
}

bool MegaManState::IsBleeding()
{
	return isBleed;
}

bool MegaManState::GetIsDelayShoot()
{
	return isDelayShoot;
}

float MegaManState::GetEnergyLevel()
{
	return energyLevel;
}

int MegaManState::GetStyleSpark()
{
	if (state == State::Jouncing)
		return 2;
	return 1;
}


float MegaManState::GetGlideWidth()
{
	return megaMan->GetPosition().x > startGlide ? megaMan->GetPosition().x - startGlide : startGlide - megaMan->GetPosition().x;
}

float MegaManState::GetClampHeight()
{
	return startGlide - megaMan->GetPosition().y;
}

float MegaManState::GetStarGlide()
{
	return startGlide;
}


//Kiểm tra hướng
void MegaManState::CheckSide(Keyboard* keyboard)
{
	if (state == State::Gliding || state == State::GlidingShoot ||
		state == State::GlidingAerial || state == State::GlidingAerialShoot ||
		state == State::Kicking || state == State::KickingShoot ||
		state == State::Clamping || state == State::ClampingShoot) 
		return;

	if (keyboard->IsKeyDown(DIK_RIGHT))
	{
		megaMan->SetVelocityX(RunSpeed);
		megaMan->SetFlipFlag(false);
	}
	else if (keyboard->IsKeyDown(DIK_LEFT))
	{
		megaMan->SetVelocityX(-RunSpeed);;
		megaMan->SetFlipFlag(true);
	}
	else megaMan->SetVelocityX(0);
}

//Trạng thái đứng
void MegaManState::StandState(Keyboard* keyboard)
{
	isJump = false;
	isGlide = false;
	isFall = false;
	isJounce = false;
	isShoot = false;
	allowDrawSpark = false;
	allowDrawSmoke = false;

	if (keyboard->GIsKeyUp(DIK_A)) allowGlide = true;

	if (keyboard->IsKeyDown(DIK_RIGHT))
	{
		state = State::Running;
	}
	else if (keyboard->IsKeyDown(DIK_LEFT))
	{
		state = State::Running;
	}
	else if (keyboard->IsKeyDown(DIK_SPACE))
	{
		state = State::Jumping;
	}
	else if (keyboard->IsKeyDown(DIK_S))
	{
		state = State::StandingShoot;
	}
	else if (keyboard->IsKeyDown(DIK_A))
	{
		if (allowGlide) state = State::Gliding;
	}
	else
	{
		if (megaMan->GetVelocity().y == -Gravity)
		{
			state = State::Falling;
		}
		else
		{
			megaMan->SetVelocityY(-Gravity);
			state = State::Standing;
		}
	}
}

//Trang thái chạy
void MegaManState::RunState(Keyboard* keyboard)
{
	isJump = false;
	isGlide = false;
	isShoot = false;
	allowDrawSpark = false;
	allowDrawSmoke = false;

	if (keyboard->GIsKeyUp(DIK_A)) allowGlide = true;

	if (keyboard->IsKeyDown(DIK_RIGHT) || keyboard->IsKeyDown(DIK_LEFT))
	{
		if (keyboard->IsKeyDown(DIK_SPACE))
		{
			state = State::Jumping;
		} 
		else if (keyboard->IsKeyDown(DIK_A))
		{
			if (allowGlide)
			{
				if (keyboard->IsKeyDown(DIK_S))
					state = State::GlidingShoot;
				else state = State::Gliding;
			}
		}
		else
		{
			if (megaMan->GetVelocity().y == -Gravity)
			{
				state = State::Falling;
			}
			else
			{
				megaMan->SetVelocityY(-Gravity);
				if (keyboard->IsKeyDown(DIK_S))			
					state = State::RunningShoot;
				else state = State::Running;
			}
		}
	}
	else
	{
		state = State::Standing;
	}
}

//Trang thái nhảy
void MegaManState::JumpState(Keyboard* keyboard)
{
	isShoot = false;
	allowDrawSpark = false;
	allowDrawSmoke = false;

	if (!isJump)
	{
		startJump = megaMan->GetPosition().y;
		megaMan->SetVelocityY(JumpSpeed);
		isJump = true;
	}

	if (keyboard->IsKeyDown(DIK_SPACE))
	{
		if (keyboard->IsKeyDown(DIK_W))
		{
			state = State::Jouncing;
		}
		else 
		{
			if ((megaMan->GetPosition().y - startJump) >= JumpMax)
			{
				megaMan->SetVelocityY(-Gravity);
				state = State::Falling;
			}
			else
			{
				if (keyboard->IsKeyDown(DIK_A))
				{
					megaMan->SetVelocityY(-Gravity);
					state = State::Falling;
				}
				else if (keyboard->IsKeyDown(DIK_S))
					state = State::JumpingShoot;
				else
					state = State::Jumping;
			}
		}
			
	}
	else
	{
		if ((megaMan->GetPosition().y - startJump) >= JumpMin)
		{
			megaMan->SetVelocityY(-Gravity);
			state = State::Falling;
		}
		else
		{
			if (keyboard->IsKeyDown(DIK_A))
			{
				megaMan->SetVelocityY(-Gravity);
				state = State::Falling;
			}	
			else if (keyboard->IsKeyDown(DIK_S)) 
				state = State::JumpingShoot;
			else 
				state = State::Jumping;
		}
	}	
}

//Trang thái rơi
void MegaManState::FallState(Keyboard* keyboard)
{
	isGlide = false;
	isShoot = false;
	allowDrawSpark = false;
	allowDrawSmoke = false;

	if (keyboard->GIsKeyUp(DIK_A)) allowGlide = true;

	if (megaMan->GetVelocity().y == 0)
	{
		state = State::Standing;
	}
	else 
	{
		megaMan->SetVelocityY(megaMan->GetVelocity().y - FallAcceleration);
		if (keyboard->IsKeyDown(DIK_A))
		{
			if(allowGlide) state = State::GlidingAerial;
		}
		else if (keyboard->IsKeyDown(DIK_S))
			state = State::FallingShoot;
		else
			state = State::Falling;
	}
}

//Trang thái lướt
void MegaManState::GlideState(Keyboard* keyboard)
{
	isShoot = false;
	allowGlide = false;
	allowDrawSpark = true;
	allowDrawSmoke = true;

	if (!isGlide)
	{
		//Vị trí bắt đầu lướt
		startGlide = megaMan->GetPosition().x;
		if (!megaMan->GetFlipFlag()) megaMan->SetVelocityX(GlideSpeed);
		else megaMan->SetVelocityX(-GlideSpeed);
		megaMan->SetVelocityY(0);
		isGlide = true;
	}

	if (keyboard->GIsKeyDown(DIK_A))
	{
		// Hủy lươt nếu chuyển động ngược hướng lướt
		if (keyboard->IsKeyDown(DIK_RIGHT) && megaMan->GetFlipFlag() || keyboard->IsKeyDown(DIK_LEFT) && !megaMan->GetFlipFlag())
		{
			state = State::Standing;
		}
		else
		{
			//Khoảng cách lướt xa tối đa
			if (GetGlideWidth() >= GlideMax)
			{
				state = State::Standing;
			}
			else
			{
				if (megaMan->GetVelocity().y == -Gravity)
				{
					state = State::Falling;
				}
				else
				{
					megaMan->SetVelocityY(-Gravity);
					if (keyboard->IsKeyDown(DIK_S)) state = State::GlidingShoot;
					else state = State::Gliding;
				}
			}
		}	
	}
	else
	{
		if (keyboard->IsKeyDown(DIK_RIGHT) || keyboard->IsKeyDown(DIK_LEFT))
		{
			state = State::Standing;
		}
		else
		{
			//Khoảng cách lướt xa tối thiểu
			if (GetGlideWidth() >= GlideMin)
			{
				state = State::Standing;
			}
			else
			{
				if (keyboard->IsKeyDown(DIK_S)) state = State::GlidingShoot;
				else state = State::Gliding;
			}
		}	
	}
}

//Trang thái lướt
void MegaManState::GlidingAerialState(Keyboard* keyboard)
{
	isShoot = false;
	allowGlide = false;
	allowDrawSpark = true;
	allowDrawSmoke = false;

	if (!isGlide)
	{
		//Vị trí bắt đầu lướt
		startGlide = megaMan->GetPosition().x;
		if (!megaMan->GetFlipFlag()) megaMan->SetVelocityX(GlideSpeed);
		else megaMan->SetVelocityX(-GlideSpeed);
		megaMan->SetVelocityY(0);
		isGlide = true;
	}

	if (keyboard->GIsKeyDown(DIK_A))
	{
		// Hủy lươt nếu chuyển động ngược hướng lướt
		if (keyboard->IsKeyDown(DIK_RIGHT) && megaMan->GetFlipFlag() || keyboard->IsKeyDown(DIK_LEFT) && !megaMan->GetFlipFlag())
		{
			megaMan->SetVelocityY(-Gravity);
			state = State::Falling;
		}
		else
		{
			//Khoảng cách lướt xa tối đa
			if (GetGlideWidth() >= GlideMax)
			{
				megaMan->SetVelocityY(-Gravity);
				state = State::Falling;
			}
			else
			{
				if (keyboard->IsKeyDown(DIK_S)) state = State::GlidingAerialShoot;
				else state = State::GlidingAerial;
			}
		}
	}
	else
	{
		if (keyboard->IsKeyDown(DIK_RIGHT) || keyboard->IsKeyDown(DIK_LEFT))
		{
			megaMan->SetVelocityY(-Gravity);
			state = State::Falling;
		}
		else
		{
			//Khoảng cách lướt xa tối thiểu
			if (GetGlideWidth() >= GlideMin)
			{
				megaMan->SetVelocityY(-Gravity);
				state = State::Falling;
			}
			else
			{
				if (keyboard->IsKeyDown(DIK_S)) state = State::GlidingAerialShoot;
				else state = State::GlidingAerial;
			}
		}
	}
}

//Trang thái bám
void MegaManState::ClampState(Keyboard* keyboard)
{
	isJump = false;
	isShoot = false;
	allowDrawSpark = false;
	allowDrawSmoke = true;

	if (!isGlide)
	{
		//Vị trí bắt đầu lướt
		startGlide = megaMan->GetPosition().y;
		megaMan->SetVelocityY(-ClampSpeed);
		isGlide = true;
	}

	if (megaMan->GetVelocity().x != 0)
	{
		state = State::Falling;
		return;
	}
	else
	{
		if (!megaMan->GetFlipFlag()) megaMan->SetVelocityX(ClampSpeed);
		else megaMan->SetVelocityX(-ClampSpeed);
	}

	if (megaMan->GetVelocity().y == 0)
	{
		state = State::Standing;
	}
	else
	{
		if (keyboard->IsKeyDown(DIK_SPACE))
		{
			state = State::Kicking;
		}
		else if (keyboard->IsKeyDown(DIK_S))
		{
			state = State::ClampingShoot;
		}
		else 
			state = State::Clamping;
	}
}

//Trang thái đạp
void MegaManState::KickState(Keyboard* keyboard)
{
	isGlide = false;
	isShoot = false;
	allowDrawSpark = false;
	allowDrawSmoke = false;


	if (!isJump)
	{
		startJump = megaMan->GetPosition().y;
		megaMan->SetVelocityY(2);
		if (!megaMan->GetFlipFlag()) megaMan->SetVelocityX(-KickSpeed);
		else megaMan->SetVelocityX(KickSpeed);
		isJump = true;
	}

	if ((megaMan->GetPosition().y - startJump) >= 20)
	{
		megaMan->SetVelocityX(-megaMan->GetVelocity().x);
		state = State::Jumping;
	}
	else
	{
		if (keyboard->IsKeyDown(DIK_S))
		{
			state = State::KickingShoot;
		}
		else 
			state = State::Kicking;
	}
}

//Trang thái nẩy
void MegaManState::JounceState(Keyboard* keyboard)
{
	isGlide = false;
	isShoot = false;
	allowDrawSpark = true;
	allowDrawSmoke = false;

	if (!isJounce)
	{
		startJump = megaMan->GetPosition().y;
		megaMan->SetVelocityY(0);
		isJounce = true;
	}

	if ((megaMan->GetPosition().y - startJump) >= 100)
	{
		megaMan->SetVelocityY(-Gravity);
		state = State::Falling;
	}
	else
	{
		megaMan->SetVelocityY(megaMan->GetVelocity().y + 0.08f);
		state = State::Jouncing;
	}
}

//Trang thái bắn
void MegaManState::ShootState(Keyboard* keyboard)
{
	isDelayShoot = true;

	switch (state)
	{
	case MegaManState::StandingShoot:
		StandState(keyboard);
		break;
	case MegaManState::RunningShoot:
		RunState(keyboard);
		break;
	case MegaManState::JumpingShoot:
		JumpState(keyboard);
		break;
	case MegaManState::FallingShoot:
		FallState(keyboard);
		break;
	case MegaManState::GlidingShoot:
		GlideState(keyboard);
		break;
	case MegaManState::GlidingAerialShoot:
		GlidingAerialState(keyboard);
		break;
	case MegaManState::ClampingShoot:
		ClampState(keyboard);
		break;
	case MegaManState::KickingShoot:
		KickState(keyboard);
		break;
	}

	if (keyboard->GIsKeyUp(DIK_S))
	{
		isShoot = true;
	}

}

//Trạng thái bị thương
void MegaManState::BleedState(int side, int dame)
{
	if (dame == 0)
		return;

	this->side = side;
	isBleed = true;

	if (isBleed)
	{
		//Mất máu do quái đụng
		if (side != 0)
		{
			if (timeBleed >= 0.3f)
			{
				timeBleed = 0.0f;
				velocityBleed.y = Gravity;
				megaMan->SetHP(megaMan->GetHP() - dame);
			}
		}
	}
}

void MegaManState::Update(float dt, Keyboard* keyboard)
{
	//Nháy
	if (timeEnergy > TimeBulletLv2)
	{
		if (appear)
		{
			if ((int)(timeEnergy * 10) % 2 == 0)
				megaMan->SetAllowDraw(true);
			appear = false;
		}
		else
		{
			megaMan->SetAllowDraw(false);
			appear = true;
		}
	}
	else
	{
		megaMan->SetAllowDraw(true);
	}

	//Deley shoot
	if (isDelayShoot)
	{
		timeDelayShoot += dt;
		if (timeDelayShoot > DelayAnimation)
		{
			isDelayShoot = false;
			timeDelayShoot = 0;
		}
	}

	//trạng thái mất máu
	if (isBleed)
	{
		timeBleed += dt;

		//chỉnh Vận tốc
		velocityBleed.y = velocityBleed.y - 0.075f;

		//Đang bị đẩy
		if (velocityBleed.y > -Gravity && megaMan->GetVelocity().y != 0.0f)
		{
			megaMan->SetVelocityY(velocityBleed.y);

			if (side > 0)	//va vào bên phải
				megaMan->SetVelocityX(-0.75);
			else			//va vào bên trái
				megaMan->SetVelocityX(0.75);
		}

		if (timeBleed > 0.5f)
		{
			isBleed = false;
			state = MegaManState::Falling;
		}
	}

	//Năng lượng
	switch (state)
	{
	case MegaManState::StandingShoot:
	case MegaManState::RunningShoot:
	case MegaManState::JumpingShoot:
	case MegaManState::FallingShoot:
	case MegaManState::GlidingShoot:
	case MegaManState::GlidingAerialShoot:
	case MegaManState::ClampingShoot:
	case MegaManState::KickingShoot:
	{
		timeEnergy += dt;
		timeShoot = 0;
		break;
	}
	default:
		timeShoot += dt;
		break;
	}
	
	if (timeEnergy < TimeBulletLv2)
		energyLevel = 0;
	else if (timeEnergy >= TimeBulletLv2 && timeEnergy <= TimeBulletLv3)
		energyLevel = 1;
	else
		energyLevel = 2;

	if (isShoot || timeShoot > TimeBulletLv2)
	{
		timeEnergy = 0;
		timeShoot = 0;
	}
}