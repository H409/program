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
#include "../system/input_joypad.h"
#include "../system/xi_pad.h"

#include "../system/input_mouse.h"

#include "math/math.h"
#include "player.h"

//------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------
#ifdef _DEBUG
#define _KEYBOAD_DEBUG
#endif // _DEBUG

//------------------------------------------------------------------------
// �\����
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �v���g�^�C�v�錾
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//------------------------------------------------------------------------
int Player::player_anime_data_[][ 3 ] = { //--  �����`���[  --//
										{ 31  , 60  , 0 } ,		// ���o��
										{ 61  , 150 , 1 } ,		// �ҋ@
										{ 151 , 180 , 1 } ,		// ����
										{ 181 , 240 , 0 } ,		// �s��
										{ 241 , 300 , 0 } ,		// �_���[�W
										
										//--  �V���b�g�K��  --//
										{ 331 , 360 , 0 } ,		// ���o��
										{ 361 , 450 , 1 } ,		// �ҋ@
										{ 451 , 480 , 1 } ,		// ����
										{ 481 , 510 , 0 } ,		// �s��
										{ 511 , 570 , 0 } ,		// �_���[�W
										
										//--  �N��  --//
										{ 601 , 630 , 0 } ,		// ���o��
										{ 631 , 720 , 1 } ,		// �ҋ@
										{ 721 , 750 , 1 } ,		// ����
										{ 751 , 810 , 0 } ,		// �s��
										{ 811 , 870 , 0 } };	// �_���[�W

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
	pKim_ = nullptr ;
	camera_vector_ = float3();
	move_ = float3();
	speed_ = float3( 0.01f , 0.01f , 0.01f );

	position_ = float3( 0 , 0 , 0 );

	ID_ = 0 ;		// 1P

	state_ = STATE::NONE ;

	old_anime_ = ANIME::WAIT ;
	anime_ = ANIME::WAIT ;
	wepon_ = WEAPON::GUN ;
	//player_anime_data_[ NOW_ANIMETION ][ 0 ];

	pKim_ = new Kim( pDevice_ );
	pKim_->Load( "resources/model/ZZI_1_MO.kim" );
}

//-------------------------------------------------------------------
// �֐��� : �f�X�g���N�^
//
// ����   : �Ȃ�
//-------------------------------------------------------------------
Player::~Player( void )
{
	SafeRelease( pKim_ );
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
	move_ = float3();
	position_ = pos ;
	state_ = STATE::WAIT ;

	rotDest_ = float3();

	old_anime_ = ANIME::WAIT ;
	anime_ = ANIME::WAIT ;
	wepon_ = WEAPON::GUN ;
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

	auto a = NOW_ANIMETION ;
	pKim_->SetAnime( player_anime_data_[ NOW_ANIMETION ][ 0 ] ,
					 player_anime_data_[ NOW_ANIMETION ][ 1 ] ,
					 player_anime_data_[ NOW_ANIMETION ][ 2 ] );

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
#ifdef _KEYBOAD_DEBUG
	ControlKeyBorad();
	ControlJoypad();

#else
	ControlJoypad();

#endif // _DEBUG
}
//-------------------------------------------------------------------
// �֐��� : �L�[�{�[�h�X�V
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------	
void Player::ControlKeyBorad( void )
{
	bool bMove = false ;	// �ړ�
	action_ = false ;
	float rot_diff = 0 ;	//

	D3DXVec3Normalize( ( D3DXVECTOR3* )&camera_vector_ , ( D3DXVECTOR3* )&camera_vector_ );

	if( GET_INPUT_MOUSE()->GetTrigger( InputMouse::MOUSE_KEY::RIGHT ) == true )
	{
		if( state_ != STATE::AIM )
		{
			anime_ = ANIME::WAIT ;
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
		move_._x += camera_vector_._x * speed_._x ; 
		move_._z += camera_vector_._z * speed_._z ;

		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );

		bMove = true ;
	}


	//--  �ړ��@��  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_S ) == true )
	{
		move_._x -= camera_vector_._x * speed_._x ; 
		move_._z -= camera_vector_._z * speed_._z ;

		rotDest_._y = atan2f( -camera_vector_._x , -camera_vector_._z );

		bMove = true ;

	}

	//--  �ړ��@��  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_A ) == true )
	{
		D3DXVECTOR3 vec ;
		D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&camera_vector_ );

		move_._x -= vec.x * speed_._x ;
		move_._z -= vec.z * speed_._z ;

		rotDest_._y = atan2f( -vec.x , -vec.z );

		bMove = true ;
	}

	//--  �ړ��@�E  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_D ) == true )
	{
		D3DXVECTOR3 vec ;
		D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&camera_vector_ );

		move_._x += vec.x * speed_._x ;
		move_._z += vec.z * speed_._z ;

		rotDest_._y = atan2f( vec.x , vec.z );

		bMove = true ;
	}

	//--  �G�C��  --//
	if( state_ == STATE::AIM )
	{
		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );
		rotDest_._y += 0.4f ;

		//--  �A�j���[�V�������ҋ@�Ȃ�  --//
		if( anime_ == ANIME::WAIT )
		{
			//--  �A�N�V����  --//
			if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_SPACE ) )
			{
				if( action_ == false )
				{
					action_ = true ;
					anime_ = ANIME::ACTION ;
					old_anime_ = ANIME::WAIT ;

					auto a = OLD_ANIMETION ;
					pKim_->SetOldAnime( player_anime_data_[ OLD_ANIMETION ][ 0 ] ,
										player_anime_data_[ OLD_ANIMETION ][ 1 ] ,
										player_anime_data_[ OLD_ANIMETION ][ 2 ] );
				}
			}
		}

		move_ *= 0 ;
		rot_diff = 0.11f ;
		bMove = false ;
	}
	else
	{
		//--  ��~��  --//
		const float stop = 0.02f ;
		if( anime_ != ANIME::TAKE_OUT )
		{
			if( move_._x < stop && move_._x > -stop &&
				move_._z < stop && move_._z > -stop )
			{
				anime_ = ANIME::WAIT ;
			}
		}
	}
	
	//--  �ҋ@��  --//
	if( anime_ == ANIME::WAIT )
	{
		//--  ������o��  --//
		if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_E ) == true )
		{
			//--  ���o���A�j���[�V���������Ă��Ȃ��Ȃ�  --//
			if( pKim_->GetAnimarionPlay( ( int )ANIME::TAKE_OUT ) == false )
			{
				wepon_ = ( WEAPON )( ( ( int )wepon_ + 1 ) % 3 );

				anime_ = ANIME::TAKE_OUT ;
				old_anime_ = ANIME::WAIT ;
			}
		}
	}

	//--  �������Ȃ�  --//
	if( bMove == true )
	{
		//--  �A�j���[�V����  --//
		anime_ = ANIME::WALK ;
	}

	if( pKim_->GetSingleAnimationEnd() == true )
	{
		anime_ = old_anime_ ;
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

	rotation_._y += diff * ( 0.09f + rot_diff );
}

//-------------------------------------------------------------------
// �֐��� : �W���C�p�b�h�X�V
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------	
void Player::ControlJoypad( void )
{
	bool bMove = false ;	// �ړ�
	action_ = false ;
	float rot_diff = 0 ;	//

	//D3DXVec3Normalize( ( D3DXVECTOR3* )&camera_vector_ , ( D3DXVECTOR3* )&camera_vector_ );

	if( GET_INPUT_XPAD( ID_ )->GetPress( XIPad::KEY::L2 ) == true )
	{
		state_ = STATE::AIM ;
	}
	else
	{
		if( GET_INPUT_XPAD( ID_ )->GetRelease( XIPad::KEY::L2 ) == true )
		{
			anime_ = ANIME::WAIT ;
			state_ = STATE::WAIT ;
		}
	}

	//--  �ړ�  --//	
	auto x_pad_move = GET_INPUT_XPAD( ID_ )->GetLStick();
	
	D3DXVECTOR3 vec ;
	D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&camera_vector_ );
	auto vec2 = D3DXVECTOR3( x_pad_move._x , 0 , x_pad_move._y );
	vec.x = vec.x * vec2.x ;
	vec.y = vec.y * vec2.y ;
	vec.z = vec.z * vec2.z ;

	D3DXVec3Normalize( ( D3DXVECTOR3* )&vec , ( D3DXVECTOR3* )&vec );

	move_._x += vec.x * speed_._x ; 
	move_._z += vec.z * speed_._z ;

	rotDest_._y = atan2f( vec.x , vec.z );


	//--  �G�C��  --//
	if( state_ == STATE::AIM )
	{
		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );
		rotDest_._y += 0.4f ;

		//--  �A�j���[�V�������ҋ@�Ȃ�  --//
		if( anime_ == ANIME::WAIT )
		{
			//--  �A�N�V����  --//
			if( GET_INPUT_XPAD( ID_ )->GetPress( XIPad::KEY::R2 ) == true )
			{
				if( action_ == false )
				{
					action_ = true ;
					anime_ = ANIME::ACTION ;
					old_anime_ = ANIME::WAIT ;
				}
			}
		}

		move_ *= 0 ;
		rot_diff = 0.11f ;
		bMove = false ;
	}
	else
	{
		//--  ��~��  --//
		const float stop = 0.02f ;
		if( anime_ != ANIME::TAKE_OUT )
		{
			if( move_._x < stop && move_._x > -stop &&
				move_._z < stop && move_._z > -stop )
			{
				anime_ = ANIME::WAIT;
			}
		}
	}
	
	//--  �ҋ@��  --//
	if( anime_ == ANIME::WAIT )
	{
		//--  ������o��  --//
		if( GET_INPUT_XPAD( ID_ )->GetTrigger( XIPad::KEY::Y ) == true == true )
		{
			//--  ���o���A�j���[�V���������Ă��Ȃ��Ȃ�  --//
			if( pKim_->GetAnimarionPlay( ( int )ANIME::TAKE_OUT ) == false )
			{
				wepon_ = ( WEAPON )( ( ( int )wepon_ + 1 ) % 3 );

				anime_ = ANIME::TAKE_OUT ;
				old_anime_ = ANIME::WAIT ;
			}
		}
	}

	//--  �������Ȃ�  --//
	if( bMove == true )
	{
		//--  �A�j���[�V����  --//
		anime_ = ANIME::WALK ;
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

	rotation_._y += diff * ( 0.09f + rot_diff );
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
