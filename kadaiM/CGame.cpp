//=============================================================================
//
// �V�[���J�ڏ��� [Game.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CGame.h"
#include "CFade.h"
#include "CDebugProc.h"
#include "CInputKeyboard.h"
#include "CManager.h"
#include "CRender.h"
#include "CScene.h"
#include "CScene2D.h"
#include "CScene3D.h"
#include "CCamera.h"
#include "CLight.h"
#include "CSceneX.h"
#include "CSceneBillboard.h"
#include "CInputKeyboard.h"
#include "CDebugProc.h"
#include "CEnemy.h"
#include "CMeshField.h"
#include "CMeshWall.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CMeshCylinder.h"
#include "CMeshDome.h"
#include "CColision.h"
#include "CPaticle.h"
#include "CScore.h"
#include "CTimer.h"
#include "yuka.h"
#include "CPause.h"
#include "CSound.h"
#include "Clogo.h"
#include "CEnding.h"
#include "CSkyBox.h"
#include "Joy.h"

//�}�N����`
#define WALL_TO_FIELD	(250)

//�ÓI�����o�ϐ�������
CGame* CGame::m_instance = NULL;
CPlayer* CGame::m_pPlayer = NULL;
CEnemy* CGame::m_pEnemy[ENEMY_NUM_MAX] = {NULL};
CPlayerLife* CGame::m_pPlayLife[PLAYER_LIFE_MAX] = {NULL};
bool CGame::m_pause = false;
bool CGame::m_Cler = false;
bool CGame::m_Over = false;

bool dbflag = false;

//�C���X�^���X����
CGame* CGame::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CGame();
	}
	return m_instance;
}
//�C���X�^���X���
void CGame::freeInstance()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}
//������
bool CGame::Init(void *lpArgs)
{

	m_startCnt = 0;

	m_pRender = CManager::GetRender();

	//�J�����̏�����
	CCamera::getInstance()->Init(m_pRender);
/*
	if(m_plogo == NULL)
	{
		m_plogo = new Clogo();
	}
	if(m_pclaer == NULL)
	{
		m_pclaer = new Clogo();
	}
	if(m_pover == NULL)
	{
		m_pover = new Clogo();
	}
*/
	//�v���C���[
	m_pPlayer = CPlayer::Create(m_pRender,D3DXVECTOR3(250,0,-350));
//	CScene2D::Create(m_pRender,D3DXVECTOR3(100,100,0),"kaka",OBJTYPE_2D);
	
	//�[��
//	CSceneX::Create(m_pRender,D3DXVECTOR3(100,0,-200),"data\\Model\\naya.x","data\\Texture\\naya.jpg");
	//�W�[�v
//	CSceneX::Create(m_pRender,D3DXVECTOR3(200,0,-250),"data\\Model\\jeep.x","data\\Texture\\jeep.png");
	//�A��
//	CSceneX::Create(m_pRender,D3DXVECTOR3(150,0,-200),"data\\Model\\plant01.x",NULL);
//	CSceneX::Create(m_pRender,D3DXVECTOR3(200,0,-200),"data\\Model\\plant02.x",NULL);
//	CSceneX::Create(m_pRender,D3DXVECTOR3(250,0,-200),"data\\Model\\plant03.x",NULL);
//	CSceneX::Create(m_pRender,D3DXVECTOR3(300,0,-200),"data\\Model\\plant04.x",NULL);
//	CSceneX::Create(m_pRender,D3DXVECTOR3(350,0,-200),"data\\Model\\head.x",NULL);
	

	//�t�B�[���h
	CMeshField::Create(m_pRender,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),10,10,50.0f,50.0f,"data\\Texture\\field005.png");
	//��
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(1).x-WALL_TO_FIELD,0,CMeshField::GetVertex(1).z),D3DXVECTOR3(0,0,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(2).x+WALL_TO_FIELD,0,CMeshField::GetVertex(2).z),D3DXVECTOR3(0,D3DX_PI,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(3).x,0,CMeshField::GetVertex(3).z+WALL_TO_FIELD),D3DXVECTOR3(0,D3DX_PI/2.0f,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(0).x,0,CMeshField::GetVertex(0).z-WALL_TO_FIELD),D3DXVECTOR3(0,D3DX_PI/-2.0f,0));

	//�h�[��
	//CMeshDome::Create(m_pRender,D3DXVECTOR3(250,0,-250),D3DXVECTOR3(0,0,0));
	CSkyBox::Create(m_pRender,D3DXVECTOR3(250,0,-250),"data\\Model\\cube.x","data\\Texture\\sky005.jpg");
	//�~��
	//CMeshCylinder::Create(m_pRender,D3DXVECTOR3(250,0,-250),D3DXVECTOR3(0,0,0));
	//�X�R�A
//	CScore::Create(m_pRender,D3DXVECTOR3(0,0,0));
	//����
//	CTimer::Create(m_pRender,D3DXVECTOR3(0,0,0));
	
	//GetRady�����\��
//	m_plogo->Init(m_pRender,D3DXVECTOR3(400,300,0),200,100,"data\\Texture\\ready.png");
//	m_pclaer->Init(m_pRender,D3DXVECTOR3(400,300,0),200,100,"data\\Texture\\clear.png");
//	m_pover->Init(m_pRender,D3DXVECTOR3(400,300,0),200,100,"data\\Texture\\gameover.png");
	
	
	//�v���C���[�c�@�\��
//	m_pPlayLife[0] = CPlayerLife::Create(m_pRender,D3DXVECTOR3(25,550,0));
//	m_pPlayLife[1] = CPlayerLife::Create(m_pRender,D3DXVECTOR3(75,550,0));
//	m_pPlayLife[2] = CPlayerLife::Create(m_pRender,D3DXVECTOR3(125,550,0));

	//�G
//	m_pEnemy[0] = CEnemy::Create(m_pRender,D3DXVECTOR3(300,0,-250),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[1] = CEnemy::Create(m_pRender,D3DXVECTOR3(300,0,-150),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[2] = CEnemy::Create(m_pRender,D3DXVECTOR3(200,0,-150),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[3] = CEnemy::Create(m_pRender,D3DXVECTOR3(100,0,-150),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[4] = CEnemy::Create(m_pRender,D3DXVECTOR3(400,0,-250),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[5] = CEnemy::Create(m_pRender,D3DXVECTOR3(500,0,-250),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[6] = CEnemy::Create(m_pRender,D3DXVECTOR3(100,0,-50),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[7] = CEnemy::Create(m_pRender,D3DXVECTOR3(100,0,-250),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[8] = CEnemy::Create(m_pRender,D3DXVECTOR3(200,0,-350),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[9] = CEnemy::Create(m_pRender,D3DXVECTOR3(100,0,-350),0,0,ENEMY_NORMAL,"data\\Model\\golam.x","data\\Texture\\golam.png");
//	m_pEnemy[10] = CEnemy::Create(m_pRender,D3DXVECTOR3(250,250,-250),0,1,ENEMY_BOSS,"data\\Model\\golam.x","data\\Texture\\golam.png");
	//��
//	CYuka::Create(m_pRender,D3DXVECTOR3(300,20,-250));
//	CYuka::Create(m_pRender,D3DXVECTOR3(350,20,-250));
//	CYuka::Create(m_pRender,D3DXVECTOR3(400,20,-250));

	//�|�[�Y��ʏ�����
//	m_pPause = new CPause();
//	m_pPause->Init(m_pRender);
//	CPause::getInstance()->Init(m_pRender);

	//�t�H�O���g���邩
	/*
	D3DCAPS9 caps;
	ZeroMemory(&caps,sizeof(D3DCAPS9));
	m_pRender->getDevice()->GetDeviceCaps(&caps);	
	if( ( caps.RasterCaps & D3DPRASTERCAPS_FOGTABLE ) == 0 )	 
	{ 
		if(MessageBox(0,"�s�N�Z���t�H�O���g���Ȃ��\��������܂��B���s���܂���?",
			 "",MB_ABORTRETRYIGNORE) == IDABORT)
		{
			 return false;
		}
	}
	//�t�H�O�̐ݒ�
	{		 
		FLOAT 	Density=0.0009f;		

		m_pRender->getDevice()->SetRenderState(D3DRS_FOGENABLE, TRUE);
		m_pRender->getDevice()->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(255,255,255,255));
		m_pRender->getDevice()->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE );
		m_pRender->getDevice()->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP );
		m_pRender->getDevice()->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&Density));
	}
	
//	*/

	//�g�p�����f�[�^�����������ă��C���V�[����
	this->m_PhaseInfo.dwScene = CPhase::PHASE_MAIN;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;	

	

	m_pause = false;
	m_Cler = false;
	m_Over = false;
	m_initManager = true;
	m_endCnt = 0;
	m_pclaer->SetDrawFlag(false);
	m_pover->SetDrawFlag(false);

	//�T�E���h�Đ�
	CSound::getInstance()->PlaySound(SOUND_LABEL_BGM001);

	return true;
}

//�X�V
bool CGame::Update(void* lpArgs)
{
	
	//�J�����X�V
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_F7))
	{
		dbflag ^= true;
		
	}
	if(dbflag)
	{
		CCamera::getInstance()->UpdateDebug();
		
	}
	else
	{
		CCamera::getInstance()->Update();
	}
	CFade* pFade = CFade::getinstance();

	//�f�o�b�O�p
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_RETURN))
	{
		//m_Cler = true;
	}

	if(pFade->GetFadeMode() == FADE_OUT_FINISH)
	{
		
		pFade->SetFadeMode(FADE_IN);
		this->m_PhaseInfo.dwScene = CPhase::PHASE_RELEASE;
		this->m_PhaseInfo.dwSubScene = 0;
		this->m_PhaseInfo.nCount = 0;
	}
	//�|�[�Y
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_P) || CJoySystem::getInstance()->GetJoyBtnPush(JOY_BTN4))
	{
		m_pause ^= true;
	}

	if(m_pause)
	{
		CPause::getInstance()->Update();
		if(CPause::getInstance()->GetModeChange() == MODE_CONTINUE)
		{

		}
		if(CPause::getInstance()->GetModeChange()==MODE_RESET || CPause::getInstance()->GetModeChange()==MODE_QUIT)
		{
			if(pFade->GetFadeMode()==FADE_NONE)
			{
				pFade->SetFadeMode(FADE_OUT);
				
			}
		}
	}
	else
	{
		//�Q�[���I�[�o�[
		if(!m_pPlayer->GetLifeFlag())
		{
			m_Over = true;
			m_pover->SetDrawFlag(true);
		}
		/*
		//�Q�[���N���A
		if(CEnemy::GetEnemyCnt() == ENEMY_NUM_MAX)
		{
			m_Cler = true;
			m_pclaer->SetDrawFlag(true);
		}
		*/
		if(m_Cler || m_Over)
		{
			m_endCnt++;
			if(m_endCnt >= GAME_END_TIME)
			{
				if(pFade->GetFadeMode() == FADE_NONE)
				{
					pFade->SetFadeMode(FADE_OUT);
				}
			}
		}
		m_startCnt++;
		if(m_startCnt >= GAME_START_TIME)
		{
			m_plogo->SetDrawFlag(false);
		}
		//�X�V
		CScene::UpdateAll();
	}
//	CDebugProc::Print("�G�̐�\n",CEnemy::GetEnemyCnt());
	CDebugProc::Print("�Q�[�����C��\n");



	return true;
}

//�J��
bool CGame::Release(void* lpArgs)
{
	
	//�T�E���h�X�g�b�v
	CSound::getInstance()->StopSound(SOUND_LABEL_BGM001);
	
	m_plogo->Uninit();
	SAFE_DELETE(m_plogo);
	
	m_pclaer->Uninit();
	SAFE_DELETE(m_pclaer);

	m_pover->Uninit();
	SAFE_DELETE(m_pover);

	//�����L���O��ǂݍ���ł���
	CEnding::getInstance()->LoadRanking();
	//�����L���O�ݒ�
	CEnding::getInstance()->SetRank(CScore::GetScore());

	m_pRender->getDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	m_initManager = false;
	//���Z�b�g
	if(CPause::getInstance()->GetModeChange()==MODE_RESET)
	{
		//�Q�[��
		if(lpArgs != NULL)
		{
			*((DWORD *)lpArgs) = MODE_GAME;
		}	
	}
	else if(CPause::getInstance()->GetModeChange()==MODE_QUIT)
	{
		//�^�C�g����
		if(lpArgs != NULL)
		{
			*((DWORD *)lpArgs) = MODE_TITLE;
		}
	}
	if(m_Cler || m_Over)
	{
		//���U���g��ʂ�
		if(lpArgs != NULL)
		{
			*((MODE *)lpArgs) = MODE_RESULT;
		}
	}
	//�t�F�[�Y���g�p�������̂����J��
	CScene::FreePhase();

	//�|�[�Y�J��
	CPause::getInstance()->Uninit();
	

	//�g�p�����f�[�^�����������ď������V�[����
	this->m_PhaseInfo.dwScene = CPhase::PHASE_INIT;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;

	return true;
}
//�`��
bool CGame::Draw(void* lpArgs)
{
	if(m_initManager)
	{
		//�J�����ݒ�
		CCamera::getInstance()->SetCamera();
		if(m_pause)
		{
			CPause::getInstance()->Draw();
		}
		else
		{
			//�`��
			CScene::DrawAll();
			if(m_plogo != NULL)
			{
				m_plogo->Draw();
			}
			if(m_pclaer != NULL)
			{
				m_pclaer->Draw();
			}
			if(m_pover != NULL)
			{
				m_pover->Draw();
			}

		}
	}
	return true;
}
bool CGame::DrawShade(void* lpArgs)
{
	if(m_initManager)
	{
		if(m_pause)
		{
			CPause::getInstance()->Draw();
		}
		else
		{
			//�`��
			CScene::DrawShadeAll();
		}
	}
	return true;
}