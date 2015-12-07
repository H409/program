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

#include "../system/input_mouse.h"

#include "math/math.h"
#include "player.h"

//------------------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 構造体
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// プロトタイプ宣言
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// 静的メンバ変数
//------------------------------------------------------------------------


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
	position_ = pos ;
	pKim_ = new Kim( pDevice_ );
	pKim_->Load( "resources/model/ZZI_1_MO.kim" );

	rotDest_ = float3();
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
	bool bMove = false ;	// 移動
	action_ = false ;
	float rot_diff = 0 ;	//

	D3DXVec3Normalize( ( D3DXVECTOR3* )&camera_vector_ , ( D3DXVECTOR3* )&camera_vector_ );

	if( GET_INPUT_MOUSE()->GetTrigger( InputMouse::MOUSE_KEY::RIGHT ) == true )
	{
		if( state_ != STATE::AIM )
		{
			pKim_->SetAnime( Kim::ANIME::WAIT );
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
		if( pKim_->GetAnime() == Kim::ANIME::WAIT )
		{
			//--  アクション  --//
			if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_SPACE ) )
			{
				if( action_ == false )
				{
					action_ = true ;
					pKim_->SetAnime( Kim::ANIME::ACTION );
					pKim_->SetOldAnime( Kim::ANIME::WAIT );
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
		if( pKim_->GetAnime() != Kim::ANIME::TAKE_OUT )
		{
			if( move_._x < stop && move_._x > -stop &&
				move_._z < stop && move_._z > -stop )
			{
				pKim_->SetAnime( Kim::ANIME::WAIT );
			}
		}
	}
	
	//--  待機中  --//
	if( pKim_->GetAnime() == Kim::ANIME::WAIT )
	{
		//--  武器取り出し  --//
		if( GET_INPUT_KEYBOARD()->GetTrigger( DIK_E ) == true )
		{
			//--  取り出しアニメーションをしていないなら  --//
			if( pKim_->GetAnimarionPlay( ( int )Kim::ANIME::TAKE_OUT ) == false )
			{
				int wepon = ( int )pKim_->GetWepon();
				wepon = ( wepon + 1 ) % 3 ;

				pKim_->SetWepon( ( Kim::WEAPON )wepon );
				pKim_->SetAnime( Kim::ANIME::TAKE_OUT );
				pKim_->SetOldAnime( Kim::ANIME::WAIT );
			}
		}
	}

	//--  動いたなら  --//
	if( bMove == true )
	{
		//--  アニメーション  --//
		pKim_->SetAnime( Kim::ANIME::WALK );
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
