//=============================================================================
//
// �ۉe���� [CShadow.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//���d��`�h�~
#ifndef __CSHADOW_H__
#define __CSHADOW_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"

//�O���錾

//�N���X��`
class CShadow:public CScene
{
private:
	D3DXVECTOR3					m_pos;					// ���W
	D3DXVECTOR3					m_rot;					// ��]
	D3DXVECTOR3					m_scl;					// �g�k
	D3DXMATRIX					m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXMATRIX					m_mtxRot;
	LPD3DXMESH					m_pD3DXMeshModel;		// ���b�V��
	LPD3DXMESH					m_pSphereMesh;			// ����
	LPD3DXBUFFER				m_pD3DXBuffMatModel;	// �}�e���A��
	LPDIRECT3DTEXTURE9*			m_pD3DTextureModel;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DDEVICE9			m_pD3DDevice;			// �f�o�C�X
	DWORD						m_nNumMatModel;			//
	bool						m_initManager;
	D3DMATERIAL9*				m_pMeshMaterials;
	D3DMATERIAL9*				m_pSphereMeshMaterials;	//�}�e���A��
	CShadow*					m_pParent;				//�e
	char*						m_pTexName;
	LPD3DXFRAME					m_pFrameRoot;			//�X�L�����b�V��
    LPD3DXANIMATIONCONTROLLER	m_pAnimController;		//�X�L�����b�V��
	D3DXVECTOR3					m_Vertex;
	LPD3DXEFFECT				m_pEffect;
	IDirect3DTexture9*			m_pDepthTexture;
	CRender*					m_pRender;
	bool						m_bSphere;				//���̗p�\���t���O
	bool						m_createSphere;			//���̍쐬�p�t���O
	bool						m_LifeFlag;
	D3DSURFACE_DESC				m_desc;
public:
	CShadow(int nPriority = 2,OBJTYPE objtype = OBJTYPE_X):CScene(nPriority,objtype){m_pTexName = NULL;}
	virtual ~CShadow()
	{
		//�G�t�F�N�g�t�@�C�����
		SAFE_RELEASE( m_pEffect );

	}

	//������
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere);
	HRESULT InitAnim(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere);
	HRESULT	InitSphere(void);
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
	//���[���h�}�g���b�N�X�擾
	D3DXMATRIX GetWorldMatrix()
	{
		return m_mtxWorld;
	}
	//���[���h�}�g���b�N�X�ݒ�
	void SetWorldMatrix(D3DXMATRIX mat)
	{
		m_mtxWorld = mat;
	}
	void SetRotMatrix(D3DXMATRIX mat)
	{
		m_mtxRot = mat;
	}
	//�t���O�ݒ�
	void SetBSphere(bool flag)
	{
		m_bSphere = flag;
	}
	//�t���O�擾
	bool GetBSphere(void)
	{
		return m_bSphere;
	}
	bool GetLifeFlag(void)
	{
		return m_LifeFlag;
	}
	void SetLifeFlag(bool bflag)
	{
		m_LifeFlag = bflag;
	}
	void SetRotNormalize(void)
	{
		if( m_rot.y < -D3DX_PI )
		{
			m_rot.y += 2 * D3DX_PI;
		}
		else if( m_rot.y > D3DX_PI )
		{
			m_rot.y -= 2 * D3DX_PI;
		}
		if( m_rot.x < -D3DX_PI )
		{
			m_rot.x += 2 * D3DX_PI;
		}
		else if( m_rot.x > D3DX_PI )
		{
			m_rot.x -= 2 * D3DX_PI;
		}
		if( m_rot.z < -D3DX_PI )
		{
			m_rot.z += 2 * D3DX_PI;
		}
		else if( m_rot.z > D3DX_PI )
		{
			m_rot.z -= 2 * D3DX_PI;
		}
	}
	//�e�擾
	CShadow*	GetParent(void)
	{
		return m_pParent;
	}
	//�e�ݒ�
	void SetParent(CShadow* pScene)
	{
		
		m_pParent = pScene;
	}
	LPD3DXFRAME* GetFrame(void)
	{
		return &m_pFrameRoot;
	}

	LPD3DXANIMATIONCONTROLLER* GetController(void)
	{
		return &m_pAnimController;
	}

	D3DXVECTOR3* FindVertex(DWORD dwIndex);

	void CreateBBox(D3DXVECTOR3* pvecMax,D3DXVECTOR3* pvecMin);
	static CShadow* Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename);
};


#endif


//eof