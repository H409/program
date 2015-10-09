//=============================================================================
//
// スコア処理 [CScore.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CScore.h"
#include "CRender.h"

int CScore::m_Score = 0;
CNumber* CScore::m_pNumber[SCORE_DIGIT] = {NULL};
//生成
CScore* CScore::Create(CRender* pRender,D3DXVECTOR3 pos)
{
	CScore* pScore = new CScore(5);

	pScore->Init(pRender);

	pScore->SetPosition(pos);

	return pScore;
}

//初期化
HRESULT CScore::Init(CRender* pRender)
{
	m_pD3DDevice = pRender->getDevice();
	m_Score = 0;

	//ナンバー生成
	for(int i = 0;i < SCORE_DIGIT;i++)
	{
		m_pNumber[i] = CNumber::Create(pRender,D3DXVECTOR3(static_cast<float>(i*50)+25,+25,0));
	}
	ChangeScore(0);
	m_Cnt = 0;
	return S_OK;
}
//更新
void CScore::Update(void)
{
	/*
	for(int i = 0;i < SCORE_DIGIT;i++)
	{
		m_pNumber[i]->Update();
	}
	*/
	m_Cnt++;

	if(m_Cnt >= 100)
	{
		m_Cnt = 0;
			
	}
	
}
//開放
void CScore::Uninit(void)
{
	for(int i = 0;i < SCORE_DIGIT;i++)
	{
		m_pNumber[i]->Uninit();
		SAFE_DELETE(m_pNumber[i]);	
	}
	
	Release();
}

//描画
void CScore::Draw(void)
{
	for(int i = 0;i < SCORE_DIGIT;i++)
	{
		m_pNumber[i]->Draw();
	}
}
void CScore::DrawShade()
{
	for(int i = 0;i < SCORE_DIGIT;i++)
	{
		m_pNumber[i]->DrawShade();
	}
}
//スコア値変更
void CScore::ChangeScore(int nValue)
{
	m_Score+=nValue;
	
	if(m_Score >= 99999)
	{
		m_Score = 99999;
	}
	if(m_Score <= 0)
	{
		m_Score = 0;
	}
	int nNumber[SCORE_DIGIT] = {0};

	for(int i = 0,j = SCORE_DIGIT-1;i < SCORE_DIGIT;i++,j--)
	{
		nNumber[j] = (m_Score/(int)pow((double)10,(double)i))%(int)10;
		
	}
	for(int i = 0;i < SCORE_DIGIT;i++)
	{
		m_pNumber[i]->ChengeNumber(nNumber[i]);
		m_pNumber[i]->Update();
	}
}

//eof