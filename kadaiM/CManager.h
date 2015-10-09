//多重定義防止
#ifndef __CMANAGER_H__
#define __CMANAGER_H__

//ヘッダーインクルード
#include "main.h"


//前方宣言
class CRender;
class CScene;
class CLight;
class CCamera;
class CInputKeyboard;
class CDebugProc;
class CSceneX;
class CPlayer;
class CFade;
class CTitle;
class CGame;
class CEnding;

//クラス定義
class CManager
{
private:
	static CRender*		m_pRender;
	CScene*				m_pScenes;
	CLight*				m_pLight;
	CCamera*			m_pCamera;
	CDebugProc*			m_pDebugProc;
	CSceneX*			m_pDummy;
	static CPlayer*		m_pPlayer;
	static CFade*		m_pFade;
	CTitle*				m_pTitle;
	CGame*				m_pGame;
	CEnding*			m_pEnding;
	MODE				m_mode;
public:

	//コンストラクタ
	CManager()
	{
		m_pPlayer = NULL;
		m_mode = MODE_TITLE;
	}
	//デストラクタ
	virtual ~CManager(){}
	//初期化
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,bool bWindow);
	//開放
	void Uninit(void);
	//更新
	void Updata(void);
	//描画
	void Draw(void);

	//ゲッター
	static CRender* GetRender(void)
	{
		return m_pRender;
	}
	static CPlayer* GetPlayer(void)
	{
		return m_pPlayer;
	}

	static CFade* GetFade(void)
	{
		return m_pFade;
	}

};


#endif