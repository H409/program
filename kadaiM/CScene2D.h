#ifndef __CSCENE2D_H__
#define __CSCENE2D_H__

#include "main.h"
#include "CScene.h"

//前方宣言
class CRender;

//クラス定義
class CScene2D:public CScene
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// テクスチャ情報読み込み用
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// 頂点バッファ
	D3DXVECTOR3				m_pos;					// 座標
	D3DXVECTOR3				m_rot;					// 回転
	float					m_fLength;				// 中心から頂点までの長さ
	float					m_fAngle;				// 中心から頂点への角度
	int						m_Red;
	int						m_Green;
	int						m_Blue;
	int						m_Alpha;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	char*					m_pTexName;
	bool					m_drawFlag;
	CRender*				m_pRender;
public:
	CScene2D(int nPriority = 3,OBJTYPE objtype = OBJTYPE_2D):CScene(nPriority,objtype)
	{
		m_pD3DVtxBuffer = NULL;
		m_pD3DTex = NULL;
	}
	virtual ~CScene2D(){}

	//初期化
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,int nRed,int nGreen,int nBlue,int nalpha,int nWidth,int nHeight,char* pTexFileName);
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
	bool GetDrawFlag(void)
	{
		return m_drawFlag;
	}
	void SetDrawFlag(bool flag)
	{
		m_drawFlag = flag;
	}
	void SetAlpha(int nAlpha)
	{
		m_Alpha = nAlpha;
	}
	void SetRed(int nRed)
	{
		m_Red = nRed;
	}
	void SetBlue(int nBlue)
	{
		m_Blue = nBlue;
	}
	void SetGreen(int nGreen)
	{
		m_Green = nGreen;
	}
	static CScene2D* Create(CRender* pRender,D3DXVECTOR3 pos,char* ptexFileName,OBJTYPE objtype);
	static CScene2D* Create(CRender* pRender,D3DXVECTOR3 pos,int nWidth,int nHeight,char* ptexFileName,OBJTYPE objtype);
};
#endif