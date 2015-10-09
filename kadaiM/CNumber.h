//=============================================================================
//
// ���l����������� [CNumber.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
#ifndef __CNUMBER_H__
#define __CNUMBER_H__

//�w�b�_�[
#include "main.h"
#include "CScene.h"
//�O���錾
class CRender;

//�N���X��`
class CNumber
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// �e�N�X�`�����ǂݍ��ݗp
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// ���_�o�b�t�@
	D3DXVECTOR3				m_pos;					// ���W
	D3DXVECTOR3				m_rot;					// ��]
	float					m_fLength;				// ���S���璸�_�܂ł̒���
	float					m_fAngle;				// ���S���璸�_�ւ̊p�x
	D3DXVECTOR2				m_Tex;					// �e�N�X�`�����W
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	int						m_Num;
public:
	CNumber(){}
	virtual ~CNumber(){}

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

	//����
	static CNumber* Create(CRender* pRender,const D3DXVECTOR3 pos);

	//���l�ύX
	void ChengeNumber(int Value);
};

#endif