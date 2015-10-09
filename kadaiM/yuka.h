//=============================================================================
//
// プリミティブ表示処理 [yuka.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
#ifndef __YUKA_H__
#define __YUKA_H__

//ヘッダーインクルード
#include "main.h"
#include "CSceneX.h"


//前方宣言
class CRender;

//クラス定義
class CYuka:public CSceneX
{
private:
	D3DXVECTOR3				m_vecDir;
	static CSceneX*			m_pSceneXDummy;
	CRender*				m_pRender;
	D3DXVECTOR3				m_vecMove;	//移動
	float					m_fangleModel;
	D3DXVECTOR3				m_rotDest;	//角度
	D3DXVECTOR3				m_vtxMin;
	D3DXVECTOR3				m_vtxMax;
	D3DXVECTOR3				m_posOld;
	D3DXVECTOR3				m_rotOld;
	bool					m_initManager;

public:
	CYuka(int nPriority = 3):CSceneX(3,OBJTYPE_GIMMICK)
	{
		m_vtxMin = D3DXVECTOR3(0,0,0);
		m_vtxMax = D3DXVECTOR3(0,0,0);
	}
	virtual ~CYuka()
	{

	}
	static CYuka* Create(CRender* pRender,D3DXVECTOR3 pos);
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos);
	void Update();
	void Uninit();
	void Draw();

	//古い座標取得・設定
	void SetPositionOld(D3DXVECTOR3 pos){m_posOld = pos;}
	D3DXVECTOR3 GetPositionOld(void){return m_posOld;}
	//古い角度取得・設定
	void SetRotationOld(D3DXVECTOR3 rot){m_rotOld = rot;}
	D3DXVECTOR3 GetRotationOld(void){return m_rotOld;}
	//頂点位置取得
	D3DXVECTOR3 GetVertexMin(void){return m_vtxMin;}
	D3DXVECTOR3 GetVertexMax(void){return m_vtxMax;}

};
#endif