//=============================================================================
//
// プリミティブ表示処理 [CEnemy.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//多重定義防止
#ifndef __CENEMY_H__
#define __CENEMY_H__

//ヘッダーインクルード
#include "CSceneX.h"
#include "CInputKeyboard.h"


//マクロ定義
#define ENEMY_MOVE_PTN_MAX			(3)
#define ENEMY_ATTACK_PTN_MAX		(3)
#define ENEMY_RANGE_VALUE			(100)
#define ENEMY_RANGE_MARGIN_VALUE	(40)
#define ENEMY_ATTACK_CNT1			(100)
#define ENEMY_ATTACK_CNT2			(50)

typedef enum
{
	ENEMY_NONE = 0,
	ENEMY_NORMAL,
	ENEMY_BOSS,
	ENEMY_MAX
}ENEMY_TYPE;

//前方宣言
class CRender;

//クラス定義
class CEnemy:public CSceneX
{
private:
	D3DXVECTOR3				vecDir;
	char					m_movePtn;
	char					m_atkPtn;
	ENEMY_TYPE				m_Enemy_Type;
	D3DXVECTOR3				m_vecMove;
	int						m_atkCnt;
	int						m_moveCnt;
	CRender*				m_pRender;
	static int				m_EnemyCnt;
	int						m_EnemyLife;
	bool					m_stanby;
public:
	CEnemy(int nPriority = 3):CSceneX(3)
	{
		m_EnemyCnt = 0;
	}
	virtual ~CEnemy()
	{

	}
	static CEnemy* Create(CRender* pRender,D3DXVECTOR3 pos,char movetype,char atkptn,ENEMY_TYPE enemytype,char* xfilename,char* texfilename);
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,char movetype,char atkptn,ENEMY_TYPE enemytype,char* xfilename,char* texfilename);
	void Update();
	void Uninit();
	void Draw();

	static int GetEnemyCnt(void)
	{
		return m_EnemyCnt;
	}
	static void SetEnemyCnt(int cnt)
	{
		m_EnemyCnt = cnt;
	}
	int GetEnemyLife(void)
	{
		return m_EnemyLife;
	}
	void SetEnemyLife(int n)
	{
		m_EnemyLife = n;
	}
	ENEMY_TYPE GetEnemyType(void)
	{
		return m_Enemy_Type;
	}
	void SetEnemyType(ENEMY_TYPE type)
	{
		m_Enemy_Type = type;
	}
	bool MoveEnemy(int);
	void MovePtn1Enemy(int);
	void MovePtn2Enemy(int);
	void MovePtn3Enemy(int);

	bool AttackEnemy(int);
	void AttackPtn1Enemy(int);
	void AttackPtn2Enemy(int);
	void AttackPtn3Enemy(int);


};


#endif