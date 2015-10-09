//=============================================================================
//
// シーン遷移処理 [CTutorial.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CTutorial.h"
#include "CFade.h"
#include "CDebugProc.h"
#include "CInputKeyboard.h"
#include "CManager.h"
#include "CScene2D.h"
#include "CSound.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "Joy.h"

//静的メンバ変数初期化
CTutorial* CTutorial::m_instance = NULL;

//インスタンス生成
CTutorial* CTutorial::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CTutorial();
	}
	return m_instance;
}
//インスタンス解放
void CTutorial::freeInstance()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}
//初期化
bool CTutorial::Init(void *lpArgs)
{
	m_pRender = CManager::GetRender();

	if(m_pPushLogo == NULL)
	{
		m_pPushLogo = new Clogo();
	}
	
	CScene2D::Create(m_pRender,D3DXVECTOR3(400,300,0),"data\\Texture\\sucreen3.bmp",OBJTYPE_2D);
	CScene2D::Create(m_pRender,D3DXVECTOR3(400,300,0),"data\\Texture\\Tutorial.png",OBJTYPE_2D);
	CScene2D::Create(m_pRender,D3DXVECTOR3(50,550,0),"data\\Texture\\jyujika.png",OBJTYPE_2DGIM);
	CScene2D::Create(m_pRender,D3DXVECTOR3(750,550,0),"data\\Texture\\jyujika1.png",OBJTYPE_2DGIM);
	m_pPushLogo->Init(m_pRender,D3DXVECTOR3(400,480,0),200,50,"data\\Texture\\push.png");	
//	CPlayer::Create(m_pRender,D3DXVECTOR3(250,0,-250));

	m_initManager = true;
	//サウンド再生
	CSound::getInstance()->PlaySound(SOUND_LABEL_BGM003);
	//使用したデータを初期化してメインシーンへ
	this->m_PhaseInfo.dwScene = CPhase::PHASE_MAIN;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;	

	return true;
}

//更新
bool CTutorial::Update(void* lpArgs)
{

	CFade* pFade = CFade::getinstance();

	m_pPushLogo->Update();

	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_RETURN) || CJoySystem::getInstance()->GetJoyBtnPush(JOY_BTN1))
	{
		if(pFade->GetFadeMode() == FADE_NONE)
		{
			//サウンド再生
			CSound::getInstance()->PlaySound(SOUND_LABEL_SE_YES);
			pFade->SetFadeMode(FADE_OUT);
		}
			
	}
	if(pFade->GetFadeMode() == FADE_OUT_FINISH)
	{
		
		
		pFade->SetFadeMode(FADE_IN);
		this->m_PhaseInfo.dwScene = CPhase::PHASE_RELEASE;
		this->m_PhaseInfo.dwSubScene = 0;
		this->m_PhaseInfo.nCount = 0;
	}	
	//更新
	CScene::UpdateAll();

	CDebugProc::Print("タイトルメイン\n");
	return true;
}

//開放
bool CTutorial::Release(void* lpArgs)
{
	//サウンドを止める
	CSound::getInstance()->StopSound(SOUND_LABEL_BGM003);

	m_pPushLogo->Uninit();
	SAFE_DELETE(m_pPushLogo);

	//フェーズ中使用したものだけ開放
	CScene::FreePhase();
	if(lpArgs != NULL)
	{
		*((MODE *)lpArgs) = MODE_GAME;
	}
	m_initManager = false;
	
	//使用したデータを初期化して初期化シーンへ
	this->m_PhaseInfo.dwScene = CPhase::PHASE_INIT;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;

	return true;
}
//描画
bool CTutorial::Draw(void* lpArgs)
{
	//描画
	if(m_initManager)
	{
		
		CScene::DrawAll();
		if(m_pPushLogo != NULL)
		{
			m_pPushLogo->Draw();
		}
	}
	return true;
}
bool CTutorial::DrawShade(void* lpArgs)
{
	if(m_initManager)
	{
		//描画
		CScene::DrawShadeAll();
	}
	return true;
}