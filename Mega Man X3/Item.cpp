#include "Item.h"

Item::Item()
{
}

Item::Item(Object* megaMan, Sprite* sprite_Items, SpriteSheet* spriteSheet_Items)
{
	tag = Object::Tag::Items;
	sprite = sprite_Items;
	animationItem = new Animation(spriteSheet_Items);
	allowDraw = true;
	transform = D3DXVECTOR2(0, 0);
}

Item::~Item()
{
	delete animationItem;
}

Item::ItemType Item::GetItemType() {
	return itemType;
}

void Item::SetItemType(ItemType type)
{
	itemType = type;
}

Item::ItemState Item::GetItemState() {
	return itemState;
}

void Item::SetItemState(ItemState state)
{
	itemState = state;
}

bool Item::GetAppear()
{
	return appear;
}

//Tạo Itemss mới
void Item::NewItem(D3DXVECTOR2 pos)
{
	int type = rand() % (1 - 0 + 1) - 0;	// (b - a + 1) + a;

	switch (type)
	{
	case Item::HPItem1:
		HP = 1;
		itemType = Item::HPItem1;
		break;
	case Item::HPItem2:
		HP = 2;
		itemType = Item::HPItem2;
		break;
	default:
		break;
	}

	allowDraw = true;
	appear = true;
	velocity.y = 0.5f;
	timeExist = 0.0f;
	position = pos;
	itemState = Item::Appearing;
}

void Item::ChangeAnimation()
{
	switch (itemType)
	{
	case Item::HPItem1:
		SetBound(2, 2);
		switch (itemState)
		{
		case Item::Appearing:
		{
			animationItem->SetFrame(position, false, 0, 21, 21);
			break;
		}
		case Item::Grounding:
			animationItem->SetFrame(position, false, 10, 22, 24);
			break;
		}
		break;

	case Item::HPItem2:
		SetBound(4, 4);
		switch (itemState)
		{
		case Item::Appearing:
		{
			animationItem->SetFrame(position, false, 0, 25, 25);
			break;
		}
		case Item::Grounding:
			animationItem->SetFrame(position, false, 10, 26, 28);
			break;
		}
		break;
		
	default:
		break;
	}
}

void Item::Update(float dt, Keyboard* key)
{
	if (appear)
	{
		ChangeAnimation();
		Object::Update(dt, key);
		animationItem->Update(dt, key);

		if (velocity.y > -Gravity)
		{
			velocity.y -= 0.1f;
		}

		if (itemState == ItemState::Grounding)
		{
			timeExist += dt;
			SetVelocity(0, 0);

			//Nháy
			if (timeExist > 2)
			{
				if (!allowDraw)
				{
					if ((int)(timeExist * 10) % 2 == 0)
						SetAllowDraw(true);
				}
				else
				{
					SetAllowDraw(false);
				}
			}

			//Kiểm tra biến mất
			if (timeExist > TimeItem)
			{
				timeExist = 0.0f;
				bound = { 0, 0, 0, 0 };
				allowDraw = false;
				appear = false;
			}
		}
	}
}

void Item::Render(Viewport *view)
{
	//Vẽ Itemss
	if (appear)
	{
		if (view->isContains(bound))
		{
			if (allowDraw)
			{
				sprite->SetData(
					animationItem->GetRect(),
					animationItem->GetCenter(),
					animationItem->GetPosition(),
					animationItem->GetScale(),
					animationItem->GetTransform(),
					animationItem->GetAngle()
				);
				sprite->Render(view);
			}		
		}
	}
}

//Va chạm
void Item::OnCollision(Object *obj)
{
	if (Collision::isCollision(GetBound(), obj->GetBound()))
	{
		if (obj->tag == Object::Tag::Player)
		{
			allowDraw = false;
			bound = { 0, 0, 0, 0 };
			timeExist = 0;
			appear = false;
			switch (itemType)
			{
			case Item::HPItem1:
			{
				obj->SetHP(obj->GetHP() + 2);
				if (obj->GetHP() > obj->GetHPMax())
				{
					obj->SetHP(obj->GetHPMax());
				}
				break;
			}
			case Item::HPItem2:
			{
				obj->SetHP(obj->GetHP() + 4);
				if (obj->GetHP() > obj->GetHPMax())
				{
					obj->SetHP(obj->GetHPMax());
				}
				break;
			}
			}
		}
		else
		{
			SetVelocity(0, 0);
			itemState = Item::Grounding;
		}
	}
}

