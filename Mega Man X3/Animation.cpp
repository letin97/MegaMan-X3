#include "Animation.h"


Animation::Animation(SpriteSheet* spriteSheet)
{
	this->spriteSheet = spriteSheet;
	delay = 0;
	start = 0;
	end = 0;
	repeat = true;
	scale = D3DXVECTOR2(1, 1);
	position = D3DXVECTOR2(0, 0);
	flipFlag = false;
	angle = 0;
	pause = false;
}

Animation::Animation(SpriteSheet* spriteSheet, int start, int end, int delay, bool repeat)
{
	this->spriteSheet = spriteSheet;
	this->delay = delay;
	this->index = 0;
	this->start = start;
	this->end = end;
	this->repeat = repeat;
	scale = D3DXVECTOR2(1, 1);
	position = D3DXVECTOR2(0, 0);
	flipFlag = false;
	angle = 0;
	pause = false;
}

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::SetFrame(D3DXVECTOR2 position, bool flip, int delay, int start, int end)
{
	this->position = position;
	this->flipFlag = flip;
	this->delay = delay;
	this->start = start;
	this->end = end;
}

void Animation::Animation::SetFrame(D3DXVECTOR2 position, bool flip, int delay, int start, int end, bool repeat)
{
	this->position = position;
	this->flipFlag = flip;
	this->delay = delay;
	this->start = start;
	this->end = end;
	this->repeat = repeat;
}

int Animation::GetIndex()
{
	return index;
}

void Animation::SetIndex(int index)
{
	this->index = index;
}

RECT Animation::GetRect()
{
	return spriteSheet->GetRect(index);
}


bool Animation::GetFlipFlag()
{
	return flipFlag;
}

int Animation::GetDelay()
{
	return delay;
}

int Animation::GetStart()
{
	return start;
}

int Animation::GetEnd()
{
	return end;
}

void Animation::SetPause(bool pause)
{
	this->pause = pause;
}
void Animation::SetPause(bool pause, int index)
{
	this->indexPause = index;
	this->pause = pause;
}

void Animation::Update(float dt, Keyboard* keyboard)
{
	if ( index == end && repeat == false)
	{
		
	}
	else
	{
		//Chuyển frame tiếp theo
		if (timeCurrent * 100 >= delay)
		{
			timeCurrent = 0;
			index++;
		}
		else timeCurrent += dt;

		//Kiểm tra index
		if (index < start || index > end)
		{
			index = start;
		}
	}

	//Kiểm tra frame dừng
	if (pause)
	{
		index = indexPause;
	}
	//Kiểm tra Flip
	Flip(flipFlag);

	//Set rect mới
	this->rect = GetRect();

	//Lấy center
	center.x = (rect.right - rect.left) * 0.5;
	center.y = (rect.bottom - rect.top) * 0.5;

	if (spriteSheet->GetTransform(index).x != 0)
	{
		if (flipFlag)
		{
			transform.x = -spriteSheet->GetTransform(index).x;
		}
		else
		{
			transform.x = spriteSheet->GetTransform(index).x;
		}
		
	}
	else transform.x = 0;

	if (spriteSheet->GetTransform(index).y != 0)
	{
		transform.y = spriteSheet->GetTransform(index).y;
	}
	else transform.y = 0;
	
}

//Lấy tọa độ cây súng so với vị trí vẽ
D3DXVECTOR2 Animation::GetGun(int index)
{
	D3DXVECTOR2 pGun;
	if (flipFlag)
		pGun.x = -spriteSheet->GetGun(index).x;
	else
		pGun.x = spriteSheet->GetGun(index).x;

	pGun.y = spriteSheet->GetGun(index).y;

	return pGun;
}