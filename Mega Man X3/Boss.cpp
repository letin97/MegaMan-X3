#include"Boss.h"

Boss::Boss()
{
}


Boss::~Boss()
{
	delete animationBoss;
}

void Boss::Update(float gametime, Keyboard *key)
{
	Object::Update(gametime, key);
}
void Boss::Render(Viewport *view)
{

}
void Boss::OnCollision()
{

}
void Boss::OnCollision(Object *obj, D3DXVECTOR2 dis)
{

}
void Boss::OnCollision(Object *obj)
{

}
void Boss::ChangeAnimation(Keyboard *key)
{

}