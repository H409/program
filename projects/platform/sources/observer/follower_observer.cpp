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

		//--  基本座標移動  --//
		eye_._x = target_position_._x - sinf( rotation_._y + rot ) * length ;
		eye_._y = height_ ;
		eye_._z = target_position_._z - cosf( rotation_._y + rot ) * length ;

		//auto look_at = float3(look_at_._x,0.0f,look_at_._z);

		look_at_ = float3( vector._x * target_length_ , 0 , vector._z * target_length_ );
		look_at_ = look_at_ + target_position_ ;
	}
	else
	{
		////--  基本座標移動  --//
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

//
//typedef struct
//{
//	float a ;
//	float b ;
//	float c ;
//	float d ;
//}PLANE ;		// 平面
//
//typedef struct
//{
//	PLANE LeftPlane ;
//	PLANE RightPlane ;
//	PLANE TopPlane ;
//	PLANE BottomPlane ;
//	float NearClip ;
//	float FarClip ;
//}FRUSTUM ;		// 視錐台


	//--  設定  --//
	//SetupFOVClipPlanes( &frustum_ );

////-------------------------------------------------------------------
//// 関数名 : ３点から平面パラメータ作成
//// 
//// 引数   : const D3DXVECTOR3& P0 : 座標
//// 引数   : const D3DXVECTOR3& P1 : 座標
//// 引数   : const D3DXVECTOR3& P2 : 座標
//// 引数   : PLANE *pPlane : 視錘
//// 返り値 : なし
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
//// 関数名 : 視錘の設定
//// 
//// 引数   : FRUSTUM *frustum : 視錘台
//// 返り値 : なし
////-------------------------------------------------------------------
//void CCAMERA::SetupFOVClipPlanes( FRUSTUM *frustum )
//{
//	float angle = PI / 4 ;											// 視野角
//	float aspect = ( float )WINDOW_WIDTH / ( float )WINDOW_HEIGHT ;	// アスペクト比
//	float nearClip = NEAR_NUM ;										// near値
//	float farClip = FAR_NUM ;										// far値
//										
//	D3DXVECTOR3	P0 , P1 , P2 ;
//
//	float fTan = tan( angle * 0.5f );
//
//	//--  左平面  --//
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
//	//--  右平面  --//
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
//	//--  上平面  --//
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
//	//--  下平面  --//
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
//// 関数名 : 視錐台判定処理
//// 
//// 引数   : D3DXVECTOR3& objectPos : オブジェクト位置
//// 引数   : float radius : 半径
//// 引数   : FRUSTUM& frustum : 半径
//// 引数   : D3DXMATRIX& view : 半径
//// 返り値 : なし
////-------------------------------------------------------------------
//bool CCAMERA::MeshFOVCheck( D3DXVECTOR3& objectPos , float radius , FRUSTUM& frustum , D3DXMATRIX& view )
//{
//	//--  半径なし  --//
//	if( radius == 0 )
//	{
//		return true ;		// 絶対描画
//	}
//
//	float Dist ;
//	D3DXVECTOR3 viewPos ;
//
//	//--  ビュー空間Ｚ変換  --//	
//	viewPos.z =	view._13 * objectPos.x + view._23 * objectPos.y + view._33 * objectPos.z + view._43 ;
//
//	//--  ニアクリップ平面より手前か  --//
//	if( ( viewPos.z + radius ) < frustum.NearClip )
//	{
//		return false ;
//	}
//
//	//--  ファークリップ平面より奥か  --//
//	if( ( viewPos.z - radius ) > frustum.FarClip )
//	{
//		return false;
//	}
//
//	//--  ビュー空間Ｘ変換  --//
//	viewPos.x =	view._11 * objectPos.x + view._21 * objectPos.y + view._31 * objectPos.z + view._41 ;
//
//	//--  左側面より左側か  --//
//	Dist = ( viewPos.x * frustum.LeftPlane.a ) + ( viewPos.z * frustum.LeftPlane.c );
//
//	if( Dist > radius )
//	{
//		return false;
//	}
//
//	//--  右側面より右側か  --//
//	Dist = ( viewPos.x * frustum.RightPlane.a ) + ( viewPos.z * frustum.RightPlane.c );
//
//	if( Dist > radius )
//	{
//		return false;
//	}
//
//	//--  ビュー空間Ｙ変換  --//
//	viewPos.y =	view._12 * objectPos.x + view._22 * objectPos.y + view._32 * objectPos.z + view._42 ;
//
//	//--  上側面より上側か  --//
//	Dist = ( viewPos.y * frustum.TopPlane.b ) + ( viewPos.z * frustum.TopPlane.c );
//
//	if( Dist > radius )
//	{
//		return false ;
//	}
//
//	//--  下側面より下側か  --//
//	Dist = ( viewPos.y * frustum.BottomPlane.b ) + ( viewPos.z * frustum.BottomPlane.c );
//
//	if( Dist > radius )
//	{
//		return false ;
//	}
//
//	return true ;
//}