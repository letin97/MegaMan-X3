#include "Collapse.h"
#include <cstdlib>
#include <ctime>

Collapse::Collapse(Sprite *sprite_collapse, SpriteSheet* spriteSheet)
{
	sprite = sprite_collapse;
	for (int i = 0; i < 4; i++)
	{
		element[i] = new Object();
	}
	spriteSheetCollapse = spriteSheet;
}

Collapse::Collapse()
{
}

Collapse::~Collapse()
{
	
}

void Collapse::NewCollapse(D3DXVECTOR2 pos, int type)
{
	switch (type)
	{
	case Collapse::CollapseHeadGunner:
		start = 21;
		end = 33;
		break;
	case Collapse::CollapseNotorBanger:
		start = 53;
		end = 66;
		break;
	case Collapse::CollapseHelit:
		start = 72;
		end = 80;
		break;
	default:
		break;
	}

	int r;
	srand(time(NULL));

	//Tạo ngẫu nhiên vận tốc
	for (int i = 0; i < 4; i++)
	{
		// rand() % (b – a + 1) + a
		r = rand() % (20 - 0 + 1) + 0;
		float vx = -1 + 0.1 * r;
		float vy = 1 + 0.1 * r;

		element[i]->SetVelocity(D3DXVECTOR2(vx, vy));
		element[i]->SetPosition(pos);
	}

	//Lấy ngẫu nhiên 4 mảnh vỡ
	bool kt;
	int n = 0;
	do {
		kt = true;
		r = rand() % (end - start + 1) + start;
		for (int i = 0; i < 4; i++) 
		{
			if (listRECT[i] == r) {
				kt = false;
			}
		}
		if (kt == true) {
			listRECT[n] = r;
			n++;
		}
	} while (n < 4);

	allowDraw = true;
	appear = true;
	position = pos;
	SetBound(5, 5);
}

void Collapse::Update(float dt, Keyboard* key)
{
	if (appear)
	{
		//Nháy
		if (!allowDraw)
		{
			SetAllowDraw(true);
		}
		else
		{
			SetAllowDraw(false);
		}

		for (int i = 0; i < 4; i++)
		{
			element[i]->Update(dt, key);
			element[i]->SetVelocityY(element[i]->GetVelocity().y - 0.15f);
		}
	}
}

//Vẽ
void Collapse::Render(Viewport* view)
{
	if (appear)
	{
		if (view->isContains(bound))
		{
			if (allowDraw)
			{
				for (int i = 0; i < 4; i++)
				{
					sprite->SetRect(spriteSheetCollapse->GetRect(listRECT[i]));
					sprite->SetPosition(element[i]->GetPosition());
					sprite->Render(view);
				}
			}
		}
		else
		{
			bound = { 0, 0, 0, 0 };
			allowDraw = false;
			appear = false;
		}
	}
}