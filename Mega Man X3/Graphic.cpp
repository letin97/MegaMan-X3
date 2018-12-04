#include "Graphic.h"

Graphic::Graphic(HWND hWnd, int width, int height)
{
	this->hWnd = hWnd;
	this->width = width;
	this->height = height;
	this->d3d = NULL;
	this->d3ddv = NULL;
	this->d3dSprite = NULL;
}

Graphic::~Graphic()
{
}

//Cài đặt thiết bị
bool Graphic::InitDirectX()
{
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!this->d3d)
	{
		return false;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//Tạo Format phù hợp
	d3dpp.BackBufferWidth = this->width;
	d3dpp.BackBufferHeight = this->height;
	d3dpp.hDeviceWindow = this->hWnd;			//Handle cửa sổ cần vẽ lên
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//Tham số hay dùng
	d3dpp.Windowed = true;						//Chế độ có cửa sổ
												//CreateDevice(Thiết bị vẽ mặc định, Hỗ trợ phần cứng, Cửa sổ vẽ, (Không rõ),
												//thông số BlackBuffer, Con trỏ nhận dữ liệu sai khi tạo Device);
	HRESULT hr = this->d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		this->hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&this->d3ddv);

	if (FAILED(hr))
	{
		return false;
	}

	//Tạo các Texture
	hr = D3DXCreateSprite(this->d3ddv, &this->d3dSprite);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
LPDIRECT3DTEXTURE9 Graphic::LoadTexture(string path, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO info;
	HRESULT hr;
	ZeroMemory(&info, sizeof(info));
	//Lấy thông tin về hình ảnh
	hr = D3DXGetImageInfoFromFile(path.c_str(), &info);
	if (hr != D3D_OK)
	{
		return NULL;
	}
	//Tạo Texture
	hr = D3DXCreateTextureFromFileEx(
		this->d3ddv,
		path.c_str(),
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,		//Tự chọn Fomat phù hợp
		D3DPOOL_DEFAULT,	//Lớp bộ nhớ cho texture
		D3DX_DEFAULT,		//Bộ lọc hình ảnh
		D3DX_DEFAULT,		//Bộ lọc mip
		transcolor,			//Chỉ ra màu trong suốt
		&info,				//Thông tin ảnh
		NULL,				//Đổ màu
		&texture);

	if (hr != D3D_OK)
	{
		return 0;
	}
	return texture;
}

//Load 1 Surface
PDIRECT3DSURFACE9 Graphic::LoadSurface(string path, D3DCOLOR transcolor)
{
	PDIRECT3DSURFACE9 surface = NULL;
	D3DXIMAGE_INFO info;
	HRESULT hr;
	ZeroMemory(&info, sizeof(info));
	hr = D3DXGetImageInfoFromFile(path.c_str(), &info);

	if (hr != D3D_OK)
	{
		return NULL;
	}
	//Tạo Surface
	hr = this->d3ddv->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_X8R8G8B8,	//surface format
		D3DPOOL_DEFAULT,	//Bộ nhớ lưu tự động
		&surface,			//Con trỏ lưu surface được tạo ra
		NULL);

	if (hr != D3D_OK)
	{
		return 0;
	}

	hr = D3DXLoadSurfaceFromFile(
		surface,
		NULL,
		NULL,
		path.c_str(),
		NULL,
		D3DX_DEFAULT,
		transcolor,
		NULL);

	if (hr != D3D_OK)
	{
		return 0;
	}
	return surface;
}

void Graphic::Begin()
{
	//Xóa cửa sổ vẽ bằng màu đen D3DCOLOR_XRGB(0, 0, 0);
	this->d3ddv->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1, NULL);
	
	//Bắt đầu vẽ
	this->d3ddv->BeginScene();
	this->d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void Graphic::End()
{
	//Kết thúc vẽ
	this->d3dSprite->End();
	this->d3ddv->EndScene();
	//Thể hiện tương đối các đối tượng BlackBuffer ra ngoài màn hình
	this->d3ddv->Present(NULL, NULL, NULL, NULL);
}

//Vẽ các hình
void Graphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT source, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DCOLOR color)
{
	this->d3dSprite->Draw(texture, &source, &D3DXVECTOR3(center.x, center.y, 0), &D3DXVECTOR3(position.x, position.y, 0), color);
}

//Vẽ
void Graphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, RECT rect, D3DXVECTOR2 center, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DCOLOR color)
{
	//Vẽ theo thông số cho trước
	D3DXVECTOR2 centerMatrix = position;
	float rad = angle * (3.14159265358979323846 / 180);
	D3DXMATRIX matrix; //Ma trận biến đổi 
	D3DXMATRIX oldMatrix;
	this->d3dSprite->GetTransform(&oldMatrix);
	D3DXMatrixTransformation2D(
		&matrix,				//Matrix
		&centerMatrix,			//Vị trí scale
		0,						//Góc scale
		&scale,					//Vector scale
		&centerMatrix,			//Vị trí góc quay
		rad,					//Góc quay theo rad
		&transform);			//vector tịnh tiến = velocity
								//Vẽ theo thông số cho trước

	this->d3dSprite->SetTransform(&matrix);
	//Vẽ
	this->d3dSprite->Draw(texture, &rect, &D3DXVECTOR3(center.x, center.y, 0), &D3DXVECTOR3(position.x, position.y, 0), color);
	//Thiết lập lại Ma trận cũ
	this->d3dSprite->SetTransform(&oldMatrix);
}

//Vẽ các surface
void Graphic::DrawSurface()
{
	//Lấy Backbuffer
	this->d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
}

//Lấy thiết bị vẽ
LPDIRECT3DDEVICE9 Graphic::GetDevice()
{
	return this->d3ddv;
}
//Lấy Hwnd
HWND Graphic::GetHwnd()
{
	return this->hWnd;
}
//Lấy Sprite
LPD3DXSPRITE Graphic::GetSprite()
{
	return this->d3dSprite;
}