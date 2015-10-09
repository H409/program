//ヘッダーインクルード
#include "CLight.h"
#include "CRender.h"
#include "CInputKeyboard.h"

//静的メンバ変数初期化
CLight* CLight::m_instance = NULL;

CLight* CLight::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CLight();
	}
	return m_instance;
}

void CLight::Release()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

//初期化
HRESULT CLight::Init(CRender* pRender)
{
	LPDIRECT3DDEVICE9 pDevice = pRender->getDevice();
	D3DXVECTOR3 vecDir;							// 方向ベクトル

	ZeroMemory( &m_aLight[0], sizeof( D3DLIGHT9 ) );
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[0].Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	vecDir = D3DXVECTOR3( 2.0f, -2.0f, 1.0f );

	D3DXVec3Normalize( ( D3DXVECTOR3* )&m_aLight[0].Direction, &vecDir );

	pDevice->SetLight( 0, &m_aLight[0] );

	pDevice->LightEnable( 0, TRUE );

	ZeroMemory( &m_aLight[1], sizeof( D3DLIGHT9 ) );
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[1].Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	vecDir = D3DXVECTOR3( -0.3f, 1.0f, -0.2f );

	D3DXVec3Normalize( ( D3DXVECTOR3* )&m_aLight[1].Direction, &vecDir );

	pDevice->SetLight( 1, &m_aLight[1] );

	pDevice->LightEnable( 1, TRUE );

	ZeroMemory( &m_aLight[2], sizeof( D3DLIGHT9 ) );
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;
	m_aLight[2].Diffuse = D3DXCOLOR( 1.0f, 1.0f, 1.0f, 1.0f );

	vecDir = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );

	D3DXVec3Normalize( ( D3DXVECTOR3* )&m_aLight[2].Direction, &vecDir );

	pDevice->SetLight( 2, &m_aLight[2] );

	pDevice->LightEnable( 2, TRUE );
	
	//レンダーステートの設定
	pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );	
	// アンビエントライト（環境光）を設定する
	pDevice->SetRenderState( D3DRS_AMBIENT, 0x00111111 );
	// スペキュラ（鏡面反射）を有効にする
	pDevice->SetRenderState(D3DRS_SPECULARENABLE,TRUE);
	
	return S_OK;
}
void CLight::Uninit()
{

}
void CLight::Update()
{
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_LEFT ) )
	{

	}
}
//
void CLight::ShadeLight(void)
{
	m_vecLight	= D3DXVECTOR3(50,50,-250);
	m_vecLook	= D3DXVECTOR3(250.0f,0,-250.0f);
	m_vecUp		= D3DXVECTOR3(0,1,0);
	m_vecEye	= D3DXVECTOR3( 250.0f, 50.0f,-350.0f );
	m_vecLook=D3DXVECTOR3(0,0,0);
	D3DXMATRIX matRotation;
	D3DXMatrixRotationY(&matRotation,0.01f);
	D3DXVec3TransformCoord(&m_vecLight,&m_vecLight,&matRotation);
	D3DXMatrixLookAtLH(&m_matLight,&m_vecLight,&m_vecLook,&m_vecUp);

}