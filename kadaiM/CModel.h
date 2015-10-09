//���d��`�h�~
#ifndef __CMODEL_H__
#define __CMODEL_H__



//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"


//�N���X��`
class CModel:public CScene
{
private:
	D3DXVECTOR3					m_pos;					// ���W
	D3DXVECTOR3					m_rot;					// ��]
	D3DXVECTOR3					m_scl;					// �g�k
	D3DXMATRIX					m_mtxWorld;				// ���[���h�}�g���b�N�X
	LPD3DXMESH					m_pD3DXMeshModel;		// ���b�V��
	LPD3DXBUFFER				m_pD3DXBuffMatModel;	// �}�e���A��
	LPDIRECT3DTEXTURE9*			m_pD3DTextureModel;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DDEVICE9			m_pD3DDevice;			// �f�o�C�X
	DWORD						m_nNumMatModel;			//
	bool						m_initManager;
	D3DMATERIAL9*				m_pMeshMaterials;
	char*						m_pTexName;
	LPD3DXFRAME					m_pFrameRoot;			//�X�L�����b�V��
    LPD3DXANIMATIONCONTROLLER	m_pAnimController;		//�X�L�����b�V��
	D3DXVECTOR3					m_Vertex;
	LPD3DXEFFECT				m_pEffect;
	IDirect3DTexture9*			m_pDepthTexture;
	CRender*					m_pRender;
public:
	CModel(int nPriority = 3,OBJTYPE objtype = OBJTYPE_X):CScene(nPriority,objtype){m_pTexName = NULL;}
	virtual ~CModel()
	{
		
	}

	//������
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere);
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
	static CModel* Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename);
};
#endif