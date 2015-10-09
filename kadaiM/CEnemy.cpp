//=============================================================================
//
// ÉvÉäÉ~ÉeÉBÉuï\é¶èàóù [CEnemy.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//ÉwÉbÉ_Å[ÉCÉìÉNÉãÅ[Éh
#include "CEnemy.h"
#include "CGame.h"
#include "CColision.h"
#include "CPlayer.h"
#include "CGame.h"
#include <cmath>
#include "CBullet.h"
#include "CSound.h"

//ê√ìIÉÅÉìÉoïœêîèâä˙âª
int CEnemy::m_EnemyCnt = 0;

//çÏê¨
CEnemy* CEnemy::Create(CRender* pRender,D3DXVECTOR3 pos,char movetype,char atkptn,ENEMY_TYPE enemytype,char* xfilename,char* texfilename)
{

	CEnemy* pEnemy = new CEnemy(3);

	pEnemy->Init(pRender,pos,movetype,atkptn,enemytype,xfilename,texfilename);

	pEnemy->SetPosition(pos);
	/*
	if(m_pSceneXDummy == NULL)
	{
		m_pSceneXDummy = CSceneX::Create(pRender,D3DXVECTOR3(-200,10,0),NULL);
	}
	*/
	return pEnemy;
}
//èâä˙âª
HRESULT CEnemy::Init(CRender* pRender)
{
	m_pRender = pRender;
	return CSceneX::Init(pRender,GetPosition(),"data\\Model\\golam.x","data\\Texture\\golam.png",true);
}
HRESULT CEnemy::Init(CRender* pRender,D3DXVECTOR3 pos,char movetype,char atkptn,ENEMY_TYPE enemytype,char* xfilename,char* texfilename)
{
	SetPosition(pos);
	m_atkPtn = atkptn;
	m_movePtn = movetype;
	m_Enemy_Type = enemytype;
	m_atkCnt = 0;
	m_moveCnt = 0;
	m_pRender = pRender;
	m_stanby = false;
	m_vecMove = D3DXVECTOR3(0.55f,0,0.55f);

	switch(enemytype)
	{
		case ENEMY_NORMAL:
			xfilename = "data\\Model\\tank000.x";
			texfilename = NULL;
			m_EnemyLife = 0;
			break;
		case ENEMY_BOSS:
			xfilename	= "data\\Model\\golam.x";
			texfilename = "data\\Texture\\golam.png";
			m_EnemyLife = 9;
			break;
	}

	return CSceneX::Init(pRender,GetPosition(),xfilename,texfilename,true);
}
//äJï˙
void CEnemy::Uninit()
{
	CSceneX::Uninit();
//	m_pSceneXDummy->Uninit();	
}
//çXêV
void CEnemy::Update()
{
	/*
	if(CGame::GetClearFlag())
	{
		CEnemy::Uninit();
	}
	//*/


	
	D3DXVECTOR3 tmp = GetPosition();
	D3DXVECTOR3 nor(0,0,0);
	D3DXVECTOR3 tmp1(0,0,0);
	if(m_Enemy_Type == ENEMY_NORMAL)
	{
		//îªíË
		tmp.y = CColision::getInstance()->GetHeight(tmp,&nor);
	}
	if(m_Enemy_Type == ENEMY_BOSS)
	{
		if(m_EnemyCnt == ENEMY_NUM_MAX-1)
		{
			//îªíË
			tmp1.y = CColision::getInstance()->GetHeight(tmp,&nor);
			tmp.y--;
			if(tmp.y < tmp1.y)
			{
				tmp.y = tmp1.y;
				m_stanby = true;
			}
			
		}
		else
		{
			tmp.y = 250;
		}
	}
	if(CGame::getInstance()->GetStartCnt() >= GAME_START_TIME)
	{
		if(CSceneX::GetLifeFlag())
		{
			//ìGÇÃçUåÇ
			AttackEnemy(m_atkPtn);
			//ìGÇÃìÆÇ´
			MoveEnemy(m_movePtn);
		}
	}
	tmp.x = GetPosition().x;
	tmp.z = GetPosition().z;
	//ç¿ïWê›íË
	SetPosition(tmp);

	CSceneX::Update();
}
//ï`âÊ
void CEnemy::Draw()
{
	CSceneX::Draw();
}

//=================================================================================================================
//ìGà⁄ìÆ
//=================================================================================================================
bool CEnemy::MoveEnemy(int i)
{

	switch(m_movePtn)
	{
		case 0:
			MovePtn1Enemy(0);
			break;
		case 1:
			MovePtn2Enemy(0);
			break;
		case 2:
			MovePtn3Enemy(0);
			break;
	}
	
	

		
	return TRUE;
}
//===========================================================================
//ìGÇÃà⁄ìÆÇÃéÌóﬁ1
//===========================================================================
void CEnemy::MovePtn1Enemy(int i)
{
	CPlayer* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotate();

	rot.y = CColision::getInstance()->GetTargetDeg(pos.x,pos.z,pPlayer->GetPosition().x,pPlayer->GetPosition().z);

	if(pPlayer != NULL)
	{
		if(CColision::getInstance()->Sphere(GetPosition().x,GetPosition().y,GetPosition().z,ENEMY_RANGE_VALUE,
			pPlayer->GetPosition().x,pPlayer->GetPosition().y,pPlayer->GetPosition().z,10))
		{
			
			if(CColision::getInstance()->Sphere(GetPosition().x,GetPosition().y,GetPosition().z,ENEMY_RANGE_MARGIN_VALUE,
			pPlayer->GetPosition().x,pPlayer->GetPosition().y,pPlayer->GetPosition().z,10))
			{	

			}
			else
			{
				pos.x -= sinf(rot.y) * m_vecMove.x;
				pos.z -= cosf(rot.y) * m_vecMove.z;

				//É|ÉWÉVÉáÉìê›íË
				SetPosition(pos);
				//äpìxê›íË
				SetRotate(rot);
			}
		}
	}
}
//===========================================================================
//ìGÇÃà⁄ìÆÇÃéÌóﬁ2
//===========================================================================
void CEnemy::MovePtn2Enemy(int i)
{
	/*
	//ÉvÉåÉCÉÑÅ[í«è]
//	g_stdEnemy[i].std.pos.x +=sinf(g_stdEnemy[i].std.rot.y)*g_stdEnemy[i].std.vecMove.x;
//	g_stdEnemy[i].std.pos.z +=cosf(g_stdEnemy[i].std.rot.y)*g_stdEnemy[i].std.vecMove.z;

	g_armyEnemy[i].std.pos.x -=sinf(g_armyEnemy[i].std.rot.y)*g_armyEnemy[i].std.vecMove.x;
	g_armyEnemy[i].std.pos.z -=cosf(g_armyEnemy[i].std.rot.y)*g_armyEnemy[i].std.vecMove.z;
	*/
}
//===========================================================================
//ìGÇÃà⁄ìÆÇÃéÌóﬁ3
//===========================================================================
void CEnemy::MovePtn3Enemy(int i)
{

}

//=================================================================================================================
//ìGçUåÇ
//=================================================================================================================
bool CEnemy::AttackEnemy(int i)
{
	switch(m_atkPtn)
	{
		case 0:
			AttackPtn1Enemy(0);
			break;
		case 1:
			AttackPtn2Enemy(0);
			break;
		case 2:
			AttackPtn3Enemy(0);
			break;
	}
	return TRUE;
}
//===========================================================================
//ìGÇÃçUåÇÇÃéÌóﬁ1
//===========================================================================
void CEnemy::AttackPtn1Enemy(int i)
{
	CPlayer* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotate();

	if(pPlayer != NULL)
	{
		if(CColision::getInstance()->Sphere(GetPosition().x,GetPosition().y,GetPosition().z,ENEMY_RANGE_VALUE,
			pPlayer->GetPosition().x,pPlayer->GetPosition().y,pPlayer->GetPosition().z,10))
		{
			m_atkCnt++;
			if(m_atkCnt >= ENEMY_ATTACK_CNT1)
			{
				CSound::getInstance()->PlaySound(SOUND_LABEL_SE_SHOT);
				m_atkCnt = 0;
				//íeî≠éÀ
				CBullet::Create(m_pRender,GetPosition(),GetRotate().y,BULLET_ENEMY,"data\\Texture\\bullet000.png");
			}
		}
	}
}
//===========================================================================
//ìGÇÃçUåÇÇÃéÌóﬁ2
//===========================================================================
void CEnemy::AttackPtn2Enemy(int i)
{
	CPlayer* pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = GetPosition();
	D3DXVECTOR3 rot = GetRotate();
	D3DXVECTOR3 shotpos = GetPosition();
	D3DXVECTOR3 shotpos1 = GetPosition();

	shotpos.y = 20.0f;
	shotpos1.y = 10.0f;
	/*
	if(pPlayer != NULL)
	{
		if(CColision::getInstance()->Sphere(GetPosition().x,GetPosition().y,GetPosition().z,ENEMY_RANGE_VALUE,
			pPlayer->GetPosition().x,pPlayer->GetPosition().y,pPlayer->GetPosition().z,10))
		{
			m_atkCnt++;
			if(m_atkCnt >= ENEMY_ATTACK_CNT1)
			{
				CSound::getInstance()->PlaySound(SOUND_LABEL_SE_SHOT);
				m_atkCnt = 0;
				//íeî≠éÀ
				CBullet::Create(m_pRender,shotpos,GetRotate().y,BULLET_BOSS,"data\\Texture\\iwa.png");
			}
		}
	}
	*/
	if(m_stanby)
	{
		m_atkCnt++;
		if(m_atkCnt >= ENEMY_ATTACK_CNT1)
		{
			CSound::getInstance()->PlaySound(SOUND_LABEL_SE_SHOT);
			m_atkCnt = 0;
			//íeî≠éÀ
			CBullet::Create(m_pRender,shotpos,GetRotate().y + D3DX_PI/6,BULLET_BOSS,"data\\Texture\\iwa.png");
			CBullet::Create(m_pRender,shotpos,GetRotate().y,BULLET_BOSS,"data\\Texture\\iwa.png");
			CBullet::Create(m_pRender,shotpos,GetRotate().y - D3DX_PI/6,BULLET_BOSS,"data\\Texture\\iwa.png");
			CBullet::Create(m_pRender,shotpos1,GetRotate().y + D3DX_PI/6,BULLET_BOSS,"data\\Texture\\iwa.png");
			CBullet::Create(m_pRender,shotpos1,GetRotate().y,BULLET_BOSS,"data\\Texture\\iwa.png");
			CBullet::Create(m_pRender,shotpos1,GetRotate().y - D3DX_PI/6,BULLET_BOSS,"data\\Texture\\iwa.png");
		}
	}
}

//===========================================================================
//ìGÇÃçUåÇÇÃéÌóﬁ3
//===========================================================================
void CEnemy::AttackPtn3Enemy(int i)
{

}