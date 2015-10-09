//=============================================================================
//
// 数値を一個だけ処理 [CNumber.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
#ifndef __CNUMBER_H__
#define __CNUMBER_H__

//ヘッダー
#include "main.h"
#include "CScene.h"
//前方宣言
class CRender;

//クラス定義
class CNumber
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// テクスチャ情報読み込み用
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// 頂点バッファ
	D3DXVECTOR3				m_pos;					// 座標
	D3DXVECTOR3				m_rot;					// 回転
	float					m_fLength;				// 中心から頂点までの長さ
	float					m_fAngle;				// 中心から頂点への角度
	D3DXVECTOR2				m_Tex;					// テクスチャ座標
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	int						m_Num;
public:
	CNumber(){}
	virtual ~CNumber(){}

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

	//生成
	static CNumber* Create(CRender* pRender,const D3DXVECTOR3 pos);

	//数値変更
	void ChengeNumber(int Value);
};

#endif