//=============================================================================
//
// 各フェーズ処理 [CTitle.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義
#ifndef __CTITLE_H__
#define __CTITLE_H__

//ヘッダーインクルード
#include "CPhase.h"
#include "Clogo.h"

//前方宣言
class CRender;
class Clogo;

//クラス定義
class CTitle:public CPhase
{
private:
	bool  m_Cler;
	bool  m_pause;
	static CTitle* m_instance;
	CRender* m_pRender;
	bool  m_initManager;
	Clogo* m_pPushLogo;
	Clogo* m_pTitleLogo;
public:

	//インスタンス生成
	static CTitle* getInstance();
	//インスタンス解放
	static void freeInstance();

	//コンストラクタ
	CTitle()
	{
		m_initManager = false;
		m_pPushLogo = NULL;
	}
	//デストラクタ
	~CTitle()
	{
		if(m_pPushLogo != NULL)
		{
			m_pPushLogo->Uninit();
			SAFE_DELETE(m_pPushLogo);
		}
	}
	//各シーン
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);
	virtual bool DrawShade(void *lpArgs = NULL);
};

#endif