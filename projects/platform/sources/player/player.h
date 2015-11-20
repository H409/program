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
	Player( LPDIRECT3DDEVICE9 pDevice );		// コンストラクタ
	~Player();									// デストラクタ

	void Init( float3 pos );		// 初期化
	void Update( void );				// 更新
	void Draw( void );					// 描画
	void Uninit( void );				// 終了

	//--  kimのポインタ  --//
	Kim* GetKimPointer( void ){ return pKim_ ; }

	void SetCameraVector( float3 vec ){ camera_vector_ = vec ; }

	void SetID( int id ){ ID_ = id ; }

	//--  インスタンス生成  --//
	//static Player* Create( LPDIRECT3DDEVICE9 pDevice , float3 pos );

private : 
	LPDIRECT3DDEVICE9 pDevice_ ;
	Kim* pKim_ ;

	float3 camera_vector_ ;		// カメラ方向
	float3 move_ ;				// 移動量
	float3 speed_ ;				// 速度
	float3 rotDest_ ;			// 目的の向き
	
	int ID_ ;

	void Control( void );
	void UpdateKimMatrix( void );

protected : 
};

#endif // _PLAYER_H_

// END