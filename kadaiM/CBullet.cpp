//=============================================================================
//
// �v���~�e�B�u�\������ [CBullet.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CBullet.h"
#include "CMeshWall.h"
#include "CMeshField.h"
#include "CExplosion.h"
#include "CColision.h"
#include "CGame.h"
#include "CEnemy.h"
#include "CPaticle.h"
#include "CPlayer.h"
#include "CScore.h"

//�N���X��`

//�쐬
CBullet* CBullet::Create(CRender* pRender,D3DXVECTOR3 pos,float fangle,BULLET_TYPE btype,char* ptexname)
{

	CBullet* pBullet = new CBullet(3);

	pBullet->Init(pRender,fangle,btype,ptexname);

	pBullet->SetPosition(pos);

	

	return pBullet;
}
//������
HRESULT CBullet::Init(CRender* pRender,float fangle,BULLET_TYPE btype,char* ptexname)
{
	m_pRender = pRender;
	m_fangle = fangle;
	m_btype = btype;
	m_velocity = D3DXVECTOR3(0,5.0f,0);
	m_dt = 0.02f;
	return CSceneBillboard::Init(pRender,ptexname,m_fangle,15.0f);
}
//�J��
void CBullet::Uninit()
{
	CSceneBillboard::Uninit();	
}
//�X�V
void CBullet::Update()
{
	D3DXVECTOR3 tmp = GetPosition();
	D3DXVECTOR3 nor(0,0,0);
	float dt = 0.02f;
	D3DXVECTOR3 velocity(0,2.5f,0);	//���x
	float grav = -9.8f;
	//����
	tmp.y = CColision::getInstance()->GetHeight(tmp,&nor);

	CEnemy* pEnemy = CGame::GetEnemy(0);
	CPlayer* pPlayer = CGame::GetPlayer();

	m_vecDir = GetPosition();

	//�G
	if(m_btype == BULLET_ENEMY)
	{
		m_vecDir.x-=sinf(m_fangle)*BULLET_SPEED;
	
		m_vecDir.z-=cosf(m_fangle)*BULLET_SPEED;

		SetPosition(m_vecDir);
	}
	
	
	//�{�X
	if(m_btype == BULLET_BOSS)
	{

		//m_dt = ((float)rand() / (float)RAND_MAX)*1.0f + 0.1f;
		m_dt = 0.05f;

		m_velocity.y  += grav * m_dt;

		m_vecDir.x-=sinf(m_fangle)*BULLET_SPEED;
				
		m_vecDir.y += m_velocity.y;

		m_vecDir.z-=cosf(m_fangle)*BULLET_SPEED;

		SetPosition(m_vecDir);
	}
	//�v���C���[
	if(m_btype == BULLET_PLAYER)
	{

		m_vecDir.x-=sinf(m_fangle)*BULLET_SPEED;
	
		m_vecDir.z-=cosf(m_fangle)*BULLET_SPEED;

		SetPosition(m_vecDir);
	}

	//�n�ʂƂ̓����蔻��
	if(tmp.y > m_vecDir.y)
	{
		//�p�[�e�B�N��
		CPaticle::Create(m_pRender,m_vecDir,"data\\Texture\\fire.jpg");
		CBullet::Uninit();
	}
	//D3DXVec3Cross();
	//D3DXVec3Dot();
	D3DXVECTOR3 vecLine[4];				
	D3DXVECTOR3 vecToTarget[4];				
	D3DXVECTOR3 vecTmp[4];
	D3DXVECTOR3 vecMath[4];

	for(int i = 0;i < 4;i++)
	{
		vecMath[i] = CMeshField::GetVertex(i);
	}
	vecMath[0].z = -10;
	vecMath[1].x = 490;
	vecMath[1].z = -10;
	vecMath[2].x = 10;
	vecMath[3].x = 490;
	vecMath[3].z = -490;

	vecLine[0] = vecMath[1]-vecMath[0];
	vecToTarget[0] = m_vecDir - vecMath[0];
	

	D3DXVec3Cross(&vecTmp[0],&vecLine[0],&vecToTarget[0]);
	if(vecToTarget[0].x * vecLine[0].z - vecToTarget[0].z*vecLine[0].x <= 0)
	{
		//�p�[�e�B�N��
		CPaticle::Create(m_pRender,m_vecDir,"data\\Texture\\fire.jpg");
		CBullet::Uninit();
		
		return;
	}
	
	vecLine[1] = vecMath[3]-vecMath[1];
	vecToTarget[1] = m_vecDir - vecMath[1];

	D3DXVec3Cross(&vecTmp[1],&vecLine[1],&vecToTarget[1]);
	if(vecToTarget[1].x * vecLine[1].z - vecToTarget[1].z*vecLine[1].x <= 0)
	{
		//�p�[�e�B�N��
		CPaticle::Create(m_pRender,m_vecDir,"data\\Texture\\fire.jpg");
		CBullet::Uninit();
		
		return;
	}

	vecLine[2] = vecMath[2]-vecMath[3];
	vecToTarget[2] = m_vecDir - vecMath[3];

	D3DXVec3Cross(&vecTmp[0],&vecLine[0],&vecToTarget[0]);
	if(vecToTarget[2].x * vecLine[2].z - vecToTarget[2].z*vecLine[2].x <= 0)
	{
		//�p�[�e�B�N��
		CPaticle::Create(m_pRender,m_vecDir,"data\\Texture\\fire.jpg");
		CBullet::Uninit();
		
		return;
	}
	vecLine[3] = vecMath[0]-vecMath[2];
	vecToTarget[3] = m_vecDir - vecMath[2];

	D3DXVec3Cross(&vecTmp[3],&vecLine[3],&vecToTarget[3]);
	if(vecToTarget[3].x * vecLine[3].z - vecToTarget[3].z*vecLine[3].x <= 0)
	{
		//�p�[�e�B�N��
		CPaticle::Create(m_pRender,m_vecDir,"data\\Texture\\fire.jpg");
		CBullet::Uninit();
		
		return;
	}
	
	float range = 0.0f;
	if(m_btype == BULLET_PLAYER)
	{
		//�G�ƒe�̓����蔻��
		for(int i = 0;i < ENEMY_NUM_MAX;i++)
		{
			if(CGame::GetEnemy(i)->GetLifeFlag())
			{
				if(CGame::GetEnemy(i)->GetEnemyType() == ENEMY_NORMAL)
				{
					range = 10.0f;
				}
				else if(CGame::GetEnemy(i)->GetEnemyType() == ENEMY_BOSS)
				{
					range = 50.0f;
				}
				if(CColision::getInstance()->Sphere(m_vecDir.x,m_vecDir.y,m_vecDir.z,10,
					CGame::GetEnemy(i)->GetPosition().x,CGame::GetEnemy(i)->GetPosition().y,CGame::GetEnemy(i)->GetPosition().z,range))
				{
					if(CGame::GetEnemy(i)->GetEnemyLife() != 0)
					{
						CGame::GetEnemy(i)->SetEnemyLife(CGame::GetEnemy(i)->GetEnemyLife()-1);
					}
					else if(CGame::GetEnemy(i)->GetEnemyLife() == 0)
					{
						//�G�̐�
						CEnemy::SetEnemyCnt(CEnemy::GetEnemyCnt()+1);
						CGame::GetEnemy(i)->SetLifeFlag(false);//Uninit();
						//CExplosion::Create(m_pRender,m_vecDir,D3DX_PI);
						//�p�[�e�B�N��
						CPaticle::Create(m_pRender,m_vecDir,"data\\Texture\\fire.jpg");
						
						if(CGame::GetEnemy(i)->GetEnemyType() == ENEMY_NORMAL)
						{
							//�X�R�A���Z
							CScore::ChangeScore(100);
						}
						else if(CGame::GetEnemy(i)->GetEnemyType() == ENEMY_BOSS)
						{
							//�X�R�A���Z
							CScore::ChangeScore(1000);
						}
					}
					
					CBullet::Uninit();
					//CGame::SetClearFlag(true);
				}
			}
		}
	}
	
	

	if(pPlayer != NULL)
	{
		if(m_btype == BULLET_ENEMY || m_btype == BULLET_BOSS)
		{
			if(pPlayer->GetLifeFlag())
			{
				if(CColision::getInstance()->Sphere(m_vecDir.x,m_vecDir.y,m_vecDir.z,10,
					pPlayer->GetPosition().x,pPlayer->GetPosition().y,pPlayer->GetPosition().z,10))
				{
					if(pPlayer->GetLifeCnt() != 0)
					{
						pPlayer->SetLifeCnt(pPlayer->GetLifeCnt()-1);
					}
					else if (pPlayer->GetLifeCnt() == 0)
					{
						pPlayer->SetLifeFlag(false);
					}
					CGame::GetPlayerLife(pPlayer->GetLifeCnt())->SetDrwaFlag(false);
					//CExplosion::Create(m_pRender,m_vecDir,D3DX_PI);
					//�p�[�e�B�N��
					CPaticle::Create(m_pRender,m_vecDir,"data\\Texture\\fire.jpg");
					CBullet::Uninit();
				}
			}
		}
	}
	CSceneBillboard::Update();
}
//�`��
void CBullet::Draw()
{
	CSceneBillboard::Draw();
}