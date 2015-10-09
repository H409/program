//ヘッダーインクルード
#include "CCamera.h"
#include "CRender.h"
#include <cmath>
#include "CPlayer.h"
#include "CDebugProc.h"

//マクロ
#define CAMERA_POS_SPEED	( 2.0f )
#define CAMERA_LOOK_AT		(0.0f)
#define CAMERA_EYE_SEED		(1.0f);
#define CAMERA_AT_SEED		(0.05f)
#define CMAERA_SIGHT_MOVE		(0.5f)			// 視点移動係数
#define CAMERA_POS_HEIGHT	(50.0f)
#define CAMERA_ROT_SEED		(0.95f)

float g_angleYaw = 0; 

CCamera* CCamera::m_instance = NULL;

D3DXMATRIX   g_mtxView;

//カメラのインスタンス生成
CCamera* CCamera::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CCamera();
	}
	return m_instance;
}

//カメラのインスタンス解放
void CCamera::Release()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

//初期化
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
	// 視点から注視点までの距離を設定
	m_fLengthCameraXZ = sqrtf((m_posCameraR.x-m_posCameraP.x)*(m_posCameraR.x-m_posCameraP.x)+(m_posCameraR.z-m_posCameraP.z)*(m_posCameraR.z-m_posCameraP.z));

	// 視点から注視点への角度を設定
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
	// 視点から注視点までの距離を設定
	m_fLengthCameraXZ = sqrtf((m_posCameraR.x-m_posCameraP.x)*(m_posCameraR.x-m_posCameraP.x)+(m_posCameraR.z-m_posCameraP.z)*(m_posCameraR.z-m_posCameraP.z));

	// 視点から注視点への角度を設定
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
	m_fAngle = D3DX_PI;			// １８０°

	m_rotCamera.y += D3DX_PI * 0.001f;
	m_posCameraP.x = m_posCameraR.x + sinf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
	m_posCameraP.z = m_posCameraR.z + cosf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
}
void CCamera::Update()
{


	float modelRot = 0.0f;
	//視点からモデルまでの距離を設定
//	m_fLengthCameraXZ = sqrtf((m_plpos.x-m_posCameraP.x)*(m_plpos.x-m_posCameraP.x)+(m_plpos.z-m_posCameraP.z)*(m_plpos.z-m_posCameraP.z));
	// 視点から注視点への角度を設定
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
		
			// 角度を正規化
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
			//移動中
			cameraLookAt = 40.0f;
			//▼視点
			m_posCameraPDest.x = m_plpos.x - sinf(m_rotCamera.y)*m_fLengthCameraXZ;//-sinf(g_modelRot) * g_cameraLookAt;
			m_posCameraPDest.y = CAMERA_POS_HEIGHT;//sinf(D3DX_PI/3)*g_fLengthCameraXZ;
			m_posCameraPDest.z = m_plpos.z - cosf(m_rotCamera.y)*m_fLengthCameraXZ;//-cosf(g_modelRot)-g_fLengthCameraXZ;
				
			//注視点
			m_posCameraRDest.x = m_plpos.x - sinf(modelRot) * cameraLookAt;	//モデルのちょっと先
			m_posCameraRDest.y = m_plpos.y;
			m_posCameraRDest.z = m_plpos.z - cosf(modelRot) * cameraLookAt;	//モデルのちょっと先
			m_stopFlag = false;
			*/
			m_rotCamera.y = atan2f( ( m_plpos.x-m_posCameraP.x ), ( m_plpos.z - m_posCameraP.z ) );
			//移動中
			cameraLookAt = 20.0f;

			//差分
			stopRot = modelRot-m_rotCamera.y;

			// 角度を正規化
			if( stopRot < -D3DX_PI )
			{
				stopRot += 2 * D3DX_PI;
			
			}
			else if( stopRot > D3DX_PI )
			{
				stopRot -= 2 * D3DX_PI;
			}
			//一周しないようにするため
			if(stopRot < 0.0f)
			{
				nowRot = m_rotCamera.y + (stopRot+D3DX_PI)*0.01f;
			}
			else
			{
				nowRot = m_rotCamera.y + (stopRot-D3DX_PI)*0.01f;
			}
		
			// 角度を正規化
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
			//▼視点
			m_posCameraPDest.x = m_plpos.x - sinf(nowRot)*m_fLengthCameraXZ;
			m_posCameraPDest.y = m_plpos.y + CAMERA_POS_HEIGHT;
			m_posCameraPDest.z = m_plpos.z - cosf(nowRot)*m_fLengthCameraXZ;

			//注視点
			m_posCameraRDest.x = m_plpos.x - sinf(modelRot) * cameraLookAt;	//モデルのちょっと先
			m_posCameraRDest.y = m_plpos.y;
			m_posCameraRDest.z = m_plpos.z - cosf(modelRot) * cameraLookAt;	//モデルのちょっと先
		}
		else
		{
	//*/
	///*
			
			/*
			//▼視点
			m_posCameraPDest.x = m_plpos.x - sinf(m_rotCamera.y)*m_fLengthCameraXZ;//-sinf(g_modelRot) * g_cameraLookAt;
			m_posCameraPDest.y = CAMERA_POS_HEIGHT;//sinf(D3DX_PI/3)*g_fLengthCameraXZ;
			m_posCameraPDest.z = m_plpos.z - cosf(m_rotCamera.y)*m_fLengthCameraXZ;//-cosf(g_modelRot)-g_fLengthCameraXZ;
				
			//注視点
			m_posCameraRDest.x = m_plpos.x - sinf(modelRot) * cameraLookAt;	//モデルのちょっと先
			m_posCameraRDest.y = m_plpos.y;
			m_posCameraRDest.z = m_plpos.z - cosf(modelRot) * cameraLookAt;	//モデルのちょっと先
			m_stopFlag = false;
			*/
	//*/
	/*
			//if(!m_stopFlag)
			{
				//停止中
				m_rotCamera.y = atan2f( ( m_plpos.x-m_posCameraP.x ), ( m_plpos.z - m_posCameraP.z ) );
				m_stopFlag = true;
			}
			cameraLookAt = 30.0f;
			//差分
			stopRot = modelRot-m_rotCamera.y;

			// 角度を正規化
			if( stopRot < -D3DX_PI )
			{
				stopRot += 2 * D3DX_PI;
			
			}
			else if( stopRot > D3DX_PI )
			{
				stopRot -= 2 * D3DX_PI;
			}
			//一周しないようにするため
			if(stopRot < 0.0f)
			{
				nowRot = m_rotCamera.y + (stopRot+D3DX_PI)*0.009f;
			}
			else
			{
				nowRot = m_rotCamera.y + (stopRot-D3DX_PI)*0.009f;
			}
		
			// 角度を正規化
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
			//▼視点
			m_posCameraPDest.x = m_plpos.x - sinf(nowRot)*m_fLengthCameraXZ;
			m_posCameraPDest.y = m_plpos.y + CAMERA_POS_HEIGHT;
			m_posCameraPDest.z = m_plpos.z - cosf(nowRot)*m_fLengthCameraXZ;

			//注視点
			m_posCameraRDest.x = m_plpos.x - sinf(modelRot) * cameraLookAt;	//モデルのちょっと先
			m_posCameraRDest.y = m_plpos.y;
			m_posCameraRDest.z = m_plpos.z - cosf(modelRot) * cameraLookAt;	//モデルのちょっと先
	//*/
		}
		//▼カメラの位置（視点、注視点）
		//視点
		m_posCameraP.x += (m_posCameraPDest.x-m_posCameraP.x) * CAMERA_EYE_SEED;
		m_posCameraP.y += (m_posCameraPDest.y-m_posCameraP.y) * CMAERA_SIGHT_MOVE;
		m_posCameraP.z += (m_posCameraPDest.z-m_posCameraP.z) * CAMERA_EYE_SEED;
		//注視点
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
	//ビュートランスフォーム
	D3DXMatrixLookAtLH(&m_mtxView,&m_posCameraP,&m_posCameraR,&m_vecCameraU);
	g_mtxView = m_mtxView;
	m_pDevice->SetTransform(D3DTS_VIEW,&m_mtxView);
	
	//プロジェクショントランスフォーム
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
	//▼視点
	//奥
	// Y軸に対しての平行移動
	// 左移動
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_LEFT )  )
	{
		m_fAngle = -D3DX_PI / 2;		// -９０°
		m_posCameraP.x += sinf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;
		m_posCameraP.z += cosf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;

		//注視点の位置を補正
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// 右移動
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_RIGHT )  )
	{
		m_fAngle = D3DX_PI / 2;		// ９０°
		m_posCameraP.x += sinf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;
		m_posCameraP.z += cosf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;

		//注視点の位置を補正
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// 前移動
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_UP )  )
	{
		m_fAngle = D3DX_PI * 0.0f;		// ０°
		m_posCameraP.x += sinf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;
		m_posCameraP.z += cosf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;

		//注視点の位置を補正
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// 後ろ移動
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_DOWN ) )
	{
		m_fAngle = D3DX_PI;			// １８０°
		m_posCameraP.x += sinf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;
		m_posCameraP.z += cosf( m_rotCamera.y + m_fAngle ) * CAMERA_POS_SPEED;

		//注視点の位置を補正
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// X軸に対しての平行移動
	// 上移動
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_Y ) )
	{
		m_fAngle = 0.0f;			// ０°
		m_posCameraP.y -= cosf( m_rotCamera.x + m_fAngle ) * CAMERA_POS_SPEED;
	}
	// 下移動
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_N ) )
	{
		m_fAngle = D3DX_PI;			// １８０°
		m_posCameraP.y -= cosf( m_rotCamera.x + m_fAngle ) * CAMERA_POS_SPEED;
	}
	// Y軸に対しての回転
	// 左旋回
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_Z ) )
	{
		// m_rotCamera.yは、PからRを見た角度であるが旋回はRからPを見た角度を使いたいので１８０°補正する必要がある
		m_fAngle = D3DX_PI;			// １８０°

		m_rotCamera.y += D3DX_PI * 0.01f;
		m_posCameraP.x = m_posCameraR.x + sinf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
		m_posCameraP.z = m_posCameraR.z + cosf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
	}
	// 右旋回
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_C ) )
	{
		// m_rotCamera.yは、PからRを見た角度であるが旋回はRからPを見た角度を使いたいので１８０°補正する必要がある
		m_fAngle = D3DX_PI;			// １８０°

		m_rotCamera.y -= D3DX_PI * 0.01f;
		m_posCameraP.x = m_posCameraR.x + sinf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
		m_posCameraP.z = m_posCameraR.z + cosf( m_rotCamera.y + m_fAngle ) * m_fLengthCameraXZ;
	}

	// ▼注視点操作
	// 左旋回
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_Q ) )
	{
		m_rotCamera.y -= D3DX_PI * 0.01f;
		
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// 右旋回
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_E ) )
	{
		m_rotCamera.y += D3DX_PI * 0.01f;
		m_posCameraR.x = m_posCameraP.x + sinf( m_rotCamera.y ) * m_fLengthCameraXZ;
		m_posCameraR.z = m_posCameraP.z + cosf( m_rotCamera.y ) * m_fLengthCameraXZ;
	}
	// 上移動
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_T ) )
	{
		m_posCameraR.y++;
	}
	// 下移動
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_B ) )
	{
		m_posCameraR.y--;
	}

	

	
	// リセット
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_P ) )
	{
		m_posCameraP = D3DXVECTOR3( 0.0f, 200.0f,-200.0f );
		m_posCameraR = D3DXVECTOR3( 0.0f, 0.0f,		0.0f );
		m_vecCameraU = D3DXVECTOR3( 0.0f, 1.0f,		0.0f );

		// 視点から注視点への角度を設定
		m_rotCamera.y = atan2f( ( m_posCameraR.x-m_posCameraP.x ), ( m_posCameraR.z - m_posCameraP.z ) );
		m_rotCamera.x = atan2f( ( m_posCameraR.z-m_posCameraP.z ), ( m_posCameraR.y - m_posCameraP.y ) );
	}
	//ズームイン
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_DELETE ) )
	{
		float min = D3DXToRadian(5.0f);
		
		m_faglView -= 0.01f;

		if(m_faglView < min)
		{
			m_faglView = min;
		}
	}
	//ズームアウト
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