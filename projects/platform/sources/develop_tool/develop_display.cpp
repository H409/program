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

		// �e�L�X�g�`��
		font_->DrawText(NULL,string_,-1,&rect,DT_LEFT,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		font_->DrawText(NULL,stringR_,-1,&rectR,DT_LEFT,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

		// �f�o�b�O���̃N���A
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

	// �ψ����̎Q�ƊJ�n
	va_start(args,in_format);

	// ������ɕύX
	vsprintf(work,in_format,args);

	// �ψ����̎Q�ƏI��
	va_end(args);

	// ���O�ɏ���
	strcat(string_,work);
#endif // _RELEASE
}

void DevelopDisplay::PrintR(const char* in_format,...)
{
#ifndef _RELEASE
	char work[STRING_MAX] = { NULL };
	va_list args;

	// �ψ����̎Q�ƊJ�n
	va_start(args,in_format);

	// ������ɕύX
	vsprintf(work,in_format,args);

	// �ψ����̎Q�ƏI��
	va_end(args);

	// ���O�ɏ���
	strcat(stringR_,work);
#endif // _RELEASE
}
}// namespace develop_tool

//-----------------------------------EOF---------------------------------------
