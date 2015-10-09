//=============================================================================
//
// �X�R�A���� [CTimer.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//�w�b�_�[�C���N���[�h
#include "CTimer.h"
#include "CRender.h"

#define TIME_CNT	(60)

int CTimer::m_Time = 100;
int CTimer::m_Cnt = 0;
//����
CTimer* CTimer::Create(CRender* pRender,D3DXVECTOR3 pos)
{
	CTimer* pTime = new CTimer(5);

	pTime->Init(pRender);

	pTime->SetPosition(pos);

	return pTime;
}

//������
HRESULT CTimer::Init(CRender* pRender)
{
	m_pD3DDevice = pRender->getDevice();
	m_Time = 0;

	//�i���o�[����
	for(int i = 0;i < TIMER_DIGIT;i++)
	{
		m_pNumber[i] = CNumber::Create(pRender,D3DXVECTOR3(static_cast<float>(i*50)+350,+25,0));
	}

	m_Cnt = 0;
	m_Time = 100;
	ChangeTime(0);
	return S_OK;
}
//�X�V
void CTimer::Update(void)
{
	/*
	for(int i = 0;i < SCORE_DIGIT;i++)
	{
		m_pNumber[i]->Update();
	}
	*/
	m_Cnt++;

	if(m_Cnt >= TIME_CNT)
	{
		m_Cnt = 0;
		//�^�C���}�C�i�X
		ChangeTime(-1);
	}
	
}
//�J��
void CTimer::Uninit(void)
{
	for(int i = 0;i < TIMER_DIGIT;i++)
	{
		m_pNumber[i]->Uninit();
		SAFE_DELETE(m_pNumber[i]);
	}
	m_Cnt = 0;
	Release();
}

//�`��
void CTimer::Draw(void)
{
	for(int i = 0;i < TIMER_DIGIT;i++)
	{
		m_pNumber[i]->Draw();
	}
}
void CTimer::DrawShade(void)
{
	for(int i = 0;i < TIMER_DIGIT;i++)
	{
		m_pNumber[i]->DrawShade();
	}
}
//�X�R�A�l�ύX
void CTimer::ChangeTime(int nValue)
{
	m_Time+=nValue;
	
	if(m_Time >= 99999)
	{
		m_Time = 99999;
	}
	if(m_Time <= 0)
	{
		m_Time = 0;
	}
	int nNumber[TIMER_DIGIT] = {0};

	for(int i = 0,j = TIMER_DIGIT-1;i < TIMER_DIGIT;i++,j--)
	{
		nNumber[j] = (m_Time/(int)pow((double)10,(double)i))%(int)10;
		
	}
	for(int i = 0;i < TIMER_DIGIT;i++)
	{
		m_pNumber[i]->ChengeNumber(nNumber[i]);
		m_pNumber[i]->Update();
	}
}

//eof