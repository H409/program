//=============================================================================
//
// �V�[���J�ڏ��� [CTutorial.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CTutorial.h"
#include "CFade.h"
#include "CDebugProc.h"
#include "CInputKeyboard.h"
#include "CManager.h"
#include "CScene2D.h"
#include "CSound.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "Joy.h"

//�ÓI�����o�ϐ�������
CTutorial* CTutorial::m_instance = NULL;

//�C���X�^���X����
CTutorial* CTutorial::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CTutorial();
	}
	return m_instance;
}
//�C���X�^���X���
void CTutorial::freeInstance()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}
//������
bool CTutorial::Init(void *lpArgs)
{
	m_pRender = CManager::GetRender();

	if(m_pPushLogo == NULL)
	{
		m_pPushLogo = new Clogo();
	}
	
	CScene2D::Create(m_pRender,D3DXVECTOR3(400,300,0),"data\\Texture\\sucreen3.bmp",OBJTYPE_2D);
	CScene2D::Create(m_pRender,D3DXVECTOR3(400,300,0),"data\\Texture\\Tutorial.png",OBJTYPE_2D);
	CScene2D::Create(m_pRender,D3DXVECTOR3(50,550,0),"data\\Texture\\jyujika.png",OBJTYPE_2DGIM);
	CScene2D::Create(m_pRender,D3DXVECTOR3(750,550,0),"data\\Texture\\jyujika1.png",OBJTYPE_2DGIM);
	m_pPushLogo->Init(m_pRender,D3DXVECTOR3(400,480,0),200,50,"data\\Texture\\push.png");	
//	CPlayer::Create(m_pRender,D3DXVECTOR3(250,0,-250));

	m_initManager = true;
	//�T�E���h�Đ�
	CSound::getInstance()->PlaySound(SOUND_LABEL_BGM003);
	//�g�p�����f�[�^�����������ă��C���V�[����
	this->m_PhaseInfo.dwScene = CPhase::PHASE_MAIN;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;	

	return true;
}

//�X�V
bool CTutorial::Update(void* lpArgs)
{

	CFade* pFade = CFade::getinstance();

	m_pPushLogo->Update();

	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_RETURN) || CJoySystem::getInstance()->GetJoyBtnPush(JOY_BTN1))
	{
		if(pFade->GetFadeMode() == FADE_NONE)
		{
			//�T�E���h�Đ�
			CSound::getInstance()->PlaySound(SOUND_LABEL_SE_YES);
			pFade->SetFadeMode(FADE_OUT);
		}
			
	}
	if(pFade->GetFadeMode() == FADE_OUT_FINISH)
	{
		
		
		pFade->SetFadeMode(FADE_IN);
		this->m_PhaseInfo.dwScene = CPhase::PHASE_RELEASE;
		this->m_PhaseInfo.dwSubScene = 0;
		this->m_PhaseInfo.nCount = 0;
	}	
	//�X�V
	CScene::UpdateAll();

	CDebugProc::Print("�^�C�g�����C��\n");
	return true;
}

//�J��
bool CTutorial::Release(void* lpArgs)
{
	//�T�E���h���~�߂�
	CSound::getInstance()->StopSound(SOUND_LABEL_BGM003);

	m_pPushLogo->Uninit();
	SAFE_DELETE(m_pPushLogo);

	//�t�F�[�Y���g�p�������̂����J��
	CScene::FreePhase();
	if(lpArgs != NULL)
	{
		*((MODE *)lpArgs) = MODE_GAME;
	}
	m_initManager = false;
	
	//�g�p�����f�[�^�����������ď������V�[����
	this->m_PhaseInfo.dwScene = CPhase::PHASE_INIT;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;

	return true;
}
//�`��
bool CTutorial::Draw(void* lpArgs)
{
	//�`��
	if(m_initManager)
	{
		
		CScene::DrawAll();
		if(m_pPushLogo != NULL)
		{
			m_pPushLogo->Draw();
		}
	}
	return true;
}
bool CTutorial::DrawShade(void* lpArgs)
{
	if(m_initManager)
	{
		//�`��
		CScene::DrawShadeAll();
	}
	return true;
}