//=============================================================================
//
// プリミティブ表示処理 [main.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

#include "main.h"
#include "CManager.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MUTEX_NAME	("MyGame")
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Deviceオブジェクト(描画に必要)
int					g_nCountFPS;			// FPSカウンタ
//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//メモリリークチェック
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );


	HANDLE			hMutex = NULL;	//多重起動防止用
		
	//▼ミューテックスオブジェクトの生成
	hMutex = CreateMutex(NULL,TRUE,MUTEX_NAME);
	//多重起動のチェック
	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
		//多重起動が確認されたら強制終了させる
		MessageBox(NULL,"アプリケーションは既に開かれています","起動エラー",MB_OK);
		return 0;
	}
	//計算用
	RECT rc = {0};
	int nWidth = 0,nHeight = 0;
	int nWindowX = -1, nWindowY = -1;
	DWORD	dwWindowStyle = WS_OVERLAPPEDWINDOW&~(WS_THICKFRAME | WS_MAXIMIZEBOX);
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND hWnd;
	MSG msg;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);


	//ウィンドウサイズを調整
	SetRect(&rc,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	AdjustWindowRectEx(&rc,dwWindowStyle,FALSE,0);
	nWidth = rc.right-rc.left;
	nHeight = rc.bottom-rc.top;
	
	if(nWindowX == -1)
	{
		nWindowX = (GetSystemMetrics(SM_CXSCREEN)-nWidth)>>1;
	}
	if(nWindowY == -1)
	{
		nWindowY = (GetSystemMetrics(SM_CYSCREEN)-nHeight)>>1;
	}

	//&~WS_MINIMIZEBOX
	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						WINDOW_NAME,
						dwWindowStyle,
						nWindowX,
						nWindowY,
						nWidth,
						nHeight,
						NULL,
						NULL,
						hInstance,
						NULL);
	//変数宣言
	CManager*			pManager;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// 初期化処理(ウィンドウを作成してから行う)
	pManager = new CManager();
	if(FAILED(pManager->Init(hInstance,hWnd,TRUE)))
	{
		return -1;
	}

	
	//フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// メッセージを取得しなかった場合"0"を返す
		{// Windowsの処理
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				pManager->Updata();	
				// 描画処理
				pManager->Draw();
		
				dwFrameCount++;
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	//開放
	pManager->Uninit();
	
	SAFE_DELETE(pManager);

	//▼ミューテックスオブジェクトの解放
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);


	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
			case VK_ESCAPE:
				DestroyWindow(hWnd);
				break;
			case VK_F7:
				
				break;
		}
			
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int GetFPS(void)
{
	return g_nCountFPS;
}
