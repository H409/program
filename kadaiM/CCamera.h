//多重定義防止
#ifndef __CCAMERA_H__
#define __CCAMERA_H__

//ヘッダーインクルード
#include "main.h"
#include "CInputKeyboard.h"
#include "CRender.h"
//前方宣言
class CRender;

//クラス定義
class CCamera
{
private:
	D3DXVECTOR3  m_posCameraP;		// 視点
	D3DXVECTOR3  m_posCameraR;		// 注視点
	D3DXVECTOR3  m_vecCameraU;		// 上方向ベクトル
	D3DXMATRIX   m_mtxView;			// ビューマトリックス
	D3DXMATRIX	 m_mtxProjection;	// プロジェクションマトリックス
	D3DXVECTOR3	 m_rotCamera;		// カメラの向き
	float		 m_fLengthCameraXZ;	// 視点から注視点までの距離( x, z )
	D3DXVECTOR3  m_posCameraPDest;	// 視点の先
	D3DXVECTOR3  m_posCameraRDest;	// 注視点の先
	D3DVIEWPORT9 m_viewport;		// ビューポート
	float		 m_faglView;		// 画角用（ズーム）
	D3DXVECTOR3  m_vecSpeed;		// スピード
	D3DXMATRIX   m_mtxRot;			// 回転用行列
	float		 m_fAngle;			// 角度
	LPDIRECT3DDEVICE9	m_pDevice;		
	CInputKeyboard*		m_pInputKeyboard;
	D3DXVECTOR3	m_plpos;			//
	bool		m_bFlag;			//回転か移動
	bool		m_initManager;
	bool		m_stopFlag;	
	MODE		m_mode;
	static CCamera* m_instance;
public:
	
	static CCamera* getInstance();
	static void Release();

	CCamera(){}
	virtual ~CCamera(){}
	HRESULT Init(CRender* pRender);
	HRESULT TitleInit(CRender* pRender);
	void Update(void);
	void TitleUpdate(void);
	void UpdateDebug(void);
	void Uninit(void);
	void SetCamera(void);
	D3DXMATRIX GetMtxView()
	{
		return m_mtxView;
	}
	D3DXMATRIX GetMtxProjection()
	{
		return m_mtxProjection;
	}
	
	void SetKeyBoard(CInputKeyboard* pInputKeyboard)
	{
		m_pInputKeyboard = pInputKeyboard;
	}
	

};
D3DXMATRIX GetMtxView();
float GetAngleYaw(void);
#endif