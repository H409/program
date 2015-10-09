//多重定義防止
#ifndef __CLOGO_H__
#define __CLOGO_H__

//ヘッダーインクルード
#include "main.h"

//前方宣言
class CRender;
//クラス定義
class Clogo
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
	int						m_cnt;
	CRender*				m_pRender;
public:
	//コンストラクタ
	Clogo(){}
	//デストラクタ
	virtual ~Clogo(){}
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,int nWidth,int nHeight,char* ptexFileName);
	void	Update(void);
	void	Draw(void);
	void	Uninit(void);
	bool GetDrawFlag(void)
	{
		return m_drawFlag;
	}
	void SetDrawFlag(bool flag)
	{
		m_drawFlag = flag;
	}

};

#endif