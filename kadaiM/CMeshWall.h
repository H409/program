//=============================================================================
//
// ���b�V���ǂ̏��� [meshWall.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//���d��`�h�~
#ifndef __MESHWALL_H__
#define __MESHWALL_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"

//�O���錾
class CRender;

//�N���X��`
class CMeshWall:public CScene
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

	int						m_nNumBlockX, m_nNumBlockY;			// �u���b�N��
	int						m_nNumVertex;						// �����_��
	int						m_nNumPolygon;						// ���|���S����
	float					m_fSizeBlockX, m_fSizeBlockY;		// �u���b�N�T�C�Y
	D3DXVECTOR3				m_Vertex;						//
	static D3DXVECTOR3				m_rotVer[4];
	static	int				m_nCreateCnt;
public:

	CMeshWall(int nPriority = 3):CScene(nPriority){m_nCreateCnt++;}
	virtual ~CMeshWall(){}

	//������
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY,D3DXVECTOR3 pos,D3DXVECTOR3 rot,char *pTexPath);
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
	static CMeshWall* Create(CRender* pRender,D3DXVECTOR3 pos,D3DXVECTOR3 rot);

	D3DXVECTOR3 GetVertex();
};

#endif