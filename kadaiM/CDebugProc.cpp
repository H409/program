//�w�b�_�[�C���N���[�h
#include "CDebugProc.h"
#include <stdio.h>
#include <sstream>
//�x����������
#pragma warning(disable:4996)

//�ÓI�����o�ϐ��̏�����
LPD3DXFONT CDebugProc::m_pD3DXFont = NULL;
char	   CDebugProc::m_aStr[LENGTH_STRING_BUFF] = {0};
bool	   CDebugProc::m_bDisp = true;
RECT	   CDebugProc::m_rect = {0,0,0,0};
//������
void CDebugProc::Init(CRender* pRender)
{

	//�t�H���g�̏�����
	D3DXCreateFont(pRender->getDevice(), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r �o�S�V�b�N", &m_pD3DXFont);
	//�o�b�t�@�̃N���A
	memset(m_aStr,0,sizeof(char)*LENGTH_STRING_BUFF);
	
	m_rect.bottom = 0;
	m_rect.left = 0;
	m_rect.right = 0;
	m_rect.top = 0;
}
//�J��
void CDebugProc::Uninit(void)
{
	SAFE_RELEASE(m_pD3DXFont);
}

//�`��
void CDebugProc::Draw(void)
{
	//������̃T�C�Y���v�Z
	m_pD3DXFont->DrawText(NULL,m_aStr,-1,&m_rect,DT_CALCRECT,NULL);
	// �e�L�X�g�`��
	m_pD3DXFont->DrawText(NULL, m_aStr, -1, &m_rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	//�o�b�t�@�̃N���A
	memset(m_aStr,0,sizeof(char)*1024);
}
//�f�o�b�O�\���̓o�^
void CDebugProc::Print(const char *fmt,...)
{
#ifdef _DEBUG
	char str[256];
	va_list lpValist = NULL;	//�ϒ��������X�g�A�N�Z�X�p
	
	m_rect.left = 0;
	m_rect.top = 20;
	m_rect.bottom = 0;
	m_rect.right = 0;

	//�G���[�`�F�b�N
	if(!fmt)return;

	//�ϒ��������X�g�ւ̃A�N�Z�X���J�n����
	//��1������va_list�^�ϐ����w�肷��
	//��2�����͍Ō�̌Œ�������w��
	va_start(lpValist,fmt);

	//�ϒ��������X�g����l���擾���A�\�����镶����Ƃ��Ĕz��Ɋi�[����
	vsprintf(str,fmt,lpValist);

	//�ϒ��������X�g���������
	va_end(lpValist);
	//�A��
	strcat(m_aStr,str);
#endif
}
bool CDebugProc::IsEnableDisp(void)
{
	return m_bDisp;
}
void CDebugProc::EnableDisp(bool bDisp)
{

	m_bDisp = bDisp;
}