//=============================================================================
//
// 各フェーズ処理 [CEnding.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//警告制限無視
#pragma warning(disable:4996)

//ヘッダーインクルード
#include "CEnding.h"
#include "CFade.h"
#include "CDebugProc.h"
#include "CInputKeyboard.h"
#include "CManager.h"
#include "CSound.h"
#include "CPaticle.h"
#include "CCamera.h"
#include "utill_lib.h"
#include "Joy.h"

//マクロ定義
#define FILE_NAME "data\\rank\\ranking.bin"
#define END_CNT_MAX	(200)

//静的メンバ変数初期化
CEnding* CEnding::m_instance = NULL;

//インスタンス生成
CEnding* CEnding::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CEnding();
	}
	return m_instance;
}
//インスタンス解放
void CEnding::freeInstance()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

//初期化
bool CEnding::Init(void *lpArgs)
{
	m_pRender = CManager::GetRender();

	//カメラの初期化
	CCamera::getInstance()->TitleInit(m_pRender);

	m_EndCnt = 0;

	if(m_pPushLogo == NULL)
	{
		m_pPushLogo = new Clogo();
	}
	//ランキング読み込み
	LoadRanking();

	//ナンバー生成
	for(int i = 0;i < RANK_DIGIT;i++)
	{
		m_pRank1[i] = CNumber::Create(m_pRender,D3DXVECTOR3(static_cast<float>(i*50)+225,+225,0));
		m_pRank2[i] = CNumber::Create(m_pRender,D3DXVECTOR3(static_cast<float>(i*50)+225,+325,0));
		m_pRank3[i] = CNumber::Create(m_pRender,D3DXVECTOR3(static_cast<float>(i*50)+225,+425,0));

		m_pRank1[i]->ChengeNumber(0);
		m_pRank2[i]->ChengeNumber(0);
		m_pRank3[i]->ChengeNumber(0);
	}
	int nNumber1[RANK_DIGIT] = {0};
	int nNumber2[RANK_DIGIT] = {0};
	int nNumber3[RANK_DIGIT] = {0};

	for(int i = 0,j = RANK_DIGIT-1;i < RANK_DIGIT;i++,j--)
	{
		nNumber1[j] = (m_Rank[0]/(int)pow((double)10,(double)i))%(int)10;
		nNumber2[j] = (m_Rank[1]/(int)pow((double)10,(double)i))%(int)10;
		nNumber3[j] = (m_Rank[2]/(int)pow((double)10,(double)i))%(int)10;
	}
	for(int i = 0;i < RANK_DIGIT;i++)
	{
		m_pRank1[i]->ChengeNumber(nNumber1[i]);
		m_pRank2[i]->ChengeNumber(nNumber2[i]);
		m_pRank3[i]->ChengeNumber(nNumber3[i]);
	}	

	

	CScene2D::Create(m_pRender,D3DXVECTOR3(400,300,0),"data\\Texture\\Result.png",OBJTYPE_2D);
	CScene2D::Create(m_pRender,D3DXVECTOR3(50,550,0),"data\\Texture\\jyujika.png",OBJTYPE_2DGIM);
	CScene2D::Create(m_pRender,D3DXVECTOR3(750,550,0),"data\\Texture\\jyujika1.png",OBJTYPE_2DGIM);

	m_pPushLogo->Init(m_pRender,D3DXVECTOR3(400,550,0),200,50,"data\\Texture\\push.png");
//	CPaticle::Create(m_pRender,D3DXVECTOR3(0,0,-50),"data\\Texture\\spark.bmp");
//	CPaticle::Create(m_pRender,D3DXVECTOR3(0,0,-50),"data\\Texture\\smoke.bmp");
	m_initManager = true;
	
	//音楽再生
	CSound::getInstance()->PlaySound(SOUND_LABEL_BGM004);
	//使用したデータを初期化してメインシーンへ
	this->m_PhaseInfo.dwScene = CPhase::PHASE_MAIN;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;	

	return true;
}

//更新
bool CEnding::Update(void* lpArgs)
{
	m_EndCnt++;

	CFade* pFade = CFade::getinstance();

	m_pPushLogo->Update();

	for(int i = 0;i < RANK_DIGIT;i++)
	{
		m_pRank1[i]->Update();
		m_pRank2[i]->Update();
		m_pRank3[i]->Update();

		

	}
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_RETURN) || CJoySystem::getInstance()->GetJoyBtnPush(JOY_BTN1))
	{
		if(pFade->GetFadeMode() == FADE_NONE)
		{
			pFade->SetFadeMode(FADE_OUT);
		}
			
	}
	if(m_EndCnt >= END_CNT_MAX)
	{
		if(pFade->GetFadeMode() == FADE_NONE)
		{
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

	CDebugProc::Print("エンディングメイン\n");
	return true;
}

//開放
bool CEnding::Release(void* lpArgs)
{
	//フェーズ中使用したものだけ開放
	CScene::FreePhase();

	m_pPushLogo->Uninit();
	SAFE_DELETE(m_pPushLogo);
	
	m_EndCnt = 0;

	for(int i = 0;i < RANK_DIGIT;i++)
	{
		m_pRank1[i]->Uninit();
		SAFE_DELETE(m_pRank1[i]);
		
		m_pRank2[i]->Uninit();
		SAFE_DELETE(m_pRank2[i]);
		
		m_pRank3[i]->Uninit();
		SAFE_DELETE(m_pRank3[i]);
	}

	m_initManager = false;
	
	//音楽停止
	CSound::getInstance()->StopSound(SOUND_LABEL_BGM004);

	if(lpArgs != NULL)
	{
		*((MODE *)lpArgs) = MODE_TITLE;
	}
	
	//使用したデータを初期化して初期化シーンへ
	this->m_PhaseInfo.dwScene = CPhase::PHASE_INIT;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;

	return true;
}
//描画
bool CEnding::Draw(void* lpArgs)
{
	if(m_initManager)
	{
		//カメラ設定
		CCamera::getInstance()->SetCamera();
		//描画
		CScene::DrawAll();
		if(m_pPushLogo != NULL)
		{
			m_pPushLogo->Draw();
		}
		for(int i = 0;i < RANK_DIGIT;i++)
		{
			m_pRank1[i]->Draw();
			m_pRank2[i]->Draw();
			m_pRank3[i]->Draw();
		}
	}
	return true;
}
bool CEnding::DrawShade(void* lpArgs)
{
	if(m_initManager)
	{
		//カメラ設定
		CCamera::getInstance()->SetCamera();
		//描画
		CScene::DrawShadeAll();
	}
	return true;
}

//書き込み
bool CEnding::SaveRanking()
{


	//変数宣言
	FILE *fp = NULL;
	
	// ファイルのオープン
	fp = fopen( FILE_NAME, "wb" );

	//書き込み
	// オープンチェック
	if( fp != NULL )
	{
		// データ書き込み
		for(int i = 0;i < RANK_MAX-1;i++)
		{
			fwrite(&m_Rank[i],sizeof(int),1,fp);
		}
		// ファイルクローズ
		fclose( fp );
	}
	else
	{
		// ファイルクローズ
		fclose( fp );
		return false;
	}	
	
	return TRUE;
}
//読み込み
bool CEnding::LoadRanking()
{
	
	//変数宣言
	FILE *fp = NULL;

	// ファイルのオープン
	fp = fopen( FILE_NAME, "rb" );

	//読み込み
	// ファイルが開けたらデータを読み込む
	if( fp != NULL )
	{
		// データ読み込み

		for(int i = 0;i < RANK_MAX-1;i++)
		{
			fread(&m_Rank[i],sizeof(int),1,fp);
		}
		// ファイルクローズ
		fclose( fp );
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}
//設定
void CEnding::SetRank(int iNum)
{
/*	デバッグ用
	m_Rank[0] = 300;
	m_Rank[1] = 200;
	m_Rank[2] = 100;
//*/	

	//最後の要素に現在プレイしていたゲームのスコアを設定
	m_Rank[RANK_MAX-1] = iNum;
	//クイックソートを行う
	QuickSort(&m_Rank[0],0,RANK_MAX,DESC);
	//書き込み
	this->SaveRanking();
	

}
//取得
int CEnding::GetRank(int iNum)
{
	if(iNum > RANK_MAX)
	{
		return 0;
	}
	return m_Rank[iNum];
}
//eof