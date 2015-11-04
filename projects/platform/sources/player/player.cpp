//-----------------------------------------------------------------------------
//
// プレイヤー処理 : player.cpp
// Author : sembon takanori
//
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------
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
}

//-------------------------------------------------------------------
// 関数名 : デストラクタ
//
// 引数   : なし
//-------------------------------------------------------------------
Player::~Player( void )
{
	pKim_->Release();
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
	pKim_->Load( "resources/model/ZZI_taiki4.kim" );
}

//-------------------------------------------------------------------
// 関数名 : 更新
//
// 引数   : なし
// 返り値 : なし
//-------------------------------------------------------------------
void Player::Update( void )
{
	pKim_->Update();
	pKim_->SetWorld( ( D3DXMATRIX& )matrix_ );
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
