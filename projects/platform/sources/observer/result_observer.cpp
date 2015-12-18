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
#include "../system/xi_pad.h"

#include "result_observer.h"

//=============================================================================
// constructor
//=============================================================================
ResultObserver::ResultObserver(const f32& in_radian, const f32& in_width, const f32& in_height)
	:Observer3D(in_radian, in_width, in_height)
	, target_length_(2.0f)
{
	rotation_ = float3();
	eye_ = float3();
	state_ = STATE::NONE;
	ID_ = 0;
	length_ = 7.0f;
	height_ = 7.0f;
}

//=============================================================================
// update
//=============================================================================
void ResultObserver::Update(void)
{
	rotation_._y += 0.001f;
	//自動で周回をする
	eye_._x = look_at_._x - sinf(rotation_._y)*length_;
	eye_._y = height_;
	eye_._z = look_at_._z - cosf(rotation_._y)*length_;
	look_at_ = float3(0.0f, 0.0f, 0.0f);
	view_matrix_ = utility::math::LookAtLH(eye_, look_at_, up_);
}

ResultObserver::STATE ResultObserver::GetState(void) const
{
	return state_;
}

//=============================================================================
// 
//=============================================================================
void ResultObserver::TargetLookRotation_(void)
{
	const float MOVE_EPSIRON = 0.05f;		// 誤差
	const float MOVE_DEST_X = 0.015f;		// 減数
	const float MOVE_DEST_Y = 0.005f;		// 減数

											//--  取得  --//
	auto x_pad_move = GET_INPUT_XPAD(ID_)->GetRStick();

	//--  誤差判定  --//
	if (x_pad_move._x > MOVE_EPSIRON || x_pad_move._x < -MOVE_EPSIRON)
	{
		rotation_._y += x_pad_move._x * MOVE_DEST_X;
	}

	//--  誤差判定  --//
	if (x_pad_move._y > MOVE_EPSIRON || x_pad_move._y < -MOVE_EPSIRON)
	{
		rotation_._z += x_pad_move._y * MOVE_DEST_Y;
	}

	//if( x_pad_move._z != 0 )
	//{
	//	length_ -= length_ / ( x_pad_move._z * 0.025f ) ;	// ズーム
	//}
}

//=============================================================================
// 
//=============================================================================
void ResultObserver::MouseMove_(void)
{
	//--  自由移動  --//
	//if( cameraState_ == CAMERA_STATE_FREE )
	{
		const float MOVE_EPSIRON = 0.05f;		// 誤差
		const float MOVE_DEST_X = 0.015f;		// 減数
		const float MOVE_DEST_Y = 0.005f;		// 減数

												//--  取得  --//
		auto mouseMove = GET_INPUT_MOUSE()->GetDiff();

		//--  クリック  --//
		if (GET_INPUT_MOUSE()->GetPress(InputMouse::MOUSE_KEY::LEFT) == true)
		{
			//--  誤差判定  --//
			if (mouseMove._x > MOVE_EPSIRON || mouseMove._x < -MOVE_EPSIRON)
			{
				rotation_._y += mouseMove._x * MOVE_DEST_X;
			}

			//--  誤差判定  --//
			if (mouseMove._y > MOVE_EPSIRON || mouseMove._y < -MOVE_EPSIRON)
			{
				rotation_._z += mouseMove._y * MOVE_DEST_Y;
			}
		}

		if (mouseMove._z != 0)
		{
			length_ -= length_ / (mouseMove._z * 0.025f);	// ズーム
		}
	}
}

//=============================================================================
// 
//=============================================================================
void ResultObserver::SetTargetPosition(const float3 & in_position)
{
	target_position_ = in_position;
}

//=============================================================================
// set vector
//=============================================================================
void ResultObserver::SetTargetVector(const float3 & in_vector)
{
	target_vector_ = utility::math::Normalize(float3(in_vector._x, 0.0f, in_vector._z));;
}

//=============================================================================
// set target length
//=============================================================================
void ResultObserver::SetTargetLength(const f32 & in_length)
{
	target_length_ = in_length;
}

//=============================================================================
// set length
//=============================================================================
void ResultObserver::SetLength(const f32 & in_length)
{
	length_ = in_length;
}

//=============================================================================
// set height
//=============================================================================
void ResultObserver::SetHeight(const f32& in_height)
{
	height_ = in_height;
}

//---------------------------------- EOF --------------------------------------