//�w�b�_�[�C���N���[�h
#include "CCamera.h"
#include "CRender.h"
#include <cmath>
#include "CPlayer.h"
#include "CDebugProc.h"

//�}�N��
#define CAMERA_POS_SPEED	( 2.0f )
#define CAMERA_LOOK_AT		(0.0f)
#define CAMERA_EYE_SEED		(1.0f);
#define CAMERA_AT_SEED		(0.05f)
#define CMAERA_SIGHT_MOVE		(0.5f)			// ���_�ړ��W��
#define CAMERA_POS_HEIGHT	(50.0f)
#define CAMERA_ROT_SEED		(0.95f)

float g_angleYaw = 0; 

CCamera* CCamera::m_instance = NULL;

D3DXMATRIX   g_mtxView;

//�J�����̃C���X�^���X����
CCamera* CCamera::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CCamera();
	}
	return m_instance;
}

//�J�����̃C���X�^���X���
void CCamera::Release()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

//������
HRESULT CCamera::Init(CRender* pRender)
{
	m_pDevice = pRender->getDevice();
	m_mode = pRender->GetMode();
	m_posCameraP = D3DXVECTOR3( 250.0f, 50.0f,-350.0f );
	m_posCameraR = D3DXVECTOR3( 250.0f, 0.0f,	-250.0f );
	m_vecCameraU = D3DXVECTOR3( 0.0f, 1.0f,		0.0f );
	m_vecSpeed = D3DXVECTOR3( 0.0f, 0.0f,0.0f );
	m_posCameraPDest = m_posCameraP;
	m_posCameraRDest = m_posCameraR;
	// ���_���璍���_�܂ł̋�����ݒ�
	m_fLengthCameraXZ = sqrtf((m_posCameraR.x-m_posCameraP.x)*(m_posCameraR.x-m_posCameraP.x)+(m_posCameraR.z-m_posCameraP.z)*(m_posCameraR.z-m_posCameraP.z));

	// ���_���璍���_�ւ̊p�x��ݒ�
	m_rotCamera.y = atan2f( ( m_posCameraR.x-m_posCameraP.x ), ( m_posCameraR.z - m_posCameraP.z ) );
	m_rotCamera.x = atan2f( ( m_posCameraR.z-m_posCameraP.z ), ( m_posCameraR.y - m_posCameraP.y ) );
	m_rotCamera.z = 0.0f;

	m_initManager = true;
	if(m_initManager)
	{
		m_plpos.x = 250;
		m_plpos.y = 0;
		m_plpos.z = -250;
	}
	m_fAngle = 0.0f;
	m_faglView = D3DX_PI/3;
	
	m_bFlag = true;
	m_stopFlag = false;
	//m_plpos = GetPos();

	return S_OK;
}
HRESULT CCamera::TitleInit(CRender* pRender)
{
	m_pDevice = pRender->getDevice();
	m_mode = pRender->GetMode();
	m_posCameraP = D3DXVECTOR3( 0.0f, 50.0f,-80.0f );
	m_posCameraR = D3DXVECTOR3( 0.0f, 0.0f,	-0.0f );
	m_vecCameraU = D3DXVECTOR3( 0.0f, 1.0f,		0.0f );
	m_vecSpeed = D3DXVECTOR3( 0.0f, 0.0f,0.0f );
	m_posCameraPDest = m_posCameraP;
	m_posCameraRDest = m_posCameraR;
	// ���_���璍���_�܂ł̋�����ݒ�
	m_fLengthCameraXZ = sqrtf((m_posCameraR.x-m_posCameraP.x)*(m_posCameraR.x-m_posCameraP.x)+(m_posCameraR.z-m_posCameraP.z)*(m_posCameraR.z-m_posCameraP.z));

	// ���_���璍���_�ւ̊p�x��ݒ�
	m_rotCamera.y = atan2f( ( m_posCameraR.x-m_posCameraP.x ), ( m_posCameraR.z - m_posCameraP.z ) );
	m_rotCamera.x = atan2f( ( m_posCameraR.z-m_posCameraP.z ), ( m_posCameraR.y - m_posCameraP.y ) );
	m_rotCamera.z = 0.0f;

	m_initManager = true;
	if(m_initManager)
	{
		m_plpos.x = 250;
		m_plpos.y = 0;
		m_plpos.z = -250;
	}
	m_fAngle = 0.0f;
	m_faglView = D3DX_PI/10;
	
	m_bFlag = true;
	m_stopFlag = false;
	//m_plpos = GetPos();

	return S_OK;
}
void CCamera::TitleUpdate()
{
	m_fAngle = D3DX_PI;			// �P�W�O��

	m_rotCamera.y += D3DX_PI * 0.001f;
	m_posCameraP.x = m_posCameraR.x + sinf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
	m_posCameraP.z = m_posCameraR.z + cosf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
}
void CCamera::Update()
{


	float modelRot = 0.0f;
	//���_���烂�f���܂ł̋�����ݒ�
//	m_fLengthCameraXZ = sqrtf((m_plpos.x-m_posCameraP.x)*(m_plpos.x-m_posCameraP.x)+(m_plpos.z-m_posCameraP.z)*(m_plpos.z-m_posCameraP.z));
	// ���_���璍���_�ւ̊p�x��ݒ�
//	m_rotCamera.y = atan2f( ( m_plpos.x-m_posCameraP.x ), ( m_plpos.z - m_posCameraP.z ) );
//	m_rotCamera.x = atan2f( ( m_plpos.z-m_posCameraP.z ), ( m_plpos.y - m_posCameraP.y ) );

	
	float cameraLookAt = 30.0f;
	float stopRot = 0.0f;
	float changeValue = 0.0f;
	float nowRot = 0.0f;
	D3DXVECTOR3 velocity(0,0,0);
	D3DXVECTOR3 rot(0,0,0);
	D3DXVECTOR3 cross(0,0,0);
///*
	
//	if(m_mode == MODE_GAME)
	{
		if(m_initManager)
		{
			m_initManager = false;
		}
		else
		{
		
			m_plpos = GetPos();
		
			// �p�x�𐳋K��
			if( m_rotCamera.y < -D3DX_PI )
			{
				m_rotCamera.y += 2 * D3DX_PI;
			}
			else if( m_rotCamera.y > D3DX_PI )
			{
				m_rotCamera.y -= 2 * D3DX_PI;
			}
			modelRot = GetRot().y;
			rot = GetRot();
			velocity = GetVelocity();
			g_angleYaw = m_rotCamera.y;

		}
	
	

		//if( velocity.x == 0.0f || velocity.z == 0.0f)
		//{
		//	m_bFlag = false;
		//}
		//else
		{
			m_bFlag = true;
		}
	///*
		if(m_bFlag)
		{
			/*
			//�ړ���
			cameraLookAt = 40.0f;
			//�����_
			m_posCameraPDest.x = m_plpos.x - sinf(m_rotCamera.y)*m_fLengthCameraXZ;//-sinf(g_modelRot) * g_cameraLookAt;
			m_posCameraPDest.y = CAMERA_POS_HEIGHT;//sinf(D3DX_PI/3)*g_fLengthCameraXZ;
			m_posCameraPDest.z = m_plpos.z - cosf(m_rotCamera.y)*m_fLengthCameraXZ;//-cosf(g_modelRot)-g_fLengthCameraXZ;
				
			//�����_
			m_posCameraRDest.x = m_plpos.x - sinf(modelRot) * cameraLookAt;	//���f���̂�����Ɛ�
			m_posCameraRDest.y = m_plpos.y;
			m_posCameraRDest.z = m_plpos.z - cosf(modelRot) * cameraLookAt;	//���f���̂�����Ɛ�
			m_stopFlag = false;
			*/
			m_rotCamera.y = atan2f( ( m_plpos.x-m_posCameraP.x ), ( m_plpos.z - m_posCameraP.z ) );
			//�ړ���
			cameraLookAt = 20.0f;

			//����
			stopRot = modelRot-m_rotCamera.y;

			// �p�x�𐳋K��
			if( stopRot < -D3DX_PI )
			{
				stopRot += 2 * D3DX_PI;
			
			}
			else if( stopRot > D3DX_PI )
			{
				stopRot -= 2 * D3DX_PI;
			}
			//������Ȃ��悤�ɂ��邽��
			if(stopRot < 0.0f)
			{
				nowRot = m_rotCamera.y + (stopRot+D3DX_PI)*0.01f;
			}
			else
			{
				nowRot = m_rotCamera.y + (stopRot-D3DX_PI)*0.01f;
			}
		
			// �p�x�𐳋K��
			if( nowRot < -D3DX_PI )
			{
				nowRot += 2 * D3DX_PI;
			}
			else if( nowRot > D3DX_PI )
			{
				nowRot -= 2 * D3DX_PI;
			}
		
			//nowRot*=-1;
			//D3DXVec3Cross(&cross,&rot,&m_rotCamera);
			//�����_
			m_posCameraPDest.x = m_plpos.x - sinf(nowRot)*m_fLengthCameraXZ;
			m_posCameraPDest.y = m_plpos.y + CAMERA_POS_HEIGHT;
			m_posCameraPDest.z = m_plpos.z - cosf(nowRot)*m_fLengthCameraXZ;

			//�����_
			m_posCameraRDest.x = m_plpos.x - sinf(modelRot) * cameraLookAt;	//���f���̂�����Ɛ�
			m_posCameraRDest.y = m_plpos.y;
			m_posCameraRDest.z = m_plpos.z - cosf(modelRot) * cameraLookAt;	//���f���̂�����Ɛ�
		}
		else
		{
	//*/
	///*
			
			/*
			//�����_
			m_posCameraPDest.x = m_plpos.x - sinf(m_rotCamera.y)*m_fLengthCameraXZ;//-sinf(g_modelRot) * g_cameraLookAt;
			m_posCameraPDest.y = CAMERA_POS_HEIGHT;//sinf(D3DX_PI/3)*g_fLengthCameraXZ;
			m_posCameraPDest.z = m_plpos.z - cosf(m_rotCamera.y)*m_fLengthCameraXZ;//-cosf(g_modelRot)-g_fLengthCameraXZ;
				
			//�����_
			m_posCameraRDest.x = m_plpos.x - sinf(modelRot) * cameraLookAt;	//���f���̂�����Ɛ�
			m_posCameraRDest.y = m_plpos.y;
			m_posCameraRDest.z = m_plpos.z - cosf(modelRot) * cameraLookAt;	//���f���̂�����Ɛ�
			m_stopFlag = false;
			*/
	//*/
	/*
			//if(!m_stopFlag)
			{
				//��~��
				m_rotCamera.y = atan2f( ( m_plpos.x-m_posCameraP.x ), ( m_plpos.z - m_posCameraP.z ) );
				m_stopFlag = true;
			}
			cameraLookAt = 30.0f;
			//����
			stopRot = modelRot-m_rotCamera.y;

			// �p�x�𐳋K��
			if( stopRot < -D3DX_PI )
			{
				stopRot += 2 * D3DX_PI;
			
			}
			else if( stopRot > D3DX_PI )
			{
				stopRot -= 2 * D3DX_PI;
			}
			//������Ȃ��悤�ɂ��邽��
			if(stopRot < 0.0f)
			{
				nowRot = m_rotCamera.y + (stopRot+D3DX_PI)*0.009f;
			}
			else
			{
				nowRot = m_rotCamera.y + (stopRot-D3DX_PI)*0.009f;
			}
		
			// �p�x�𐳋K��
			if( nowRot < -D3DX_PI )
			{
				nowRot += 2 * D3DX_PI;
			}
			else if( nowRot > D3DX_PI )
			{
				nowRot -= 2 * D3DX_PI;
			}
		
			//nowRot*=-1;
			//D3DXVec3Cross(&cross,&rot,&m_rotCamera);
			//�����_
			m_posCameraPDest.x = m_plpos.x - sinf(nowRot)*m_fLengthCameraXZ;
			m_posCameraPDest.y = m_plpos.y + CAMERA_POS_HEIGHT;
			m_posCameraPDest.z = m_plpos.z - cosf(nowRot)*m_fLengthCameraXZ;

			//�����_
			m_posCameraRDest.x = m_plpos.x - sinf(modelRot) * cameraLookAt;	//���f���̂�����Ɛ�
			m_posCameraRDest.y = m_plpos.y;
			m_posCameraRDest.z = m_plpos.z - cosf(modelRot) * cameraLookAt;	//���f���̂�����Ɛ�
	//*/
		}
		//���J�����̈ʒu�i���_�A�����_�j
		//���_
		m_posCameraP.x += (m_posCameraPDest.x-m_posCameraP.x) * CAMERA_EYE_SEED;
		m_posCameraP.y += (m_posCameraPDest.y-m_posCameraP.y) * CMAERA_SIGHT_MOVE;
		m_posCameraP.z += (m_posCameraPDest.z-m_posCameraP.z) * CAMERA_EYE_SEED;
		//�����_
		m_posCameraR.x += (m_posCameraRDest.x-m_posCameraR.x) * CAMERA_AT_SEED;
		m_posCameraR.y += (m_posCameraRDest.y-m_posCameraR.y) * CMAERA_SIGHT_MOVE;
		m_posCameraR.z += (m_posCameraRDest.z-m_posCameraR.z) * CAMERA_AT_SEED;
	}
	CDebugProc::Print("\nCAMERA%f",nowRot);
	CDebugProc::Print("\nCFlag%d",m_bFlag);
	
}

void CCamera::Uninit()
{

}
void CCamera::SetCamera()
{
	//�r���[�g�����X�t�H�[��
	D3DXMatrixLookAtLH(&m_mtxView,&m_posCameraP,&m_posCameraR,&m_vecCameraU);
	g_mtxView = m_mtxView;
	m_pDevice->SetTransform(D3DTS_VIEW,&m_mtxView);
	
	//�v���W�F�N�V�����g�����X�t�H�[��
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,m_faglView,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,10.0f,10000.0f);
	m_pDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);
}

D3DXMATRIX GetMtxView()
{
	return g_mtxView;
}
float GetAngleYaw(void)
{
	return g_angleYaw;
}
void CCamera::UpdateDebug()
{
	//�����_
	//��
	// Y���ɑ΂��Ă̕��s�ړ�
	// ���ړ�
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_LEFT )  )
	{
		m_fAngle = -D3DX_PI / 2;		// -�X�O��
		m_posCameraP.x += sinf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;
		m_posCameraP.z += cosf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;

		//�����_�̈ʒu��␳
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// �E�ړ�
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_RIGHT )  )
	{
		m_fAngle = D3DX_PI / 2;		// �X�O��
		m_posCameraP.x += sinf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;
		m_posCameraP.z += cosf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;

		//�����_�̈ʒu��␳
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// �O�ړ�
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_UP )  )
	{
		m_fAngle = D3DX_PI * 0.0f;		// �O��
		m_posCameraP.x += sinf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;
		m_posCameraP.z += cosf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;

		//�����_�̈ʒu��␳
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// ���ړ�
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_DOWN ) )
	{
		m_fAngle = D3DX_PI;			// �P�W�O��
		m_posCameraP.x += sinf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;
		m_posCameraP.z += cosf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;

		//�����_�̈ʒu��␳
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// X���ɑ΂��Ă̕��s�ړ�
	// ��ړ�
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_Y ) )
	{
		m_fAngle = 0.0f;			// �O��
		m_posCameraP.y -= cosf( m_rotCamera.x + m_fAngle ) * CAMERA_POS_SPEED;
	}
	// ���ړ�
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_N ) )
	{
		m_fAngle = D3DX_PI;			// �P�W�O��
		m_posCameraP.y -= cosf( m_rotCamera.x + m_fAngle ) * CAMERA_POS_SPEED;
	}
	// Y���ɑ΂��Ẳ�]
	// ������
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_Z ) )
	{
		// m_rotCamera.y�́AP����R�������p�x�ł��邪�����R����P�������p�x���g�������̂łP�W�O���␳����K�v������
		m_fAngle = D3DX_PI;			// �P�W�O��

		m_rotCamera.y += D3DX_PI * 0.01f;
		m_posCameraP.x = m_posCameraR.x + sinf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
		m_posCameraP.z = m_posCameraR.z + cosf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
	}
	// �E����
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_C ) )
	{
		// m_rotCamera.y�́AP����R�������p�x�ł��邪�����R����P�������p�x���g�������̂łP�W�O���␳����K�v������
		m_fAngle = D3DX_PI;			// �P�W�O��

		m_rotCamera.y -= D3DX_PI * 0.01f;
		m_posCameraP.x = m_posCameraR.x + sinf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
		m_posCameraP.z = m_posCameraR.z + cosf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
	}

	// �������_����
	// ������
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_Q ) )
	{
		m_rotCamera.y -= D3DX_PI * 0.01f;
		
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// �E����
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_E ) )
	{
		m_rotCamera.y += D3DX_PI * 0.01f;
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// ��ړ�
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_T ) )
	{
		m_posCameraR.y++;
	}
	// ���ړ�
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_B ) )
	{
		m_posCameraR.y--;
	}

	

	
	// ���Z�b�g
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_P ) )
	{
		m_posCameraP = D3DXVECTOR3( 0.0f, 200.0f,-200.0f );
		m_posCameraR = D3DXVECTOR3( 0.0f, 0.0f,		0.0f );
		m_vecCameraU = D3DXVECTOR3( 0.0f, 1.0f,		0.0f );

		// ���_���璍���_�ւ̊p�x��ݒ�
		m_rotCamera.y = atan2f( ( m_posCameraR.x-m_posCameraP.x ), ( m_posCameraR.z - m_posCameraP.z ) );
		m_rotCamera.x = atan2f( ( m_posCameraR.z-m_posCameraP.z ), ( m_posCameraR.y - m_posCameraP.y ) );
	}
	//�Y�[���C��
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_DELETE ) )
	{
		float min = D3DXToRadian(5.0f);
		
		m_faglView -= 0.01f;

		if(m_faglView < min)
		{
			m_faglView = min;
		}
	}
	//�Y�[���A�E�g
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_INSERT ) )
	{
		float max = D3DX_PI * 0.5f;

		m_faglView += 0.01f;

		
		if(m_faglView > max)
		{
			m_faglView = max;
		}

	}
	g_angleYaw = m_rotCamera.y;
}