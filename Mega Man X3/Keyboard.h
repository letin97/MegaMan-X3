#pragma once
#include <dinput.h>

class Keyboard
{
	LPDIRECTINPUT8 di;			//Đối tượng nhập xuất
	LPDIRECTINPUTDEVICE8 did;	//Thiết bị nhập xuất
	char key_buffer[256];		//Buffer lưu dữ liệu lấy từ thiết bị
	HWND hWnd;					//Handle cửa sổ vẽ

public:
	Keyboard(HWND hWnd);
	~Keyboard();

	//Cài đặt bàn phím
	bool Init();

	//Lấy trạng thái bàn phím
	void GetStage();

	//Nhận diện phím nhấn
	bool IsKeyDown(int key);

	//Kiểm tra trạng thái phím có đang down
	bool GIsKeyDown(int key);

	//Kiểm tra trạng thái phím có đang up
	bool GIsKeyUp(int key);

	//Hủy bàn phím
	void KillKeyboard();
};

