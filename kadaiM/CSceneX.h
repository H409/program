#ifndef __CSCENEX_H__
#define __CSCENEX_H__

//�w�b�_�[
#include "main.h"
#include "CScene.h"
#include "CSkinAnimetion.h"

//�O���錾
class CRender;
class SKIN_MESH;

//�\���̒�`
typedef struct 
{
	D3DXVECTOR3 vecCenter;
	float fRadius;
}SPHERE,*LPSPHERE;

//�N���X��`
class CSceneX:public CScene
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
	CSceneX*					m_pSceneX;
	char*						m_pTexName;
	LPD3DXFRAME					m_pFrameRoot;			//�X�L�����b�V��
    LPD3DXANIMATIONCONTROLLER	m_pAnimController;		//�X�L�����b�V��
	D3DXVECTOR3					m_Vertex;
	LPD3DXEFFECT				m_pEffect;
	IDirect3DTexture9*			m_pDepthTexture;
	CRender*					m_pRender;
	SKIN_MESH*					m_SkinMesh;
	SPHERE						m_Sphere;				//���̗p
	bool						m_bSphere;				//���̗p�\���t���O
	bool						m_createSphere;			//���̍쐬�p�t���O
	bool						m_LifeFlag;
public:
	CSceneX(int nPriority = 3,OBJTYPE objtype = OBJTYPE_X):CScene(nPriority,objtype){m_pTexName = NULL;}
	virtual ~CSceneX()
	{
		
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
	//�g�k�擾
	D3DXVECTOR3 GetScale(void)
	{
		return m_scl;
	}
	//�g�k�ݒ�
	void SetScale(D3DXVECTOR3 scl)
	{
		m_scl = scl;
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
	//���擾
	SPHERE GetSphere(void)
	{
		return m_Sphere;
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
	static CSceneX* Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename);
};

#endif