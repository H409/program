//=============================================================================
//
// フェード処理 [CFade.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義防止
#ifndef __CFADE_H__
#define __CFADE_H__

//ヘッダーインクルード
#include "main.h"
#include "CScene2D.h"


//モードチェンジ用列挙型
typedef enum
{
	FADE_NONE,
	FADE_OUT,
	FADE_IN,
	FADE_OUT_FINISH,
	FADE_IN_FINISH,
	FADE_MAX
}FADEMODE;

class CRender;

//クラス定義
class CFade
{
private:
	FADEMODE	m_FadeMode;
	bool		m_fadeFlag;
	CRender*	m_pRender;
	int			m_Alpha;
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// テクスチャ情報読み込み用
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// 頂点バッファ
	D3DXVECTOR3				m_pos;					// 座標
	D3DXVECTOR3				m_rot;					// 回転
	float					m_fLength;				// 中心から頂点までの長さ
	float					m_fAngle;				// 中心から頂点への角度
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	char*					m_pTexName;
	static CFade*			m_instance;
public:
	static CFade*			getinstance();
	static void				Release();
	CFade()
	{
		m_Alpha = 0;
	}
	virtual ~CFade()
	{
		SAFE_RELEASE(m_pD3DVtxBuffer);	//頂点バッファの開放
	}
	
	HRESULT Init(CRender* pRender);
	void Update();
	void Uninit();
	void Draw();

	FADEMODE	GetFadeMode(void)
	{
		return m_FadeMode;
	}
	void		SetFadeMode(FADEMODE iNum)
	{
		m_FadeMode = iNum;
	}

	bool		FadeOut(void);
	bool		FadeIn(void);

	static unsigned __stdcall FadeThread( LPVOID Param );
};

#endif