#include "Explosion.h"


Explosion::Explosion()
{
}

Explosion::Explosion(Sprite* sprite_explosion, SpriteSheet* sprite_sheet)
{
	sprite = sprite_explosion;
	animationExplosion = new Animation(sprite_sheet, 5, 0, 7, false);
	allowDraw = false;
	position = D3DXVECTOR2(0, 0);
	velocity = D3DXVECTOR2(0, 0);
	transform = D3DXVECTOR2(0, 0);

}

Explosion::~Explosion()
{
	delete animationExplosion;
}

void Explosion::NewExplosion(D3DXVECTOR2 position)
{
	allowDraw = true;
	this->position = position;
}

void Explosion::ChangeAnimation()
{
	animationExplosion->SetFrame(position, false, 5, 0, 7);
	if (animationExplosion->GetIndex() == animationExplosion->GetEnd())
	{
		allowDraw = false;
		animationExplosion->SetIndex(animationExplosion->GetStart());
	}
}

void Explosion::Update(float dt, Keyboard* key)
{
	if (allowDraw)
	{
		ChangeAnimation();
		animationExplosion->Update(dt, key);
	}
}

void Explosion::Render(Viewport* viewport)
{
	if (allowDraw)
	{
		sprite->SetData(
			animationExplosion->GetRect(),
			animationExplosion->GetCenter(),
			animationExplosion->GetPosition(),
			animationExplosion->GetScale(),
			animationExplosion->GetTransform(),
			animationExplosion->GetAngle()
		);
		sprite->Render(viewport);
	}
}
