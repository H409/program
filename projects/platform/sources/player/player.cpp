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
#include "../system/input_keyboard.h"
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

	camera_vector_ = float3();
	move_ = float3();
	speed_ = float3( 0.025f , 0.025f , 0.025f );

	position_ = float3( 0 , 0 , 0 );

	ID_ = 0 ;		// 1P
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

	rotDest_ = float3();
	scale_ = float3( 0.02f , 0.02f , 0.02f );
}

//-------------------------------------------------------------------
// �֐��� : �X�V
//
// ����   : �Ȃ�
// �Ԃ�l : �Ȃ�
//-------------------------------------------------------------------
void Player::Update( void )
{
	//--  ����  --//
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

	//--  �ړ��@�O  --//	
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_W ) == true )
	{
		//move_._x += sinf( camera_vector_._y ) * speed_._x ;
		//move_._z += cosf( camera_vector_._y ) * speed_._z ;

		move_._x += camera_vector_._x * speed_._x ; 
		move_._z += camera_vector_._z * speed_._z ;

		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );
	}


	//--  �ړ��@��  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_S ) == true )
	{
		//move_._x -= sinf( camera_vector_._y ) * speed_._x ;
		//move_._z -= cosf( camera_vector_._y ) * speed_._z ;

		move_._x -= camera_vector_._x * speed_._x ; 
		move_._z -= camera_vector_._z * speed_._z ;

		rotDest_._y = atan2f( -camera_vector_._x , -camera_vector_._z );
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
