//�w�b�_�[�C���N���[�h
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
#include "CFade.h"
#include "CTitle.h"
#include "CTutorial.h"
#include "CGame.h"
#include "CEnding.h"
#include "CPause.h"
#include "CSound.h"
#include "Joy.h"

//�}�N����`
#define WALL_TO_FIELD	(250)

//�ÓI�����o�ϐ��̏�����
CRender* CManager::m_pRender = NULL;
CPlayer* CManager::m_pPlayer = NULL;
CFade*	CManager::m_pFade = NULL;
//������
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd,bool bWindow)
{
	//�쐬
	m_pRender = new CRender();
	
//	m_pLight = new CLight();
//	m_pCamera = new CCamera();
	m_pDebugProc = new CDebugProc();


	//�L�[�{�[�h������
	CInputKeyboard::getInstance()->Init(hInstance,hWnd);
	
	//�W���C�X�e�B�b�N������
	CJoySystem::getInstance()->JoyInitInfo();

	//�����_�[�N���X
	m_pRender->Init(hWnd,bWindow);
	//�f�o�b�O�p������
	m_pDebugProc->Init(m_pRender);
	//�T�E���h������
	CSound::getInstance()->InitSound(hWnd);

	//���C�g������
//	m_pLight->Init(m_pRender);
	
	CLight::getInstance()->Init(m_pRender);
	

	//�V�[���n�I�u�W�F�N�g
	///*
//	CScene2D::Create(m_pRender,D3DXVECTOR3(100,100,0));
//	CScene3D::Create(m_pRender,D3DXVECTOR3(0,0,0));
//	CSceneX::Create(m_pRender,D3DXVECTOR3(100,10,0),"data\\Model\\airplane000.x");
//	CSceneBillboard::Create(m_pRender,D3DXVECTOR3(-100,0,0));
	//*/
	
	
//	CSceneX::Create(m_pRender,D3DXVECTOR3(0,10,0));
//	CEnemy::Create(m_pRender,D3DXVECTOR3(100,10,0));
//	CSceneX::Create(m_pRender,D3DXVECTOR3(330,10,0));
	//�J����
//	m_pCamera->Init(m_pRender);
	CCamera::getInstance()->Init(m_pRender);
/*
	//�v���C���[
	m_pPlayer = CPlayer::Create(m_pRender,D3DXVECTOR3(250,0,-250));
	
	//�p�[�e�B�N��
//	CPaticle::Create(m_pRender,D3DXVECTOR3(250,0,-250),"data\\Texture\\effect000.jpg");

	//�[��
	CSceneX::Create(m_pRender,D3DXVECTOR3(100,0,-200),"data\\Model\\naya.x","data\\Texture\\naya.jpg");
	//�A��
	CSceneX::Create(m_pRender,D3DXVECTOR3(150,0,-200),"data\\Model\\plant01.x",NULL);
	CSceneX::Create(m_pRender,D3DXVECTOR3(200,0,-200),"data\\Model\\plant02.x",NULL);
	CSceneX::Create(m_pRender,D3DXVECTOR3(250,0,-200),"data\\Model\\plant03.x",NULL);
	CSceneX::Create(m_pRender,D3DXVECTOR3(300,0,-200),"data\\Model\\plant04.x",NULL);
	CSceneX::Create(m_pRender,D3DXVECTOR3(350,0,-200),"data\\Model\\plant05.x",NULL);
	
//	CMeshField::Create(m_pRender,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),50,50,50.0f,50.0f,"data\\Texture\\field000.jpg");
//	CSceneBillboard::Create(m_pRender,D3DXVECTOR3(100,0,-100),"data\\Texture\\tree000.png",100.0f);
	//�t�B�[���h
	CMeshField::Create(m_pRender,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),10,10,50.0f,50.0f,"data\\Texture\\field005.png");
	//��
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(1).x-WALL_TO_FIELD,0,CMeshField::GetVertex(1).z),D3DXVECTOR3(0,0,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(2).x+WALL_TO_FIELD,0,CMeshField::GetVertex(2).z),D3DXVECTOR3(0,D3DX_PI,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(3).x,0,CMeshField::GetVertex(3).z+WALL_TO_FIELD),D3DXVECTOR3(0,D3DX_PI/2.0f,0));
	CMeshWall::Create(m_pRender,D3DXVECTOR3(CMeshField::GetVertex(0).x,0,CMeshField::GetVertex(0).z-WALL_TO_FIELD),D3DXVECTOR3(0,D3DX_PI/-2.0f,0));

//	CMeshField::Create(m_pRender,D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),1,1,100.0f,100.0f,"data\\Texture\\field000.jpg");
	//�h�[��
	CMeshDome::Create(m_pRender,D3DXVECTOR3(250,0,-250),D3DXVECTOR3(0,0,0));
	//�~��
	CMeshCylinder::Create(m_pRender,D3DXVECTOR3(250,0,-250),D3DXVECTOR3(0,0,0));
	//�X�R�A
	CScore::Create(m_pRender,D3DXVECTOR3(0,0,0));
	//����
	CTimer::Create(m_pRender,D3DXVECTOR3(0,0,0));
	//�G
//	CEnemy::Create(m_pRender,D3DXVECTOR3(300,0,-250));
	//��
	CYuka::Create(m_pRender,D3DXVECTOR3(300,20,-250));
	CYuka::Create(m_pRender,D3DXVECTOR3(350,20,-250));
	CYuka::Create(m_pRender,D3DXVECTOR3(400,20,-250));
*/
	//�t�F�[�h������
	CFade::getinstance()->Init(m_pRender);
	
	return S_OK;
}
//�J��
void CManager::Uninit()
{
	
	// �I������
	CInputKeyboard::deleteInstance();
	CJoySystem::Release();
	CColision::Release();
	//�T�E���h�J��
	CSound::getInstance()->UninitSound();
	CSound::Release();
	m_pRender->Uninit();
	m_pDebugProc->Uninit();
//	m_pScenes->Release();
	CScene::ReleaseAll();

	//�e�t�F�[�Y�J��
	CTitle::freeInstance();
	CTutorial::freeInstance();
	CGame::freeInstance();
	CEnding::freeInstance();

	CFade::Release();
	CPause::Resease();

	
	SAFE_DELETE(m_pRender);
	CLight::Release();
	CCamera::Release();
//	SAFE_DELETE(m_pLight);
//	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pDebugProc);
}
//�X�V
void CManager::Updata()
{
	
	//�L�[���͍X�V
	CInputKeyboard::getInstance()->Update();
	//�W���C�X�e�B�b�N�X�V
	CJoySystem::getInstance()->JoyUpdateInfo();
	//CCamera::getInstance()->UpdateDebug();

	
	
	//�`��N���X�X�V	
	m_pRender->Update();


	
}
//�`��
void CManager::Draw()
{
	
	//�`��
	m_pRender->Draw();
	
	
	
}