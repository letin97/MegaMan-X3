#pragma once
#include <d3dx9.h>
#include <vector>
#include "Keyboard.h"
#include "Define.h"

using namespace Define;


class Viewport
{
protected:

	D3DXVECTOR2 positionWorld;
	float width;
	float height;
	RECT Stage0 = { 0, 1280, 768, 1056 };
	int i = 0;
	RECT Stage = Stage0;
	int start = 0, end = 1024;
	int top = 1280, bottom = 1056;
	int moveTop = 0;
	int moveBottom = 0;

public:
	Viewport();
	//x và y là tọa độ thế giới left-top
	Viewport(float x, float y);
	Viewport(float x, float y, float width, float height);

	~Viewport();

	D3DXVECTOR2 GetPosition();
	void SetPosition(D3DXVECTOR2 Position);
	void SetPositionX(float x);
	void SetPositionY(float y);
	float GetWidth();
	float GetHeight();

	D3DXVECTOR2 TransformPosition(D3DXVECTOR2 position);

	//Kiểm tra 1 rect còn trong màn hình không
	bool isContains(RECT rect);

	//Kích thước RECT màn hình tính trong World
	RECT GetBound();

	//Update View theo 1 đối tượng
	void Update(float gameTime, Keyboard* key, D3DXVECTOR2 &posMegaMan, D3DXVECTOR2 velocityMan, std::vector <RECT> listStage);
};

