//*****************************************************************************
//
// follower observer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "math/math.h"
#include "../system/win_system.h"
#include "../system/input_manager.h"
#include "../system/input_mouse.h"

#include "follower_observer.h"

//=============================================================================
// constructor
//=============================================================================
FollowerObserver::FollowerObserver(const f32& in_radian,const f32& in_width,const f32& in_height)
	:Observer3D(in_radian,in_width,in_height)
	,target_length_(2.0f)
{
	rotation_ = float3();
	eye_ = float3();
	state_ = STATE::NONE ;
}

//=============================================================================
// update
//=============================================================================
void FollowerObserver::Update(void)
{
	//look_at_ = target_position_ ;
	//look_at_._z += target_length_ ;

	//auto look_at = float3(look_at_._x,0.0f,look_at_._z);
	//auto eye = float3(eye_._x,0.0f,eye_._z);
	//auto vector = look_at_ - eye ;
	//vector = utility::math::Normalize(vector);

	////auto length = utility::math::Length(vector);

	//eye_._x = look_at_._x ;
	//eye_._y = height_;
	//eye_._z = target_position_._z - length_ ;


#ifdef _DEBUG
	MouseMove_();
#endif // _DEBUG

	if( state_ == STATE::FOLLWER )
	{
		//--  ��{���W�ړ�  --//
		eye_._x = target_position_._x - sinf( rotation_._y ) * length_ ;
		eye_._y = height_ ;
		eye_._z = target_position_._z - cosf( rotation_._y ) * length_ ;

		//auto look_at = float3(look_at_._x,0.0f,look_at_._z);
		auto eye = float3( eye_._x , 0.0f , eye_._z );
		auto vector = target_position_ - eye ;
		vector = utility::math::Normalize( vector );

		look_at_ = float3( vector._x * target_length_ , 0 , vector._z * target_length_ );
		look_at_ = look_at_ + target_position_ ;
	}

	if( state_ == STATE::AIM )
	{
		float length = length_ * 0.7f ;
		float rot = -0.2f ;
		auto eye = float3( eye_._x , 0.0f , eye_._z );
		auto vector = look_at_ - eye ;
		vector = utility::math::Normalize( vector );

		//D3DXVECTOR3 vec ;
		//D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&vector );
		auto vec = feild_icon_ - target_position_ ;
		D3DXVec3Normalize( ( D3DXVECTOR3* )&vec , ( D3DXVECTOR3* )&vec );

		rotation_._y = atan2f( vec._x , vec._z );

		//--  ��{���W�ړ�  --//
		eye_._x = target_position_._x - sinf( rotation_._y + rot ) * length ;
		eye_._y = height_ ;
		eye_._z = target_position_._z - cosf( rotation_._y + rot ) * length ;

		//auto look_at = float3(look_at_._x,0.0f,look_at_._z);

		look_at_ = float3( vector._x * target_length_ , 0 , vector._z * target_length_ );
		look_at_ = look_at_ + target_position_ ;
	}
	else
	{
		////--  ��{���W�ړ�  --//
		//eye_._x = target_position_._x - sinf( rotation_._y ) * length_ ;
		//eye_._y = height_ ;
		//eye_._z = target_position_._z - cosf( rotation_._y ) * length_ ;
	}

	view_matrix_ = utility::math::LookAtLH(eye_,look_at_,up_);
}

FollowerObserver::STATE FollowerObserver::GetState(void) const
{
	return state_;
}

//=============================================================================
// 
//=============================================================================
void FollowerObserver::MouseMove_( void )
{
	//--  ���R�ړ�  --//
	//if( cameraState_ == CAMERA_STATE_FREE )
	{
		const float MOVE_EPSIRON = 0.05f ;		// �덷
		const float MOVE_DEST_X = 0.015f ;		// ����
		const float MOVE_DEST_Y = 0.005f ;		// ����

		//--  �擾  --//
		auto mouseMove = GET_INPUT_MOUSE()->GetDiff();

		//--  �N���b�N  --//
		if( GET_INPUT_MOUSE()->GetPress( InputMouse::MOUSE_KEY::LEFT ) == true )
		{
			//--  �덷����  --//
			if( mouseMove._x > MOVE_EPSIRON ||  mouseMove._x < -MOVE_EPSIRON )
			{
				rotation_._y += mouseMove._x * MOVE_DEST_X ;
			}

			//--  �덷����  --//
			if( mouseMove._y > MOVE_EPSIRON ||  mouseMove._y < -MOVE_EPSIRON )
			{
				rotation_._z += mouseMove._y * MOVE_DEST_Y ;
			}
		}

		if( mouseMove._z != 0 )
		{
			length_ -= length_ / ( mouseMove._z * 0.025f ) ;	// �Y�[��
		}
	}
}

//=============================================================================
// 
//=============================================================================
void FollowerObserver::SetTargetPosition(const float3 & in_position)
{
	target_position_ = in_position;
}

//=============================================================================
// set vector
//=============================================================================
void FollowerObserver::SetTargetVector(const float3 & in_vector)
{
	target_vector_ = utility::math::Normalize(float3(in_vector._x,0.0f,in_vector._z));;
}

//=============================================================================
// set target length
//=============================================================================
void FollowerObserver::SetTargetLength(const f32 & in_length)
{
	target_length_ = in_length;
}

//=============================================================================
// set length
//=============================================================================
void FollowerObserver::SetLength(const f32 & in_length)
{
	length_ = in_length;
}

//=============================================================================
// set height
//=============================================================================
void FollowerObserver::SetHeight(const f32& in_height)
{
	height_ = in_height;
}

//---------------------------------- EOF --------------------------------------

//
//typedef struct
//{
//	float a ;
//	float b ;
//	float c ;
//	float d ;
//}PLANE ;		// ����
//
//typedef struct
//{
//	PLANE LeftPlane ;
//	PLANE RightPlane ;
//	PLANE TopPlane ;
//	PLANE BottomPlane ;
//	float NearClip ;
//	float FarClip ;
//}FRUSTUM ;		// ������


	//--  �ݒ�  --//
	//SetupFOVClipPlanes( &frustum_ );

////-------------------------------------------------------------------
//// �֐��� : �R�_���畽�ʃp�����[�^�쐬
//// 
//// ����   : const D3DXVECTOR3& P0 : ���W
//// ����   : const D3DXVECTOR3& P1 : ���W
//// ����   : const D3DXVECTOR3& P2 : ���W
//// ����   : PLANE *pPlane : ����
//// �Ԃ�l : �Ȃ�
////-------------------------------------------------------------------
//void CCAMERA::PlaneFromPoints( const D3DXVECTOR3 &P0 , const D3DXVECTOR3 &P1 , const D3DXVECTOR3 &P2 , PLANE *pPlane )
//{
//	D3DXVECTOR3 V0 , V1 , V2 ;
//
//	V0 = P1 - P0 ;
//	V1 = P2 - P0 ;
//
//	D3DXVec3Cross( &V2, &V0, &V1 );
//	D3DXVec3Normalize( &V2 , &V2 );
//
//	pPlane->a = V2.x ;
//	pPlane->b = V2.y ;
//	pPlane->c = V2.z ;
//	pPlane->d = -( V2.x * P0.x + V2.y * P0.y + V2.z * P0.z );
//}
//
////-------------------------------------------------------------------
//// �֐��� : �����̐ݒ�
//// 
//// ����   : FRUSTUM *frustum : ������
//// �Ԃ�l : �Ȃ�
////-------------------------------------------------------------------
//void CCAMERA::SetupFOVClipPlanes( FRUSTUM *frustum )
//{
//	float angle = PI / 4 ;											// ����p
//	float aspect = ( float )WINDOW_WIDTH / ( float )WINDOW_HEIGHT ;	// �A�X�y�N�g��
//	float nearClip = NEAR_NUM ;										// near�l
//	float farClip = FAR_NUM ;										// far�l
//										
//	D3DXVECTOR3	P0 , P1 , P2 ;
//
//	float fTan = tan( angle * 0.5f );
//
//	//--  ������  --//
//	P0.x = 0.0f ;
//	P0.y = 0.0f ;
//	P0.z = 0.0f ;
//	P1.x = -farClip * ( fTan / aspect );
//	P1.y = -farClip * ( fTan );
//	P1.z = farClip ;
//	P2.x = P1.x ;
//	P2.y = -P1.y ;
//	P2.z = P1.z ;
//	PlaneFromPoints( P0 , P1 , P2 , &frustum->LeftPlane );
//
//	//--  �E����  --//
//	P0.x = 0.0f ;
//	P0.y = 0.0f ;
//	P0.z = 0.0f ;
//	P1.x = farClip * ( fTan / aspect);
//	P1.y = farClip * ( fTan );
//	P1.z = farClip ;
//	P2.x = P1.x ;
//	P2.y = -P1.y ;
//	P2.z = P1.z ;
//	PlaneFromPoints( P0, P1 , P2 , &frustum->RightPlane );
//
//	//--  �㕽��  --//
//	P0.x = 0.0f ;
//	P0.y = 0.0f ;
//	P0.z = 0.0f ;
//	P1.x = -farClip * ( fTan / aspect);
//	P1.y = farClip * ( fTan );
//	P1.z = farClip ;
//	P2.x = -P1.x ;
//	P2.y = P1.y ;
//	P2.z = P1.z ;
//	PlaneFromPoints( P0, P1 , P2 , &frustum->TopPlane );
//
//	//--  ������  --//
//	P0.x = 0.0f ;
//	P0.y = 0.0f ;
//	P0.z = 0.0f ;
//	P1.x = farClip * ( fTan / aspect);
//	P1.y = -farClip * ( fTan );
//	P1.z = farClip ;
//	P2.x = -P1.x ;
//	P2.y = P1.y ;
//	P2.z = P1.z ;
//	PlaneFromPoints( P0, P1 , P2 , &frustum->BottomPlane );
//
//	frustum->NearClip = nearClip ;
//	frustum->FarClip = farClip ;
//}
//
////-------------------------------------------------------------------
//// �֐��� : �����䔻�菈��
//// 
//// ����   : D3DXVECTOR3& objectPos : �I�u�W�F�N�g�ʒu
//// ����   : float radius : ���a
//// ����   : FRUSTUM& frustum : ���a
//// ����   : D3DXMATRIX& view : ���a
//// �Ԃ�l : �Ȃ�
////-------------------------------------------------------------------
//bool CCAMERA::MeshFOVCheck( D3DXVECTOR3& objectPos , float radius , FRUSTUM& frustum , D3DXMATRIX& view )
//{
//	//--  ���a�Ȃ�  --//
//	if( radius == 0 )
//	{
//		return true ;		// ��Ε`��
//	}
//
//	float Dist ;
//	D3DXVECTOR3 viewPos ;
//
//	//--  �r���[��Ԃy�ϊ�  --//	
//	viewPos.z =	view._13 * objectPos.x + view._23 * objectPos.y + view._33 * objectPos.z + view._43 ;
//
//	//--  �j�A�N���b�v���ʂ���O��  --//
//	if( ( viewPos.z + radius ) < frustum.NearClip )
//	{
//		return false ;
//	}
//
//	//--  �t�@�[�N���b�v���ʂ�艜��  --//
//	if( ( viewPos.z - radius ) > frustum.FarClip )
//	{
//		return false;
//	}
//
//	//--  �r���[��Ԃw�ϊ�  --//
//	viewPos.x =	view._11 * objectPos.x + view._21 * objectPos.y + view._31 * objectPos.z + view._41 ;
//
//	//--  �����ʂ�荶����  --//
//	Dist = ( viewPos.x * frustum.LeftPlane.a ) + ( viewPos.z * frustum.LeftPlane.c );
//
//	if( Dist > radius )
//	{
//		return false;
//	}
//
//	//--  �E���ʂ��E����  --//
//	Dist = ( viewPos.x * frustum.RightPlane.a ) + ( viewPos.z * frustum.RightPlane.c );
//
//	if( Dist > radius )
//	{
//		return false;
//	}
//
//	//--  �r���[��Ԃx�ϊ�  --//
//	viewPos.y =	view._12 * objectPos.x + view._22 * objectPos.y + view._32 * objectPos.z + view._42 ;
//
//	//--  �㑤�ʂ��㑤��  --//
//	Dist = ( viewPos.y * frustum.TopPlane.b ) + ( viewPos.z * frustum.TopPlane.c );
//
//	if( Dist > radius )
//	{
//		return false ;
//	}
//
//	//--  �����ʂ�艺����  --//
//	Dist = ( viewPos.y * frustum.BottomPlane.b ) + ( viewPos.z * frustum.BottomPlane.c );
//
//	if( Dist > radius )
//	{
//		return false ;
//	}
//
//	return true ;
//}