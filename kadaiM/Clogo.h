//���d��`�h�~
#ifndef __CLOGO_H__
#define __CLOGO_H__

//�w�b�_�[�C���N���[�h
#include "main.h"

//�O���錾
class CRender;
//�N���X��`
class Clogo
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// �e�N�X�`�����ǂݍ��ݗp
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// ���_�o�b�t�@
	D3DXVECTOR3				m_pos;					// ���W
	D3DXVECTOR3				m_rot;					// ��]
	float					m_fLength;				// ���S���璸�_�܂ł̒���
	float					m_fAngle;				// ���S���璸�_�ւ̊p�x
	int						m_Red;
	int						m_Green;
	int						m_Blue;
	int						m_Alpha;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	char*					m_pTexName;
	bool					m_drawFlag;
	int						m_cnt;
	CRender*				m_pRender;
public:
	//�R���X�g���N�^
	Clogo(){}
	//�f�X�g���N�^
	virtual ~Clogo(){}
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,int nWidth,int nHeight,char* ptexFileName);
	void	Update(void);
	void	Draw(void);
	void	Uninit(void);
	bool GetDrawFlag(void)
	{
		return m_drawFlag;
	}
	void SetDrawFlag(bool flag)
	{
		m_drawFlag = flag;
	}

};

#endif