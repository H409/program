//=============================================================================
//
// 当たり判定の処理 [CColision.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CColision.h"
#include "CPlayer.h"

//マクロ定義
#define SIZE	(50.0f)
#define BLOCK	(10)

//静的メンバ変数初期化
CColision* CColision::m_Instance = NULL;

//インスタンス生成
CColision* CColision::getInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new CColision();	
	}
	return m_Instance;
}
//インスタンス開放
void CColision::Release()
{
	if(m_Instance != NULL)
	{
		delete m_Instance;
		m_Instance = NULL;
	}
}
//コンストラクタ
CColision::CColision()
{
	for(int i = 0;i < 4;i++)
	{
		m_Vector[i] = D3DXVECTOR3(0,0,0);
		m_norVector[i] = D3DXVECTOR3(0,0,0);
	}
	
}

//デストラクタ
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

	//TODO：ここをどうにかする
	m_Vector[0] = m_tmpVector[nNum];
	m_Vector[1] = m_tmpVector[nNum+1];
	m_Vector[2] = m_tmpVector[nNum1];
	m_Vector[3] = m_tmpVector[nNum1+1];

	Vec0 = m_Vector[0] - m_Vector[2];
	Vec1 = pos - m_Vector[2];
	//左側
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

	//右側
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

	//外積
	D3DXVec3Cross(pNormal,&Vec0,&Vec1);
	//正規化
	D3DXVec3Normalize(pNormal,pNormal);
	n0.y*=-1;
	if(pNormal->y == 0.0f)
	{
		return 0.0f;
	}
	fHeight = p0.y - (pNormal->x*(pos.x-p0.x)+pNormal->z*(pos.z-p0.z))/pNormal->y;
	
	return fHeight;
}
//球の判定
bool CColision::Sphere(float x1, float y1,float z1, float r1, float x2, float y2,float z2, float r2)
{
	

	return (pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2)) < pow(r1 + r2,2);
}
//球の当たり判定
bool ColSphere(float x1, float y1,float z1, float r1, float x2, float y2,float z2, float r2)
{
	D3DXVECTOR3 vec1,vec2;

	vec1.x = x1;
	vec1.y = y1;
	vec1.z = z1;

	vec2.x = x2;
	vec2.y = y2;
	vec2.z = z2;

	//2つの物体の中心間の距離を求める
	D3DXVECTOR3 vecLength = vec2 - vec1;
	FLOAT fLength = D3DXVec3Length(&vecLength);

	//衝突判定
	if(fLength <= r1 + r2)
	{
		return true;
	}

	return false;

}
//==================================================================
//機能：目的の座標を常に調べる（誘導弾）
//引数：第1引数：弾を発射するX座標
//		第2引数：弾を発射するY座標
//		第3引数：標的のX座標
//		第4引数：標的のY座標
//戻り値：着弾地点の角度
//==================================================================
float CColision::GetTargetDeg(float x,float z,float tgt_x,float tgt_z)
{
	float x_ratio,z_ratio;	//比率格納
	float rad;		//ラジアン角度格納

	//比率を求める
	x_ratio = tgt_x - x;
	z_ratio = tgt_z - z;
	//比率から角度を求める
	rad = atan2(-x_ratio,-z_ratio);

	return rad;	//着弾地点への角度を返す
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