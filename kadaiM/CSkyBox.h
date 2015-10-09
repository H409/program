//=============================================================================
// シェーダー作成処理 [CSkyBox.h]
// Author : MASAHIRO YAMAGUCHI
// スカイボックス初期化等
//=============================================================================

//多重定義防止
#ifndef __CSKYBOX_H__
#define __CSKYBOX_H__

//ヘッダーインクルード
#include "main.h"
#include "CScene.h"

//マクロ定義
#define CUBE_FACE			(6)
#define CUBEMAP_DIMENSION	(800)
#define CUBE_VERTEX			(4)

//前方宣言
class CRender;

class CSkyBox:public CScene
{
private:
	D3DXVECTOR3					m_pos;					// 座標
	D3DXVECTOR3					m_rot;					// 回転
	D3DXVECTOR3					m_scl;					// 拡縮
	D3DXMATRIX					m_mtxWorld;				// ワールドマトリックス
	LPD3DXMESH					m_pD3DXMeshModel;		// メッシュ
	LPD3DXBUFFER				m_pD3DXBuffMatModel;	// マテリアル
	LPDIRECT3DTEXTURE9*			m_pD3DTextureModel;		// テクスチャへのポインタ
	LPDIRECT3DDEVICE9			m_pD3DDevice;			// デバイス
	DWORD						m_nNumMatModel;			//
	bool						m_initManager;
	D3DMATERIAL9*				m_pMeshMaterials;
	CSkyBox*					m_pSceneX;
	char*						m_pTexName;
	D3DXVECTOR3					m_Vertex;
	LPD3DXEFFECT				m_pEffect;
	IDirect3DTexture9*			m_pDepthTexture;
	CRender*					m_pRender;
	LPDIRECT3DVERTEXBUFFER9 m_pD3DVtxBuff;						// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pD3DTex[CUBE_FACE];				// テクスチャへのポインタ

	LPDIRECT3DCUBETEXTURE9	m_pCubeEnvMap; //デカールとしてのキューブテクスチャ
	LPDIRECT3DCUBETEXTURE9	m_pCubeRender; //他のジオメトリのレンダリングターゲットとなるキューブテクスチャ
	LPDIRECT3DSURFACE9		m_pBackBuffer;
	LPDIRECT3DSURFACE9		m_pZBuffer;
	LPDIRECT3DSURFACE9		m_pCubeZBuffer[CUBE_FACE];

	//表面
	TLVERTEX				m_Ver1[CUBE_VERTEX];
	TLVERTEX				m_Ver2[CUBE_VERTEX];
	TLVERTEX				m_Ver3[CUBE_VERTEX];
	TLVERTEX				m_Ver4[CUBE_VERTEX];
	TLVERTEX				m_Ver5[CUBE_VERTEX];
	TLVERTEX				m_Ver6[CUBE_VERTEX];
public:
	CSkyBox(int nPriority = 3,OBJTYPE objtype = OBJTYPE_X):CScene(nPriority,objtype){m_pTexName = NULL;}
	virtual ~CSkyBox()
	{
		
	}

	//初期化
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename);

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
	D3DXMATRIX GetWorldMatrix()
	{
		return m_mtxWorld;
	}
	//ワールドマトリックス設定
	void SetWorldMatrix(D3DXMATRIX mat)
	{
		m_mtxWorld = mat;
	}
	void SetRotNormalize(void)
	{
		if( m_rot.y < -D3DX_PI )
		{
			m_rot.y += 2 * D3DX_PI;
		}
		else if( m_rot.y > D3DX_PI )
		{
			m_rot.y -= 2 * D3DX_PI;
		}
	}
	static CSkyBox* Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename);
};

#endif