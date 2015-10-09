//=============================================================================
//
// 各フェーズ処理 [CGame.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義防止
#ifndef __CGAME_H__
#define __CGAME_H__

//ヘッダーインクルード
#include "CPhase.h"
#include "Clogo.h"
//マクロ定義
#define ENEMY_NUM_MAX	(11)
#define PLAYER_LIFE_MAX (3)
#define GAME_START_TIME	(100)
#define GAME_END_TIME	(100)

//前方宣言
class CPlayer;
class CRender;
class CPause;
class CEnemy;
class CPlayerLife;
class CScene2D;
class Clogo;

//クラス定義
class CGame:public CPhase
{
private:
	static bool	m_Cler;
	static bool	m_Over;
	static CGame* m_instance;
	bool m_initManager;
	static CPlayer* m_pPlayer;
	static CEnemy*	m_pEnemy[ENEMY_NUM_MAX];
	static CPlayerLife* m_pPlayLife[PLAYER_LIFE_MAX];
	CRender* m_pRender;
	static bool  m_pause;
	CPause*	m_pPause;
	int		m_startCnt;
	int		m_endCnt;
	CScene2D*	m_Scene2D;
	Clogo*		m_plogo;
	Clogo*		m_pclaer;
	Clogo*		m_pover;
public:

	//インスタンス生成
	static CGame* getInstance();
	//インスタンス解放
	static void freeInstance();

	//コンストラクタ
	CGame()
	{
		m_initManager = false;
		m_pPause = NULL;
		m_plogo = NULL;
		m_pclaer = NULL;
		m_pover = NULL;
	}
	//デストラクタ
	~CGame()
	{
		if(m_plogo != NULL)
		{
			m_plogo->Uninit();
			SAFE_DELETE(m_plogo);
		}
		if(m_pclaer != NULL)
		{
			m_pclaer->Uninit();
			SAFE_DELETE(m_pclaer);
		}
		if(m_pover != NULL)
		{
			m_pover->Uninit();
			SAFE_DELETE(m_pover);
		}
	}
	int GetStartCnt(void)
	{
		return m_startCnt;
	}
	static CPlayer* GetPlayer(void)
	{
		return m_pPlayer;
	}
	static CEnemy* GetEnemy(int index)
	{
		return m_pEnemy[index];
	}
	static CPlayerLife* GetPlayerLife(int index)
	{
		return m_pPlayLife[index];
	}
	static bool GetPauseFlag(void)
	{
		return m_pause;
	}
	static void SetPauseFlag(bool bflag)
	{
		m_pause = bflag;
	}
	static bool GetClearFlag(void)
	{
		return m_Cler;
	}
	static void SetClearFlag(bool bflag)
	{
		m_Cler = bflag;
	}
	static bool GetGameOverFlag(void)
	{
		return m_Over;
	}
	static void SetGameOverFlag(bool bflag)
	{
		m_Over = bflag;
	}
	//各シーン
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);
	virtual bool DrawShade(void *lpArgs = NULL);
};

#endif

//eof