#pragma once
#include <d3dx9.h>
#include "Keyboard.h"
#include "Animation.h"
#include "MegaManState.h"
#include "Define.h"
using namespace Define;

class MegaManAnimation :public Animation
{
protected:
	D3DXVECTOR2 pGun;
	D3DXVECTOR2 pSpark;
public:
	MegaManAnimation(SpriteSheet* info) :Animation(info) {}
	MegaManAnimation();
	~MegaManAnimation();

	void StandAnimation();
	void RunAnimation(); 
	void JumpAnimation(); 
	void FallAnimation();
	void GlideAnimation();
	void ClampAnimation();
	void KickAnimation();
	void JouncingAnimation();

	void StandShootAnimation();
	void RunShootAnimation();
	void GlideShootAnimation();
	void JumpShootAnimation();
	void FallShootAnimation();
	void ClampShootAnimation();
	void KickShootAnimation();

	void BleedAnimation();

	D3DXVECTOR2 GetGun(int index);
	D3DXVECTOR2 GetSpark(int index);

	void Update(float dt, Keyboard* key);
};

