//ヘッダーインクルード
#include "CRender.h"
#include "CScene.h"
#include "CManager.h"
#include "CFade.h"
#include "CDebugProc.h"
#include "CInputKeyboard.h"
#include "CTitle.h"
#include "CGame.h"
#include "CEnding.h"
#include "CTutorial.h"

//クラス定義
//コンストラクタ
CRender::CRender()
{
//	m_mode = MODE_GAME;
	m_mode = MODE_TITLE;
//	m_mode = MODE_TUTOLIAL;
//	m_mode = MODE_RESULT;
}
//デストラクタ
CRender::~CRender()
{
//	SAFE_RELEASE(m_pBackBufferTexture);
//	SAFE_RELEASE(m_pRenderTexture);
//	SAFE_RELEASE(m_pRenderTexSurface);
//	SAFE_RELEASE(m_pZBuffer);
}

//初期化
HRESULT CRender::Init(HWND hWnd,BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferCount			= 1;						// バックバッファの数
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	d3dpp.Windowed					= bWindow;					// ウィンドウモード
	d3dpp.EnableAutoDepthStencil	= TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= /*D3DFMT_D24FS8;*/D3DFMT_D16;				// デプスバッファとして16bitを使う

	if(bWindow)
	{// ウィンドウモード
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{// フルスクリーンモード
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
									D3DDEVTYPE_HAL,							// ディスプレイタイプ
									hWnd,									// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
									&d3dpp,									// デバイスのプレゼンテーションパラメータ
									&m_pD3DDevice)))						// デバイスインターフェースへのポインタ
	{
		MessageBox(hWnd,"ERROR","低レベル",MB_OK);
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&m_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}
	SAFE_RELEASE(m_pD3D);		//Direct3Dオブジェクトの開放
	//レンダラーステートの設定
	//カリングをする
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);	
	//Zバッファ使用
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	//アルファブレンド
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, TRUE );	
	m_pD3DDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// サンプラーステートパラメータの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
	//深度値格納用の「テクスチャオブジェクト」の作成
	//１．レンダーターゲット用のテクスチャ作成
	/*
	D3DXCreateTexture(m_pD3DDevice,//デバイス
				 800,//テクスチャに描画結果を書き込む時のそのテクスチャの幅
				 600,//テクスチャに描画結果を書き込む時のそのテクスチャの高さ
				 0,//ミップマップレベル
				 D3DUSAGE_RENDERTARGET,//この定数がレンダーターゲットを示す
				 //D3DFMT_G16R16,//カラーフォーマット
				 D3DFMT_R8G8B8,
				 //D3DFMT_A16B16G16R16,
				 D3DPOOL_DEFAULT,
				 &m_pRenderTexture);//レンダーテクスチャポインタ
	*/
/*
	if(FAILED( D3DXCreateTexture(m_pD3DDevice,800,600,0,
		D3DUSAGE_RENDERTARGET,D3DFMT_R32F ,D3DPOOL_DEFAULT,&m_pRenderTexture)))
	{	
		if(FAILED( D3DXCreateTexture(m_pD3DDevice,800,600,0,
		D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8 ,D3DPOOL_DEFAULT,&m_pRenderTexture)))
		{
			MessageBox(0,"テクスチャの作成に失敗しました","",MB_OK);
			return E_FAIL;
		}			
	}
	//2 バックバッファをポインタに事前に入れておく
	m_pD3DDevice->GetRenderTarget(0,&m_pBackBufferTexture);



	//3レンダーターゲットとして作成したテクスチャのサーフェイスを取得
	m_pRenderTexture->GetSurfaceLevel(0,&m_pRenderTexSurface);
	
	//Zバッファ
	m_pD3DDevice->CreateDepthStencilSurface(800,600,/*D3DFMT_D24S8D3//DFMT_D16,D3DMULTISAMPLE_NONE,0,TRUE,&m_pZBuffer,NULL);
*/
	return S_OK;
}
//開放
void CRender::Uninit(void)
{
	SAFE_RELEASE(m_pD3DDevice); //Direct3dDeviceオブジェクトの開放
	CFade::Release();
}
//更新
void CRender::Update()
{

	CPhase	*lpPhase[] = 
	{
		CTitle::getInstance(),
		CTutorial::getInstance(),
		CGame::getInstance(),
		CEnding::getInstance(),
	};
		
	//各シーンオブジェクト更新
	
	//各シーンを呼び出す
	lpPhase[m_mode]->Phase((MODE *)&m_mode);
	
	CFade::getinstance()->Update();	
	//スクショ撮る
	if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_F7))
	{
		SaveSceneToFIle("sucreen.bmp",D3DXIFF_BMP);
	}
}
//描画
void CRender::Draw()
{
	CPhase	*lpPhase[] = 
	{
		CTitle::getInstance(),
		CTutorial::getInstance(),
		CGame::getInstance(),
		CEnding::getInstance(),
	};
/*
	//レンダーターゲットを変更
	ChangeRenderTarget();

	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//画面のクリア
	m_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(0,0,0,0),1.0f,0);	
	//描画開始
	if(SUCCEEDED(m_pD3DDevice->BeginScene()))				
	{
		
		//各シーンオブジェクト描画
		//各シーンを呼び出す
		lpPhase[m_mode]->Draw();
		CFade::getinstance()->Draw();
		CDebugProc::Print("FPS%d\n",GetFPS());
		CDebugProc::Draw();
		//描画の終了
		m_pD3DDevice->EndScene();
	}
//*/
	//バックバッファに戻す
//	ResetRenderTarget();
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	
	m_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(0,0,0,0),1.0f,0);	
	//描画開始
	if(SUCCEEDED(m_pD3DDevice->BeginScene()))				
	{
//		CFade::getinstance()->Draw();		
		//各シーンオブジェクト描画
		//各シーンを呼び出す
		lpPhase[m_mode]->Draw();
		CFade::getinstance()->Draw();
		CDebugProc::Print("FPS%d\n",GetFPS());
		CDebugProc::Draw();
		//描画の終了
		m_pD3DDevice->EndScene();
	}
//*/
	//フリップ処理(最終描画)
	m_pD3DDevice->Present(NULL,NULL,NULL,NULL);
}

//サーフェイスにファイルを保存
void CRender::SaveSceneToFIle(LPCTSTR szFileName,D3DXIMAGE_FILEFORMAT Format)
{
	//サーフェイス
	LPDIRECT3DSURFACE9 pSourceSurface=NULL;
	
	//バックバッファ取得
	m_pD3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pSourceSurface);
	//保存する
	D3DXSaveSurfaceToFile(szFileName,Format,pSourceSurface,NULL,NULL);
}

//=============================================================================
// レンダーテクスチャの取得処理
// 戻り値：LPDIRECT3DTEXTURE9		：レンダーテクスチャポインタ
// 引数１：void						：なし
//=============================================================================
IDirect3DTexture9* CRender::GetRenderTexture(void)
{
	//普通にLPDIRECT3DTEXTURE9 テクスチャのポインタをへんきゃくすればOK
	return m_pRenderTexture;
}
//=============================================================================
// レンダーターゲットの変更処理
// 戻り値：void						：なし
// 引数１：void						：なし
//=============================================================================
void CRender::ChangeRenderTarget(void)
{
	
	if(FAILED(m_pD3DDevice->SetRenderTarget(0, m_pRenderTexSurface)))
	{
		MessageBox(NULL,"レンダーターゲット変更失敗","警告",MB_OK);
	}
	//セット
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffer);
	
}

//=============================================================================
// レンダーターゲットのリセット処理
// 戻り値：void						：なし
// 引数１：void						：なし
// リセットというより厳密にはバックバッファに
// レンダーターゲットを戻しているだけ
//=============================================================================
void CRender::ResetRenderTarget(void)
{
	
	if(FAILED(m_pD3DDevice->SetRenderTarget(0, m_pBackBufferTexture)))
	{
		MessageBox(NULL,"レンダーターゲットリセット失敗","警告",MB_OK);
	}
	//Zバッファーセット
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffer);
	
}