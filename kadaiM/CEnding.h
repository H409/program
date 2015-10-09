//=============================================================================
//
// 各フェーズ処理 [CEnding.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義防止
#ifndef __CENDING_H__
#define __CENDING_H__

//ヘッダーインクルード
#include "CPhase.h"
#include "Clogo.h"
#include "CNumber.h"

//マクロ定義
#define RANK_MAX	(4)
#define RANK_DIGIT	(5)
//前方宣言
class CRender;

//クラス定義
class CEnding:public CPhase
{
private:
	bool  m_Cler;
	bool  m_pause;
	static CEnding* m_instance;
	CRender*	m_pRender;
	bool	m_initManager;
	Clogo* m_pPushLogo;
	int m_Rank[RANK_MAX];
	CNumber*			m_pRank1[RANK_DIGIT];
	CNumber*			m_pRank2[RANK_DIGIT];
	CNumber*			m_pRank3[RANK_DIGIT];
	int					m_EndCnt;
public:
	//インスタンス生成
	static CEnding* getInstance();
	//インスタンス解放
	static void freeInstance();

	//コンストラクタ
	CEnding()
	{
		m_pPushLogo = NULL;
		m_initManager = false;
	}
	//デストラクタ
	~CEnding()
	{
		if(m_pPushLogo != NULL)
		{
			m_pPushLogo->Uninit();
			SAFE_DELETE(m_pPushLogo);
		}
	}
	bool SaveRanking(void);
	bool LoadRanking(void);
	void SetRank(int iNum);
	int  GetRank(int iNum);
	//各シーン
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);
	virtual bool DrawShade(void *lpArgs = NULL);
};

#endif