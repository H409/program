//*****************************************************************************
//
// debug display
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "develop_display.h"

namespace develop_tool {
DevelopDisplay::DevelopDisplay(LPDIRECT3DDEVICE9 in_direct3ddevice9,u16 in_width,u16 in_height)
	:is_show_(false)
{
#ifndef _RELEASE
	is_show_ = true;

	ZeroMemory(string_,sizeof(s8) * STRING_MAX);
	ZeroMemory(stringR_,sizeof(s8) * STRING_MAX);

	D3DXCreateFont(in_direct3ddevice9,32,12,0,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&font_);
#endif // _RELEASE
}

DevelopDisplay::~DevelopDisplay(void)
{
#ifndef _RELEASE
	SafeRelease(font_);
#endif // _RELEASE
}

void DevelopDisplay::Update(void)
{
#ifndef _RELEASE
#endif // _RELEASE
}

void DevelopDisplay::Draw(void)
{
#ifndef _RELEASE
	if(is_show_)
	{
		RECT rect = { 0,0,width_,height_ };
		RECT rectR = { 900 , 0 , width_ , height_ };

		// テキスト描画
		font_->DrawText(NULL,string_,-1,&rect,DT_LEFT,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		font_->DrawText(NULL,stringR_,-1,&rectR,DT_LEFT,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

		// デバッグ情報のクリア
		memset(string_,'\0',sizeof(s8) * STRING_MAX);
		memset(stringR_,'\0',sizeof(s8) * STRING_MAX);
	}

	ZeroMemory(string_,sizeof(s8) * STRING_MAX);
	ZeroMemory(stringR_,sizeof(s8) * STRING_MAX);

#endif // _RELEASE
}

void DevelopDisplay::Print(const char* in_format,...)
{
#ifndef _RELEASE
	char work[STRING_MAX] = { NULL };
	va_list args;

	// 可変引数の参照開始
	va_start(args,in_format);

	// 文字列に変更
	vsprintf(work,in_format,args);

	// 可変引数の参照終了
	va_end(args);

	// ログに書込
	strcat(string_,work);
#endif // _RELEASE
}

void DevelopDisplay::PrintR(const char* in_format,...)
{
#ifndef _RELEASE
	char work[STRING_MAX] = { NULL };
	va_list args;

	// 可変引数の参照開始
	va_start(args,in_format);

	// 文字列に変更
	vsprintf(work,in_format,args);

	// 可変引数の参照終了
	va_end(args);

	// ログに書込
	strcat(stringR_,work);
#endif // _RELEASE
}
}// namespace develop_tool

//-----------------------------------EOF---------------------------------------
