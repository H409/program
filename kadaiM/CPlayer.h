//多重定義防止
#ifndef __CPLAYER_H__
#define __CPLAYER_H__

//ヘッダーインクルード
#include "main.h"
#include "CSceneX.h"

#define PLAYER_LIFE	(3)

//前方宣言
class CRender;
class AnimationLinear;
class CScene2D;

//クラス定義
class CPlayer:public CSceneX
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
	bool					m_notGravity;
	CScene*					m_pSceneLink;
	AnimationLinear*		m_pAnim;
	// クオータニオン
	D3DXQUATERNION m_q1; // モデルの最初の姿勢
	D3DXQUATERNION m_q2; // モデルの最後の姿勢
	D3DXQUATERNION m_q3; // モデルの最後の姿勢
	D3DXMATRIX				m_rotmat;
	char					m_lifeCnt;
	static CScene2D*		m_pScene2D[PLAYER_LIFE];

public:
	CPlayer(int nPriority = 3):CSceneX(3)
	{
		m_notGravity = true;
		m_pSceneLink = NULL;
	}
	virtual ~CPlayer()
	{

	}
	static CPlayer* Create(CRender* pRender,D3DXVECTOR3 pos);
	HRESULT Init(CRender* pRender);
	void Update();
	void Uninit();
	void Draw();

	CScene* GetSceneLink(void){return m_pSceneLink;}

	//古い座標取得・設定
	void SetPositionOld(D3DXVECTOR3 pos){m_posOld = pos;}
	D3DXVECTOR3 GetPositionOld(void){return m_posOld;}
	//古い角度取得・設定
	void SetRotationOld(D3DXVECTOR3 rot){m_rotOld = rot;}
	D3DXVECTOR3 GetRotationOld(void){return m_rotOld;}
	//頂点位置取得
	D3DXVECTOR3 GetVertexMin(void){return m_vtxMin;}
	D3DXVECTOR3 GetVertexMax(void){return m_vtxMax;}

	char GetLifeCnt(void)
	{
		return m_lifeCnt;
	}
	void SetLifeCnt(char lifecnt)
	{
		m_lifeCnt = lifecnt;
	}


};

class CPlayerLife:public CScene
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// テクスチャ情報読み込み用
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// 頂点バッファ
	D3DXVECTOR3				m_pos;					// 座標
	D3DXVECTOR3				m_rot;					// 回転
	float					m_fLength;				// 中心から頂点までの長さ
	float					m_fAngle;				// 中心から頂点への角度
	D3DXVECTOR2				m_Tex;					// テクスチャ座標
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	int						m_Num;
	bool					m_DrawFlag;
public:
	CPlayerLife(){}
	virtual ~CPlayerLife(){}

	//初期化
	HRESULT Init(CRender* pRender);
	//更新
	void Update();
	//開放
	void Uninit();
	//描画
	void Draw();
	void DrawShade();

	bool GetDrawFlag(void)
	{
		return m_DrawFlag;
	}
	void SetDrwaFlag(bool flag)
	{
		m_DrawFlag = flag;
	}
	//座標取得
	D3DXVECTOR3 GetPosition(void)
	{
		return m_pos;
	}
	//座標設定
	void SetPosition(D3DXVECTOR3 pos)
	{
		m_pos = pos;	
	}
	//回転取得
	D3DXVECTOR3 GetRotate(void)
	{
		return m_rot;
	}
	//回転設定
	void SetRotate(D3DXVECTOR3 rot)
	{
		m_rot = rot;	
	}

	//生成
	static CPlayerLife* Create(CRender* pRender,const D3DXVECTOR3 pos);
};

D3DXVECTOR3 GetVelocity(void);
D3DXVECTOR3 GetPos(void);
D3DXVECTOR3 GetRot(void);
#endif