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
#include "../system/input_mouse.h"

#include "follower_observer.h"

//=============================================================================
// constructor
//=============================================================================
FollowerObserver::FollowerObserver(const f32& in_radian,const f32& in_width,const f32& in_height)
	:Observer3D(in_radian,in_width,in_height)
	,target_length_(4.0f)
{
	rotation_ = float3();
	eye_ = float3();
	state_ = STATE::STATE_NONE ;
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

	if( state_ == STATE::STATE_FOLLWER )
	{
		//--  基本座標移動  --//
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
	
	if( GET_INPUT_MOUSE()->GetTrigger( InputMouse::MOUSE_KEY::RIGHT ) == true )
	{
		if( state_ != STATE::STATE_AIM )
		{
			state_ = STATE::STATE_AIM ;
		}
		else
		{
			state_ = STATE::STATE_FOLLWER ;
			length_ = 4.0f ;

		}
	}

	if( state_ == STATE::STATE_AIM )
	{
		const float length = 2.0f ;
		float rot = 0.2f ;
		auto eye = float3( eye_._x , 0.0f , eye_._z );
		auto vector = look_at_ - eye ;
		vector = utility::math::Normalize( vector );

		D3DXVECTOR3 vec ;
		D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&vector );

		//--  基本座標移動  --//
		eye_._x = target_position_._x - sinf( rotation_._y + rot ) * length ;
		eye_._y = height_ ;
		eye_._z = target_position_._z - cosf( rotation_._y + rot ) * length ;

		//auto look_at = float3(look_at_._x,0.0f,look_at_._z);


		look_at_ = float3( vector._x * target_length_ , 0 , vector._z * target_length_ );
		look_at_ = look_at_ + target_position_ ;
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
	//--  自由移動  --//
	//if( cameraState_ == CAMERA_STATE_FREE )
	{
		const float MOVE_EPSIRON = 0.05f ;		// 誤差
		const float MOVE_DEST_X = 0.015f ;		// 減数
		const float MOVE_DEST_Y = 0.005f ;		// 減数

		//--  取得  --//
		auto mouseMove = GET_INPUT_MOUSE()->GetDiff();

		//--  クリック  --//
		if( GET_INPUT_MOUSE()->GetPress( InputMouse::MOUSE_KEY::LEFT ) == true )
		{
			//--  誤差判定  --//
			if( mouseMove._x > MOVE_EPSIRON ||  mouseMove._x < -MOVE_EPSIRON )
			{
				rotation_._y += mouseMove._x * MOVE_DEST_X ;
			}

			//--  誤差判定  --//
			if( mouseMove._y > MOVE_EPSIRON ||  mouseMove._y < -MOVE_EPSIRON )
			{
				rotation_._z += mouseMove._y * MOVE_DEST_Y ;
			}
		}

		if( mouseMove._z != 0 )
		{
			length_ -= length_ / ( mouseMove._z * 0.025f ) ;	// ズーム
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
