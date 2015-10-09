//多重定義防止
#ifndef __CMODEL_H__
#define __CMODEL_H__



//ヘッダーインクルード
#include "main.h"
#include "CScene.h"


//クラス定義
class CModel:public CScene
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
	char*						m_pTexName;
	LPD3DXFRAME					m_pFrameRoot;			//スキンメッシュ
    LPD3DXANIMATIONCONTROLLER	m_pAnimController;		//スキンメッシュ
	D3DXVECTOR3					m_Vertex;
	LPD3DXEFFECT				m_pEffect;
	IDirect3DTexture9*			m_pDepthTexture;
	CRender*					m_pRender;
public:
	CModel(int nPriority = 3,OBJTYPE objtype = OBJTYPE_X):CScene(nPriority,objtype){m_pTexName = NULL;}
	virtual ~CModel()
	{
		
	}

	//初期化
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere);
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
	static CModel* Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename);
};
#endif