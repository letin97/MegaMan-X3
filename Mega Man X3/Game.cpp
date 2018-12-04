#include "Game.h"

Game::Game(HINSTANCE Hins, int width, int height, char* name,int fps)
{
	this->hInstance = Hins;
	this->width = width;
	this->height = height;
	this->hWnd = NULL;
	this->fps = fps;
	strcpy_s(this->windowName, name);
}

Game::~Game()
{
	delete graphic;
	keyboard->KillKeyboard();
	delete keyboard;
	delete SceneManager;
}

//Hàm xử lý cửa sổ
LRESULT CALLBACK Game::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//Tạo cửa sổ Game
bool Game::InitWindow()
{
	WNDCLASSEX Wndclass;
	Wndclass.cbSize = sizeof(WNDCLASSEX);
	Wndclass.cbClsExtra = 0;
	Wndclass.cbWndExtra = 0;
	Wndclass.hIconSm = 0;
	Wndclass.hIcon = 0;
	Wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wndclass.hInstance = this->hInstance;
	Wndclass.lpfnWndProc = (WNDPROC)WindowProc;
	Wndclass.lpszClassName = "Mega Man X3";
	Wndclass.lpszMenuName = NULL;
	Wndclass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&Wndclass))
	{
		return false;
	}

	this->hWnd = CreateWindow(
		"Mega Man X3",
		this->windowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		this->width,
		this->height,
		NULL, NULL,
		this->hInstance,
		NULL);

	if (!this->hWnd)
		return false;

	ShowWindow(this->hWnd, SW_NORMAL);
	UpdateWindow(this->hWnd);
}

bool Game::InitGraphic()
{
	//Tạo màn hình vẽ
	this->graphic = new Graphic(this->hWnd, GameWidth, GameHeight);
	if (!graphic->InitDirectX())
	{
		return false;
	}
	return true;
}

void Game::InitKeyboard()
{
	this->keyboard = new Keyboard(hWnd);
	this->keyboard->Init();
}

void Game::InitScene()
{
	SceneManager = new Scene();
	SceneManager->Init(graphic);
}

void Game::Init()
{
	InitWindow();
	InitGraphic();
	InitKeyboard();
	InitScene();
}

//Vòng lặp game
void Game::Run()
{
	MSG Msg;
	LARGE_INTEGER startTime;
	LARGE_INTEGER frequence;
	float Fps = 1.0f / this->fps;
	float gameTime = 0;
	LARGE_INTEGER endTime;
	float delay = 0;
	ZeroMemory(&Msg, sizeof(Msg));
	QueryPerformanceFrequency(&frequence);
	QueryPerformanceCounter(&endTime);

	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			QueryPerformanceCounter(&startTime);
			QueryPerformanceCounter(&endTime);
			gameTime += ((float)endTime.QuadPart - (float)startTime.QuadPart) / (float)frequence.QuadPart;
			if (gameTime >= Fps)
			{
				Update(gameTime);
				Render();
				gameTime = 0;
			}
			else
			{
				Sleep(Fps - gameTime);
				gameTime = Fps;
			}
		}
	}
}

//Update game
void Game::Update(float dt)
{
	//Lấy trạng thái bàn phím, chuột
	keyboard->GetStage();
	SceneManager->Update(dt, keyboard);
}

//Vẽ các Object trong game
void Game::Render()
{
	graphic->Begin();
	SceneManager->Render();
	graphic->End();
}
