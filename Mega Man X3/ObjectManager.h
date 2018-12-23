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
#include "Byte.h"
#include "BlastHornet.h"
#include "Port.h"
#include "Lifebar.h"
#include "Sound.h"

class ObjectManager
{
protected:
	MegaMan *megaMan;

	Viewport* viewport;
	Map* map;
	QuadTree  *mQuadTree;
	Lifebar *lifebar;

	Sound* sound;
	GSound* soundBlastHornet;

	vector <Object*> listObjectCollison;
	vector <Object*> listWall;
	vector <Object*> listObject;
	D3DXVECTOR2 prePosView;

	//Player
	Sprite *sprite_MegaMan;
	SpriteSheet* spriteSheet_MegaMan;

	//Efect
	Sprite *sprite_LightEnergy;
	Sprite *sprite_Spark;
	Sprite *sprite_Smoke;
	Sprite *sprite_Explosion;
	SpriteSheet* spriteSheet_LightEnergy;
	SpriteSheet* spriteSheet_Spark;
	SpriteSheet* spriteSheet_Smoke;
	SpriteSheet* spriteSheet_Explosion;

	//Bullet Item
	Sprite *sprite_Weapons_And_Items;
	SpriteSheet* spriteSheet_Weapons_And_Items;

	//Enemy
	Sprite *sprite_HeadGunner;
	Sprite *sprite_NotorBanger;
	Sprite *sprite_Helit;
	SpriteSheet* spriteSheet_HeadGunner;
	SpriteSheet* spriteSheet_NotorBanger;
	SpriteSheet* spriteSheet_Helit;

	//Boss
	Genjibo* mGenjibo;
	Byte* mByte;
	BlastHornet* mBlastHornet;
	Sprite *sprite_Genjibo;
	Sprite *sprite_Byte;
	Sprite *sprite_BlastHornet;
	SpriteSheet *spriteSheet_Genjibo;
	SpriteSheet *spriteSheet_Byte;
	SpriteSheet *spriteSheet_BlastHornet;

	//Lifebar
	Sprite *sprite_Lifebar;
	
public:
	ObjectManager();
	~ObjectManager();

	void Init(Graphic* graphic, Sound *sound);

	//Update Game sau khoảng thời gian dt
	void Update(float dt, Keyboard* key);

	//Vẽ Object lên màn hình
	void Render();

	void ReadQuadTree(TiXmlElement *root, QuadTree *node, QuadTree *father, int indexNode);
};
