//=============================================================================
//
// �X�R�A���� [CScore.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
#ifndef __CSCORE_H__
#define __CSCORE_H__

//�w�b�_�[
#include "main.h"
#include "CScene.h"
#include "CNumber.h"

//�}�N����`
#define SCORE_DIGIT	(5)

//�O���錾
class CRender;

//�N���X��`
class CScore:public CScene
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
	static int				m_Score;
	static CNumber*			m_pNumber[SCORE_DIGIT];
	int						m_Cnt;
public:
	CScore(int nPriority = 3):CScene(nPriority,OBJTYPE_2D){m_Score = 0;}
	virtual ~CScore(){}

	static int GetScore()
	{
		return m_Score;
	}

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
	//�l�ύX
	static void ChangeScore(int nValue);
	
	//����
	static CScore* Create(CRender* pRender,D3DXVECTOR3 pos);
};

#endif