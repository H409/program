//=============================================================================
// �V�F�[�_�[�쐬���� [CSkyBox.h]
// Author : MASAHIRO YAMAGUCHI
// �X�J�C�{�b�N�X��������
//=============================================================================

//���d��`�h�~
#ifndef __CSKYBOX_H__
#define __CSKYBOX_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"

//�}�N����`
#define CUBE_FACE			(6)
#define CUBEMAP_DIMENSION	(800)
#define CUBE_VERTEX			(4)

//�O���錾
class CRender;

class CSkyBox:public CScene
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
	CSkyBox*					m_pSceneX;
	char*						m_pTexName;
	D3DXVECTOR3					m_Vertex;
	LPD3DXEFFECT				m_pEffect;
	IDirect3DTexture9*			m_pDepthTexture;
	CRender*					m_pRender;
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pD3DTex[CUBE_FACE];				// �e�N�X�`���ւ̃|�C���^

	LPDIRECT3DCUBETEXTURE9	m_pCubeEnvMap; //�f�J�[���Ƃ��ẴL���[�u�e�N�X�`��
	LPDIRECT3DCUBETEXTURE9	m_pCubeRender; //���̃W�I���g���̃����_�����O�^�[�Q�b�g�ƂȂ�L���[�u�e�N�X�`��
	LPDIRECT3DSURFACE9		m_pBackBuffer;
	LPDIRECT3DSURFACE9		m_pZBuffer;
	LPDIRECT3DSURFACE9		m_pCubeZBuffer[CUBE_FACE];

	//�\��
	TLVERTEX				m_Ver1[CUBE_VERTEX];
	TLVERTEX				m_Ver2[CUBE_VERTEX];
	TLVERTEX				m_Ver3[CUBE_VERTEX];
	TLVERTEX				m_Ver4[CUBE_VERTEX];
	TLVERTEX				m_Ver5[CUBE_VERTEX];
	TLVERTEX				m_Ver6[CUBE_VERTEX];
public:
	CSkyBox(int nPriority = 3,OBJTYPE objtype = OBJTYPE_X):CScene(nPriority,objtype){m_pTexName = NULL;}
	virtual ~CSkyBox()
	{
		
	}

	//������
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename);

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
	static CSkyBox* Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename);
};

#endif