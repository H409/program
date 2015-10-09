//=============================================================================
//
// 当たり判定の処理 [CColision.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "main.h"

//クラス定義
class CColision
{
private:
	static CColision* m_Instance;
	D3DXVECTOR3 m_Vector[4];
	D3DXVECTOR3 m_norVector[4];
	D3DXVECTOR3 m_tmpVector[11*11];
public:
	static CColision* getInstance();
	static void Release();
	CColision();
	virtual ~CColision();

	float GetHeight(D3DXVECTOR3 pos,D3DXVECTOR3* pNormal);
	
	float GetHeightPolygon(D3DXVECTOR3& p0,D3DXVECTOR3& p1,D3DXVECTOR3& p2,D3DXVECTOR3& pos,D3DXVECTOR3* pNormal,int nNum,D3DXVECTOR3& n0,D3DXVECTOR3& n1,D3DXVECTOR3& n2);

	bool Sphere(float x1, float y1,float z1, float r1, float x2, float y2,float z2, float r2);
	bool ColSphere(float x1, float y1,float z1, float r1, float x2, float y2,float z2, float r2);
	void SetPolygonVector(int nIndex,D3DXVECTOR3 vec,D3DXVECTOR3 nor);
	
	float GetTargetDeg(float x,float z,float tgt_x,float tgt_z);
	
	void SetTmpVector(int nIndex,D3DXVECTOR3 vec)
	{
		m_tmpVector[nIndex] = vec;
	}
};