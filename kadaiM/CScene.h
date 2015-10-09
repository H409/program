//多重定義防止
#ifndef __CSCENE_H__
#define __CSCENE_H__

//ヘッダーインクルード
#include "main.h"
#include "CInputKeyboard.h"

//マクロ定義
#define PRIORITY_MAX	(8)

//前方宣言
class CRender;

//種類
typedef enum
{
	OBJTYPE_NONE = 0,
	OBJTYPE_2D,
	OBJTYPE_3D,
	OBJTYPE_X,
	OBJTYPE_BILLBOARD,
	OBJTYPE_GIMMICK,
	OBJTYPE_FADE,
	OBJTYPE_PAUSE,
	OBJTYPE_2DGIM,
	OBJTYPE_MAX
}OBJTYPE;

//クラス定義
class CScene
{

private:
	
	static CScene*		m_pTop[PRIORITY_MAX];	//リストの先頭アドレス
	static CScene*		m_pCur[PRIORITY_MAX];	//リストの現在位置アドレス
	CScene*				m_pNext;				//前のオブジェクトへのポインタ
	CScene*				m_pPrev;				//次のオブジェクトへのポインタ

	CScene*				m_DummyHead;			//ダミーヘッド
	CScene*				m_DummyTail;			//ダミーテイル
	const int			m_nPriority;			//プライオリティ
	bool				m_bDeath;				//オブジェクト削除フラグ
	OBJTYPE				m_objType;				//オブジェ種類
public:

	//コンストラクタ
	CScene(int nPriority = 3,OBJTYPE objtype = OBJTYPE_NONE);
	//デストラクタ
	virtual ~CScene();
	//初期化
	virtual HRESULT Init(CRender* pRender) = 0;
	//更新
	virtual void Update() = 0;
	//開放
	virtual void Uninit() = 0;
	//描画
	virtual void Draw() = 0;
	virtual void DrawShade() = 0;
	//座標取得
	virtual D3DXVECTOR3 GetPosition(void) = 0;

	//座標設定
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
		
	virtual D3DXVECTOR3 GetRotate(void) = 0;
	
	//回転設定
	virtual void SetRotate(D3DXVECTOR3 rot) = 0;
	
	//古い座標取得・設定
	virtual void SetPositionOld(D3DXVECTOR3 pos){}
	virtual D3DXVECTOR3 GetPositionOld(void){return D3DXVECTOR3(0.0f,0.0f,0.0f);}
	//古い角度取得・設定
	virtual void SetRotationOld(D3DXVECTOR3 rot){}
	virtual D3DXVECTOR3 GetRotationOld(void){return D3DXVECTOR3(0,0,0);}
	//頂点位置取得
	virtual D3DXVECTOR3 GetVertexMin(void){return D3DXVECTOR3(0,0,0);}
	virtual D3DXVECTOR3 GetVertexMax(void){return D3DXVECTOR3(0,0,0);}

	//OBJ種類取得
	OBJTYPE GetObjType(void){return m_objType;}
	CScene* GetTypePointer(OBJTYPE objtype);
	//▼リスト系
	void Release(void);
	void LinkList(void);
	void UnlinkList(CScene* pScene);
	static void DrawAll(void);
	static void DrawShadeAll(void);
	static void UpdateAll(void);
	static void ReleaseAll(void);
	static void UpdateFade(void);
	static void DrawFade(void);
	static void FreePhase(void);
	CScene* GetNext(void)
	{
		return m_pNext;
	}
	static CScene* GetTopNode(int nIndex)
	{
		return m_pTop[nIndex];
	}
};
#endif