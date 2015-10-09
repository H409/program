#ifndef __CSCENEX_H__
#define __CSCENEX_H__

//ヘッダー
#include "main.h"
#include "CScene.h"
#include "CSkinAnimetion.h"

//前方宣言
class CRender;
class SKIN_MESH;

//構造体定義
typedef struct 
{
	D3DXVECTOR3 vecCenter;
	float fRadius;
}SPHERE,*LPSPHERE;

//クラス定義
class CSceneX:public CScene
{
private:
	D3DXVECTOR3					m_pos;					// 座標
	D3DXVECTOR3					m_rot;					// 回転
	D3DXVECTOR3					m_scl;					// 拡縮
	D3DXMATRIX					m_mtxWorld;				// ワールドマトリックス
	D3DXMATRIX					m_mtxRot;
	LPD3DXMESH					m_pD3DXMeshModel;		// メッシュ
	LPD3DXMESH					m_pSphereMesh;			// 球体
	LPD3DXBUFFER				m_pD3DXBuffMatModel;	// マテリアル
	LPDIRECT3DTEXTURE9*			m_pD3DTextureModel;		// テクスチャへのポインタ
	LPDIRECT3DDEVICE9			m_pD3DDevice;			// デバイス
	DWORD						m_nNumMatModel;			//
	bool						m_initManager;
	D3DMATERIAL9*				m_pMeshMaterials;
	D3DMATERIAL9*				m_pSphereMeshMaterials;	//マテリアル
	CSceneX*					m_pSceneX;
	char*						m_pTexName;
	LPD3DXFRAME					m_pFrameRoot;			//スキンメッシュ
    LPD3DXANIMATIONCONTROLLER	m_pAnimController;		//スキンメッシュ
	D3DXVECTOR3					m_Vertex;
	LPD3DXEFFECT				m_pEffect;
	IDirect3DTexture9*			m_pDepthTexture;
	CRender*					m_pRender;
	SKIN_MESH*					m_SkinMesh;
	SPHERE						m_Sphere;				//球体用
	bool						m_bSphere;				//球体用表示フラグ
	bool						m_createSphere;			//球体作成用フラグ
	bool						m_LifeFlag;
public:
	CSceneX(int nPriority = 3,OBJTYPE objtype = OBJTYPE_X):CScene(nPriority,objtype){m_pTexName = NULL;}
	virtual ~CSceneX()
	{
		
	}

	//初期化
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere);
	HRESULT InitAnim(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere);
	HRESULT	InitSphere(void);
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
	//拡縮取得
	D3DXVECTOR3 GetScale(void)
	{
		return m_scl;
	}
	//拡縮設定
	void SetScale(D3DXVECTOR3 scl)
	{
		m_scl = scl;
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
	void SetRotMatrix(D3DXMATRIX mat)
	{
		m_mtxRot = mat;
	}
	//球取得
	SPHERE GetSphere(void)
	{
		return m_Sphere;
	}
	//フラグ設定
	void SetBSphere(bool flag)
	{
		m_bSphere = flag;
	}
	//フラグ取得
	bool GetBSphere(void)
	{
		return m_bSphere;
	}
	bool GetLifeFlag(void)
	{
		return m_LifeFlag;
	}
	void SetLifeFlag(bool bflag)
	{
		m_LifeFlag = bflag;
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
	LPD3DXFRAME* GetFrame(void)
	{
		return &m_pFrameRoot;
	}

	LPD3DXANIMATIONCONTROLLER* GetController(void)
	{
		return &m_pAnimController;
	}

	D3DXVECTOR3* FindVertex(DWORD dwIndex);

	void CreateBBox(D3DXVECTOR3* pvecMax,D3DXVECTOR3* pvecMin);
	static CSceneX* Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename);
};

#endif