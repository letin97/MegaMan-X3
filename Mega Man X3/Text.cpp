#include "Text.h"

Text::~Text()
{
	if (font != NULL)
	{
		font->Release();
		font = NULL;
	}
}
Text::Text(Graphic *graphic, int size)
{
	this->graphic = graphic;
	D3DXCreateFont(graphic->GetDevice(),		// the D3D Device
		size,									// font size
		0,										// default font width
		FW_NORMAL,								// font weight
		1,    
		false,									// italic font
		DEFAULT_CHARSET,						// default character set
		OUT_DEFAULT_PRECIS,						// default OutputPrecision,
		DEFAULT_QUALITY,						// default Quality
		DEFAULT_PITCH | FF_DONTCARE,			// default pitch and family
		"Arial Black",							// use Facename Arial Black
		&font);
}

void Text::Render(char* text, RECT r, D3DCOLOR color)
{
	font->DrawTextA(this->graphic->GetSprite(),
		text,
		-1,
		&r,
		DT_RIGHT | DT_TOP,
		color);
}
