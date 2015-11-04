//-----------------------------------------------------------------------------
//
// �v���C���[���� : player.cpp
// Author : sembon takanori
//
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------
#include "player.h"

//------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �\����
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �v���g�^�C�v�錾
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �O���[�o���ϐ�
//------------------------------------------------------------------------

//-------------------------------------------------------------------
// �֐��� : �R���X�g���N�^
//
// ����   : LPDIRECT3DDEVICE9 pDevice : �f�o�C�X
//-------------------------------------------------------------------
Player::Player( LPDIRECT3DDEVICE9 pDevice ) : Object()
{
	pDevice_ = pDevice ;
}

//-------------------------------------------------------------------
// �֐��� : �f�X�g���N�^
//
// ����   : �Ȃ�
//-------------------------------------------------------------------
Player::~Player( void )
{
	pKim_->Release();
}

//-------------------------------------------------------------------
// �֐��� : ������
//
// ����   : D3DXVECTOR2 pos : ���W
// ����   : D3DXVECTOR2 size : �T�C�Y
// �Ԃ�l : �������ǂ���
//-------------------------------------------------------------------
void Player::Init( float3 pos )
{
	position_ = pos ;
	pKim_ = new Kim( pDevice_ );
	pKim_->Load( "resources/model/ZZI_taiki4.kim" );
}

//-------------------------------------------------------------------
// �֐��� : �X�V
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------
void Player::Update( void )
{
	pKim_->Update();
	pKim_->SetWorld( ( D3DXMATRIX& )matrix_ );
}

//-------------------------------------------------------------------
// �֐��� : �`��
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------
void Player::Draw( void )
{
	pKim_->Draw();
}

//-------------------------------------------------------------------
// �֐��� : �I��
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------
void Player::Uninit( void )
{
}

////-------------------------------------------------------------------
//// �֐��� : �C���X�^���X����
////
//// ����   : LPDIRECT3DDEVICE9 pDevice
//// ����   : D3DXVECTOR2 pos : ���W
//// ����   : D3DXVECTOR2 size : �T�C�Y
//// ����   : int priority : �v���C�I���e�B
//// �Ԃ�l : ���g�̃|�C���^
////-------------------------------------------------------------------
//Player* Player::Create( LPDIRECT3DDEVICE9 pDevice , float3 pos )
//{
//	//--  �C���X�^���X����  --//
//	Player* pObject = new Player( pDevice );
//
//	//--  ������  --//
//	pObject->Init( pos );
//
//	return pObject ;
//}

// END