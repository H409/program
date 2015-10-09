//=============================================================================
// レンダーテクスチャ処理 [RenderTexture.h]
// Author : MASAHIRO YAMAGUCHI
// リアルタイムにテクスチャに描画結果を書き込むことが出来ます。
//=============================================================================
#ifndef _RENDERTEXTURE_H_
#define _RENDERTEXTURE_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CRender.h"

//クラス定義
class CRenderTarget : public CRender
{
private:
	IDirect3DSurface9* m_pBackBufferTexture;		//テクスチャ
	IDirect3DTexture9* m_pRenderTexture;			//レンダーターゲット用のテクスチャ
	IDirect3DSurface9* m_pRenderTexSurface;			//テクスチャサーフェイス
	IDirect3DSurface9* m_pZBuffer;					//zMap

public:
	//コンストラクタ
	CRenderTarget();
	//デストラクタ
	virtual ~CRenderTarget();

	IDirect3DTexture9* GetRenderTexture(void);	//レンダーテクスチャの取得
	void ChangeRenderTarget(void); 				//レンダーターゲットの変更
	void ResetRenderTarget(void);				//レンダーターゲットを元に戻す(個々での戻すは通常のバックバッファに戻るということ)
};

#endif