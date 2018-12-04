#pragma once
#include "Sprite.h"
#include "SpriteSheet.h"

class Lifebar
{
protected:
	Sprite* sprite;
	SpriteSheet* spriteSheetLifebar;
public:
	Lifebar(Sprite *sprite, SpriteSheet* spriteSheet);
	Lifebar();
	~Lifebar();
	void Render(int HP, int HPMax);
};