#ifndef __CSCENE3D_H__
#define __CSCENE3D_H__

//�w�b�_�[
#include "CScene.h"
#include "main.h"

//�O���錾
class CRender;

class CScene3D:public CScene
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// �e�N�X�`�����ǂݍ��ݗp
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// ���_�o�b�t�@
	D3DXVECTOR3				m_pos;					// ���W
	D3DXVECTOR3				m_rot;					// ��]
	D3DXVECTOR3				m_scl;					// �g�k
	D3DXMATRIX				m_mtxWorld;				// ���[���h�}�g���b�N�X
	float					m_fLength;				// ���S���璸�_�܂ł̒���
	float					m_fAngle;				// ���S���璸�_�ւ̊p�x
	LPD3DXEFFECT			m_pEffect;
	LPDIRECT3DDEVICE9       m_pD3DDevice;
public:
	CScene3D(int nPriority = 3):CScene(nPriority){}
	virtual ~CScene3D(){}

	//������
	HRESULT Init(CRender* pRender);
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
	//���[���h���W�擾
	D3DXMATRIX GetWorldMatrix(void)
	{
		return m_mtxWorld;
	}
	static CScene3D* Create(CRender* pRender,D3DXVECTOR3 pos);
};

float GetHeight(D3DXVECTOR3 pos,D3DXVECTOR3* pNormal);
float GetHeightPolygon(D3DXVECTOR3& p0,D3DXVECTOR3& p1,D3DXVECTOR3& p2,D3DXVECTOR3& pos,D3DXVECTOR3* pNormal);
#endif