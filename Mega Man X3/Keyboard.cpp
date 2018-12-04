#include "Keyboard.h"

Keyboard::Keyboard(HWND hWnd)
{
	this->di = 0;
	this->did = 0;
	this->hWnd = hWnd;
	ZeroMemory(&this->key_buffer, sizeof(this->key_buffer));
}

Keyboard::~Keyboard()
{
}

//Cài đặt bàn phím
bool Keyboard::Init()
{
	HRESULT hr = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&this->di,		//Con trỏ nhận dữ liệu trả về
		NULL);				

	if (FAILED(hr))
	{
		return false;
	}

	//Tạo bàn phím GUID_SysKeyboard
	hr = this->di->CreateDevice(GUID_SysKeyboard, &this->did, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	//Dạng dữ liệu được nhận
	hr = this->did->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return false;
	}

	//Loại hoạt động 
	hr = this->did->SetCooperativeLevel(this->hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); //DISCL_FOREGROUND chỉ hoạt động khi của sổ hWnd đang được handle
	if (FAILED(hr))
	{
		return false;
	}

	//Yêu cầu thiết bị
	hr = this->did->Acquire();
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

//Lấy trạng thái bàn phím
void Keyboard::GetStage()
{
	HRESULT hr = this->did->GetDeviceState(sizeof(this->key_buffer), (LPVOID)&this->key_buffer);
	//Nếu bàn phím nhả ra yêu cầu nhập lại
	if (FAILED(hr))
	{
		while (this->did->Acquire() == DIERR_INPUTLOST);
	}
}

//Nhân diện phím nhấn
bool Keyboard::IsKeyDown(int key)
{
	//Trả về phím có được nhân hay không
	return key_buffer[key] & 0x80;//0x80 xác định bit đầu tiên
}

//Kiểm tra trạng thái phím có đang down
bool Keyboard::GIsKeyDown(int key)
{
	return (IsKeyDown(key));
}

//Kiểm tra trạng thái phím có đang up
bool Keyboard::GIsKeyUp(int key)
{
	return (!(IsKeyDown(key)));
}

//Hủy phím
void Keyboard::KillKeyboard()
{
	if (did != NULL)
	{
		this->did->Unacquire();
		this->did->Release();
		this->did = NULL;
	}
}