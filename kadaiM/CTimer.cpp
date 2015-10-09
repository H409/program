//=============================================================================
//
// スコア処理 [CTimer.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//ヘッダーインクルード
#include "CTimer.h"
#include "CRender.h"

#define TIME_CNT	(60)

int CTimer::m_Time = 100;
int CTimer::m_Cnt = 0;
//生成
CTimer* CTimer::Create(CRender* pRender,D3DXVECTOR3 pos)
{
	CTimer* pTime = new CTimer(5);

	pTime->Init(pRender);

	pTime->SetPosition(pos);

	return pTime;
}

//初期化
HRESULT CTimer::Init(CRender* pRender)
{
	m_pD3DDevice = pRender->getDevice();
	m_Time = 0;

	//ナンバー生成
	for(int i = 0;i < TIMER_DIGIT;i++)
	{
		m_pNumber[i] = CNumber::Create(pRender,D3DXVECTOR3(static_cast<float>(i*50)+350,+25,0));
	}

	m_Cnt = 0;
	m_Time = 100;
	ChangeTime(0);
	return S_OK;
}
//更新
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
		//タイムマイナス
		ChangeTime(-1);
	}
	
}
//開放
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

//描画
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
//スコア値変更
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