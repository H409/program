//���d��`�h�~
#ifndef __CDEBUGPROC_H__
#define __CDEBUGPROC_H__

//�}�N����`
#define LENGTH_STRING_BUFF	(1028)

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CRender.h"

class CDebugProc
{
private:
	static LPD3DXFONT		m_pD3DXFont;
	static char				m_aStr[LENGTH_STRING_BUFF];
	static bool				m_bDisp;
	static RECT				m_rect;

public:
	//�R���X�g���N�^
	CDebugProc(){}
	//�f�X�g���N�^
	virtual ~CDebugProc(){}

	void Init(CRender* pRender);
	void Uninit(void);
	static void Print(const char *fmt,...);
	static void Draw(void);
	static bool IsEnableDisp(void);
	static void EnableDisp(bool bDisp);
};

#endif