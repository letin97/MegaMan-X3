#pragma once
#include <Windows.h>
#include "Graphic.h"
#include "Keyboard.h"
#include "Sound.h"
#include "Scene.h"

class Game
{
private:
	HINSTANCE hInstance;	//HINSTANCE của chương trình 
	HWND hWnd;				//HWND của của sổ
	int width;				//Chiều rộng cửa sổ
	int height;				//Chiều cao cửa sổ
	char windowName[256];	//Tên cửa sổ
	int fps;				//frame per second

	//Hàm xử lý cửa sổ
	static HRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Graphic* graphic;		//Khai báo đối tượng graphic
	
	Keyboard* keyboard;		//Khai báo đối tượng Keyboard

	Sound *sound;

	Scene* SceneManager;

public:
	Game(HINSTANCE hInstance, int width, int height, char* name, int fps);
	~Game();

	//Tạo cửa sổ
	bool InitWindow();

	//Tạo Graphic
	bool InitGraphic();

	//Tạo bàn phím
	void InitKeyboard();

	//Tạo âm thanh
	void InitSound();

	//Tạo SceneManager
	void InitScene();

	//Load Data Game
	void Init();

	//Run Game
	void Run();

	//Update Game sau khoảng thời gian dt
	void Update(float dt);

	//Vẽ Object lên màn hình
	void Render();
};

