//=============================================================================
//
// ���b�V���n�ʂ̏��� [CPaticle.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//���d��`�h�~
#ifndef __CPATICLE_H__
#define __CPATICLE_H__

//�w�b�_�[�C���N���[�h
#include "CScene.h"

//�}�N����`
#define PATICLE_MAX	(100)
#define PATICLE_DELETE_CNT	(200)
struct MY_VERTEX_1 
{
		D3DXVECTOR3 p;		// �ʒu
		FLOAT		p_size;	// �T�C�Y
		DWORD		color;	// �F
};
struct PointStrite
{
	D3DXVECTOR3	pos;		// �����ʒu
	float		psize;		// �T�C�Y
	D3DXVECTOR3 vec;		// �����x�ƕ���
	DWORD		start_time;	// �J�n���ԁi�~���b�j
	float		duration;	// �p�����ԁi�~���b�j
};

//�O���錾
class CRender;

//�N���X��`
class CPaticle:public CScene
{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture;		// �e�N�X�`���ւ̃|�C���^
	CRender*				m_pRender;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	D3DXMATRIX				m_mtxWorld;							// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;								// �ʒu
	D3DXVECTOR3				m_rot;								// ����
	D3DXVECTOR3				m_scl;								// �g�k
	int						m_DeleteCnt;
	float					m_continueTime;
	PointStrite				m_post[PATICLE_MAX];
public:

	static CPaticle* Create(CRender* pRender,D3DXVECTOR3 pos,char* ptexfilename);
	CPaticle(int nPriority = 3):CScene(nPriority){}
	virtual ~CPaticle(){}

	//������
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,char *ptexfilename);
	//�X�V
	void Update();
	//�J��
	void Uninit();
	//�`��
	void Draw();
	void DrawShade();
	//���W�擾
	D3DXVECTOR3 GetPosition(void)
	{
		return m_pos;
	}
	
	//���W�ݒ�
	void SetPosition(D3DXVECTOR3 pos)
	{
		m_pos = pos;	
	}
	//��]�擾
	D3DXVECTOR3 GetRotate(void)
	{
		return m_rot;
	}
	//��]�ݒ�
	void SetRotate(D3DXVECTOR3 rot)
	{
		m_rot = rot;	
	}
	//���[�e�B���e�B
	DWORD Float2DWORD( float val ) { return *((DWORD*)&val); }
};
#endif