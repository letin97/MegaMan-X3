#pragma once
#include "Graphic.h"
#include "Keyboard.h"
#include "Text.h"
#include "MegaMan.h"
#include "Viewport.h"
#include "Map.h"
#include "QuadTree.h"
#include "HeadGunner.h"
#include "NotorBanger.h"
#include "Helit.h"
#include "Genjibo.h"
#include "Lifebar.h"

class ObjectManager
{
protected:
	MegaMan *megaMan;

	Viewport* viewport;
	Map* map;
	QuadTree  *mQuadTree;
	Lifebar *lifebar;

	vector <Object*> listObjectCollison;
	vector <Object*> listWall;
	vector <Object*> listObject;
	D3DXVECTOR2 prePosView;

	Sprite *sprite_MegaMan;
	Sprite *sprite_Effect;
	Sprite *sprite_Weapons_And_Items;
	Sprite *sprite_Enemy;
	Sprite *sprite_Lifebar;
	Sprite *sprite_Boss_Genjibo;

	SpriteSheet* spriteSheetMegaMan;
	SpriteSheet* spriteSheetEffect;
	SpriteSheet* spriteSheetWeaponsAndItems;
	SpriteSheet* spriteSheetEnemy;
	SpriteSheet *spriteSheetBossGenjibo;

	Genjibo* mGenjibo;
	
public:
	ObjectManager();
	~ObjectManager();

	void Init(Graphic* graphic);

	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);

	//Vẽ Object lên màn hình
	void Render();

	void ReadQuadTree(TiXmlElement *root, QuadTree *node, QuadTree *father, int indexNode);
};
