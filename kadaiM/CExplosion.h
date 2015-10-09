//多重定義防止
#ifndef __CEXPLOSION_H__
#define __CEXPLOSION_H__

//ヘッダーインクルード
#include "CSceneBillboard.h"


class CExplosion:public CSceneBillboard
{
private:
	D3DXVECTOR3				m_vecDir;
	float					m_fangle;
public:
	CExplosion(int nPriority = 3):CSceneBillboard(nPriority)
	{

	}
	virtual ~CExplosion()
	{

	}
	static CExplosion* Create(CRender* pRender,D3DXVECTOR3 pos,float fangle);
	HRESULT Init(CRender* pRender,float fangle);
	void Update();
	void Uninit();
	void Draw();
};

#endif