//=============================================================================
//
// 各フェーズ処理 [CPhase.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義防止
#ifndef __CPHASE_H__
#define __CPHASE_H__

#include <windows.h>
#include <stdio.h>
#include "main.h"
///// 構造体定義 /////
typedef struct _PHASEINFO
{
	DWORD dwScene;
	DWORD dwSubScene;
	int   nCount;
}PHASEINFO,*LPPHASEINFO;




//シーン管理用クラス
class CPhase
{
protected:
	PHASEINFO	m_PhaseInfo;
	bool(CPhase::*m_lpPhase[3])(void *lpArgs);
public:
	
	//コンストラクタ
	CPhase();	
	//デストラクタ
	~CPhase();


	static const BYTE	PHASE_INIT;
	static const BYTE	PHASE_MAIN;
	static const BYTE	PHASE_RELEASE;
	//シーン情報取得用
	PHASEINFO GetPhaseInfo(void)const
	{
		return this->m_PhaseInfo;
	}
	//シーン番号設定
	void SetPhase(DWORD dwScene)
	{
		this->m_PhaseInfo.dwScene = dwScene;
	}
	//サブシーン番号設定
	void SetSubPhase(DWORD dwSubScene)
	{
		this->m_PhaseInfo.dwSubScene = dwSubScene;
	}
	//各シーンの呼び出し用関数
	bool Phase(void *lpArgs = NULL);


	//各シーン
	virtual bool Init(void *lpArgs = NULL) = 0;
	virtual bool Update(void *lpArgs = NULL) = 0;
	virtual bool Release(void *lpArgs = NULL) = 0;
	virtual bool Draw(void *lpArgs = NULL) = 0;
	virtual bool DrawShade(void *lpArgs = NULL) = 0;

};

#endif
//eof