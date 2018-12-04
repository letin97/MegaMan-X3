#pragma once
#include <d3dx9.h>
#include "Keyboard.h"
#include "Object.h"
#include "Define.h"
#include "Bullet.h"

using namespace Define;

class MegaManState
{
protected:
	Object* megaMan;
	bool isJump, isFall, isGlide, appear;
	bool allowGlide, allowDrawSpark;
	float startJump, startGlide;

	bool isShoot = false;
	bool isDelayShoot = false;
	float timeEnergy = 0, timeDelayShoot = 0, timeShoot = 0;
	int energyLevel = 1;

	bool isBleed = false;
	D3DXVECTOR2 velocityBleed;
	float timeBleed = 0.5f;
	int side;

public:
	enum State
	{
		Standing,		//Đứng im
		Running,		//Chạy
		Jumping,		//Nhảy
		Gliding,		//Trượt
		Falling,		//Rơi
		Clamping,		//Bám
		Kicking,		//Đạp
		
		StandingShoot,	//Đứng bắn
		RunningShoot,	//Chạy bắn
		JumpingShoot,	//Nhảy bắn
		FallingShoot,	//Rơi bắn
		GlidingShoot,	//Trượt bắn
		ClampingShoot,	//Bám bắn
		KickingShoot,	//Đạp
	};

	State state;

	MegaManState(Object* megaman);
	MegaManState();
	~MegaManState();

	void CheckSide(Keyboard* keyboard);
	void StandState(Keyboard* key);
	void RunState(Keyboard* key);
	void JumpState(Keyboard *key);
	void FallState(Keyboard *key);
	void GlideState(Keyboard * key);
	void ClampState(Keyboard * key);
	void KickState(Keyboard * key);
	void ShootState(Keyboard* key);
	void BleedState(int side, int dame);

	State GetState();
	void SetState(State State);

	bool GetAllowDrawSpark();
	void SetAllowDrawSpark(bool b);

	bool IsShoot();
	bool IsClamping();
	bool IsBleeding();
	bool GetIsDelayShoot();
	float GetEnergyLevel();
	
	float GetGlideWidth();
	float GetClampHeight();
	float GetStarGlide();
	
	void Update(float dt, Keyboard* keyboard);
};

