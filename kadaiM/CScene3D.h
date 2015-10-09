#ifndef __CSCENE3D_H__
#define __CSCENE3D_H__

//ヘッダー
#include "CScene.h"
#include "main.h"

//前方宣言
class CRender;

class CScene3D:public CScene
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// テクスチャ情報読み込み用
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// 頂点バッファ
	D3DXVECTOR3				m_pos;					// 座標
	D3DXVECTOR3				m_rot;					// 回転
	D3DXVECTOR3				m_scl;					// 拡縮
	D3DXMATRIX				m_mtxWorld;				// ワールドマトリックス
	float					m_fLength;				// 中心から頂点までの長さ
	float					m_fAngle;				// 中心から頂点への角度
	LPD3DXEFFECT			m_pEffect;
	LPDIRECT3DDEVICE9       m_pD3DDevice;
public:
	CScene3D(int nPriority = 3):CScene(nPriority){}
	virtual ~CScene3D(){}

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
	//ワールド座標取得
	D3DXMATRIX GetWorldMatrix(void)
	{
		return m_mtxWorld;
	}
	static CScene3D* Create(CRender* pRender,D3DXVECTOR3 pos);
};

float GetHeight(D3DXVECTOR3 pos,D3DXVECTOR3* pNormal);
float GetHeightPolygon(D3DXVECTOR3& p0,D3DXVECTOR3& p1,D3DXVECTOR3& p2,D3DXVECTOR3& pos,D3DXVECTOR3* pNormal);
#endif