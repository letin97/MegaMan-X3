#pragma once
#include "Sprite.h"
#include "Collision.h"
#include "Sound.h"

class Object
{
protected:
	Sprite* sprite;
	Sound* sound;
	float width;		
	float height;
	D3DXVECTOR2 position;			//Vị trí vẽ
	D3DXVECTOR2 velocity;			//Vector vận tốc
	D3DXVECTOR2 positionStart;		//Vị trí bắt đầu
	D3DXVECTOR2 transform;			//Vector dịch chuyển
	RECT bound;						//Khung
	float angle;					//Góc quay
	bool flipFlag;					//Cờ lật
	bool allowDraw;					//cho phép vẽ
	string name;					//Tên
	int HP = 0, damage = 0;
	int HPMax;

public:
	int id;
	enum Tag
	{
		Player,
		Bullets,
		Wall,
		Enemys,
		Items,
		Port,
		Elevator,
		Stage,
		None
	};
	Tag tag;

	Object();
	~Object();

	//Tag
	Tag GetTag();
	static Tag GetTag(string name);
	void SetTag(string name);

	//Cờ lật
	virtual bool GetFlipFlag();
	virtual void SetFlipFlag(bool flag);

	//Khung va chạm
	virtual RECT GetBound();
	virtual void SetBound(float width, float height);
	virtual void SetBound(RECT bound);
	RECT GetBoard(D3DXVECTOR2 distance);

	//Thông tin frame
	virtual float GetWidth();
	virtual void SetWidth(float width);
	virtual float GetHeight();
	virtual void SetHeight(float height);

	//Vị trí
	virtual D3DXVECTOR2 GetPosition();
	virtual D3DXVECTOR2 GetPositionStart();
	virtual void SetPosition(D3DXVECTOR2 position);
	virtual void SetPositionStart(D3DXVECTOR2 position);
	virtual void SetPositionX(float x);
	virtual void SetPositionY(float y);

	//Vận tốc
	virtual D3DXVECTOR2 GetVelocity();
	virtual void SetVelocity(D3DXVECTOR2 velocity);
	virtual void SetVelocityX(float vx);
	virtual void SetVelocityY(float vy);
	virtual void SetVelocity(float x, float y);
	virtual void AddVelocity(float x, float y);

	//Dịch chuyển
	virtual D3DXVECTOR2 GetTransform();
	virtual void SetTransform(D3DXVECTOR2 transform);
	virtual void SetTransform(float x, float y);

	//Góc
	virtual float GetAngle();
	virtual void SetAngle(float angle);

	//Tính khoảng cách trong khoảng dt
	virtual D3DXVECTOR2 Distance(float dt);

	virtual void Update(float dt, Keyboard* key);
	virtual void Render(Viewport* viewport);

	//Va chạm
	virtual void OnCollision(Object *obj, D3DXVECTOR2 distance);
	virtual void OnCollision(Object *obj) {}
	virtual void OnCollision() {}
	
	virtual void New();

	//Cờ vẽ
	virtual bool GetAllowDraw();
	virtual void SetAllowDraw(bool allowDraw);

	//Tên
	virtual string GetName();
	virtual void SetName(string name);
	
	//Máu
	virtual int GetHP();
	virtual void SetHP(int hp);
	virtual int GetHPMax();
	virtual void SetHPMax(int hp);
	
	//Damage
	virtual int GetDamage();
	virtual void SetDamage(int damage);
};

