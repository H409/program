//-----------------------------------------------------------------------------
//
// プレイヤー処理 : player.h
// Author : sembon takanori
//
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------
#include "../object/object.h"
#include "../fbx/kim.h"

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
// 前方参照
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// クラス
//------------------------------------------------------------------------
class Player : public Object
{
public : 
	enum STATE
	{
		NONE = -1 ,		// なし
		WAIT ,			// 待機
		WALK ,			// 歩く
		DASH ,			// 走る
		DIG ,			// 掘る
		SHOOT ,			// 撃つ
		AIM ,			// エイム
		DOWN ,			// ダウン
		MAX
	};

	Player( LPDIRECT3DDEVICE9 pDevice );		// コンストラクタ
	~Player();									// デストラクタ

	void Init( float3 pos );		// 初期化
	void Update( void );				// 更新
	void Draw( void );					// 描画
	void Uninit( void );				// 終了

	//--  kimのポインタ  --//
	Kim* GetKimPointer( void ){ return pKim_ ; }
	
	STATE GetState( void ){ return state_ ; }
	STATE GetAnime( void ){ return anime_ ; }

	void SetID( int id ){ ID_ = id ; }
	int GetID( void ){ return ID_ ; }

	const float3& GetOldPosition( void ){ return old_position_ ; }
	void SetOldPosition( const float3& pos ){ old_position_ = pos ; }

	void SetMove(const float3& in_move) { move_ = in_move; }
	const float3& GetMove(void) { return move_; }
	//--  設定  --//
	void SetCameraVector( const float3& vec ){ camera_vector_ = vec ; }

	//--  インスタンス生成  --//
	//static Player* Create( LPDIRECT3DDEVICE9 pDevice , float3 pos );

private : 
	LPDIRECT3DDEVICE9 pDevice_ ;
	Kim* pKim_ ;

	float3 camera_vector_ ;		// カメラ方向
	float3 move_ ;				// 移動量
	float3 speed_ ;				// 速度
	float3 rotDest_ ;			// 目的の向き
	float3 old_position_ ;		// 前の位置

	int ID_ ;
	int anime_data_[ STATE::MAX ][ 2 ];

	STATE state_ ;
	STATE anime_ ;

	void Control( void );
	void UpdateKimMatrix( void );

protected : 
};

#endif // _PLAYER_H_

// END