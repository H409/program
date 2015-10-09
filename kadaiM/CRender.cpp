//�w�b�_�[�C���N���[�h
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

//�N���X��`
//�R���X�g���N�^
CRender::CRender()
{
//	m_mode = MODE_GAME;
	m_mode = MODE_TITLE;
//	m_mode = MODE_TUTOLIAL;
//	m_mode = MODE_RESULT;
}
//�f�X�g���N�^
CRender::~CRender()
{
//	SAFE_RELEASE(m_pBackBufferTexture);
//	SAFE_RELEASE(m_pRenderTexture);
//	SAFE_RELEASE(m_pRenderTexSurface);
//	SAFE_RELEASE(m_pZBuffer);
}

//������
HRESULT CRender::Init(HWND hWnd,BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferCount			= 1;						// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			= SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			= SCREEN_HEIGHT;			// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;			// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed					= bWindow;					// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil	= TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= /*D3DFMT_D24FS8;*/D3DFMT_D16;				// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if(bWindow)
	{// �E�B���h�E���[�h
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{// �t���X�N���[�����[�h
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
									D3DDEVTYPE_HAL,							// �f�B�X�v���C�^�C�v
									hWnd,									// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
									&d3dpp,									// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
									&m_pD3DDevice)))						// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		MessageBox(hWnd,"ERROR","�჌�x��",MB_OK);
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&m_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}
	SAFE_RELEASE(m_pD3D);		//Direct3D�I�u�W�F�N�g�̊J��
	//�����_���[�X�e�[�g�̐ݒ�
	//�J�����O������
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);	
	//Z�o�b�t�@�g�p
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
	//�A���t�@�u�����h
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, TRUE );	
	m_pD3DDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
	//�[�x�l�i�[�p�́u�e�N�X�`���I�u�W�F�N�g�v�̍쐬
	//�P�D�����_�[�^�[�Q�b�g�p�̃e�N�X�`���쐬
	/*
	D3DXCreateTexture(m_pD3DDevice,//�f�o�C�X
				 800,//�e�N�X�`���ɕ`�挋�ʂ��������ގ��̂��̃e�N�X�`���̕�
				 600,//�e�N�X�`���ɕ`�挋�ʂ��������ގ��̂��̃e�N�X�`���̍���
				 0,//�~�b�v�}�b�v���x��
				 D3DUSAGE_RENDERTARGET,//���̒萔�������_�[�^�[�Q�b�g������
				 //D3DFMT_G16R16,//�J���[�t�H�[�}�b�g
				 D3DFMT_R8G8B8,
				 //D3DFMT_A16B16G16R16,
				 D3DPOOL_DEFAULT,
				 &m_pRenderTexture);//�����_�[�e�N�X�`���|�C���^
	*/
/*
	if(FAILED( D3DXCreateTexture(m_pD3DDevice,800,600,0,
		D3DUSAGE_RENDERTARGET,D3DFMT_R32F ,D3DPOOL_DEFAULT,&m_pRenderTexture)))
	{	
		if(FAILED( D3DXCreateTexture(m_pD3DDevice,800,600,0,
		D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8 ,D3DPOOL_DEFAULT,&m_pRenderTexture)))
		{
			MessageBox(0,"�e�N�X�`���̍쐬�Ɏ��s���܂���","",MB_OK);
			return E_FAIL;
		}			
	}
	//2 �o�b�N�o�b�t�@���|�C���^�Ɏ��O�ɓ���Ă���
	m_pD3DDevice->GetRenderTarget(0,&m_pBackBufferTexture);



	//3�����_�[�^�[�Q�b�g�Ƃ��č쐬�����e�N�X�`���̃T�[�t�F�C�X���擾
	m_pRenderTexture->GetSurfaceLevel(0,&m_pRenderTexSurface);
	
	//Z�o�b�t�@
	m_pD3DDevice->CreateDepthStencilSurface(800,600,/*D3DFMT_D24S8D3//DFMT_D16,D3DMULTISAMPLE_NONE,0,TRUE,&m_pZBuffer,NULL);
*/
	return S_OK;
}
//�J��
void CRender::Uninit(void)
{
	SAFE_RELEASE(m_pD3DDevice); //Direct3dDevice�I�u�W�F�N�g�̊J��
	CFade::Release();
}
//�X�V
void CRender::Update()
{

	CPhase	*lpPhase[] = 
	{
		CTitle::getInstance(),
		CTutorial::getInstance(),
		CGame::getInstance(),
		CEnding::getInstance(),
	};
		
	//�e�V�[���I�u�W�F�N�g�X�V
	
	//�e�V�[�����Ăяo��
	lpPhase[m_mode]->Phase((MODE *)&m_mode);
	
	CFade::getinstance()->Update();	
	//�X�N�V���B��
	if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_F7))
	{
		SaveSceneToFIle("sucreen.bmp",D3DXIFF_BMP);
	}
}
//�`��
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
	//�����_�[�^�[�Q�b�g��ύX
	ChangeRenderTarget();

	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//��ʂ̃N���A
	m_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(0,0,0,0),1.0f,0);	
	//�`��J�n
	if(SUCCEEDED(m_pD3DDevice->BeginScene()))				
	{
		
		//�e�V�[���I�u�W�F�N�g�`��
		//�e�V�[�����Ăяo��
		lpPhase[m_mode]->Draw();
		CFade::getinstance()->Draw();
		CDebugProc::Print("FPS%d\n",GetFPS());
		CDebugProc::Draw();
		//�`��̏I��
		m_pD3DDevice->EndScene();
	}
//*/
	//�o�b�N�o�b�t�@�ɖ߂�
//	ResetRenderTarget();
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	
	m_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(0,0,0,0),1.0f,0);	
	//�`��J�n
	if(SUCCEEDED(m_pD3DDevice->BeginScene()))				
	{
//		CFade::getinstance()->Draw();		
		//�e�V�[���I�u�W�F�N�g�`��
		//�e�V�[�����Ăяo��
		lpPhase[m_mode]->Draw();
		CFade::getinstance()->Draw();
		CDebugProc::Print("FPS%d\n",GetFPS());
		CDebugProc::Draw();
		//�`��̏I��
		m_pD3DDevice->EndScene();
	}
//*/
	//�t���b�v����(�ŏI�`��)
	m_pD3DDevice->Present(NULL,NULL,NULL,NULL);
}

//�T�[�t�F�C�X�Ƀt�@�C����ۑ�
void CRender::SaveSceneToFIle(LPCTSTR szFileName,D3DXIMAGE_FILEFORMAT Format)
{
	//�T�[�t�F�C�X
	LPDIRECT3DSURFACE9 pSourceSurface=NULL;
	
	//�o�b�N�o�b�t�@�擾
	m_pD3DDevice->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pSourceSurface);
	//�ۑ�����
	D3DXSaveSurfaceToFile(szFileName,Format,pSourceSurface,NULL,NULL);
}

//=============================================================================
// �����_�[�e�N�X�`���̎擾����
// �߂�l�FLPDIRECT3DTEXTURE9		�F�����_�[�e�N�X�`���|�C���^
// �����P�Fvoid						�F�Ȃ�
//=============================================================================
IDirect3DTexture9* CRender::GetRenderTexture(void)
{
	//���ʂ�LPDIRECT3DTEXTURE9 �e�N�X�`���̃|�C���^���ւ񂫂Ⴍ�����OK
	return m_pRenderTexture;
}
//=============================================================================
// �����_�[�^�[�Q�b�g�̕ύX����
// �߂�l�Fvoid						�F�Ȃ�
// �����P�Fvoid						�F�Ȃ�
//=============================================================================
void CRender::ChangeRenderTarget(void)
{
	
	if(FAILED(m_pD3DDevice->SetRenderTarget(0, m_pRenderTexSurface)))
	{
		MessageBox(NULL,"�����_�[�^�[�Q�b�g�ύX���s","�x��",MB_OK);
	}
	//�Z�b�g
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffer);
	
}

//=============================================================================
// �����_�[�^�[�Q�b�g�̃��Z�b�g����
// �߂�l�Fvoid						�F�Ȃ�
// �����P�Fvoid						�F�Ȃ�
// ���Z�b�g�Ƃ�����茵���ɂ̓o�b�N�o�b�t�@��
// �����_�[�^�[�Q�b�g��߂��Ă��邾��
//=============================================================================
void CRender::ResetRenderTarget(void)
{
	
	if(FAILED(m_pD3DDevice->SetRenderTarget(0, m_pBackBufferTexture)))
	{
		MessageBox(NULL,"�����_�[�^�[�Q�b�g���Z�b�g���s","�x��",MB_OK);
	}
	//Z�o�b�t�@�[�Z�b�g
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffer);
	
}