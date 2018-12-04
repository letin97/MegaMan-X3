#pragma once
#include "Object.h"
#include "Define.h"
#include "Sprite.h"
#include "SpriteSheet.h"

class Collapse : public Object
{
protected:
	Object* element[4];
	SpriteSheet* spriteSheetCollapse;
	int start, end;
	int listRECT[4];
	bool appear;
public:
	Collapse(Sprite *sprite_collapse, SpriteSheet* spriteSheet);
	Collapse();
	~Collapse();

	void NewCollapse(D3DXVECTOR2 pos, int enemyType);
	void Update(float dt, Keyboard* key);
	void Render(Viewport* view);
};