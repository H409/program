//=============================================================================
//
// 各フェーズ処理 [CTutorial.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義
#ifndef __CTUTORIAL_H__
#define __CTUTORIAL_H__

//ヘッダーインクルード
#include "CPhase.h"
#include "Clogo.h"

//前方宣言
class CRender;

//クラス定義
class CTutorial:public CPhase
{
private:
	bool  m_Cler;
	bool  m_pause;
	static CTutorial* m_instance;
	CRender* m_pRender;
	bool  m_initManager;
	Clogo* m_pPushLogo;
public:

	//インスタンス生成
	static CTutorial* getInstance();
	//インスタンス解放
	static void freeInstance();

	//コンストラクタ
	CTutorial()
	{
		m_initManager = false;
		m_pPushLogo = NULL;
	}
	//デストラクタ
	~CTutorial()
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