#pragma once
#include "Boss.h"
#include "Bee.h"
#include "Parasitic.h"

class BlastHornet : public Boss
{
protected:
	//Player
	MegaMan *megaMan;
	bool isUp, isLeft, isLaunch;
	D3DXVECTOR2 posStartSwoop;
	int numRound;
	int numBee;
public:
	Bee* listBee[5];
	Parasitic* parasitic;
	enum BlastHornetState
	{
		Flying,
		FlyingRound,
		Pricking,
		Swooping,
		Launching,
		Dying
	};
	BlastHornetState state;

	BlastHornet() {}
	~BlastHornet() {}
	BlastHornet(MegaMan *megaMan, Sprite* sprite_BlastHornet,
		SpriteSheet* spriteSheet_BlastHornet, D3DXVECTOR2 pos);

	void Update(float dt, Keyboard* key);
	void Render(Viewport* viewport);
	void OnCollision(Object *obj, D3DXVECTOR2 distance);
	void OnCollision(Object *obj);
	void OnCollision();
	void ChangeAnimation(Keyboard* key);
};