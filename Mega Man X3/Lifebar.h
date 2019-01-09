#pragma once
#include "Sprite.h"
#include "SpriteSheet.h"

class Lifebar
{
protected:
	Sprite* sprite;
	SpriteSheet* spriteSheetLifebar;
public:
	enum LifebarType
	{
		LifebarMegaMan,
		LifebarBoss,
	};
	LifebarType type;

	Lifebar(Sprite *sprite, SpriteSheet* spriteSheet, LifebarType type);
	Lifebar();
	~Lifebar();
	void Render(int HP, int HPMax);
};