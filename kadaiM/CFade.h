//=============================================================================
//
// �t�F�[�h���� [CFade.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//���d��`�h�~
#ifndef __CFADE_H__
#define __CFADE_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene2D.h"


//���[�h�`�F���W�p�񋓌^
typedef enum
{
	FADE_NONE,
	FADE_OUT,
	FADE_IN,
	FADE_OUT_FINISH,
	FADE_IN_FINISH,
	FADE_MAX
}FADEMODE;

class CRender;

//�N���X��`
class CFade
{
private:
	FADEMODE	m_FadeMode;
	bool		m_fadeFlag;
	CRender*	m_pRender;
	int			m_Alpha;
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// �e�N�X�`�����ǂݍ��ݗp
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// ���_�o�b�t�@
	D3DXVECTOR3				m_pos;					// ���W
	D3DXVECTOR3				m_rot;					// ��]
	float					m_fLength;				// ���S���璸�_�܂ł̒���
	float					m_fAngle;				// ���S���璸�_�ւ̊p�x
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	char*					m_pTexName;
	static CFade*			m_instance;
public:
	static CFade*			getinstance();
	static void				Release();
	CFade()
	{
		m_Alpha = 0;
	}
	virtual ~CFade()
	{
		SAFE_RELEASE(m_pD3DVtxBuffer);	//���_�o�b�t�@�̊J��
	}
	
	HRESULT Init(CRender* pRender);
	void Update();
	void Uninit();
	void Draw();

	FADEMODE	GetFadeMode(void)
	{
		return m_FadeMode;
	}
	void		SetFadeMode(FADEMODE iNum)
	{
		m_FadeMode = iNum;
	}

	bool		FadeOut(void);
	bool		FadeIn(void);

	static unsigned __stdcall FadeThread( LPVOID Param );
};

#endif