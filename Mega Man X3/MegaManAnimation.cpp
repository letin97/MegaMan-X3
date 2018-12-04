﻿#include "MegaManAnimation.h"


MegaManAnimation::MegaManAnimation()
{
}

MegaManAnimation::~MegaManAnimation()
{
}


void MegaManAnimation::StandAnimation()
{
	repeat = true;
	delay = 15;
	start = 7; end = 9;
}


void MegaManAnimation::RunAnimation()
{
	repeat = true;
	delay = 5;
	start = 19; end = 29;
}

void MegaManAnimation::JumpAnimation()
{
	repeat = false;
	delay = 15;
	start = 12; end = 14;
}

void MegaManAnimation::FallAnimation()
{
	repeat = false;
	delay = 10;
	start = 16; end = 16;
}


void MegaManAnimation::GlideAnimation()
{
	repeat = false;
	delay = 10;
	start = 37; end = 38;
}

void MegaManAnimation::ClampAnimation()
{
	repeat = false;
	delay = 10;
	start = 52; end = 54;
}

void MegaManAnimation::KickAnimation()
{
	repeat = false;
	delay = 10;
	start = 55; end = 56;
}


void MegaManAnimation::StandShootAnimation()
{
	repeat = true;
	delay = 10;
	start = 10; end = 11;
}

void MegaManAnimation::RunShootAnimation()
{
	repeat = true;
	delay = 5;
	start = 41; end = 51;
}

void MegaManAnimation::GlideShootAnimation()
{
	repeat = false;
	delay = 10;
	start = 39; end = 40;
}

void MegaManAnimation::JumpShootAnimation()
{
	repeat = false;
	delay = 15;
	start = 30; end = 32;
}

void MegaManAnimation::FallShootAnimation()
{
	repeat = false;
	delay = 10;
	start = 33; end = 34;
}

void MegaManAnimation::ClampShootAnimation()
{
	repeat = false;
	delay = 10;
	start = 57; end = 59;
}

void MegaManAnimation::KickShootAnimation()
{
	repeat = false;
	delay = 10;
	start = 60; end = 61;
}

void MegaManAnimation::BleedAnimation()
{
	repeat = true;
	delay = 5;
	start = 62; end = 72;
}

//Lấy tọa độ cây súng so với vị trí vẽ
D3DXVECTOR2 MegaManAnimation::GetGun(int index)
{
	if (flipFlag)
		pGun.x = -spriteSheet->GetGun(index).x;
	else
		pGun.x = spriteSheet->GetGun(index).x;

	pGun.y = spriteSheet->GetGun(index).y;

	return pGun;
}

//Lấy tọa độ tia lửa so với vị trí vẽ
D3DXVECTOR2 MegaManAnimation::GetSpark(int index)
{
	if (flipFlag)
		pSpark.x = -spriteSheet->GetSpark(index).x;
	else
		pSpark.x = spriteSheet->GetSpark(index).x;

	pSpark.y = spriteSheet->GetSpark(index).y;

	return pSpark;
}

void MegaManAnimation::Update(float dt, Keyboard* keyboard)
{
	Animation::Update(dt, keyboard);
}
