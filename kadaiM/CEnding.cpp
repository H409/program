//=============================================================================
//
// �e�t�F�[�Y���� [CEnding.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//�x����������
#pragma warning(disable:4996)

//�w�b�_�[�C���N���[�h
#include "CEnding.h"
#include "CFade.h"
#include "CDebugProc.h"
#include "CInputKeyboard.h"
#include "CManager.h"
#include "CSound.h"
#include "CPaticle.h"
#include "CCamera.h"
#include "utill_lib.h"
#include "Joy.h"

//�}�N����`
#define FILE_NAME "data\\rank\\ranking.bin"
#define END_CNT_MAX	(200)

//�ÓI�����o�ϐ�������
CEnding* CEnding::m_instance = NULL;

//�C���X�^���X����
CEnding* CEnding::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CEnding();
	}
	return m_instance;
}
//�C���X�^���X���
void CEnding::freeInstance()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

//������
bool CEnding::Init(void *lpArgs)
{
	m_pRender = CManager::GetRender();

	//�J�����̏�����
	CCamera::getInstance()->TitleInit(m_pRender);

	m_EndCnt = 0;

	if(m_pPushLogo == NULL)
	{
		m_pPushLogo = new Clogo();
	}
	//�����L���O�ǂݍ���
	LoadRanking();

	//�i���o�[����
	for(int i = 0;i < RANK_DIGIT;i++)
	{
		m_pRank1[i] = CNumber::Create(m_pRender,D3DXVECTOR3(static_cast<float>(i*50)+225,+225,0));
		m_pRank2[i] = CNumber::Create(m_pRender,D3DXVECTOR3(static_cast<float>(i*50)+225,+325,0));
		m_pRank3[i] = CNumber::Create(m_pRender,D3DXVECTOR3(static_cast<float>(i*50)+225,+425,0));

		m_pRank1[i]->ChengeNumber(0);
		m_pRank2[i]->ChengeNumber(0);
		m_pRank3[i]->ChengeNumber(0);
	}
	int nNumber1[RANK_DIGIT] = {0};
	int nNumber2[RANK_DIGIT] = {0};
	int nNumber3[RANK_DIGIT] = {0};

	for(int i = 0,j = RANK_DIGIT-1;i < RANK_DIGIT;i++,j--)
	{
		nNumber1[j] = (m_Rank[0]/(int)pow((double)10,(double)i))%(int)10;
		nNumber2[j] = (m_Rank[1]/(int)pow((double)10,(double)i))%(int)10;
		nNumber3[j] = (m_Rank[2]/(int)pow((double)10,(double)i))%(int)10;
	}
	for(int i = 0;i < RANK_DIGIT;i++)
	{
		m_pRank1[i]->ChengeNumber(nNumber1[i]);
		m_pRank2[i]->ChengeNumber(nNumber2[i]);
		m_pRank3[i]->ChengeNumber(nNumber3[i]);
	}	

	

	CScene2D::Create(m_pRender,D3DXVECTOR3(400,300,0),"data\\Texture\\Result.png",OBJTYPE_2D);
	CScene2D::Create(m_pRender,D3DXVECTOR3(50,550,0),"data\\Texture\\jyujika.png",OBJTYPE_2DGIM);
	CScene2D::Create(m_pRender,D3DXVECTOR3(750,550,0),"data\\Texture\\jyujika1.png",OBJTYPE_2DGIM);

	m_pPushLogo->Init(m_pRender,D3DXVECTOR3(400,550,0),200,50,"data\\Texture\\push.png");
//	CPaticle::Create(m_pRender,D3DXVECTOR3(0,0,-50),"data\\Texture\\spark.bmp");
//	CPaticle::Create(m_pRender,D3DXVECTOR3(0,0,-50),"data\\Texture\\smoke.bmp");
	m_initManager = true;
	
	//���y�Đ�
	CSound::getInstance()->PlaySound(SOUND_LABEL_BGM004);
	//�g�p�����f�[�^�����������ă��C���V�[����
	this->m_PhaseInfo.dwScene = CPhase::PHASE_MAIN;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;	

	return true;
}

//�X�V
bool CEnding::Update(void* lpArgs)
{
	m_EndCnt++;

	CFade* pFade = CFade::getinstance();

	m_pPushLogo->Update();

	for(int i = 0;i < RANK_DIGIT;i++)
	{
		m_pRank1[i]->Update();
		m_pRank2[i]->Update();
		m_pRank3[i]->Update();

		

	}
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_RETURN) || CJoySystem::getInstance()->GetJoyBtnPush(JOY_BTN1))
	{
		if(pFade->GetFadeMode() == FADE_NONE)
		{
			pFade->SetFadeMode(FADE_OUT);
		}
			
	}
	if(m_EndCnt >= END_CNT_MAX)
	{
		if(pFade->GetFadeMode() == FADE_NONE)
		{
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

	CDebugProc::Print("�G���f�B���O���C��\n");
	return true;
}

//�J��
bool CEnding::Release(void* lpArgs)
{
	//�t�F�[�Y���g�p�������̂����J��
	CScene::FreePhase();

	m_pPushLogo->Uninit();
	SAFE_DELETE(m_pPushLogo);
	
	m_EndCnt = 0;

	for(int i = 0;i < RANK_DIGIT;i++)
	{
		m_pRank1[i]->Uninit();
		SAFE_DELETE(m_pRank1[i]);
		
		m_pRank2[i]->Uninit();
		SAFE_DELETE(m_pRank2[i]);
		
		m_pRank3[i]->Uninit();
		SAFE_DELETE(m_pRank3[i]);
	}

	m_initManager = false;
	
	//���y��~
	CSound::getInstance()->StopSound(SOUND_LABEL_BGM004);

	if(lpArgs != NULL)
	{
		*((MODE *)lpArgs) = MODE_TITLE;
	}
	
	//�g�p�����f�[�^�����������ď������V�[����
	this->m_PhaseInfo.dwScene = CPhase::PHASE_INIT;
	this->m_PhaseInfo.dwSubScene = 0;
	this->m_PhaseInfo.nCount = 0;

	return true;
}
//�`��
bool CEnding::Draw(void* lpArgs)
{
	if(m_initManager)
	{
		//�J�����ݒ�
		CCamera::getInstance()->SetCamera();
		//�`��
		CScene::DrawAll();
		if(m_pPushLogo != NULL)
		{
			m_pPushLogo->Draw();
		}
		for(int i = 0;i < RANK_DIGIT;i++)
		{
			m_pRank1[i]->Draw();
			m_pRank2[i]->Draw();
			m_pRank3[i]->Draw();
		}
	}
	return true;
}
bool CEnding::DrawShade(void* lpArgs)
{
	if(m_initManager)
	{
		//�J�����ݒ�
		CCamera::getInstance()->SetCamera();
		//�`��
		CScene::DrawShadeAll();
	}
	return true;
}

//��������
bool CEnding::SaveRanking()
{


	//�ϐ��錾
	FILE *fp = NULL;
	
	// �t�@�C���̃I�[�v��
	fp = fopen( FILE_NAME, "wb" );

	//��������
	// �I�[�v���`�F�b�N
	if( fp != NULL )
	{
		// �f�[�^��������
		for(int i = 0;i < RANK_MAX-1;i++)
		{
			fwrite(&m_Rank[i],sizeof(int),1,fp);
		}
		// �t�@�C���N���[�Y
		fclose( fp );
	}
	else
	{
		// �t�@�C���N���[�Y
		fclose( fp );
		return false;
	}	
	
	return TRUE;
}
//�ǂݍ���
bool CEnding::LoadRanking()
{
	
	//�ϐ��錾
	FILE *fp = NULL;

	// �t�@�C���̃I�[�v��
	fp = fopen( FILE_NAME, "rb" );

	//�ǂݍ���
	// �t�@�C�����J������f�[�^��ǂݍ���
	if( fp != NULL )
	{
		// �f�[�^�ǂݍ���

		for(int i = 0;i < RANK_MAX-1;i++)
		{
			fread(&m_Rank[i],sizeof(int),1,fp);
		}
		// �t�@�C���N���[�Y
		fclose( fp );
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}
//�ݒ�
void CEnding::SetRank(int iNum)
{
/*	�f�o�b�O�p
	m_Rank[0] = 300;
	m_Rank[1] = 200;
	m_Rank[2] = 100;
//*/	

	//�Ō�̗v�f�Ɍ��݃v���C���Ă����Q�[���̃X�R�A��ݒ�
	m_Rank[RANK_MAX-1] = iNum;
	//�N�C�b�N�\�[�g���s��
	QuickSort(&m_Rank[0],0,RANK_MAX,DESC);
	//��������
	this->SaveRanking();
	

}
//�擾
int CEnding::GetRank(int iNum)
{
	if(iNum > RANK_MAX)
	{
		return 0;
	}
	return m_Rank[iNum];
}
//eof