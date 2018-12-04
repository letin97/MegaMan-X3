#include "Smoke.h"


Smoke::Smoke()
{
}

Smoke::Smoke(Sprite* sprite_smoke, SpriteSheet* sprite_sheet)
{
	sprite = sprite_smoke;
	animationSmoke = new Animation(sprite_sheet, 0, 5, 8, false);
	allowDraw = false;

	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);

}

Smoke::~Smoke()
{
	delete animationSmoke;
}

void Smoke::NewSmoke(D3DXVECTOR2 position, bool flipflag)
{
	this->allowDraw = true;
	this->position = position;
	this->flipFlag = flipflag;
	SetVelocityY(GetVelocity().y + 0.2);
}

void Smoke::ChangeAnimation()
{
	animationSmoke->SetFrame(position, flipFlag, 8, 0, 5);
	if (animationSmoke->GetIndex() == animationSmoke->GetEnd())
	{
		allowDraw = false;
		SetVelocityY(0);
		animationSmoke->SetIndex(animationSmoke->GetStart());
	}
}

void Smoke::Update(float dt, Keyboard* key)
{
	if (allowDraw)
	{
		ChangeAnimation();
		Object::Update(dt, key);
		animationSmoke->Update(dt, key);
	}
}

void Smoke::Render(Viewport* viewport)
{
	if (allowDraw)
	{
		sprite->SetData(
			animationSmoke->GetRect(),
			animationSmoke->GetCenter(),
			animationSmoke->GetPosition(),
			animationSmoke->GetScale(),
			animationSmoke->GetTransform(),
			animationSmoke->GetAngle()
		);
		sprite->Render(viewport);
	}
}
