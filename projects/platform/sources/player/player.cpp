//-----------------------------------------------------------------------------
//
// プレイヤー処理 : player.cpp
// Author : sembon takanori
//
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------
// インクルード
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
// マクロ定義
//------------------------------------------------------------------------
#ifdef _DEBUG
#define _KEYBOAD_DEBUG
#endif // _DEBUG

//------------------------------------------------------------------------
// 構造体
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// プロトタイプ宣言
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 静的メンバ変数
//------------------------------------------------------------------------
int Player::player_anime_data_[][ 3 ] = { //--  ランチャー  --//
										{ 31  , 60  , 0 } ,		// 取り出し
										{ 61  , 150 , 1 } ,		// 待機
										{ 151 , 180 , 1 } ,		// 歩く
										{ 181 , 240 , 0 } ,		// 行動
										{ 241 , 300 , 0 } ,		// ダメージ
										
										//--  ショットガン  --//
										{ 331 , 360 , 0 } ,		// 取り出し
										{ 361 , 450 , 1 } ,		// 待機
										{ 451 , 480 , 1 } ,		// 歩く
										{ 481 , 510 , 0 } ,		// 行動
										{ 511 , 570 , 0 } ,		// ダメージ
										
										//--  クワ  --//
										{ 601 , 630 , 0 } ,		// 取り出し
										{ 631 , 720 , 1 } ,		// 待機
										{ 721 , 750 , 1 } ,		// 歩く
										{ 751 , 810 , 0 } ,		// 行動
										{ 811 , 870 , 0 } };	// ダメージ

//------------------------------------------------------------------------
// グローバル変数
//------------------------------------------------------------------------

//-------------------------------------------------------------------
// 関数名 : コンストラクタ
//
// 引数   : LPDIRECT3DDEVICE9 pDevice : デバイス
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
// 関数名 : デストラクタ
//
// 引数   : なし
//-------------------------------------------------------------------
Player::~Player( void )
{
	SafeRelease( pKim_ );
}

//-------------------------------------------------------------------
// 関数名 : 初期化
//
// 引数   : D3DXVECTOR2 pos : 座標
// 引数   : D3DXVECTOR2 size : サイズ
// 返り値 : 成功かどうか
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
// 関数名 : 更新
//
// 引数   : なし
// 返り値 : なし
//-------------------------------------------------------------------
void Player::Update( void )
{
	old_position_ = position_ ;

	//--  移動  --//
	Control();

	auto a = NOW_ANIMETION ;
	pKim_->SetAnime( player_anime_data_[ NOW_ANIMETION ][ 0 ] ,
					 player_anime_data_[ NOW_ANIMETION ][ 1 ] ,
					 player_anime_data_[ NOW_ANIMETION ][ 2 ] );

	//--  kim更新  --//
	UpdateKimMatrix();
}

//-------------------------------------------------------------------
// 関数名 : 描画
//
// 引数   : なし
// 返り値 : なし
//-------------------------------------------------------------------
void Player::Draw( void )
{
	pKim_->Draw();
}

//-------------------------------------------------------------------
// 関数名 : 終了
//
// 引数   : なし
// 返り値 : なし
//-------------------------------------------------------------------
void Player::Uninit( void )
{
}

//-------------------------------------------------------------------
// 関数名 : 操作
//
// 引数   : なし
// 返り値 : なし
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
// 関数名 : キーボード更新
//
// 引数   : なし
// 返り値 : なし
//-------------------------------------------------------------------	
void Player::ControlKeyBorad( void )
{
	bool bMove = false ;	// 移動
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

	//--  移動　前  --//	
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_W ) == true )
	{
		move_._x += camera_vector_._x * speed_._x ; 
		move_._z += camera_vector_._z * speed_._z ;

		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );

		bMove = true ;
	}


	//--  移動　後  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_S ) == true )
	{
		move_._x -= camera_vector_._x * speed_._x ; 
		move_._z -= camera_vector_._z * speed_._z ;

		rotDest_._y = atan2f( -camera_vector_._x , -camera_vector_._z );

		bMove = true ;

	}

	//--  移動　左  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_A ) == true )
	{
		D3DXVECTOR3 vec ;
		D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&camera_vector_ );

		move_._x -= vec.x * speed_._x ;
		move_._z -= vec.z * speed_._z ;

		rotDest_._y = atan2f( -vec.x , -vec.z );

		bMove = true ;
	}

	//--  移動　右  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_D ) == true )
	{
		D3DXVECTOR3 vec ;
		D3DXVec3Cross( &vec , &D3DXVECTOR3( 0 , 1 , 0 ) , ( D3DXVECTOR3* )&camera_vector_ );

		move_._x += vec.x * speed_._x ;
		move_._z += vec.z * speed_._z ;

		rotDest_._y = atan2f( vec.x , vec.z );

		bMove = true ;
	}

	//--  エイム  --//
	if( state_ == STATE::AIM )
	{
		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );
		rotDest_._y += 0.4f ;

		//--  アニメーションが待機なら  --//
		if( anime_ == ANIME::WAIT )
		{
			//--  アクション  --//
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
		//--  停止時  --//
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
	
	//--  待機中  --//
	if( anime_ == ANIME::WAIT )
	{
		//--  武器取り出し  --//
		if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_E ) == true )
		{
			//--  取り出しアニメーションをしていないなら  --//
			if( pKim_->GetAnimarionPlay( ( int )ANIME::TAKE_OUT ) == false )
			{
				wepon_ = ( WEAPON )( ( ( int )wepon_ + 1 ) % 3 );

				anime_ = ANIME::TAKE_OUT ;
				old_anime_ = ANIME::WAIT ;
			}
		}
	}

	//--  動いたなら  --//
	if( bMove == true )
	{
		//--  アニメーション  --//
		anime_ = ANIME::WALK ;
	}

	if( pKim_->GetSingleAnimationEnd() == true )
	{
		anime_ = old_anime_ ;
	}
	
	//--  移動  --//
	position_._x += move_._x ;
	position_._y += move_._y ;
	position_._z += move_._z ;

	move_._x *= 0.855f ;
	move_._z *= 0.855f ;

	rotDest_._y = utility::math::Wrap( rotDest_._y , ( f32 )-utility::math::PI , ( f32 )utility::math::PI );

	//--  向きの慣性更新  --//
	auto diff = rotDest_._y - rotation_._y ;
	diff = utility::math::Wrap( diff , ( f32 )-utility::math::PI , ( f32 )utility::math::PI );

	rotation_._y += diff * ( 0.09f + rot_diff );
}

//-------------------------------------------------------------------
// 関数名 : ジョイパッド更新
//
// 引数   : なし
// 返り値 : なし
//-------------------------------------------------------------------	
void Player::ControlJoypad( void )
{
	bool bMove = false ;	// 移動
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

	//--  移動  --//	
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


	//--  エイム  --//
	if( state_ == STATE::AIM )
	{
		rotDest_._y = atan2f( camera_vector_._x , camera_vector_._z );
		rotDest_._y += 0.4f ;

		//--  アニメーションが待機なら  --//
		if( anime_ == ANIME::WAIT )
		{
			//--  アクション  --//
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
		//--  停止時  --//
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
	
	//--  待機中  --//
	if( anime_ == ANIME::WAIT )
	{
		//--  武器取り出し  --//
		if( GET_INPUT_XPAD( ID_ )->GetTrigger( XIPad::KEY::Y ) == true == true )
		{
			//--  取り出しアニメーションをしていないなら  --//
			if( pKim_->GetAnimarionPlay( ( int )ANIME::TAKE_OUT ) == false )
			{
				wepon_ = ( WEAPON )( ( ( int )wepon_ + 1 ) % 3 );

				anime_ = ANIME::TAKE_OUT ;
				old_anime_ = ANIME::WAIT ;
			}
		}
	}

	//--  動いたなら  --//
	if( bMove == true )
	{
		//--  アニメーション  --//
		anime_ = ANIME::WALK ;
	}
	
	//--  移動  --//
	position_._x += move_._x ;
	position_._y += move_._y ;
	position_._z += move_._z ;

	move_._x *= 0.855f ;
	move_._z *= 0.855f ;

	rotDest_._y = utility::math::Wrap( rotDest_._y , ( f32 )-utility::math::PI , ( f32 )utility::math::PI );

	//--  向きの慣性更新  --//
	auto diff = rotDest_._y - rotation_._y ;
	diff = utility::math::Wrap( diff , ( f32 )-utility::math::PI , ( f32 )utility::math::PI );

	rotation_._y += diff * ( 0.09f + rot_diff );
}


//-------------------------------------------------------------------
// 関数名 : kim更新
//
// 引数   : なし
// 返り値 : なし
//-------------------------------------------------------------------
void Player::UpdateKimMatrix( void )
{
	//--  FBX更新  --//
	D3DXMATRIX  mtxScl , mtxRot , mtxTranslate ; //ワーク用
	
	D3DXMatrixIdentity( ( D3DXMATRIX* )&matrix_ );	//ワールドマトリックス初期化

	//--  スケールの反映  --//
	D3DXMatrixScaling( &mtxScl , scale_._x , scale_._y , scale_._z );
	D3DXMatrixMultiply( ( D3DXMATRIX* )&matrix_ , ( D3DXMATRIX* )&matrix_ , &mtxScl );	//行列の掛け算

	//--  回転の反映  --//
	D3DXMatrixRotationYawPitchRoll( &mtxRot , rotation_._y , rotation_._x , rotation_._z );
	D3DXMatrixMultiply( ( D3DXMATRIX* )&matrix_ , ( D3DXMATRIX* )&matrix_ , &mtxRot );	//行列の掛け算

	//--  位置の反映  --//
	D3DXMatrixTranslation( &mtxTranslate , position_._x , position_._y , position_._z );
	D3DXMatrixMultiply( ( D3DXMATRIX* )&matrix_ , ( D3DXMATRIX* )&matrix_ , &mtxTranslate );	//行列の掛け算

	pKim_->SetWorld( ( D3DXMATRIX& )matrix_ );
	pKim_->Update();
}

////-------------------------------------------------------------------
//// 関数名 : インスタンス生成
////
//// 引数   : LPDIRECT3DDEVICE9 pDevice
//// 引数   : D3DXVECTOR2 pos : 座標
//// 引数   : D3DXVECTOR2 size : サイズ
//// 引数   : int priority : プライオリティ
//// 返り値 : 自身のポインタ
////-------------------------------------------------------------------
//Player* Player::Create( LPDIRECT3DDEVICE9 pDevice , float3 pos )
//{
//	//--  インスタンス生成  --//
//	Player* pObject = new Player( pDevice );
//
//	//--  初期化  --//
//	pObject->Init( pos );
//
//	return pObject ;
//}

// END
