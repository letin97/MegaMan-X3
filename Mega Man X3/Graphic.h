#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
using namespace std;

class Graphic
{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddv;
	
	LPDIRECT3DSURFACE9 backBuffer;	
	LPDIRECT3DSURFACE9 surface;

	LPD3DXSPRITE d3dSprite;
	
	LPD3DXSPRITE spriteHandler;		
	
	HWND hWnd;		//HWND của texture
	int width;		//Chiều rộng
	int height;		//Chiều cao

public:
	Graphic(HWND hWnd, int width, int height);
	~Graphic();

	//Cài đặt DirectX
	bool InitDirectX();

	//Bắt đầu vẽ
	void Begin();

	//Kết thúc vẽ
	void End();

	//Load 1 Texture
	LPDIRECT3DTEXTURE9 LoadTexture(string path, D3DCOLOR);

	//Load 1 Surface
	LPDIRECT3DSURFACE9 LoadSurface(string path, D3DCOLOR);

	//Vẽ các hình
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DCOLOR color);
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DCOLOR color);
	
	//Vẽ các surface
	void DrawSurface();
	
	//Lấy thiết bị
	LPDIRECT3DDEVICE9 GetDevice();
	HWND GetHwnd();
	LPD3DXSPRITE GetSprite();
};

