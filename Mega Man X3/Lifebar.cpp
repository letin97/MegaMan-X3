#include "Lifebar.h"

Lifebar::Lifebar(Sprite *sprite, SpriteSheet* spriteSheet)
{
	this->sprite = sprite;
	spriteSheetLifebar = spriteSheet;
}

Lifebar::Lifebar()
{
}

Lifebar::~Lifebar()
{
	delete sprite;
}

//Vẽ
void Lifebar::Render(int HP, int HPMax)
{
	int height = 2;

	float x = 15.0f;
	float y = 30 + HPMax * height;

	sprite->SetRect(spriteSheetLifebar->GetRect(29));
	sprite->SetPosition(D3DXVECTOR2(x, 30 - 4));
	sprite->Render();

	sprite->SetRect(spriteSheetLifebar->GetRect(32));
	sprite->SetPosition(D3DXVECTOR2(x, y));
	sprite->Render();

	float xRender = x, yRender = y;
	int yHealt = y - HP * height;

	if (HP <= 8)
	{
		for (int i = 0; i < HPMax - 7; i++)
		{
			yRender = y - i * height;

			if (yRender > yHealt)
			{
				sprite->SetRect(spriteSheetLifebar->GetRect(31));
				sprite->SetPosition(D3DXVECTOR2(xRender, yRender - 16));
				sprite->Render();
			}
			else
			{
				sprite->SetRect(spriteSheetLifebar->GetRect(30));
				sprite->SetPosition(D3DXVECTOR2(xRender, yRender - 16));
				sprite->Render();
			}
		}
	}
	else
	{
		for (int i = 0; i < HPMax - 7; i++)
		{
			yRender = 30 + i * height;

			if (yRender < yHealt)
			{
				sprite->SetRect(spriteSheetLifebar->GetRect(30));
				sprite->SetPosition(D3DXVECTOR2(xRender, yRender));
				sprite->Render();
			}
			else
			{
				sprite->SetRect(spriteSheetLifebar->GetRect(31));
				sprite->SetPosition(D3DXVECTOR2(xRender, yRender));
				sprite->Render();
			}
		}
	}
}