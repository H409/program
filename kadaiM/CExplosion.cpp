
//=============================================================================
//
// プリミティブ表示処理 [CPlayer.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CExplosion.h"

//クラス定義

//作成
CExplosion* CExplosion::Create(CRender* pRender,D3DXVECTOR3 pos,float fangle)
{

	CExplosion* pBullet = new CExplosion(3);

	pBullet->Init(pRender,fangle);

	pBullet->SetPosition(pos);

	

	return pBullet;
}
//初期化
HRESULT CExplosion::Init(CRender* pRender,float fangle)
{

	return CSceneBillboard::InitAnime(pRender,"data\\Texture\\explosion.png");
}
//開放
void CExplosion::Uninit()
{
	CSceneBillboard::Uninit();	
}
//更新
void CExplosion::Update()
{
	m_vecDir = GetPosition();

	CSceneBillboard::UpdateAnime();
	
}
//描画
void CExplosion::Draw()
{
	CSceneBillboard::DrawAnime();
}