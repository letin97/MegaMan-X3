#include "Parasitic.h"

Parasitic::Parasitic(Sprite* sprite_BlastHornet, SpriteSheet* spriteSheet_BlastHornet)
{
	sprite = sprite_BlastHornet;
	//sprite->SetColor(D3DCOLOR_ARGB(100, 255, 255, 255));
	animation = new Animation(spriteSheet_BlastHornet);
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);
	tag = Object::None;
	allowDraw = false;
	SetBound(6, 6);
	damage = 0;
}

void Parasitic::New(D3DXVECTOR2 pos)
{
	allowDraw = true;
	appear = true;
	position = pos;
	state = Flying;
	isCling = false;
}

void Parasitic::OnCollision(Object *obj, D3DXVECTOR2 distance)
{
	
}

void Parasitic::ChangeAnimation(Keyboard* key)
{
	SetBound(6, 6);
	switch (state)
	{
	case ParasiticState::Flying:
	{
		animation->SetFrame(position, flipFlag, 5, 75, 76, true);
		break;
	}
	case ParasiticState::Cling:
	{
		animation->SetFrame(position, flipFlag, 5, 77, 78, true);
		break;
	}
	}
}

void Parasitic::Update(float dt, Keyboard* key)
{
	ChangeAnimation(key);
	Object::Update(dt, key);
	animation->Update(dt, key);

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
	}

	if (isCling)
	{
		state = Cling;
		timeExist += dt;
		if (timeExist > 5.0f)
		{
			bound = { 0, 0, 0, 0 };
			timeExist = 0.0f;
			allowDraw = false;
			appear = false;
		}
	}	
}

void Parasitic::Render(Viewport* viewport)
{
	if (!appear) return;

	sprite->SetData(
		animation->GetRect(),
		animation->GetCenter(),
		animation->GetPosition(),
		animation->GetScale(),
		animation->GetTransform(),
		animation->GetAngle()
	);
	sprite->Render(viewport);
}