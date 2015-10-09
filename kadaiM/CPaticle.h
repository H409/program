//=============================================================================
//
// メッシュ地面の処理 [CPaticle.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//多重定義防止
#ifndef __CPATICLE_H__
#define __CPATICLE_H__

//ヘッダーインクルード
#include "CScene.h"

//マクロ定義
#define PATICLE_MAX	(100)
#define PATICLE_DELETE_CNT	(200)
struct MY_VERTEX_1 
{
		D3DXVECTOR3 p;		// 位置
		FLOAT		p_size;	// サイズ
		DWORD		color;	// 色
};
struct PointStrite
{
	D3DXVECTOR3	pos;		// 初期位置
	float		psize;		// サイズ
	D3DXVECTOR3 vec;		// 初速度と方向
	DWORD		start_time;	// 開始時間（ミリ秒）
	float		duration;	// 継続時間（ミリ秒）
};

//前方宣言
class CRender;

//クラス定義
class CPaticle:public CScene
{
private:
	LPDIRECT3DVERTEXBUFFER9	m_pVBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture;		// テクスチャへのポインタ
	CRender*				m_pRender;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	D3DXMATRIX				m_mtxWorld;							// ワールドマトリックス
	D3DXVECTOR3				m_pos;								// 位置
	D3DXVECTOR3				m_rot;								// 向き
	D3DXVECTOR3				m_scl;								// 拡縮
	int						m_DeleteCnt;
	float					m_continueTime;
	PointStrite				m_post[PATICLE_MAX];
public:

	static CPaticle* Create(CRender* pRender,D3DXVECTOR3 pos,char* ptexfilename);
	CPaticle(int nPriority = 3):CScene(nPriority){}
	virtual ~CPaticle(){}

	//初期化
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,char *ptexfilename);
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
	//ユーティリティ
	DWORD Float2DWORD( float val ) { return *((DWORD*)&val); }
};
#endif