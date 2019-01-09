#include "Lifebar.h"

Lifebar::Lifebar(Sprite *sprite, SpriteSheet* spriteSheet, LifebarType type)
{
	this->sprite = sprite;
	spriteSheetLifebar = spriteSheet;
	this->type = type;
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

	switch (type)
	{
	case LifebarType::LifebarMegaMan:
		x = 15.0f;
		sprite->SetRect(spriteSheetLifebar->GetRect(32));
		sprite->SetPosition(D3DXVECTOR2(x, y));
		sprite->Render();
		break;
	case LifebarType::LifebarBoss:
		x = 226.0f;
		sprite->SetRect(spriteSheetLifebar->GetRect(33));
		sprite->SetPosition(D3DXVECTOR2(x, y));
		sprite->Render();
		break;
	default:
		break;
	}

	sprite->SetRect(spriteSheetLifebar->GetRect(29));
	sprite->SetPosition(D3DXVECTOR2(x, 30 - 4));
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