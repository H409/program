//ƒwƒbƒ_[ƒCƒ“ƒNƒ‹[ƒh
#include "yuka.h"
#include "CRender.h"
#include "CDebugProc.h"
#include "CInputKeyboard.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CManager.h"
#include "CGame.h"

DWORD g_dwIndex = 0;
//ì¬
CYuka* CYuka::Create(CRender* pRender,D3DXVECTOR3 pos)
{

	CYuka* pGimmick = new CYuka(3);

	pGimmick->Init(pRender,pos);


	return pGimmick;
}
//‰Šú‰»
HRESULT CYuka::Init(CRender* pRender)
{
	//TODO:‚¿‚á‚ñ‚Æ‚·‚é
	m_vtxMax = D3DXVECTOR3(20.0f,3.5f,20.0f);
	m_vtxMin = D3DXVECTOR3(-20.0f,-3.5f,-20.0f);
	m_initManager = false;

	return CSceneX::Init(pRender,GetPosition(),"data\\Model\\gimick.x",NULL,false);
}
HRESULT CYuka::Init(CRender* pRender,D3DXVECTOR3 pos)
{
	m_vtxMax = D3DXVECTOR3(20.0f,3.5f,20.0f);
	m_vtxMin = D3DXVECTOR3(-20.0f,-3.5f,-20.0f);
	m_initManager = false;
	m_vecMove = D3DXVECTOR3(0,0,0);

	return CSceneX::Init(pRender,pos,"data\\Model\\yuka.x",NULL,false);
}
//ŠJ•ú
void CYuka::Uninit()
{
	m_initManager = false;
	CSceneX::Uninit();
//	m_pSceneXDummy->Uninit();	
}
//XV
void CYuka::Update()
{

	if(!m_initManager)
	{
		CreateBBox(&m_vtxMax,&m_vtxMin);
		m_initManager = true;
	}

	D3DXVECTOR3 pos1 = GetPosition();
	D3DXVECTOR3 rot1 = GetRotate();
	SetPositionOld(pos1);
	SetRotationOld(rot1);

	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_H ) )
	{
		m_fangleModel = -D3DX_PI/2;
		//rot1.y = GetAngleYaw()-m_fangleModel;

		pos1.x -= sinf(GetAngleYaw()+D3DX_PI/2)*0.9f;
		pos1.z -= cosf(GetAngleYaw()+D3DX_PI/2)*0.9f;
	}
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_K ) )
	{
		m_fangleModel = D3DX_PI/2;
		//rot1.y = GetAngleYaw()-m_fangleModel;
		
		pos1.x += sinf(GetAngleYaw()+D3DX_PI/2)*0.9f;
		pos1.z += cosf(GetAngleYaw()+D3DX_PI/2)*0.9f;
	}
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_U ) )
	{
		m_fangleModel = D3DX_PI;
		//rot1.y = GetAngleYaw()-m_fangleModel;

		pos1.x -= sinf(GetAngleYaw()+D3DX_PI)*0.9f;
		pos1.z -= cosf(GetAngleYaw()+D3DX_PI)*0.9f;
	}
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_J ) )
	{
		m_fangleModel = 0;
		//rot1.y = GetAngleYaw()-m_fangleModel;

		pos1.x += sinf(GetAngleYaw()+D3DX_PI)*0.9f;
		pos1.z += cosf(GetAngleYaw()+D3DX_PI)*0.9f;
	}
	if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_O))
	{
		pos1.y += 0.5f;
	}
	if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_L))
	{
		pos1.y -= 0.5f;
	}
	
	//‰ñ“]
	if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_F))
	{
		rot1.y-=D3DX_PI*0.01f;
		// Šp“x‚ğ³‹K‰»
		if( rot1.y < -D3DX_PI )
		{
			rot1.y += 2 * D3DX_PI;
		}
		else if( rot1.y > D3DX_PI )
		{
			rot1.y -= 2 * D3DX_PI;
		}
	}
	if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_G))
	{
		rot1.y+=D3DX_PI*0.01f;
		// Šp“x‚ğ³‹K‰»
		if( rot1.y < -D3DX_PI )
		{
			rot1.y += 2 * D3DX_PI;
		}
		else if( rot1.y > D3DX_PI )
		{
			rot1.y -= 2 * D3DX_PI;
		}
	}

	SetPosition(pos1);
	SetRotate(rot1);

	D3DXVECTOR3* pVertex = NULL;
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_UP))
	{
		g_dwIndex++;	
	}

	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_DOWN))
	{
		g_dwIndex--;	
	}
	pVertex = FindVertex(g_dwIndex);

	CDebugProc::Print("\nGIMMICKX%fY%fZ%f:index%d\n",pVertex->x,pVertex->y,pVertex->z,g_dwIndex);

	
	CPlayer* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 rotOffset(0,0,0);
	D3DXVECTOR3 posOffset(0,0,0);
	D3DXVECTOR3 rottmp(0,0,0);
	D3DXVECTOR3 playerPos(0,0,0);
	D3DXVECTOR3 playerRot(0,0,0);
	D3DXVECTOR3 tmp(0,0,0);

	if(pPlayer != NULL)
	{
		if(pPlayer->GetSceneLink() == this)
		{
			rotOffset = GetRotate()-GetRotationOld();			//‡@
			
			// Šp“x‚ğ³‹K‰»
			if( rotOffset.y < -D3DX_PI )
			{
				rotOffset.y += 2 * D3DX_PI;
			
			}
			else if( rotOffset.y > D3DX_PI )
			{
				rotOffset.y -= 2 * D3DX_PI;
			}
			tmp = GetPosition() + m_vtxMax;

			posOffset = pPlayer->GetPosition()-GetPosition();	//‡A
			rottmp.x = cosf(rotOffset.y)*posOffset.x + sinf(rotOffset.y)*posOffset.z;	//‡B
			rottmp.z = cosf(rotOffset.y)*posOffset.z - sinf(rotOffset.y)*posOffset.x;	//‡B

			playerPos.x = GetPosition().x + rottmp.x;		//‡C
			playerPos.z = GetPosition().z + rottmp.z;		//‡C
			playerPos.y = tmp.y;

			m_vecMove = GetPosition() - GetPositionOld();	//‡D

			playerPos.x += m_vecMove.x;		//‡E
			playerPos.z += m_vecMove.z;		//‡E

			playerRot = pPlayer->GetRotate() + rotOffset;
			// Šp“x‚ğ³‹K‰»
			if( playerRot.y < -D3DX_PI )
			{
				playerRot.y += 2 * D3DX_PI;
			
			}
			else if( playerRot.y > D3DX_PI )
			{
				playerRot.y -= 2 * D3DX_PI;
			}
			

			pPlayer->SetPosition(playerPos);
			pPlayer->SetRotate(playerRot);
		}
	}

	CSceneX::Update();
}
//•`‰æ
void CYuka::Draw()
{
	CSceneX::Draw();
}