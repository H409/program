#ifndef __CSCENEBILLBOARD_H__
#define __CSCENEBILLBOARD_H__

//ヘッダーインクルード
#include "main.h"
#include "CScene.h"

//マクロ定義
#define ANIM_PTN			(8)
#define ANIM_WAIT			(10)
#define U_POSITION			(1.25f)
#define V_POSITION			(5)
#define EXPROSION_ENDCNT	(80)

//クラス定義
class CSceneBillboard:public CScene
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
	bool					m_bFlag;
	float					m_fTexU;
	float					m_fTexUt;
	int						m_nAnimCnt;

	LPDIRECT3DDEVICE9       m_pD3DDevice;			// デバイス
public:
	//コンストラクタ
	CSceneBillboard(int nPriority = 3):CScene(nPriority){}
	//デストラクタ
	virtual ~CSceneBillboard(){}

	//初期化
	HRESULT Init(CRender* pRender);

	HRESULT Init(CRender* pRender,char* ptexfilename,float fangle,float fsize);

	HRESULT	InitAnime(CRender* pRender,char* ptexfilename);
	//更新
	void Update();
	void UpdateAnime();
	//開放
	void Uninit();
	//描画
	void Draw();
	void DrawShade();
	void DrawAnime();
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
	static CSceneBillboard* Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,float fsize);
};


#endif