//=============================================================================
//
// �|�[�Y���� [CPause.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//���d��`�h�~
#ifndef __CPAUSE_H__
#define __CPAUSE_H__

//�w�b�_�[�C���N���[�h
#include "main.h"

//�񋓌^��`
typedef enum
{
	MODE_NONE,
	MODE_CONTINUE,
	MODE_RESET,
	MODE_QUIT,
	MODE_CHANGE_MAX
}MODE_CHANGE;

//�\���̒�`
typedef struct _FLOATPOINT
{
	float x;
	float y;

}FLOATPOINT;
typedef struct CURSOL
{
	FLOATPOINT pos;
	int Width;
	int Height;
	BYTE flag;
	float	fLength;		//�|���S���̑Ίp���̒���
	float	fAngle;			//�|���S���̑Ίp���̊p�x
	float	fSubLength;
	bool	bFlag;
}CURSOL,*LPCURSOL;



//�O���錾
class CRender;

//�N���X��`
class CPause
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// �e�N�X�`�����ǂݍ��ݗp
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// ���_�o�b�t�@
	LPDIRECT3DTEXTURE9		m_pD3DTexCur[3];		// �e�N�X�`�����ǂݍ��ݗp
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBufferCur;		// ���_�o�b�t�@
	D3DXVECTOR3				m_pos;					// ���W
	D3DXVECTOR3				m_rot;					// ��]
	float					m_fLength;				// ���S���璸�_�܂ł̒���
	float					m_fAngle;				// ���S���璸�_�ւ̊p�x
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	CURSOL					m_Cursor[3];
	char					m_curf;
	MODE_CHANGE				m_modechange;
	static CPause*			m_instance;
	int						m_type;
	BYTE					m_Red;
	BYTE					m_Green;
	BYTE					m_Blue;
	BYTE					m_Alpha[3];
public:

	static CPause* getInstance(void);
	static void Resease(void);
	//�R���X�g���N�^
	CPause()
	{
		for(int i = 0;i < 3;i++)
		{
			m_pD3DTexCur[i] = NULL;
		}
		m_pD3DVtxBufferCur = NULL;
		m_pD3DTex = NULL;
		m_pD3DVtxBuffer = NULL;

	}
	//�f�X�g���N�^
	~CPause()
	{
		/*
		for(int i = 0;i < 3;i++)
		{
			SAFE_RELEASE(m_pD3DTexCur[i]);
		}
		SAFE_RELEASE(m_pD3DVtxBufferCur);
		SAFE_RELEASE(m_pD3DVtxBuffer);
		SAFE_RELEASE(m_pD3DTex);
		*/
	}

	//������
	HRESULT Init(CRender* pRender);
	//�X�V
	void Update();
	//�J��
	void Uninit();
	//�`��
	void Draw();

	MODE_CHANGE GetModeChange(void)
	{
		return m_modechange;
	}
};

#endif
//eof