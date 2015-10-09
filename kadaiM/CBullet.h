//多重定義防止
#ifndef __CBULLET_H__
#define __CBULLET_H__

//ヘッダーインクルード
#include "CSceneBillboard.h"

//マクロ定義
#define BULLET_SPEED	(4.0f)

typedef enum
{
	BULLET_NONE = 0,
	BULLET_PLAYER,
	BULLET_ENEMY,
	BULLET_BOSS,
	BULLET_MAX
}BULLET_TYPE;


//前方宣言
class CRender;

class CBullet:public CSceneBillboard
{
private:
	D3DXVECTOR3				m_vecDir;
	float					m_fangle;
	CRender*				m_pRender;
	BULLET_TYPE				m_btype;
	D3DXVECTOR3				m_velocity;
	float					m_dt;
public:
	CBullet(int nPriority = 3):CSceneBillboard(nPriority)
	{

	}
	virtual ~CBullet()
	{

	}
	static CBullet* Create(CRender* pRender,D3DXVECTOR3 pos,float fangle,BULLET_TYPE btype,char* ptexname);
	HRESULT Init(CRender* pRender,float fangle,BULLET_TYPE btype,char* ptexname);
	void Update();
	void Uninit();
	void Draw();
};

#endif