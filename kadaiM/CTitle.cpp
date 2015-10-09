//=============================================================================
//
// シーン遷移処理 [CTitle.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CTitle.h"
#include "CFade.h"
#include "CDebugProc.h"
#include "CInputKeyboard.h"
#include "CManager.h"
#include "CScene2D.h"
#include "CSound.h"
#include "CSceneX.h"
#include "CCamera.h"
#include "Clogo.h"
#include "CModel.h"
#include "CPaticle.h"
#include "Joy.h"
#include "CMeshCylinder.h"

//静的メンバ変数初期化
CTitle* CTitle::m_instance = NULL;

//インスタンス生成
CTitle* CTitle::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CTitle();
	}
	return m_instance;
}
//インスタンス解放
void CTitle::freeInstance()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}
//初期化
bool CTitle::Init(void *lpArgs)
{
	m_pRender = CManager::GetRender();
	
	if(m_pPushLogo == NULL)
	{
		m_pPushLogo = new Clogo();
	}
	//カメラの初期化
	CCamera::getInstance()->TitleInit(m_pRender);

	CMeshCylinder::Create(m_pRender,D3DXVECTOR3(250,0,-250),D3DXVECTOR3(0,0,0));

	CPaticle::Create(m_pRender,D3DXVECTOR3(0,0,-50),"data\\Texture\\spark.bmp");

	CScene2D::Create(m_pRender,D3DXVECTOR3(400,80,0),300,100,"data\\Texture\\titlelogo.png",OBJTYPE_2D);
	CModel::Create(m_pRender,D3DXVECTOR3(0,0,-10),"data\\Model\\tank.x",NULL);
	m_pPushLogo->Init(m_pRender,D3DXVECTOR3(400,550,0),200,50,"data\\Texture\\push.png");
	CScene2D::Create(m_pRender,D3DXVECTOR3(50,550,0),"data\\Texture\\jyujika.png",OBJTYPE_2DGIM);
	CScene2D::Create(m_pRender,D3DXVECTOR3(750,550,0),"data\\Texture\\jyujika1.png",OBJTYPE_2DGIM);
	
	m_initManager = true;
	//サウンド再生
	CSound::getInstance()->PlaySound(SOUND_LABEL_BGM000);
	//使用したデータを初期化してメインシーンへ
	this->m_PhaseInfo.dwScene = CPhase::PHASE_MAIN;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;	

	return true;
}

//更新
bool CTitle::Update(void* lpArgs)
{

//	CCamera::getInstance()->TitleUpdate();

	m_pPushLogo->Update();

	CFade* pFade = CFade::getinstance();

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
bool CTitle::Release(void* lpArgs)
{
	//サウンドを止める
	CSound::getInstance()->StopSound(SOUND_LABEL_BGM000);

	m_pPushLogo->Uninit();
	SAFE_DELETE(m_pPushLogo);

	//フェーズ中使用したものだけ開放
	CScene::FreePhase();
	if(lpArgs != NULL)
	{
		*((MODE *)lpArgs) = MODE_TUTOLIAL;
	}
	m_initManager = false;
	
	//使用したデータを初期化して初期化シーンへ
	this->m_PhaseInfo.dwScene = CPhase::PHASE_INIT;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;

	return true;
}
//描画
bool CTitle::Draw(void* lpArgs)
{
	//描画
	if(m_initManager)
	{
		//カメラ設定
		CCamera::getInstance()->SetCamera();



		CScene::DrawAll();
		if(m_pPushLogo != NULL)
		{
			m_pPushLogo->Draw();
		}
	}
	return true;
}
bool CTitle::DrawShade(void* lpArgs)
{
	if(m_initManager)
	{
		//描画
		CScene::DrawShadeAll();
	}
	return true;
}