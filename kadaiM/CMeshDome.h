//=============================================================================
//
// メッシュ地面の処理 [meshDome.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
#ifndef __MESHDOME_H__
#define __MESHDOME_H__

//ヘッダーインクルード
#include "main.h"
#include "CScene.h"

//前方宣言
class CRender;

class CMeshDome:public CScene
{
private:
	//デバイス
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	LPDIRECT3DTEXTURE9		m_pD3DTex;							// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;						// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pD3DIndexBuff;					// インデックスバッファへのポインタ
	int						m_nNumVertexIndex;					// 頂点の総インデックス数
	D3DXMATRIX				m_mtxWorld;							// ワールドマトリックス
	D3DXVECTOR3				m_pos;								// 位置
	D3DXVECTOR3				m_rot;								// 向き
	D3DXVECTOR3				m_scl;								// 拡縮

	int						m_nNumBlockX, m_nNumBlockZ;			// ブロック数
	int						m_nNumVertex;						// 総頂点数
	int						m_nNumPolygon;						// 総ポリゴン数
	float					m_fSizeBlockX, m_fSizeBlockZ;		// ブロックサイズ
	float					m_fRadius;							// 半径
public:
	CMeshDome(int nPriority = 3):CScene(nPriority){}
	virtual ~CMeshDome(){}

	//初期化
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY,D3DXVECTOR3 pos,D3DXVECTOR3 rot,char *pTexPath,float fSizeRadius);
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
	//ワールドマトリックス取得
	D3DXMATRIX GetWorldMatrix(void)
	{
		return m_mtxWorld;
	}
	static CMeshDome* Create(CRender* pRender,D3DXVECTOR3 pos,D3DXVECTOR3 rot);
};

#endif