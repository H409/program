//=============================================================================
//
// �v���~�e�B�u�\������ [main.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

#include "main.h"
#include "CManager.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MUTEX_NAME	("MyGame")
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// Device�I�u�W�F�N�g(�`��ɕK�v)
int					g_nCountFPS;			// FPS�J�E���^
//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//���������[�N�`�F�b�N
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );


	HANDLE			hMutex = NULL;	//���d�N���h�~�p
		
	//���~���[�e�b�N�X�I�u�W�F�N�g�̐���
	hMutex = CreateMutex(NULL,TRUE,MUTEX_NAME);
	//���d�N���̃`�F�b�N
	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
		//���d�N�����m�F���ꂽ�狭���I��������
		MessageBox(NULL,"�A�v���P�[�V�����͊��ɊJ����Ă��܂�","�N���G���[",MB_OK);
		return 0;
	}
	//�v�Z�p
	RECT rc = {0};
	int nWidth = 0,nHeight = 0;
	int nWindowX = -1, nWindowY = -1;
	DWORD	dwWindowStyle = WS_OVERLAPPEDWINDOW&~(WS_THICKFRAME | WS_MAXIMIZEBOX);
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

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
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);


	//�E�B���h�E�T�C�Y�𒲐�
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
	// �E�B���h�E�̍쐬
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
	//�ϐ��錾
	CManager*			pManager;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	// ����������(�E�B���h�E���쐬���Ă���s��)
	pManager = new CManager();
	if(FAILED(pManager->Init(hInstance,hWnd,TRUE)))
	{
		return -1;
	}

	
	//�t���[���J�E���g������
	timeBeginPeriod(1);				// ����\��ݒ�
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{// Windows�̏���
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5�b���ƂɎ��s
			{
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				pManager->Updata();	
				// �`�揈��
				pManager->Draw();
		
				dwFrameCount++;
			}
		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	//�J��
	pManager->Uninit();
	
	SAFE_DELETE(pManager);

	//���~���[�e�b�N�X�I�u�W�F�N�g�̉��
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);


	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
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
