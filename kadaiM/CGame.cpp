//=============================================================================
//
// シーン遷移処理 [Game.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CGame.h"
#include "CFade.h"
#include "CDebugProc.h"
#include "CInputKeyboard.h"
#include "CManager.h"
#include "CRender.h"
#include "CScene.h"
#include "CScene2D.h"
#include "CScene3D.h"
#include "CCamera.h"
#include "CLight.h"
#include "CSceneX.h"
#include "CSceneBillboard.h"
#include "CInputKeyboard.h"
#include "CDebugProc.h"
#include "CEnemy.h"
#include "CMeshField.h"
#include "CMeshWall.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CMeshCylinder.h"
#include "CMeshDome.h"
#include "CColision.h"
#include "CPaticle.h"
#include "CScore.h"
#include "CTimer.h"
#include "yuka.h"
#include "CPause.h"
#include "CSound.h"
#include "Clogo.h"
#include "CEnding.h"
#include "CSkyBox.h"
#include "Joy.h"

//マクロ定義
#define WALL_TO_FIELD	(250)

//静的メンバ変数初期化
CGame* CGame::m_instance = NULL;
CPlayer* CGame::m_pPlayer = NULL;
CEnemy* CGame::m_pEnemy[ENEMY_NUM_MAX] = {NULL};
CPlayerLife* CGame::m_pPlayLife[PLAYER_LIFE_MAX] = {NULL};
bool CGame::m_pause = false;
bool CGame::m_Cler = false;
bool CGame::m_Over = false;

bool dbflag = false;

//インスタンス生成
CGame* CGame::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CGame();
	}
	return m_instance;
}
//インスタンス解放
void CGame::freeInstance()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}
//初期化
bool CGame::Init(void *lpArgs)
{

	m_startCnt = 0;

	m_pRender = CManager::GetRender();

	//カメラの初期化
	CCamera::getInstance()->Init(m_pRender);
/*
	if(m_plogo == NULL)
	{
		m_plogo = new Clogo();
	}
	if(m_pclaer == NULL)
	{
		m_pclaer = new Clogo();
	}
	if(m_pover == NULL)
	{
		m_pover = new Clogo();
	}
*/
	//プレイヤー
	m_pPlayer = CPlayer::Create(m_pRender,D3DXVECTOR3(250,0,-350));
//	CScene2D::Create(m_pRender,D3DXVECTOR3(100,100,0),"kaka",OBJTYPE_2D);
	
	//納屋
//	CSceneX::Create(m_pRender,D3DXVECTOR3(100,0,-200),"data\\Model\\naya.x","data\\Texture\\naya.jpg");
	//ジープ
//	CSceneX::Create(m_pRender,D3DXVECTOR3(200,0,-250),"data\\Model\\jeep.x","data\\Texture\\jeep.png");
	//植物
//	CSceneX::Create(m_pRender,D3DXVECTOR3(150,0,-200),"data\\Model\\plant01.x",NULL);
//	CSceneX::Create(m_pRender,D3DXVECTOR3(200,0,-200),"data\\Model\\plant02.x",NULL);
//	CSceneX::Create(m_pRender,D3DXVECTOR3(250,0,-200),"data\\Model\\plant03.x",NULL);
//	CSceneX::Create(m_pRender,D3DXVECTOR3(300,0,-200),"data\\Model\\plant04.x",NULL);
//	CSceneX::Create(m_pRender,D3DXVECTOR3(350,0,-200),"data\\Model\\head.x",NULL);
	

	//フィールド
	CMeshField::Create(m_pRender,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),10,10,50.0f,50.0f,"data\\Texture\\field005.png");
	//壁
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(1).x-WALL_TO_FIELD,0,CMeshField::GetVertex(1).z),D3DXVECTOR3(0,0,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(2).x+WALL_TO_FIELD,0,CMeshField::GetVertex(2).z),D3DXVECTOR3(0,D3DX_PI,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(3).x,0,CMeshField::GetVertex(3).z+WALL_TO_FIELD),D3DXVECTOR3(0,D3DX_PI/2.0f,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(0).x,0,CMeshField::GetVertex(0).z-WALL_TO_FIELD),D3DXVECTOR3(0,D3DX_PI/-2.0f,0));

	//ドーム
	//CMeshDome::Create(m_pRender,D3DXVECTOR3(250,0,-250),D3DXVECTOR3(0,0,0));
	CSkyBox::Create(m_pRender,D3DXVECTOR3(250,0,-250),"data\\Model\\cube.x","data\\Texture\\sky005.jpg");
	//円柱
	//CMeshCylinder::Create(m_pRender,D3DXVECTOR3(250,0,-250),D3DXVECTOR3(0,0,0));
	//スコア
//	CScore::Create(m_pRender,D3DXVECTOR3(0,0,0));
	//時間
//	CTimer::Create(m_pRender,D3DXVECTOR3(0,0,0));
	
	//GetRady文字表示
//	m_plogo->Init(m_pRender,D3DXVECTOR3(400,300,0),200,100,"data\\Texture\\ready.png");
//	m_pclaer->Init(m_pRender,D3DXVECTOR3(400,300,0),200,100,"data\\Texture\\clear.png");
//	m_pover->Init(m_pRender,D3DXVECTOR3(400,300,0),200,100,"data\\Texture\\gameover.png");
	
	
	//プレイヤー残機表示
//	m_pPlayLife[0] = CPlayerLife::Create(m_pRender,D3DXVECTOR3(25,550,0));
//	m_pPlayLife[1] = CPlayerLife::Create(m_pRender,D3DXVECTOR3(75,550,0));
//	m_pPlayLife[2] = CPlayerLife::Create(m_pRender,D3DXVECTOR3(125,550,0));

	//敵
//	m_pEnemy[0] = CEnemy::Create(m_pRender,D3DXVECTOR3(300,0,-250),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[1] = CEnemy::Create(m_pRender,D3DXVECTOR3(300,0,-150),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[2] = CEnemy::Create(m_pRender,D3DXVECTOR3(200,0,-150),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[3] = CEnemy::Create(m_pRender,D3DXVECTOR3(100,0,-150),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[4] = CEnemy::Create(m_pRender,D3DXVECTOR3(400,0,-250),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[5] = CEnemy::Create(m_pRender,D3DXVECTOR3(500,0,-250),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[6] = CEnemy::Create(m_pRender,D3DXVECTOR3(100,0,-50),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[7] = CEnemy::Create(m_pRender,D3DXVECTOR3(100,0,-250),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[8] = CEnemy::Create(m_pRender,D3DXVECTOR3(200,0,-350),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[9] = CEnemy::Create(m_pRender,D3DXVECTOR3(100,0,-350),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[10] = CEnemy::Create(m_pRender,D3DXVECTOR3(250,250,-250),0,1,ENEMY_BOSS,"data\\Model\\golam.x","data\\Texture\\golam.png");
	//床
//	CYuka::Create(m_pRender,D3DXVECTOR3(300,20,-250));
//	CYuka::Create(m_pRender,D3DXVECTOR3(350,20,-250));
//	CYuka::Create(m_pRender,D3DXVECTOR3(400,20,-250));

	//ポーズ画面初期化
//	m_pPause = new CPause();
//	m_pPause->Init(m_pRender);
//	CPause::getInstance()->Init(m_pRender);

	//フォグが使えるか
	/*
	D3DCAPS9 caps;
	ZeroMemory(&caps,sizeof(D3DCAPS9));
	m_pRender->getDevice()->GetDeviceCaps(&caps);	
	if( ( caps.RasterCaps & D3DPRASTERCAPS_FOGTABLE ) == 0 )	 
	{ 
		if(MessageBox(0,"ピクセルフォグが使えない可能性があります。続行しますか?",
			 "",MB_ABORTRETRYIGNORE) == IDABORT)
		{
			 return false;
		}
	}
	//フォグの設定
	{		 
		FLOAT 	Density=0.0009f;		

		m_pRender->getDevice()->SetRenderState(D3DRS_FOGENABLE, TRUE);
		m_pRender->getDevice()->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(255,255,255,255));
		m_pRender->getDevice()->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE );
		m_pRender->getDevice()->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP );
		m_pRender->getDevice()->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&Density));
	}
	
//	*/

	//使用したデータを初期化してメインシーンへ
	this->m_PhaseInfo.dwScene = CPhase::PHASE_MAIN;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;	

	

	m_pause = false;
	m_Cler = false;
	m_Over = false;
	m_initManager = true;
	m_endCnt = 0;
	m_pclaer->SetDrawFlag(false);
	m_pover->SetDrawFlag(false);

	//サウンド再生
	CSound::getInstance()->PlaySound(SOUND_LABEL_BGM001);

	return true;
}

//更新
bool CGame::Update(void* lpArgs)
{
	
	//カメラ更新
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_F7))
	{
		dbflag ^= true;
		
	}
	if(dbflag)
	{
		CCamera::getInstance()->UpdateDebug();
		
	}
	else
	{
		CCamera::getInstance()->Update();
	}
	CFade* pFade = CFade::getinstance();

	//デバッグ用
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_RETURN))
	{
		//m_Cler = true;
	}

	if(pFade->GetFadeMode() == FADE_OUT_FINISH)
	{
		
		pFade->SetFadeMode(FADE_IN);
		this->m_PhaseInfo.dwScene = CPhase::PHASE_RELEASE;
		this->m_PhaseInfo.dwSubScene = 0;
		this->m_PhaseInfo.nCount = 0;
	}
	//ポーズ
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_P) || CJoySystem::getInstance()->GetJoyBtnPush(JOY_BTN4))
	{
		m_pause ^= true;
	}

	if(m_pause)
	{
		CPause::getInstance()->Update();
		if(CPause::getInstance()->GetModeChange() == MODE_CONTINUE)
		{

		}
		if(CPause::getInstance()->GetModeChange()==MODE_RESET || CPause::getInstance()->GetModeChange()==MODE_QUIT)
		{
			if(pFade->GetFadeMode()==FADE_NONE)
			{
				pFade->SetFadeMode(FADE_OUT);
				
			}
		}
	}
	else
	{
		//ゲームオーバー
		if(!m_pPlayer->GetLifeFlag())
		{
			m_Over = true;
			m_pover->SetDrawFlag(true);
		}
		/*
		//ゲームクリア
		if(CEnemy::GetEnemyCnt() == ENEMY_NUM_MAX)
		{
			m_Cler = true;
			m_pclaer->SetDrawFlag(true);
		}
		*/
		if(m_Cler || m_Over)
		{
			m_endCnt++;
			if(m_endCnt >= GAME_END_TIME)
			{
				if(pFade->GetFadeMode() == FADE_NONE)
				{
					pFade->SetFadeMode(FADE_OUT);
				}
			}
		}
		m_startCnt++;
		if(m_startCnt >= GAME_START_TIME)
		{
			m_plogo->SetDrawFlag(false);
		}
		//更新
		CScene::UpdateAll();
	}
//	CDebugProc::Print("敵の数\n",CEnemy::GetEnemyCnt());
	CDebugProc::Print("ゲームメイン\n");



	return true;
}

//開放
bool CGame::Release(void* lpArgs)
{
	
	//サウンドストップ
	CSound::getInstance()->StopSound(SOUND_LABEL_BGM001);
	
	m_plogo->Uninit();
	SAFE_DELETE(m_plogo);
	
	m_pclaer->Uninit();
	SAFE_DELETE(m_pclaer);

	m_pover->Uninit();
	SAFE_DELETE(m_pover);

	//ランキングを読み込んでから
	CEnding::getInstance()->LoadRanking();
	//ランキング設定
	CEnding::getInstance()->SetRank(CScore::GetScore());

	m_pRender->getDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	m_initManager = false;
	//リセット
	if(CPause::getInstance()->GetModeChange()==MODE_RESET)
	{
		//ゲーム
		if(lpArgs != NULL)
		{
			*((DWORD *)lpArgs) = MODE_GAME;
		}	
	}
	else if(CPause::getInstance()->GetModeChange()==MODE_QUIT)
	{
		//タイトルへ
		if(lpArgs != NULL)
		{
			*((DWORD *)lpArgs) = MODE_TITLE;
		}
	}
	if(m_Cler || m_Over)
	{
		//リザルト画面へ
		if(lpArgs != NULL)
		{
			*((MODE *)lpArgs) = MODE_RESULT;
		}
	}
	//フェーズ中使用したものだけ開放
	CScene::FreePhase();

	//ポーズ開放
	CPause::getInstance()->Uninit();
	

	//使用したデータを初期化して初期化シーンへ
	this->m_PhaseInfo.dwScene = CPhase::PHASE_INIT;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;

	return true;
}
//描画
bool CGame::Draw(void* lpArgs)
{
	if(m_initManager)
	{
		//カメラ設定
		CCamera::getInstance()->SetCamera();
		if(m_pause)
		{
			CPause::getInstance()->Draw();
		}
		else
		{
			//描画
			CScene::DrawAll();
			if(m_plogo != NULL)
			{
				m_plogo->Draw();
			}
			if(m_pclaer != NULL)
			{
				m_pclaer->Draw();
			}
			if(m_pover != NULL)
			{
				m_pover->Draw();
			}

		}
	}
	return true;
}
bool CGame::DrawShade(void* lpArgs)
{
	if(m_initManager)
	{
		if(m_pause)
		{
			CPause::getInstance()->Draw();
		}
		else
		{
			//描画
			CScene::DrawShadeAll();
		}
	}
	return true;
}