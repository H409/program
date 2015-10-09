//=============================================================================
//
// �X�R�A���� [CTimer.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//���d��`�h�~
#ifndef __CTIMER_H__
#define __CTIMER_H__

//�w�b�_�[
#include "main.h"
#include "CScene.h"
#include "CNumber.h"

//�}�N����`
#define TIMER_DIGIT	(3)

//�O���錾
class CRender;

//�N���X��`
class CTimer:public CScene
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
	static int				m_Time;
	CNumber*				m_pNumber[TIMER_DIGIT];
	static int				m_Cnt;
public:
	CTimer(int nPriority = 3):CScene(nPriority){m_Time = 0;}
	virtual ~CTimer()
	{
		//for(int i = 0;i < TIMER_DIGIT;i++)
		//{
		//	m_pNumber[i]->Uninit();
		//	SAFE_DELETE(m_pNumber[i]);
		//}

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
	void ChangeTime(int nValue);
	
	//����
	static CTimer* Create(CRender* pRender,D3DXVECTOR3 pos);
};
#endif
//eof