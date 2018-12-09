#include "Object.h"

Object::Object()
{
}


Object::~Object()
{
}

void Object::New()
{
}

bool Object::GetFlipFlag()
{
	return flipFlag;
}
void Object::SetFlipFlag(bool flag)
{
	this->flipFlag = flag;
}

//Khung va chạm
RECT Object::GetBound()
{
	bound.left = position.x - width / 2;
	bound.right = bound.left + width;
	bound.top = position.y + height / 2;
	bound.bottom = bound.top - height;
	return bound;
}

void Object::SetBound(RECT bound)
{
	this->bound = bound;
}

void Object::SetBound(float width, float height)
{
	this->width = width;
	this->height = height;
	bound.left = position.x - width / 2;
	bound.right = bound.left + width;
	bound.top = position.y + height / 2;
	bound.bottom = bound.top - height;
}


//Thông tin frame
float Object::GetWidth()
{
	return this->width;
}

void Object::SetWidth(float width)
{
	this->width = width;
}

float Object::GetHeight()
{
	return this->height;
}

void Object::SetHeight(float height)
{
	this->height = height;
}

//Vị trí
D3DXVECTOR2 Object::GetPosition()
{
	return position;
}

D3DXVECTOR2 Object::GetPositionStart()
{
	return positionStart;
}

void Object::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
}

void Object::SetPositionStart(D3DXVECTOR2 position)
{
	this->positionStart = position;
}

void Object::SetPositionX(float x)
{
	position.x = x;
}

void Object::SetPositionY(float y)
{
	position.y = y;
}

//Vận tốc
D3DXVECTOR2 Object::GetVelocity()
{
	return velocity;
}

void Object::SetVelocity(D3DXVECTOR2 Velocity)
{
	velocity = Velocity;
}

void Object::SetVelocityX(float x)
{
	velocity.x = x;
}

void Object::SetVelocityY(float y)
{
	velocity.y = y;
}

void Object::SetVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Object::AddVelocity(float x, float y)
{
	velocity.x += x;
	velocity.y += y;
}

//Dịch chuyển
D3DXVECTOR2 Object::GetTransform()
{
	return transform;
}

void Object::SetTransform(D3DXVECTOR2 transform)
{
	this->transform = transform;
}

void Object::SetTransform(float x, float y)
{
	transform.x = x;
	transform.y = y;
}

//Góc quay
float Object::GetAngle()
{
	return angle;
}

void Object::SetAngle(float angle)
{
	this->angle = angle;
}

//Khoảng cách
D3DXVECTOR2 Object::Distance(float time)
{
	return velocity * 100 * time;
}

//cho phép vẽ
void Object::SetAllowDraw(bool allowDraw)
{
	this->allowDraw = allowDraw;
}

bool Object::GetAllowDraw()
{
	return allowDraw;
}

void Object::Update(float dt, Keyboard* key)
{
	position += velocity * dt * 100;
}


void Object::OnCollision(Object *obj, D3DXVECTOR2 distance)
{
}

void Object::Render(Viewport* viewport)
{

}

RECT Object::GetBoard(D3DXVECTOR2 distance)
{
	return Collision::GetBoard(this->GetBound(), distance);
}

Object::Tag Object::GetTag()
{
	return tag;
}

Object::Tag Object::GetTag(string name)
{
	if (name == "HeadGunner" || name == "NotorBanger")
	{
		return Tag::Enemys;
	}
	return Tag::None;
}

void Object::SetTag(string name)
{
	if (name == "MegaMan")
	{
		tag = Tag::Player;
	}
	else if (name == "Wall")
	{
		tag = Tag::Wall;
	}
}

//Tên
string Object::GetName()
{
	return name;
}
void Object::SetName(string name)
{
	this->name = name;
}

//Máu
int Object::GetHP()
{
	return HP;
}

void Object::SetHP(int hp)
{
	HP = hp;
}

int Object::GetHPMax()
{
	return HPMax;
}

void Object::SetHPMax(int hp)
{
	HPMax = hp;
}

//Damage
int Object::GetDamage()
{
	return damage;
}

void Object::SetDamage(int damage)
{
	this->damage = damage;
}

