//多重定義防止
#ifndef __CLIGHT_H__
#define __CLIGHT_H__

//ヘッダーインクルード
#include"main.h"

//前方宣言
class CRender;

//クラス定義
class CLight
{
private:
	D3DLIGHT9 m_aLight[3];
	D3DXVECTOR3 m_vecLight;//(0,18,10);
	D3DXMATRIX m_matLight;
	D3DXVECTOR3 m_vecEye;//(8,8,-8);
	D3DXVECTOR3 m_vecLook;//(0,0,0);
	D3DXVECTOR3 m_vecUp;//(0,1,0);
	static CLight* m_instance;
public:
	static CLight* getInstance();
	static void Release();

	CLight(){}
	virtual ~CLight(){}
	HRESULT Init(CRender* pRender);
	void Uninit();
	void Update();
	void ShadeLight(void);
	D3DXVECTOR3 GetVecLight(void)
	{
		return m_vecLight;
	}
	
	D3DXVECTOR3 GetVecEye(void)
	{
		return m_vecEye;
	}

	D3DXVECTOR3 GetVecLook(void)
	{
		return m_vecLook;
	}
	D3DXVECTOR3 GetVecUp(void)
	{
		return m_vecUp;
	}
	D3DXMATRIX GetLightMatrix(void)
	{
		return m_matLight;
	}

};


#endif
