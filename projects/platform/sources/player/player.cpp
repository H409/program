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
#include "develop_tool/develop_tool.h"

#include "math/math.h"
#include "player.h"

//------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------
#ifndef _RELEASE
#define _KEYBOAD_DEBUG
#endif // _RELESE

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
Player::Player( LPDIRECT3DDEVICE9 pDevice , int ID ) : Object()
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
	weapon_ = WEAPON::GUN ;
	
	hit_ = false ;
	aim_ = false ;

	ID_ = ID ;

	pKim_ = new Kim( pDevice_ );

	switch( ID_ )
	{
		case 0 :
			pKim_->Load( "resources/model/ZZI_1_MO.kim" );
			break ;

		case 1 :
			pKim_->Load( "resources/model/ZZI_2_MO.kim" );
			break ;

		case 2 :
			pKim_->Load( "resources/model/ZZI_3_MO.kim" );
			break ;

		case 3 :
			pKim_->Load( "resources/model/ZZI_4_MO.kim" );

			break ;

		default:
			break;
	}
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
	rotation_ = float3();

	old_anime_ = ANIME::WAIT ;
	anime_ = ANIME::WAIT ;
	weapon_ = WEAPON::GUN ;

	hit_ = false ;
	aim_ = false ;
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
	float rot_diff = 0 ;	// aim�p

	action_ = false ;
	take_out_ = false ;
	//aim_ = false ;

	if( hit_ == true )
	{
		anime_ = ANIME::DAMAGE ;

		if( pKim_->GetSingleAnimationEnd() == true )
		{
			hit_ = false ;
		}
		return ;
	}

#ifndef _RELEASE
	ControlKeyBorad();

#else
	ControlJoypad();
	ControlKeyBorad();

#endif // _DEBUG

	D3DXVECTOR3 vec ;
	D3DXVec3Normalize( ( D3DXVECTOR3* )&camera_vector_ , ( D3DXVECTOR3* )&camera_vector_ );
	D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&camera_vector_ );

	move_._x += camera_vector_._x * pad_move_._y * speed_._x ; 
	move_._z += camera_vector_._z * pad_move_._y * speed_._z ;

	move_._x += vec.x * pad_move_._x * speed_._x ;
	move_._z += vec.z * pad_move_._x * speed_._z ;

	//--  �G�C��  --//
	if( state_ == STATE::AIM )
	{
		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );
		rotDest_._y += 0.4f ;

		move_ *= 0 ;
		rot_diff = 0.4f ;

		if( action_ == true )
		{
			if( weapon_ != WEAPON::GUN )
			{
				anime_ = ANIME::ACTION ;
				old_anime_ = ANIME::WAIT ;

				pKim_->SetOldAnime( player_anime_data_[ OLD_ANIMETION ][ 0 ] ,
									player_anime_data_[ OLD_ANIMETION ][ 1 ] ,
									player_anime_data_[ OLD_ANIMETION ][ 2 ] );
			}
		}
	}
	else
	{
		//--  ��~��  --//
		const float stop = 0.02f ;

		//--  ������o�����Ă��Ȃ�  --//
		if( anime_ != ANIME::TAKE_OUT )
		{
			if( move_._x < stop && move_._x > -stop &&
				move_._z < stop && move_._z > -stop )
			{
				anime_ = ANIME::WAIT ;
			}
			else
			{
				anime_ = ANIME::WALK ;
				rotDest_._y = atan2f( move_._x , move_._z );
			}
		}
		else
		{
			move_ *= 0 ;
		}
	}
	
	//--  �ҋ@��  --//
	if( anime_ == ANIME::WAIT )
	{
		//--  ������o��  --//
		if( take_out_ == true )
		{
			weapon_ = ( WEAPON )( ( ( int )weapon_ + 1 ) % 3 );

			anime_ = ANIME::TAKE_OUT ;
			old_anime_ = ANIME::WAIT ;

			pKim_->SetOldAnime( player_anime_data_[ OLD_ANIMETION ][ 0 ] ,
								player_anime_data_[ OLD_ANIMETION ][ 1 ] ,
								player_anime_data_[ OLD_ANIMETION ][ 2 ] );
		}
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

	DEVELOP_DISPLAY( "camera_vec : %f , %f , %f\n" , camera_vector_._x , camera_vector_._y , camera_vector_._z );
	DEVELOP_DISPLAY( "pos : %f , %f , %f\n" , position_._x , position_._y , position_._z );
	//DEVELOP_DISPLAY( "move : %f , %f , %f\n" , move_._x , move_._y , move_._z );
	//DEVELOP_DISPLAY( "action : %d\n" , action_ );
	DEVELOP_DISPLAY( "anime : %d\n" , anime_ );
}
//-------------------------------------------------------------------
// �֐��� : �L�[�{�[�h�X�V
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------	
void Player::ControlKeyBorad( void )
{
	pad_move_ = float3( 0 , 0 , 0 );

	//--  �ړ��@�O  --//	
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_W ) == true )
	{
		pad_move_._y = 1 ;
	}

	//--  �ړ��@��  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_S ) == true )
	{
		pad_move_._y = -1 ;
	}

	//--  �ړ��@��  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_A ) == true )
	{
		pad_move_._x = -1 ;
	}

	//--  �ړ��@�E  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_D ) == true )
	{
		pad_move_._x = 1 ;
	}

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
	//if( GET_INPUT_MOUSE()->GetRelease( InputMouse::MOUSE_KEY::RIGHT ) == true )
	//{
	//	aim_ = false ;
	//}

	//--  �G�C��  --//
	if( state_ == STATE::AIM )
	{
		//--  �A�N�V����  --//
		if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_SPACE ) )
		{
			action_ = true ;
		}
	}

	//--  ������o��  --//
	if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_E ) == true )
	{
		take_out_ = true ;
	}

	if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_7 ) == true )
	{
		SetHit( true );
	}
}

//-------------------------------------------------------------------
// �֐��� : �W���C�p�b�h�X�V
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------	
void Player::ControlJoypad( void )
{
	//--  �ړ�  --//	
	pad_move_ = GET_INPUT_XPAD( ID_ )->GetLStick();

	if( GET_INPUT_XPAD( ID_ )->GetTrigger( XIPad::KEY::L2 ) == true )
	{
		aim_ = true ;
	}
	else
	{
		if( GET_INPUT_XPAD( ID_ )->GetRelease( XIPad::KEY::L2 ) == true )
		{
			aim_ = false ;
		}
	}

	//--  �G�C��  --//
	if( state_ == STATE::AIM )
	{
		//--  �A�N�V����  --//
		if( GET_INPUT_XPAD( ID_ )->GetTrigger( XIPad::KEY::R2 ) == true )
		{
			action_ = true ;
		}
	}

	//--  ������o��  --//
	if( GET_INPUT_XPAD( ID_ )->GetTrigger( XIPad::KEY::Y ) == true )
	{
		take_out_ = true ;
	}
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

//-------------------------------------------------------------------
// �֐��� : set
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------
void Player::SetHit( bool b )
{
	old_anime_ = ANIME::WAIT ;

	pKim_->SetOldAnime( player_anime_data_[ OLD_ANIMETION ][ 0 ] ,
						player_anime_data_[ OLD_ANIMETION ][ 1 ] ,
						player_anime_data_[ OLD_ANIMETION ][ 2 ] );

	hit_ = b ;
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
