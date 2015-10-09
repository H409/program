//=============================================================================
//
// ポーズ処理 [CPause.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//多重定義防止
#ifndef __CPAUSE_H__
#define __CPAUSE_H__

//ヘッダーインクルード
#include "main.h"

//列挙型定義
typedef enum
{
	MODE_NONE,
	MODE_CONTINUE,
	MODE_RESET,
	MODE_QUIT,
	MODE_CHANGE_MAX
}MODE_CHANGE;

//構造体定義
typedef struct _FLOATPOINT
{
	float x;
	float y;

}FLOATPOINT;
typedef struct CURSOL
{
	FLOATPOINT pos;
	int Width;
	int Height;
	BYTE flag;
	float	fLength;		//ポリゴンの対角線の長さ
	float	fAngle;			//ポリゴンの対角線の角度
	float	fSubLength;
	bool	bFlag;
}CURSOL,*LPCURSOL;



//前方宣言
class CRender;

//クラス定義
class CPause
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// テクスチャ情報読み込み用
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// 頂点バッファ
	LPDIRECT3DTEXTURE9		m_pD3DTexCur[3];		// テクスチャ情報読み込み用
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBufferCur;		// 頂点バッファ
	D3DXVECTOR3				m_pos;					// 座標
	D3DXVECTOR3				m_rot;					// 回転
	float					m_fLength;				// 中心から頂点までの長さ
	float					m_fAngle;				// 中心から頂点への角度
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	CURSOL					m_Cursor[3];
	char					m_curf;
	MODE_CHANGE				m_modechange;
	static CPause*			m_instance;
	int						m_type;
	BYTE					m_Red;
	BYTE					m_Green;
	BYTE					m_Blue;
	BYTE					m_Alpha[3];
public:

	static CPause* getInstance(void);
	static void Resease(void);
	//コンストラクタ
	CPause()
	{
		for(int i = 0;i < 3;i++)
		{
			m_pD3DTexCur[i] = NULL;
		}
		m_pD3DVtxBufferCur = NULL;
		m_pD3DTex = NULL;
		m_pD3DVtxBuffer = NULL;

	}
	//デストラクタ
	~CPause()
	{
		/*
		for(int i = 0;i < 3;i++)
		{
			SAFE_RELEASE(m_pD3DTexCur[i]);
		}
		SAFE_RELEASE(m_pD3DVtxBufferCur);
		SAFE_RELEASE(m_pD3DVtxBuffer);
		SAFE_RELEASE(m_pD3DTex);
		*/
	}

	//初期化
	HRESULT Init(CRender* pRender);
	//更新
	void Update();
	//開放
	void Uninit();
	//描画
	void Draw();

	MODE_CHANGE GetModeChange(void)
	{
		return m_modechange;
	}
};

#endif
//eof