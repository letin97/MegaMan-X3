#pragma once
#include "MegaMan.h"
#include "Animation.h"
#include "Define.h"
#include "Collision.h"
#include "Map.h"
using namespace Define;

class Port : public Object
{
protected:
	Animation* animation;
	MegaMan *megaMan;

	bool moveStage, slip;
	bool active;

public:

	enum PortState
	{
		Init,
		Opening,
		Closing
	};
	PortState state;
	
	Port();
	Port(MegaMan *man, Sprite* sprite_port, SpriteSheet* spriteSheet_Port, Sound* sound);
	~Port();

	void New();
	void New(D3DXVECTOR2 pos);
	void ChangeAnimation(Keyboard* key);
	void Update(float gameTime, Keyboard *key);
	void Render(Viewport *view);
	void OnCollision();
};

