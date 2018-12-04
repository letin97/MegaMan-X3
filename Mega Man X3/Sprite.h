#pragma once
#include <d3dx9.h>
#include "Graphic.h"
#include "Keyboard.h"
#include "SpriteSheet.h"
#include "ViewPort.h"

class Sprite
{
protected:
	Graphic* graphic;				
	LPDIRECT3DTEXTURE9 texture;
	char* pathpng;
	float width;				
	float height;
	float widthFrame;
	float heightFrame;
	

	bool flipFlag;					//Cờ lật

	RECT rect;						//Hình chữ nhật cắt từ ảnh của texture
	D3DXVECTOR2 position;			//Vị trí vẽ
	D3DXVECTOR2 center;				//Vị trí vẽ trong rect
	D3DXVECTOR2 scale;				//Kích thước
	D3DXVECTOR2 transform;			//Dịch chuyển
	D3DCOLOR color;
	float angle;					//góc quay theo độ

public:
	Sprite();
	Sprite(Graphic* graphic, const char* pathsprite);
	~Sprite();

	virtual float GetWidth();
	virtual void SetWidth(float width);
	virtual float GetHeight();
	virtual void SetHeight(float height);

	virtual float GetWidthFrame();
	virtual float GetHeightFrame();

	virtual void SetTexture(const char* pathpng);

	virtual RECT GetRect();
	virtual void SetRect(RECT rect);

	virtual D3DXVECTOR2 GetPosition();
	virtual void SetPosition(D3DXVECTOR2 position);

	virtual D3DXVECTOR2 GetCenter();
	virtual void SetCenter(D3DXVECTOR2 center);

	virtual D3DXVECTOR2 GetScale();
	virtual void SetScale(D3DXVECTOR2 scale);

	virtual D3DXVECTOR2 GetTransform();
	virtual void SetTransform(float x, float y);

	virtual float GetAngle();
	virtual void SetAngle(float angle);

	virtual void SetFlipFlag(bool flag);
	virtual void Flip(bool flag);

	virtual void SetColor(D3DCOLOR color);

	virtual void SetData(RECT rect, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle);
	virtual void Update(float dt, Keyboard* key);
	virtual void Render();
	virtual void Render(Viewport* viewport);

};
