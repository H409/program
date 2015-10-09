//=============================================================================
//
// �X�R�A���� [CScore.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CScore.h"
#include "CRender.h"

int CScore::m_Score = 0;
CNumber* CScore::m_pNumber[SCORE_DIGIT] = {NULL};
//����
CScore* CScore::Create(CRender* pRender,D3DXVECTOR3 pos)
{
	CScore* pScore = new CScore(5);

	pScore->Init(pRender);

	pScore->SetPosition(pos);

	return pScore;
}

//������
HRESULT CScore::Init(CRender* pRender)
{
	m_pD3DDevice = pRender->getDevice();
	m_Score = 0;

	//�i���o�[����
	for(int i = 0;i < SCORE_DIGIT;i++)
	{
		m_pNumber[i] = CNumber::Create(pRender,D3DXVECTOR3(static_cast<float>(i*50)+25,+25,0));
	}
	ChangeScore(0);
	m_Cnt = 0;
	return S_OK;
}
//�X�V
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
//�J��
void CScore::Uninit(void)
{
	for(int i = 0;i < SCORE_DIGIT;i++)
	{
		m_pNumber[i]->Uninit();
		SAFE_DELETE(m_pNumber[i]);	
	}
	
	Release();
}

//�`��
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
//�X�R�A�l�ύX
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