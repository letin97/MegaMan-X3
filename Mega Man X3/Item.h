#pragma once
#include "Object.h"
#include "Animation.h"
#include "Define.h"
#include "Collision.h"
#include "MegaMan.h"

using namespace Define;

class Item : public Object
{
protected:

	Animation* animationItem;
	float timeExist;
	bool appear;

public:
	enum ItemType
	{
		HPItem1,
		HPItem2,
		None
	};
	ItemType itemType;

	enum ItemState
	{
		Appearing,
		Grounding
	};
	ItemState itemState;

	Item();
	~Item();
	Item(Object* megaMan, Sprite* sprite_Item, SpriteSheet* spriteSheet_Item);

	ItemType GetItemType();
	void SetItemType(ItemType type);

	ItemState GetItemState();
	void SetItemState(ItemState state);

	bool GetAppear();
	void NewItem(D3DXVECTOR2 pos);
	void ChangeAnimation();
	void Update(float dt, Keyboard *key);
	void Render(Viewport *view);
	void OnCollision(Object *obj);
};

