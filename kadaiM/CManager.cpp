//ヘッダーインクルード
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
#include "CFade.h"
#include "CTitle.h"
#include "CTutorial.h"
#include "CGame.h"
#include "CEnding.h"
#include "CPause.h"
#include "CSound.h"
#include "Joy.h"

//マクロ定義
#define WALL_TO_FIELD	(250)

//静的メンバ変数の初期化
CRender* CManager::m_pRender = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CFade*	CManager::m_pFade = NULL;
//初期化
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd,bool bWindow)
{
	//作成
	m_pRender = new CRender();
	
//	m_pLight = new CLight();
//	m_pCamera = new CCamera();
	m_pDebugProc = new CDebugProc();


	//キーボード初期化
	CInputKeyboard::getInstance()->Init(hInstance,hWnd);
	
	//ジョイスティック初期化
	CJoySystem::getInstance()->JoyInitInfo();

	//レンダークラス
	m_pRender->Init(hWnd,bWindow);
	//デバッグ用初期化
	m_pDebugProc->Init(m_pRender);
	//サウンド初期化
	CSound::getInstance()->InitSound(hWnd);

	//ライト初期化
//	m_pLight->Init(m_pRender);
	
	CLight::getInstance()->Init(m_pRender);
	

	//シーン系オブジェクト
	///*
//	CScene2D::Create(m_pRender,D3DXVECTOR3(100,100,0));
//	CScene3D::Create(m_pRender,D3DXVECTOR3(0,0,0));
//	CSceneX::Create(m_pRender,D3DXVECTOR3(100,10,0),"data\\Model\\airplane000.x");
//	CSceneBillboard::Create(m_pRender,D3DXVECTOR3(-100,0,0));
	//*/
	
	
//	CSceneX::Create(m_pRender,D3DXVECTOR3(0,10,0));
//	CEnemy::Create(m_pRender,D3DXVECTOR3(100,10,0));
//	CSceneX::Create(m_pRender,D3DXVECTOR3(330,10,0));
	//カメラ
//	m_pCamera->Init(m_pRender);
	CCamera::getInstance()->Init(m_pRender);
/*
	//プレイヤー
	m_pPlayer = CPlayer::Create(m_pRender,D3DXVECTOR3(250,0,-250));
	
	//パーティクル
//	CPaticle::Create(m_pRender,D3DXVECTOR3(250,0,-250),"data\\Texture\\effect000.jpg");

	//納屋
	CSceneX::Create(m_pRender,D3DXVECTOR3(100,0,-200),"data\\Model\\naya.x","data\\Texture\\naya.jpg");
	//植物
	CSceneX::Create(m_pRender,D3DXVECTOR3(150,0,-200),"data\\Model\\plant01.x",NULL);
	CSceneX::Create(m_pRender,D3DXVECTOR3(200,0,-200),"data\\Model\\plant02.x",NULL);
	CSceneX::Create(m_pRender,D3DXVECTOR3(250,0,-200),"data\\Model\\plant03.x",NULL);
	CSceneX::Create(m_pRender,D3DXVECTOR3(300,0,-200),"data\\Model\\plant04.x",NULL);
	CSceneX::Create(m_pRender,D3DXVECTOR3(350,0,-200),"data\\Model\\plant05.x",NULL);
	
//	CMeshField::Create(m_pRender,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),50,50,50.0f,50.0f,"data\\Texture\\field000.jpg");
//	CSceneBillboard::Create(m_pRender,D3DXVECTOR3(100,0,-100),"data\\Texture\\tree000.png",100.0f);
	//フィールド
	CMeshField::Create(m_pRender,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),10,10,50.0f,50.0f,"data\\Texture\\field005.png");
	//壁
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(1).x-WALL_TO_FIELD,0,CMeshField::GetVertex(1).z),D3DXVECTOR3(0,0,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(2).x+WALL_TO_FIELD,0,CMeshField::GetVertex(2).z),D3DXVECTOR3(0,D3DX_PI,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(3).x,0,CMeshField::GetVertex(3).z+WALL_TO_FIELD),D3DXVECTOR3(0,D3DX_PI/2.0f,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(0).x,0,CMeshField::GetVertex(0).z-WALL_TO_FIELD),D3DXVECTOR3(0,D3DX_PI/-2.0f,0));

//	CMeshField::Create(m_pRender,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),1,1,100.0f,100.0f,"data\\Texture\\field000.jpg");
	//ドーム
	CMeshDome::Create(m_pRender,D3DXVECTOR3(250,0,-250),D3DXVECTOR3(0,0,0));
	//円柱
	CMeshCylinder::Create(m_pRender,D3DXVECTOR3(250,0,-250),D3DXVECTOR3(0,0,0));
	//スコア
	CScore::Create(m_pRender,D3DXVECTOR3(0,0,0));
	//時間
	CTimer::Create(m_pRender,D3DXVECTOR3(0,0,0));
	//敵
//	CEnemy::Create(m_pRender,D3DXVECTOR3(300,0,-250));
	//床
	CYuka::Create(m_pRender,D3DXVECTOR3(300,20,-250));
	CYuka::Create(m_pRender,D3DXVECTOR3(350,20,-250));
	CYuka::Create(m_pRender,D3DXVECTOR3(400,20,-250));
*/
	//フェード初期化
	CFade::getinstance()->Init(m_pRender);
	
	return S_OK;
}
//開放
void CManager::Uninit()
{
	
	// 終了処理
	CInputKeyboard::deleteInstance();
	CJoySystem::Release();
	CColision::Release();
	//サウンド開放
	CSound::getInstance()->UninitSound();
	CSound::Release();
	m_pRender->Uninit();
	m_pDebugProc->Uninit();
//	m_pScenes->Release();
	CScene::ReleaseAll();

	//各フェーズ開放
	CTitle::freeInstance();
	CTutorial::freeInstance();
	CGame::freeInstance();
	CEnding::freeInstance();

	CFade::Release();
	CPause::Resease();

	
	SAFE_DELETE(m_pRender);
	CLight::Release();
	CCamera::Release();
//	SAFE_DELETE(m_pLight);
//	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pDebugProc);
}
//更新
void CManager::Updata()
{
	
	//キー入力更新
	CInputKeyboard::getInstance()->Update();
	//ジョイスティック更新
	CJoySystem::getInstance()->JoyUpdateInfo();
	//CCamera::getInstance()->UpdateDebug();

	
	
	//描画クラス更新	
	m_pRender->Update();


	
}
//描画
void CManager::Draw()
{
	
	//描画
	m_pRender->Draw();
	
	
	
}