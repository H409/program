//=============================================================================
// レンダーテクスチャ処理 [RenderTexture.cpp]
// Author : MASAHIRO YAMAGUCHI
// リアルタイムにテクスチャに描画結果を書き込むことが出来ます。
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "RenderTarget.h"

//▼クラス定義
//=============================================================================
//コンストラクタ
//=============================================================================
CRenderTarget::CRenderTarget()
{
	
	//１．レンダーターゲット用のテクスチャ作成
	D3DXCreateTexture(getDevice(),//デバイス
				 800,//テクスチャに描画結果を書き込む時のそのテクスチャの幅
				 600,//テクスチャに描画結果を書き込む時のそのテクスチャの高さ
				 0,//ミップマップレベル
				 D3DUSAGE_RENDERTARGET,//この定数がレンダーターゲットを示す
				 //D3DFMT_G16R16,//カラーフォーマット
				 //D3DFMT_R8G8B8,
				 D3DFMT_A16B16G16R16,
				 D3DPOOL_DEFAULT,
				 &m_pRenderTexture);//レンダーテクスチャポインタ
	
	//2 バックバッファをポインタに事前に入れておく
	getDevice()->GetRenderTarget(0,&m_pBackBufferTexture);



	//3レンダーターゲットとして作成したテクスチャのサーフェイスを取得
	m_pRenderTexture->GetSurfaceLevel(0,&m_pRenderTexSurface);
	
	//Zバッファ
	getDevice()->CreateDepthStencilSurface(800,600,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,FALSE,&m_pZBuffer,NULL);
//	GetDevice()->CreateDepthStencilSurface(800,600,D3DFMT_D16,D3DMULTISAMPLE_NONE,0,TRUE,&g_pZBuffer,NULL);

}
//=============================================================================
//デストラクタ
//=============================================================================
CRenderTarget::~CRenderTarget()
{
	SAFE_RELEASE(m_pBackBufferTexture);
	SAFE_RELEASE(m_pRenderTexture);
	SAFE_RELEASE(m_pRenderTexSurface);
	SAFE_RELEASE(m_pZBuffer);
}


//=============================================================================
// レンダーテクスチャの取得処理
// 戻り値：LPDIRECT3DTEXTURE9		：レンダーテクスチャポインタ
// 引数１：void						：なし
//=============================================================================
IDirect3DTexture9* CRenderTarget::GetRenderTexture(void)
{
	//普通にLPDIRECT3DTEXTURE9 テクスチャのポインタをへんきゃくすればOK
	return m_pRenderTexture;
}
//=============================================================================
// レンダーターゲットの変更処理
// 戻り値：void						：なし
// 引数１：void						：なし
//=============================================================================
void CRenderTarget::ChangeRenderTarget(void)
{
	
	if(FAILED(getDevice()->SetRenderTarget(0, m_pRenderTexSurface)))
	{
		MessageBox(NULL,"レンダーターゲット変更失敗","警告",MB_OK);
	}
	//セット
	getDevice()->SetDepthStencilSurface(m_pZBuffer);
	
}

//=============================================================================
// レンダーターゲットのリセット処理
// 戻り値：void						：なし
// 引数１：void						：なし
// リセットというより厳密にはバックバッファに
// レンダーターゲットを戻しているだけ
//=============================================================================
void CRenderTarget::ResetRenderTarget(void)
{
	
	if(FAILED(getDevice()->SetRenderTarget(0, m_pBackBufferTexture)))
	{
		MessageBox(NULL,"レンダーターゲットリセット失敗","警告",MB_OK);
	}
	//Zバッファーセット
	getDevice()->SetDepthStencilSurface(m_pZBuffer);
	
}

//EOF