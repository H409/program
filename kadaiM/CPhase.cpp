//=============================================================================
//
// 各フェーズ処理 [CPhase.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CPhase.h"

//静的メンバ変数初期化
const BYTE CPhase::PHASE_INIT = 0;
const BYTE CPhase::PHASE_MAIN = 1;
const BYTE CPhase::PHASE_RELEASE = 2;

//コンストラクタ
CPhase::CPhase()
{
	memset(&this->m_PhaseInfo,0,sizeof(PHASEINFO));
	this->m_lpPhase[0] = &CPhase::Init;
	this->m_lpPhase[1] = &CPhase::Update;
	this->m_lpPhase[2] = &CPhase::Release;
}

//デストラクタ
CPhase::~CPhase()
{
	
	memset(&this->m_PhaseInfo,0,sizeof(PHASEINFO));
	this->m_PhaseInfo.dwScene = 0;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;
	this->m_lpPhase[0] = NULL;
	this->m_lpPhase[1] = NULL;
	this->m_lpPhase[2] = NULL;

}
//各シーン呼び出し
bool CPhase::Phase(void *lpArgs)
{
	
	return (this->* m_lpPhase[this->m_PhaseInfo.dwScene])(lpArgs);

}




