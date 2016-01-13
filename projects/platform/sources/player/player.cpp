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
#include "develop_tool/develop_tool.h"

#include "math/math.h"
#include "player.h"

//------------------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------------------
#ifndef _RELEASE
#define _KEYBOAD_DEBUG
#endif // _RELESE

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
	rotation_ = float3();

	old_anime_ = ANIME::WAIT ;
	anime_ = ANIME::WAIT ;
	weapon_ = WEAPON::GUN ;

	hit_ = false ;
	aim_ = false ;
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
	float rot_diff = 0 ;	// aim用

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

	//--  エイム  --//
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
		//--  停止時  --//
		const float stop = 0.02f ;

		//--  武器取り出ししていない  --//
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
	
	//--  待機中  --//
	if( anime_ == ANIME::WAIT )
	{
		//--  武器取り出し  --//
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

	DEVELOP_DISPLAY( "camera_vec : %f , %f , %f\n" , camera_vector_._x , camera_vector_._y , camera_vector_._z );
	DEVELOP_DISPLAY( "pos : %f , %f , %f\n" , position_._x , position_._y , position_._z );
	//DEVELOP_DISPLAY( "move : %f , %f , %f\n" , move_._x , move_._y , move_._z );
	//DEVELOP_DISPLAY( "action : %d\n" , action_ );
	DEVELOP_DISPLAY( "anime : %d\n" , anime_ );
}
//-------------------------------------------------------------------
// 関数名 : キーボード更新
//
// 引数   : なし
// 返り値 : なし
//-------------------------------------------------------------------	
void Player::ControlKeyBorad( void )
{
	pad_move_ = float3( 0 , 0 , 0 );

	//--  移動　前  --//	
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_W ) == true )
	{
		pad_move_._y = 1 ;
	}

	//--  移動　後  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_S ) == true )
	{
		pad_move_._y = -1 ;
	}

	//--  移動　左  --//
	if( GET_INPUT_KEYBOARD()->GetPress( DIK_A ) == true )
	{
		pad_move_._x = -1 ;
	}

	//--  移動　右  --//
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

	//--  エイム  --//
	if( state_ == STATE::AIM )
	{
		//--  アクション  --//
		if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_SPACE ) )
		{
			action_ = true ;
		}
	}

	//--  武器取り出し  --//
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
// 関数名 : ジョイパッド更新
//
// 引数   : なし
// 返り値 : なし
//-------------------------------------------------------------------	
void Player::ControlJoypad( void )
{
	//--  移動  --//	
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

	//--  エイム  --//
	if( state_ == STATE::AIM )
	{
		//--  アクション  --//
		if( GET_INPUT_XPAD( ID_ )->GetTrigger( XIPad::KEY::R2 ) == true )
		{
			action_ = true ;
		}
	}

	//--  武器取り出し  --//
	if( GET_INPUT_XPAD( ID_ )->GetTrigger( XIPad::KEY::Y ) == true )
	{
		take_out_ = true ;
	}
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

//-------------------------------------------------------------------
// 関数名 : set
//
// 引数   : なし
// 返り値 : なし
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
