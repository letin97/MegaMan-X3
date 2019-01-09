#include"Elevator.h"

Elevator::Elevator(MegaMan* man, Sprite* sprite_Elevator, SpriteSheet* spriteSheet_Elevator, Sound* sound, D3DXVECTOR2 pos)
{
	this->man = man;
	positionStart = pos;
	transform = D3DXVECTOR2(0, 0);
	this->sprite = sprite_Elevator;
	this->animation = new Animation(spriteSheet_Elevator);
	tag = Tag::Elevator;
	position = positionStart;
	SetBound(95, 30);
	allowDraw = true;
	flipFlag = false;
	state = Standing;
}

void Elevator::ChangeAnimation(Keyboard* key)
{
	switch (state)
	{
	case Elevator::Standing:
	case Elevator::Stopping:
		animation->SetFrame(position, flipFlag, 0, 0, 0, false);
		break;
	case Elevator::Running:
		animation->SetFrame(position, flipFlag, 1, 0, 1, true);
		break;
	}
}
void Elevator::Update(float dt, Keyboard* key)
{
	if (!allowDraw)
		return;

	ChangeAnimation(key);
	Object::Update(dt, key);
	animation->Update(dt, key);

	if (position.y > 1600)
	{
		state = Stopping;
	}

	if (state == Stopping)
	{
		velocity.y = 0.0f;
	}
	else if (state == Running)
	{
		velocity.y = 0.3f;
	}
}

void Elevator::OnCollision(Object *obj)
{
	if (Collision::isCollision(GetBound(), obj->GetBound()))
	{
		man->GetMegaManState()->isElevator = true;
		if(state != Stopping) state = Running;
	}
	else
	{
		man->GetMegaManState()->isElevator = false;
	}
}

void Elevator::Render(Viewport* viewport)
{
	if (viewport->isContains(bound))
	{
		allowDraw = true;

		this->sprite->SetData(
			animation->GetRect(),
			animation->GetCenter(),
			animation->GetPosition(),
			animation->GetScale(),
			animation->GetTransform(),
			animation->GetAngle()
		);
		this->sprite->Render(viewport);
	}
	else
	{
		allowDraw = false;
		man->GetMegaManState()->isElevator = false;
	}
}

