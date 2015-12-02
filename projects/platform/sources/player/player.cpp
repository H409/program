//-----------------------------------------------------------------------------
//
// �v���C���[���� : player.cpp
// Author : sembon takanori
//
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------
#include "../system/win_system.h"
#include "../system/input_manager.h"
#include "../system/input_keyboard.h"

#include "../system/input_mouse.h"

#include "math/math.h"
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
	pKim_ = nullptr;
	camera_vector_ = float3();
	move_ = float3();
	speed_ = float3( 0.01f , 0.01f , 0.01f );

	position_ = float3( 0 , 0 , 0 );

	ID_ = 0 ;		// 1P
	action_animation_end_ = false ;

	state_ = STATE::NONE ;

}

//-------------------------------------------------------------------
// �֐��� : �f�X�g���N�^
//
// ����   : �Ȃ�
//-------------------------------------------------------------------
Player::~Player( void )
{
	SafeRelease(pKim_);
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
	pKim_->Load( "resources/model/ZZI_1_MO.kim" );

	rotDest_ = float3();
}

//-------------------------------------------------------------------
// �֐��� : �X�V
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------
void Player::Update( void )
{
	old_position_ = position_ ;

	//--  �ړ�  --//
	Control();

	//--  kim�X�V  --//
	UpdateKimMatrix();
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

//-------------------------------------------------------------------
// �֐��� : ����
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------
void Player::Control( void )
{
	D3DXVec3Normalize( ( D3DXVECTOR3* )&camera_vector_ , ( D3DXVECTOR3* )&camera_vector_ );
//	pKim_->SetAnime( Kim::ANIME::WAIT );
	bool bMove = false ;	// �ړ�
	action_ = false ;

	if( GET_INPUT_MOUSE()->GetTrigger( InputMouse::MOUSE_KEY::RIGHT ) == true )
	{
		if( state_ != STATE::AIM )
		{
			state_ = STATE::AIM ;
		}
		else
		{
			state_ = STATE::WAIT ;
		}
	}

	//--  �ړ��@�O  --//	
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_W ) == true )
	{
		//move_._x += sinf( camera_vector_._y ) * speed_._x ;
		//move_._z += cosf( camera_vector_._y ) * speed_._z ;

		move_._x += camera_vector_._x * speed_._x ; 
		move_._z += camera_vector_._z * speed_._z ;

		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );

		bMove = true ;
	}


	//--  �ړ��@��  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_S ) == true )
	{
		//move_._x -= sinf( camera_vector_._y ) * speed_._x ;
		//move_._z -= cosf( camera_vector_._y ) * speed_._z ;

		move_._x -= camera_vector_._x * speed_._x ; 
		move_._z -= camera_vector_._z * speed_._z ;

		rotDest_._y = atan2f( -camera_vector_._x , -camera_vector_._z );

		bMove = true ;

	}

	//--  �ړ��@��  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_A ) == true )
	{
		//move_._x -= sinf( camera_vector_._y + D3DX_PI * 0.5f ) * speed_._x ;
		//move_._z -= cosf( camera_vector_._y + D3DX_PI * 0.5f ) * speed_._z ;
		D3DXVECTOR3 vec ;
		D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&camera_vector_ );

		move_._x -= vec.x * speed_._x ;
		move_._z -= vec.z * speed_._z ;

		//rotDest_._y = -D3DX_PI * 0.5f ;
		rotDest_._y = atan2f( -vec.x , -vec.z );

		bMove = true ;
	}

	//--  �ړ��@�E  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_D ) == true )
	{
		//move_._x += sinf( camera_vector_._y + D3DX_PI * 0.5f ) * speed_._x ;
		//move_._z += cosf( camera_vector_._y + D3DX_PI * 0.5f ) * speed_._z ;

		D3DXVECTOR3 vec ;
		D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&camera_vector_ );

		move_._x += vec.x * speed_._x ;
		move_._z += vec.z * speed_._z ;

		rotDest_._y = atan2f( vec.x , vec.z );

		//rotDest_._y = D3DX_PI * 0.5f ;

		bMove = true ;
	}

	//--  �G�C��  --//
	if( state_ == STATE::AIM )
	{
		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );
		rotDest_._y += 0.4f ;

		//--  �A�N�V����  --//
		if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_SPACE ) )
		{
			if( pKim_->GetAnime() != Kim::ANIME::ACTION )
			{
				action_ = true ;
				pKim_->SetAnime( Kim::ANIME::ACTION );
				pKim_->SetOldAnime( Kim::ANIME::WAIT );
			}
		}

		move_ *= 0 ;

		bMove = false ;
	}
	
	//--  ������o��  --//
	if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_E ) == true )
	{
		int wepon = ( int )pKim_->GetWepon();
		wepon = ( wepon + 1 ) % 3 ;

		pKim_->SetWepon( ( Kim::WEAPON )wepon );
		pKim_->SetAnime( Kim::ANIME::TAKE_OUT );
		pKim_->SetOldAnime( Kim::ANIME::WAIT );
	}

	//--  �������Ȃ�  --//
	if( bMove == true )
	{
		//--  �A�j���[�V����  --//
		pKim_->SetAnime( Kim::ANIME::WALK );
	}

	//--  �A�j���[�V�����I�������  --//
	if( pKim_->GetNewAnimarionEnd() == true )
	{
		action_animation_end_ = false ;
	}

	//--  �ړ�  --//
	position_._x += move_._x ;
	position_._y += move_._y ;
	position_._z += move_._z ;

	move_._x *= 0.855f ;
	move_._z *= 0.855f ;

	rotDest_._y = utility::math::Wrap( rotDest_._y , ( f32 )-utility::math::PI , ( f32 )utility::math::PI );

	//--  �����̊����X�V  --//
	auto diff = rotDest_._y - rotation_._y ;
	diff = utility::math::Wrap( diff , ( f32 )-utility::math::PI , ( f32 )utility::math::PI );

	rotation_._y += diff * 0.09f ;
}


//-------------------------------------------------------------------
// �֐��� : kim�X�V
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------
void Player::UpdateKimMatrix( void )
{
	//--  FBX�X�V  --//
	D3DXMATRIX  mtxScl , mtxRot , mtxTranslate ; //���[�N�p
	
	D3DXMatrixIdentity( ( D3DXMATRIX* )&matrix_ );	//���[���h�}�g���b�N�X������

	//--  �X�P�[���̔��f  --//
	D3DXMatrixScaling( &mtxScl , scale_._x , scale_._y , scale_._z );
	D3DXMatrixMultiply( ( D3DXMATRIX* )&matrix_ , ( D3DXMATRIX* )&matrix_ , &mtxScl );	//�s��̊|���Z

	//--  ��]�̔��f  --//
	D3DXMatrixRotationYawPitchRoll( &mtxRot , rotation_._y , rotation_._x , rotation_._z );
	D3DXMatrixMultiply( ( D3DXMATRIX* )&matrix_ , ( D3DXMATRIX* )&matrix_ , &mtxRot );	//�s��̊|���Z

	//--  �ʒu�̔��f  --//
	D3DXMatrixTranslation( &mtxTranslate , position_._x , position_._y , position_._z );
	D3DXMatrixMultiply( ( D3DXMATRIX* )&matrix_ , ( D3DXMATRIX* )&matrix_ , &mtxTranslate );	//�s��̊|���Z

	pKim_->SetWorld( ( D3DXMATRIX& )matrix_ );
	pKim_->Update();
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
