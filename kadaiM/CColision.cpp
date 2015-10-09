//=============================================================================
//
// �����蔻��̏��� [CColision.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CColision.h"
#include "CPlayer.h"

//�}�N����`
#define SIZE	(50.0f)
#define BLOCK	(10)

//�ÓI�����o�ϐ�������
CColision* CColision::m_Instance = NULL;

//�C���X�^���X����
CColision* CColision::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new CColision();	
	}
	return m_Instance;
}
//�C���X�^���X�J��
void CColision::Release()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}
//�R���X�g���N�^
CColision::CColision()
{
	for(int i = 0;i < 4;i++)
	{
		m_Vector[i] = D3DXVECTOR3(0,0,0);
		m_norVector[i] = D3DXVECTOR3(0,0,0);
	}
	
}

//�f�X�g���N�^
CColision::~CColision(){}

float CColision::GetHeight(D3DXVECTOR3 pos,D3DXVECTOR3* pNormal)
{
	D3DXVECTOR3 Vec0,Vec1;
	D3DXVECTOR3 tmpVec(0,0,0);
	float fPosX,fPosZ;


	fPosX = pos.x/SIZE;
	fPosZ = pos.z/SIZE;

	if(fPosX <= 0)
	{
		fPosX *= -1.0f;
	}
	if(fPosZ <= 0)
	{
		fPosZ *= -1.0f;
	}

	int nNum = static_cast<int>(fPosZ)*(BLOCK+1) + static_cast<int>(fPosX);
	int nNum1 = (static_cast<int>(fPosZ)+1)*(BLOCK+1) + static_cast<int>(fPosX);

	//TODO�F�������ǂ��ɂ�����
	m_Vector[0] = m_tmpVector[nNum];
	m_Vector[1] = m_tmpVector[nNum+1];
	m_Vector[2] = m_tmpVector[nNum1];
	m_Vector[3] = m_tmpVector[nNum1+1];

	Vec0 = m_Vector[0] - m_Vector[2];
	Vec1 = pos - m_Vector[2];
	//����
	if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
	{
		Vec0 = m_Vector[3] - m_Vector[0];
		Vec1 = pos - m_Vector[0];
		if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
		{
			Vec0 = m_Vector[2] - m_Vector[3];
			Vec1 = pos - m_Vector[3];
			if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
			{
				return GetHeightPolygon(m_Vector[2],m_Vector[0],m_Vector[3],pos,pNormal,0,m_norVector[2],m_norVector[0],m_norVector[3]);
			}
		}
	}

	//�E��
	Vec0 = m_Vector[0] - m_Vector[3];
	Vec1 = pos - m_Vector[3];	
	if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
	{
		Vec0 = m_Vector[1] - m_Vector[0];
		Vec1 = pos - m_Vector[0];
		if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
		{
			Vec0 = m_Vector[3] - m_Vector[1];
			Vec1 = pos - m_Vector[1];
			if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
			{
				return GetHeightPolygon(m_Vector[1],m_Vector[0],m_Vector[3],pos,pNormal,1,m_norVector[1],m_norVector[0],m_norVector[3]);
			}
		}
	}	
	return 0.0f;
}

float CColision::GetHeightPolygon(D3DXVECTOR3& p0,D3DXVECTOR3& p1,D3DXVECTOR3& p2,D3DXVECTOR3& pos,D3DXVECTOR3* pNormal,int nNum,D3DXVECTOR3& n0,D3DXVECTOR3& n1,D3DXVECTOR3& n2)
{
	D3DXVECTOR3 Vec0,Vec1;

	Vec0 = p1 - p0;
	Vec1 = p2 - p0;
	float fHeight = 0.0f;

	//�O��
	D3DXVec3Cross(pNormal,&Vec0,&Vec1);
	//���K��
	D3DXVec3Normalize(pNormal,pNormal);
	n0.y*=-1;
	if(pNormal->y == 0.0f)
	{
		return 0.0f;
	}
	fHeight = p0.y - (pNormal->x*(pos.x-p0.x)+pNormal->z*(pos.z-p0.z))/pNormal->y;
	
	return fHeight;
}
//���̔���
bool CColision::Sphere(float x1, float y1,float z1, float r1, float x2, float y2,float z2, float r2)
{
	

	return (pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2)) < pow(r1 + r2,2);
}
//���̓����蔻��
bool ColSphere(float x1, float y1,float z1, float r1, float x2, float y2,float z2, float r2)
{
	D3DXVECTOR3 vec1,vec2;

	vec1.x = x1;
	vec1.y = y1;
	vec1.z = z1;

	vec2.x = x2;
	vec2.y = y2;
	vec2.z = z2;

	//2�̕��̂̒��S�Ԃ̋��������߂�
	D3DXVECTOR3 vecLength = vec2 - vec1;
	FLOAT fLength = D3DXVec3Length(&vecLength);

	//�Փ˔���
	if(fLength <= r1 + r2)
	{
		return true;
	}

	return false;

}
//==================================================================
//�@�\�F�ړI�̍��W����ɒ��ׂ�i�U���e�j
//�����F��1�����F�e�𔭎˂���X���W
//		��2�����F�e�𔭎˂���Y���W
//		��3�����F�W�I��X���W
//		��4�����F�W�I��Y���W
//�߂�l�F���e�n�_�̊p�x
//==================================================================
float CColision::GetTargetDeg(float x,float z,float tgt_x,float tgt_z)
{
	float x_ratio,z_ratio;	//�䗦�i�[
	float rad;		//���W�A���p�x�i�[

	//�䗦�����߂�
	x_ratio = tgt_x - x;
	z_ratio = tgt_z - z;
	//�䗦����p�x�����߂�
	rad = atan2(-x_ratio,-z_ratio);

	return rad;	//���e�n�_�ւ̊p�x��Ԃ�
}

void CColision::SetPolygonVector(int nIndex,D3DXVECTOR3 vec,D3DXVECTOR3 nor)
{
	m_Vector[nIndex] = vec;
	m_norVector[nIndex] = nor;
}
/*
	Vec0 = m_Vector[1] - m_Vector[0];
	Vec1 = pos - m_Vector[0];	
	if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
	{
		Vec0 = m_Vector[3] - m_Vector[1];
		Vec1 = pos - m_Vector[1];
		if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
		{
			Vec0 = m_Vector[0] - m_Vector[3];
			Vec1 = pos - m_Vector[3];
			if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
			{
				return GetHeightPolygon(m_Vector[1],m_Vector[0],m_Vector[3],pos,pNormal,1,m_norVector[1],m_norVector[0],m_norVector[3]);
			}
		}
	}
*/
//eof