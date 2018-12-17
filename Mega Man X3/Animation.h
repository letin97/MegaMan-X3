#pragma once
#include "Sprite.h"

class Animation : public Sprite
{
protected:
	SpriteSheet* spriteSheet;
	float timeCurrent;
	float delay;
	int index, start, end, indexPause;
	bool repeat;
	bool pause;

public:
	Animation(SpriteSheet* spriteShhet);
	Animation(SpriteSheet* spriteShhet, int start, int end, int deday, bool repeat);
	Animation();
	~Animation();

	//Set thông số để vẽ 
	void SetFrame(D3DXVECTOR2 position, bool flip, int delay, int start, int end);
	void SetFrame(D3DXVECTOR2 position, bool flip, int delay, int start, int end, bool repeat);

	RECT GetRect();
	int GetIndex();
	void SetIndex(int index);
	bool GetFlipFlag();
	int GetDelay();
	int GetStart();
	int GetEnd();
	void SetPause(bool pause);
	void SetPause(bool, int);
	void Update(float dt, Keyboard* keyborad);

	D3DXVECTOR2 GetGun(int index);
	D3DXVECTOR2 GetSmoke(int index);
};
