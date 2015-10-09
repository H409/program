//=============================================================================
//
// スコア処理 [CTimer.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//多重定義防止
#ifndef __CTIMER_H__
#define __CTIMER_H__

//ヘッダー
#include "main.h"
#include "CScene.h"
#include "CNumber.h"

//マクロ定義
#define TIMER_DIGIT	(3)

//前方宣言
class CRender;

//クラス定義
class CTimer:public CScene
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// テクスチャ情報読み込み用
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// 頂点バッファ
	D3DXVECTOR3				m_pos;					// 座標
	D3DXVECTOR3				m_rot;					// 回転
	float					m_fLength;				// 中心から頂点までの長さ
	float					m_fAngle;				// 中心から頂点への角度
	D3DXVECTOR2				m_Tex;					// テクスチャ座標
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	static int				m_Time;
	CNumber*				m_pNumber[TIMER_DIGIT];
	static int				m_Cnt;
public:
	CTimer(int nPriority = 3):CScene(nPriority){m_Time = 0;}
	virtual ~CTimer()
	{
		//for(int i = 0;i < TIMER_DIGIT;i++)
		//{
		//	m_pNumber[i]->Uninit();
		//	SAFE_DELETE(m_pNumber[i]);
		//}

	}

	//初期化
	HRESULT Init(CRender* pRender);
	//更新
	void Update();
	//開放
	void Uninit();
	//描画
	void Draw();
	void DrawShade();
	//座標取得
	D3DXVECTOR3 GetPosition(void)
	{
		return m_pos;
	}
	//座標設定
	void SetPosition(D3DXVECTOR3 pos)
	{
		m_pos = pos;	
	}
	//回転取得
	D3DXVECTOR3 GetRotate(void)
	{
		return m_rot;
	}
	//回転設定
	void SetRotate(D3DXVECTOR3 rot)
	{
		m_rot = rot;	
	}
	//値変更
	void ChangeTime(int nValue);
	
	//生成
	static CTimer* Create(CRender* pRender,D3DXVECTOR3 pos);
};
#endif
//eof