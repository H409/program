//多重定義防止
#ifndef __CRENDER_H__
#define __CRENDER_H__

//ヘッダー
#include "main.h"

//前方宣言
class CScene;

//クラス
class CRender
{
private:
	LPDIRECT3D9				m_pD3D;					// Direct3D オブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;			// Deviceオブジェクト(描画に必要)
	MODE					m_mode;

	IDirect3DSurface9* m_pBackBufferTexture;		//テクスチャ
	IDirect3DTexture9* m_pRenderTexture;			//レンダーターゲット用のテクスチャ
	IDirect3DSurface9* m_pRenderTexSurface;			//テクスチャサーフェイス
	IDirect3DSurface9* m_pZBuffer;					//zMap

public:
	//コンストラクタ
	CRender();
	//デストラクタ
	virtual ~CRender();
	//初期化
	HRESULT Init(HWND hWnd,BOOL bWindow);
	//開放
	void Uninit(void);
	//更新
	void Update();
	//描画
	void Draw();
	MODE GetMode()
	{
		return m_mode;
	}
	//デバイス取得
	const LPDIRECT3DDEVICE9 getDevice()const
	{
		return m_pD3DDevice;
	}
	void SaveSceneToFIle(LPCTSTR szFileName,D3DXIMAGE_FILEFORMAT Format = D3DXIFF_BMP);
	
	IDirect3DTexture9* GetRenderTexture(void);	//レンダーテクスチャの取得
	void ChangeRenderTarget(void); 				//レンダーターゲットの変更
	void ResetRenderTarget(void);				//レンダーターゲットを元に戻す(個々での戻すは通常のバックバッファに戻るということ)
	IDirect3DSurface9* GetRenderSurface(void)
	{
		return m_pRenderTexSurface;
	}
};


#endif