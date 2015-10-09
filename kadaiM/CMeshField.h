//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//���d��`�h�~
#ifndef __MESHFIELD_H__
#define __MESHFIELD_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"

//�O���錾
class CRender;

//�N���X��`
class CMeshField:public CScene
{
private:
	//�f�o�C�X
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	LPDIRECT3DTEXTURE9		m_pD3DTex;							// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pD3DIndexBuff;					// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int						m_nNumVertexIndex;					// ���_�̑��C���f�b�N�X��
	D3DXMATRIX				m_mtxWorld;							// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_pos;								// �ʒu
	D3DXVECTOR3				m_rot;								// ����
	D3DXVECTOR3				m_scl;								// �g�k

	int						m_nNumBlockX, m_nNumBlockZ;			// �u���b�N��
	int						m_nNumVertex;						// �����_��
	int						m_nNumPolygon;						// ���|���S����
	float					m_fSizeBlockX, m_fSizeBlockZ;		// �u���b�N�T�C�Y
	static D3DXVECTOR3		m_Vertex[4];
	float*					m_pfheightMap;
	D3DXVECTOR3*			m_pnorBuff;
	WORD*					m_pIndex;
	VERTEX_3D*				m_pVtx;
public:

	CMeshField(int nPriority = 3):CScene(nPriority){}
	virtual ~CMeshField(){}

	//������
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 pos,D3DXVECTOR3 rot,char *pTexPath);
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
	D3DXMATRIX GetWorldMatrix(void)
	{
		return m_mtxWorld;
	}
	static CMeshField* Create(CRender* pRender,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,char* pTexFileName);

	static D3DXVECTOR3 GetVertex(int nIndex);

	bool FindNormalsOnPoly(int dwPolyIndex,D3DXVECTOR3* pvNormals );
};

#endif