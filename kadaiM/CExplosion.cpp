
//=============================================================================
//
// �v���~�e�B�u�\������ [CPlayer.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CExplosion.h"

//�N���X��`

//�쐬
CExplosion* CExplosion::Create(CRender* pRender,D3DXVECTOR3 pos,float fangle)
{

	CExplosion* pBullet = new CExplosion(3);

	pBullet->Init(pRender,fangle);

	pBullet->SetPosition(pos);

	

	return pBullet;
}
//������
HRESULT CExplosion::Init(CRender* pRender,float fangle)
{

	return CSceneBillboard::InitAnime(pRender,"data\\Texture\\explosion.png");
}
//�J��
void CExplosion::Uninit()
{
	CSceneBillboard::Uninit();	
}
//�X�V
void CExplosion::Update()
{
	m_vecDir = GetPosition();

	CSceneBillboard::UpdateAnime();
	
}
//�`��
void CExplosion::Draw()
{
	CSceneBillboard::DrawAnime();
}