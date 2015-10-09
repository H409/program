//=============================================================================
//
// メッシュ地面の処理 [meshfield.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//多重定義防止
#ifndef __MESHFIELD_H__
#define __MESHFIELD_H__

//ヘッダーインクルード
#include "main.h"
#include "CScene.h"

//前方宣言
class CRender;

//クラス定義
class CMeshField:public CScene
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
	static D3DXVECTOR3		m_Vertex[4];
	float*					m_pfheightMap;
	D3DXVECTOR3*			m_pnorBuff;
	WORD*					m_pIndex;
	VERTEX_3D*				m_pVtx;
public:

	CMeshField(int nPriority = 3):CScene(nPriority){}
	virtual ~CMeshField(){}

	//初期化
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,D3DXVECTOR3 pos,D3DXVECTOR3 rot,char *pTexPath);
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
	static CMeshField* Create(CRender* pRender,D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nNumBlockX, int nNumBlockZ, float fSizeBlockX, float fSizeBlockZ,char* pTexFileName);

	static D3DXVECTOR3 GetVertex(int nIndex);

	bool FindNormalsOnPoly(int dwPolyIndex,D3DXVECTOR3* pvNormals );
};

#endif