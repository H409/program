//=============================================================================
//
// �v���~�e�B�u�\������ [CPlayer.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CPlayer.h"
#include "CBullet.h"
#include "CInputKeyboard.h"
#include "CDebugProc.h"
#include "CCamera.h"
#include "CScene3D.h"
#include "CColision.h"
#include "CMeshField.h"
#include "CScore.h"
#include "CManager.h"
#include "AnimationLinear.h"
#include "CScene2D.h"
#include "CGame.h"
#include "CSound.h"
#include "Joy.h"

//�}�N����`
#define ROTVEC_SEED	(0.05f)
#define MODEL_VEC_SEED (0.90f)
#define MODEL_MOVE_SPEED (0.2f)
#define GRAVITY			(-0.98f)
#define JUMP			(5.0f)
#define LIFE_MARGIN_X	(25)
#define LIFE_MARGIN_Y	(25)
//�ÓI�����o�ϐ�������
CSceneX* CPlayer::m_pSceneXDummy = NULL;
CScene2D* CPlayer::m_pScene2D[PLAYER_LIFE] = {NULL};

D3DXVECTOR3 g_pos(0,0,0);
D3DXVECTOR3 g_rot(0,0,0);
D3DXVECTOR3 g_vec(0,0,0);
D3DXVECTOR3 g_v(0.0f,20.0f,0.0f);//�����x�x�N�g��
//�쐬
CPlayer* CPlayer::Create(CRender* pRender,D3DXVECTOR3 pos)
{

	CPlayer* pPlayer = new CPlayer(3);

	
	pPlayer->Init(pRender);

	pPlayer->SetPosition(pos);
	
	pPlayer->SetRotate(D3DXVECTOR3(0,0,0));

	for(int i = 0;i < PLAYER_LIFE;i++)
	{
		m_pScene2D[i] = NULL;
	}
	return pPlayer;
}
//������
HRESULT CPlayer::Init(CRender* pRender)
{
	m_pRender = pRender;
	m_vecMove = D3DXVECTOR3(0.1f,0,0);
	g_pos = GetPosition();
	g_rot = GetRotate();
	m_fangleModel = 0;
	m_rotDest = D3DXVECTOR3(0,0,0);
	m_notGravity = false;
	m_pSceneLink = NULL;

	m_lifeCnt = PLAYER_LIFE;

	//--------------------------------------
	// �N�I�[�^�j�I���쐬
	//--------------------------------------
	// �ŏ��ƍŌ�̎p��������킷��]�}�g���b�N�X�̍쐬
	D3DXMATRIX mRot1;
	D3DXMATRIX mRot2;
	D3DXMatrixRotationYawPitchRoll(&mRot1, 0.0f, 0.0f, 0.0f);

	// �}�g���b�N�X������A�N�I�[�^�j�I�����쐬
	D3DXQuaternionRotationMatrix(&m_q1, &mRot1);
	D3DXQuaternionRotationMatrix(&m_q2, &mRot1);
	D3DXQuaternionRotationMatrix(&m_q3, &mRot1);


	return CSceneX::Init(pRender,GetPosition(),"data\\Model\\tank.x",NULL,true);
	//return CSceneX::Init(pRender,GetPosition(),"data\\Model\\rag.x","data\\Texture\\rag.bmp");
}
//�J��
void CPlayer::Uninit()
{
	CSceneX::Uninit();	
}
//�X�V
void CPlayer::Update()
{

	CScene* pSceneLinkOld = m_pSceneLink;
	m_pSceneLink = NULL;

	this->m_vecDir = GetRotate();

	D3DXVECTOR3 tmp = GetPosition();
	SetPositionOld(tmp);

	float fprot = 0.0f;
	g_rot = GetRotate();
	D3DXVECTOR3 nor;
	
	
/*
	//�ړ�
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_LEFT ) )
	{
		m_fangleModel = -D3DX_PI/2;
		m_rotDest.y = GetAngleYaw()-m_fangleModel;

		m_vecMove.x -= sinf(GetAngleYaw()+D3DX_PI/2)*MODEL_MOVE_SPEED;
		m_vecMove.z -= cosf(GetAngleYaw()+D3DX_PI/2)*MODEL_MOVE_SPEED;
	}
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_RIGHT ) )
	{
		m_fangleModel = D3DX_PI/2;
		m_rotDest.y = GetAngleYaw()-m_fangleModel;

		m_vecMove.x += sinf(GetAngleYaw()+D3DX_PI/2)*MODEL_MOVE_SPEED;
		m_vecMove.z += cosf(GetAngleYaw()+D3DX_PI/2)*MODEL_MOVE_SPEED;
	}
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_UP ) )
	{
		m_fangleModel = D3DX_PI;
		m_rotDest.y = GetAngleYaw()-m_fangleModel;

		m_vecMove.x -= sinf(GetAngleYaw()+D3DX_PI)*MODEL_MOVE_SPEED;
		m_vecMove.z -= cosf(GetAngleYaw()+D3DX_PI)*MODEL_MOVE_SPEED;
	}
	if( CInputKeyboard::getInstance()->GetKeyboardPress( DIK_DOWN ) )
	{
		m_fangleModel = 0;
		m_rotDest.y = GetAngleYaw()-m_fangleModel;

		m_vecMove.x += sinf(GetAngleYaw()+D3DX_PI)*MODEL_MOVE_SPEED;
		m_vecMove.z += cosf(GetAngleYaw()+D3DX_PI)*MODEL_MOVE_SPEED;
	}
//*/
///*
	
	m_vecMove.y += GRAVITY;
/*
	//�W�����v
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_SPACE))
	{
		//if(m_notGravity)
		{
			m_vecMove.y = g_v.y;
		}
	}
*/
	if(CGame::getInstance()->GetStartCnt() >= GAME_START_TIME)
	{
		if(CSceneX::GetLifeFlag())
		{
			//�e����
			if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_SPACE) || CJoySystem::getInstance()->GetJoyBtnPush(JOY_BTN1))
			{
				CSound::getInstance()->PlaySound(SOUND_LABEL_SE_SHOT);
				CBullet::Create(m_pRender,GetPosition(),GetRotate().y,BULLET_PLAYER,"data\\Texture\\bullet000.png");
		
			}
			//��
			if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_W)|| CJoySystem::getInstance()->GetJoyStkKeep(JOY_UP))
			{	
				m_fangleModel = D3DX_PI;
				m_rotDest.y = GetAngleYaw()-m_fangleModel;
				fprot = GetAngleYaw() +m_fangleModel;
				// �p�x�𐳋K��
				if( fprot < -D3DX_PI )
				{
					fprot += 2 * D3DX_PI;
				}
				else if( fprot > D3DX_PI )
				{
					fprot -= 2 * D3DX_PI;
				}
				//m_rotDest.y = m_fangleModel;
				//���f��
				m_vecMove.x -= sinf(fprot)*MODEL_MOVE_SPEED;
				m_vecMove.z -= cosf(fprot)*MODEL_MOVE_SPEED;
				//m_vecMove.x -= sinf(m_rotDest.y)*MODEL_MOVE_SPEED;
				//m_vecMove.z -= cosf(m_rotDest.y)*MODEL_MOVE_SPEED;
			}
			//��
			if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_S) || CJoySystem::getInstance()->GetJoyStkKeep(JOY_DOWN))
			{
				m_fangleModel = 0;
				m_rotDest.y = GetAngleYaw()-m_fangleModel;
				fprot = GetAngleYaw() +m_fangleModel;
				// �p�x�𐳋K��
				if( fprot < -D3DX_PI )
				{
					fprot += 2 * D3DX_PI;
				}
				else if( fprot > D3DX_PI )
				{
					fprot -= 2 * D3DX_PI;
				}
				//m_rotDest.y = m_fangleModel;
				//���f��
				m_vecMove.x -= sinf(fprot)*MODEL_MOVE_SPEED;
				m_vecMove.z -= cosf(fprot)*MODEL_MOVE_SPEED;
				//m_vecMove.x -= sinf(m_rotDest.y)*MODEL_MOVE_SPEED;
				//m_vecMove.z -= cosf(m_rotDest.y)*MODEL_MOVE_SPEED;
			}
			//��
			if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_A) || CJoySystem::getInstance()->GetJoyStkKeep(JOY_LEFT))
			{
				m_fangleModel = -D3DX_PI/2;
				m_rotDest.y = GetAngleYaw()-m_fangleModel;
				fprot = GetAngleYaw() - m_fangleModel;
				// �p�x�𐳋K��
				if( fprot < -D3DX_PI )
				{
					fprot += 2 * D3DX_PI;
				}
				else if( fprot > D3DX_PI )
				{
					fprot -= 2 * D3DX_PI;
				}
				//m_rotDest.y = m_fangleModel;
				//���f��
				m_vecMove.x -= sinf(fprot)*MODEL_MOVE_SPEED;
				m_vecMove.z -= cosf(fprot)*MODEL_MOVE_SPEED;
				//m_vecMove.x -= sinf(m_rotDest.y)*MODEL_MOVE_SPEED;
				//m_vecMove.z -= cosf(m_rotDest.y)*MODEL_MOVE_SPEED;
			}
			//�E
			if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_D) || CJoySystem::getInstance()->GetJoyStkKeep(JOY_RIGHT))
			{
				m_fangleModel = D3DX_PI/2;
				m_rotDest.y = GetAngleYaw()-m_fangleModel;
				fprot = GetAngleYaw() - m_fangleModel;
				// �p�x�𐳋K��
				if( fprot < -D3DX_PI )
				{
					fprot += 2 * D3DX_PI;
				}
				else if( fprot > D3DX_PI )
				{
					fprot -= 2 * D3DX_PI;
				}
				//m_rotDest.y = m_fangleModel;
					
				//���f��
				m_vecMove.x -= sinf(fprot)*MODEL_MOVE_SPEED;
				m_vecMove.z -= cosf(fprot)*MODEL_MOVE_SPEED;
				//m_vecMove.x -= sinf(m_rotDest.y)*MODEL_MOVE_SPEED;
				//m_vecMove.z -= cosf(m_rotDest.y)*MODEL_MOVE_SPEED;
			}
		}
	}
//*/
	//��]
	//if(CInputKeyboard::getInstance()->GetKeyboardPress(DIK_LSHIFT))
	//{
	//	m_vecDir.y-=D3DX_PI*0.01f;
	//	// �p�x�𐳋K��
	//	if( m_vecDir.y < -D3DX_PI )
	//	{
	//		m_vecDir.y += 2 * D3DX_PI;
	//	}
	//	else if( m_vecDir.y > D3DX_PI )
	//	{
	//		m_vecDir.y -= 2 * D3DX_PI;
	//	}
	//	SetRotate(m_vecDir);
	//}

	float fDiffRotY = 0.0f;
	float fDiffRot1 = 0.0f;
	
	fDiffRotY = m_rotDest.y - GetRotate().y;
	fDiffRot1 = m_fangleModel - GetRotate().y;
	// �p�x�𐳋K��
	if( fDiffRotY < -D3DX_PI )
	{
		fDiffRotY += 2 * D3DX_PI;
	}
	else if( fDiffRotY > D3DX_PI )
	{
		fDiffRotY -= 2 * D3DX_PI;
	}

	if( fDiffRot1 < -D3DX_PI )
	{
		fDiffRot1 += 2 * D3DX_PI;
	}
	else if( fDiffRot1 > D3DX_PI )
	{
		fDiffRot1 -= 2 * D3DX_PI;
	}
	D3DXVECTOR3 tmpRotVec = D3DXVECTOR3(0,GetRotate().y + fDiffRotY * ROTVEC_SEED,0);
	D3DXVECTOR3 tmpRotVec1 = D3DXVECTOR3(0,GetRotate().y + fDiffRot1 * ROTVEC_SEED,0);
	SetRotate(tmpRotVec);
	
	// �p�x�𐳋K��
	this->SetRotNormalize();
	// �p�x�𐳋K��
	if( m_rotDest.y < -D3DX_PI )
	{
		m_rotDest.y += 2 * D3DX_PI;
	}
	else if( m_rotDest.y > D3DX_PI )
	{
		m_rotDest.y -= 2 * D3DX_PI;
	}
	

	
	g_pos = GetPosition();
	
	

//	tmp.y = GetHeight(tmp,&nor);	//�����擾
	
	D3DXVECTOR3 vecLine[4];				
	D3DXVECTOR3 vecToTarget[4];				
	D3DXVECTOR3 vecTmp[4];
	D3DXVECTOR3 vecMath[4];


	for(int i = 0;i < 4;i++)
	{
		vecMath[i] = CMeshField::GetVertex(i);
	}
	

	vecLine[0] = vecMath[1]-vecMath[0];
	vecToTarget[0] = GetPosition() - vecMath[0];
	
	//�ǂƂ̓����蔻��
	D3DXVec3Cross(&vecTmp[0],&vecLine[0],&vecToTarget[0]);
	if(vecToTarget[0].x * vecLine[0].z - vecToTarget[0].z*vecLine[0].x <= 0)
	{
		m_vecMove.z *= -1;
	}
	
	vecLine[1] = vecMath[3]-vecMath[1];
	vecToTarget[1] = GetPosition() - vecMath[1];

	D3DXVec3Cross(&vecTmp[1],&vecLine[1],&vecToTarget[1]);
	if(vecToTarget[1].x * vecLine[1].z - vecToTarget[1].z*vecLine[1].x <= 0)
	{
		m_vecMove.x *= -1;	
	}

	vecLine[2] = vecMath[2]-vecMath[3];
	vecToTarget[2] = GetPosition() - vecMath[3];

	D3DXVec3Cross(&vecTmp[0],&vecLine[0],&vecToTarget[0]);
	if(vecToTarget[2].x * vecLine[2].z - vecToTarget[2].z*vecLine[2].x <= 0)
	{
		m_vecMove.z *= -1;
	}
	vecLine[3] = vecMath[0]-vecMath[2];
	vecToTarget[3] = GetPosition() - vecMath[2];

	D3DXVec3Cross(&vecTmp[3],&vecLine[3],&vecToTarget[3]);
	if(vecToTarget[3].x * vecLine[3].z - vecToTarget[3].z*vecLine[3].x <= 0)
	{
		m_vecMove.x *= -1;
	}

	D3DXVECTOR3 tmpa(0,0,0);
	D3DXVECTOR3 ax1(0,0,0);
	float fPosY = 0.0f;
	float fcos = 0.0f;
	//����
	tmp.y = CColision::getInstance()->GetHeight(tmp,&nor);
	
	//�p������
	ax1.x = tmp.x * nor.x;
	ax1.y = tmp.x * nor.y;
	ax1.z = tmp.z * nor.z;

	fcos = D3DXVec3Dot(&tmp,&nor);

	D3DXQuaternionRotationAxis(&m_q1,&ax1,fcos);

	D3DXQUATERNION  cq1;
	D3DXQuaternionConjugate( &cq1, &m_q1 );   // �����N�H�[�^�j�I��

	D3DXQUATERNION  odq( 0, 0, 1, 0);   // ���[�J���̕����N�H�[�^�j�I���iZ���j
	D3DXQUATERNION  res;
	D3DXQuaternionMultiply( &res, &cq1, &odq );   // �����E�x�N�g���EQ1
	D3DXQuaternionMultiply( &res, &res, &m_q1 );

	D3DXVECTOR3 od;  // �p�����킹��]������x�N�g��
	od.x = res.x;
	od.y = res.y;
	od.z = res.z;

	fcos = D3DXVec3Dot(&od,&CSceneX::GetRotate());

	D3DXQuaternionRotationAxis(&m_q2,&nor,fcos);

	D3DXQuaternionMultiply( &m_q3, &m_q2, &m_q1 );
	
	D3DXMatrixRotationQuaternion( &m_rotmat, &m_q3 );
	
	//CSceneX::SetRotMatrix(m_rotmat);

	//���W�ɓ����
	fPosY = tmp.y;

	tmp.x += m_vecMove.x;
	tmp.z += m_vecMove.z;
	tmp.y += m_vecMove.y;

	if(tmp.y <= fPosY)
	{
		tmp.y = fPosY;
		m_notGravity = true;
		m_vecMove.y = 0;
	}
	else
	{
		m_notGravity = false;
	}
	//���W�ݒ�
	SetPosition(tmp);

	m_vecMove.x *= MODEL_VEC_SEED;
	m_vecMove.z *= MODEL_VEC_SEED;

	g_vec = m_vecMove;

	if(0.01f > m_vecMove.x && -0.01f < m_vecMove.x)
	{
		m_vecMove.x = 0.0f;
	}
	if(0.01f > m_vecMove.z && -0.01f < m_vecMove.z)
	{
		m_vecMove.z = 0.0f;
	}


	//�M�~�b�N�Ƃ̓����蔻��
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = GetTopNode(i);
		CScene* pNext = NULL;
		

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
		{
			pNext = pScene->GetNext();
			
			if(pScene->GetObjType() == OBJTYPE_GIMMICK)
			{
				D3DXVECTOR3 p[4];
				for(int i = 0;i < 4;i++)
				{
					p[i] = D3DXVECTOR3(0,0,0);
				}
				D3DXVECTOR3 offset = D3DXVECTOR3(0,0,0);
				D3DXVECTOR3 target = D3DXVECTOR3(0,0,0);
				D3DXVECTOR3 vecLine1 = D3DXVECTOR3(0,0,0);
				D3DXVECTOR3 vectotarget1 = D3DXVECTOR3(0,0,0);
				int			nCnt = 0;

				if(pScene != NULL)
				{
					p[0].x = pScene->GetPosition().x + pScene->GetVertexMin().x;
					p[0].z = pScene->GetPosition().z + pScene->GetVertexMax().z;
					p[1].x = pScene->GetPosition().x + pScene->GetVertexMax().x;
					p[1].z = pScene->GetPosition().z + pScene->GetVertexMax().z;
					p[2].x = pScene->GetPosition().x + pScene->GetVertexMax().x;
					p[2].z = pScene->GetPosition().z + pScene->GetVertexMin().z;
					p[3].x = pScene->GetPosition().x + pScene->GetVertexMin().x;
					p[3].z = pScene->GetPosition().z + pScene->GetVertexMin().z;

					offset = GetPosition() - pScene->GetPosition();

					target.x = pScene->GetPosition().x + (cosf(-pScene->GetRotate().y)*offset.x+sinf(-pScene->GetRotate().y)*offset.z);
					target.z = pScene->GetPosition().z + (cosf(-pScene->GetRotate().y)*offset.z+sinf(-pScene->GetRotate().y)*offset.x);

					D3DXVECTOR3 nowUpG = pScene->GetPosition() + pScene->GetVertexMax();
					D3DXVECTOR3 pastUpG = pScene->GetPositionOld() + pScene->GetVertexMax();
					D3DXVECTOR3 nowDownG = pScene->GetPosition() + pScene->GetVertexMin();
					D3DXVECTOR3 pastDownG = pScene->GetPositionOld() + pScene->GetVertexMin();

					for(int i = 0;i < 4;i++)
					{
						vecLine1 = p[(i+1)%4]-p[i];
						vectotarget1 = target-p[i];

						if(vecLine1.z * vectotarget1.x - vecLine1.x * vectotarget1.z < 0.0f)
						{
							//�͈͊O
							//CDebugProc::Print("\n�͈͊O");
						}
						else
						{
							nCnt++;
							//�͈͓�
				
							if(nCnt == 4)
							{
								CDebugProc::Print("\n�͈͓�");
								if((nowUpG.y > GetPosition().y && pastUpG.y <= GetPosition().y) || (nowUpG.y <= GetPositionOld().y && nowUpG.y > GetPosition().y))
								{
									m_pSceneLink = pScene;
									m_notGravity = true;
									tmp.y = nowUpG.y;
									m_vecMove.y = 0;
									//SetPosition(tmp);
									//SetPositionOld(tmp);
								}
								else if((GetPosition().y > nowDownG.y) || GetPositionOld().y <= nowDownG.y)
								{
									//tmp.y = nowDownG.y;
									//m_vecMove.y = 0;
									//SetPosition(tmp);
									//SetPositionOld(tmp);
								}
								else
								{
									m_notGravity = false;
								}
							}
						}
					}

				}			
			}
			pScene = pNext;

		}
	}

	
	

	CDebugProc::Print("\nPLAYERVelocityX%fY%fZ%f",m_vecMove.x,m_vecMove.y,m_vecMove.z);
	CSceneX::Update();
}
//�`��
void CPlayer::Draw()
{
	
	CSceneX::Draw();
}

//����
CPlayerLife* CPlayerLife::Create(CRender* pRender,const D3DXVECTOR3 pos)
{
	CPlayerLife* pNumber = new CPlayerLife();

	pNumber->Init(pRender);

	pNumber->SetPosition(pos);

	return pNumber;
}
//������
HRESULT CPlayerLife::Init(CRender* pRender)
{
	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\zanki.png",&m_pD3DTex);
	
	//�|���S���ݒ�
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffer,
											NULL)))
	{
		return E_FAIL;
	}
	//m_pos = D3DXVECTOR3(300,200,0);	//���W
	m_rot = D3DXVECTOR3(0,0,0);		//��]
	//�Ίp���̒���
	m_fLength = sqrtf(LIFE_MARGIN_X*LIFE_MARGIN_X+LIFE_MARGIN_Y*LIFE_MARGIN_Y);
	//�Ίp���̊p�x
	m_fAngle  = atan2((float)LIFE_MARGIN_X,(float)LIFE_MARGIN_Y);

	
	return S_OK;
}

//�X�V
void CPlayerLife::Update(void)
{

	m_rot.z -= D3DX_PI * 0.01f;
	//�p�x���K��
	if( m_rot.z < -D3DX_PI )
	{
		m_rot.z += 2 * D3DX_PI;
	}
	// �p�x�𐳋K��
	else if( m_rot.z > D3DX_PI )
	{
		m_rot.z -= 2 * D3DX_PI;
	}

	VERTEX_2D *pVtx = NULL;
	//���b�N
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//����
	pVtx[0].vtx.x = m_pos.x - sinf(-m_rot.z+m_fAngle)*m_fLength;
	pVtx[0].vtx.y = m_pos.y + cosf(-m_rot.z+m_fAngle)*m_fLength;
	//����
	pVtx[1].vtx.x = m_pos.x - sinf(m_rot.z+m_fAngle)*m_fLength;
	pVtx[1].vtx.y = m_pos.y - cosf(m_rot.z+m_fAngle)*m_fLength;
	//�E��
	pVtx[2].vtx.x = m_pos.x + sinf(m_rot.z+m_fAngle)*m_fLength;
	pVtx[2].vtx.y = m_pos.y + cosf(m_rot.z+m_fAngle)*m_fLength;
	//�E��
	pVtx[3].vtx.x = m_pos.x + sinf(-m_rot.z+m_fAngle)*m_fLength;
	pVtx[3].vtx.y = m_pos.y - cosf(-m_rot.z+m_fAngle)*m_fLength;
	//���W�ϊ���ʒu
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�F
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0,1);
	pVtx[1].tex = D3DXVECTOR2(0,0);
	pVtx[2].tex = D3DXVECTOR2(1,1);
	pVtx[3].tex = D3DXVECTOR2(1,0);
	//�A�����b�N
	m_pD3DVtxBuffer->Unlock();	
	

}

//�J��
void CPlayerLife::Uninit(void)
{
	SAFE_RELEASE(m_pD3DTex);		//�e�N�X�`���̊J��
	SAFE_RELEASE(m_pD3DVtxBuffer);	//���_�o�b�t�@�̊J��
	//__asm int 3
}

//�`��
void CPlayerLife::Draw(void)
{
	if(m_DrawFlag)
	{
		//�f�[�^��n��
		m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
		//FVF�̐ݒ�
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
		//�e�N�X�`���̐ݒ�
		m_pD3DDevice->SetTexture(0,m_pD3DTex);
		//�|���S���̐ݒ�
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
}
void CPlayerLife::DrawShade(void)
{
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}


//
D3DXVECTOR3 GetPos(void)
{
	return g_pos;
}

D3DXVECTOR3 GetRot(void)
{
	return g_rot;
}

D3DXVECTOR3 GetVelocity(void)
{
	return g_vec;
}