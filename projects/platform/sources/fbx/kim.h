#ifndef _SCENE_KIM_H_
#define _SCENE_KIM_H_
//=============================================================================
//
// FBXを変換した独自形式モデル処理 : scene_kim.h
// Author : Kenji IIZUKA
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "dx9_device.h"

//*****************************************************************************
// 構造体
//*****************************************************************************
// メッシュ情報構造体
struct KIM_MESH_DATA
{
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;
	LPDIRECT3DINDEXBUFFER9 index_buffer_;
	LPDIRECT3DTEXTURE9 texture_;
	D3DMATERIAL9 material_;
	int vertex_num_;
	int index_num_;
	int bind_weight;
	int *bind_index;
	char texture_filename_[128];
	char uv_set_name[128];

	KIM_MESH_DATA(void){
		vertex_buffer_ = NULL;
		index_buffer_ = NULL;
		bind_index = NULL;
		texture_ = NULL;
		vertex_num_ = 0;
		index_num_ = 0;
		bind_weight = 0;
		memset(&material_, 0, sizeof(D3DMATERIAL9));
	}
};

//#define FVF_KIM (D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// 頂点情報構造体
struct VERTEX_KIM
{
	D3DXVECTOR3 coord;//頂点
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;
	D3DCOLOR diffuse;
	float weight[4];//重み
	DWORD bone_index;//頂点インデックス(下位バイトが若番)
};

// ｷｰﾌﾚｰﾑ情報構造体
struct KIM_KEY_FRAME
{
	int frame_chenge;			// 次のﾌﾚｰﾑまでの長さ
	D3DXVECTOR3 translation;	// 平行移動
	D3DXQUATERNION rotation;	// ｱﾌｨﾝ情報
	D3DXVECTOR3 scaling;		// 拡縮情報

};

struct KIM_ANIMATION_DATA{
	KIM_KEY_FRAME* keyframe;	// ｷｰﾌﾚｰﾑ情報
	int num_key;				// ｷｰ数
	int current_key;			// 現在ｷｰ

	KIM_ANIMATION_DATA(){
		keyframe = NULL;
		num_key = 0;
		current_key = 0;
	}
};

// ﾎﾞｰﾝ情報構造体
struct KIM_BONE_DATA
{
	char name[64];

	int id;
	KIM_BONE_DATA* child;
	KIM_BONE_DATA* sibling;

	D3DXMATRIX offset_matrix;	// 初期状態のワールドマトリックスの逆行列
	D3DXMATRIX init_matrix;		// 初期姿勢
	D3DXMATRIX bone_matrix;		// ローカルの変換行列(こいつをGPUに送る)
	D3DXMATRIX wold_matrix;		// ワールド上の変換行列

	int current_time;			// 現在の時間
	int anime_num;
	KIM_ANIMATION_DATA *anime;

	KIM_BONE_DATA()
	{
		id = -1;
		child = NULL;
		sibling = NULL;
		memset(name, 0, 64);

		current_time = 0;
		anime_num = 0;
		anime = NULL;

		D3DXMatrixIdentity(&wold_matrix);
		D3DXMatrixIdentity(&bone_matrix);
		D3DXMatrixIdentity(&offset_matrix);
	}
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 前方参照
//*****************************************************************************

//=============================================================================
// FBXを変換した独自形式モデルクラス
//=============================================================================
class Kim
{
	static const int BONE_MAX = 13;

	enum DRAW_TYPE{
		TYPE_ONE_MY = 0,
		TYPE_ONE_ORIGINE,
		TYPE_MULTI_MY,
		TYPE_MULTI_ORIGINE,
		TYPE_STATIC_MESH,
	};

public : 

	// 処理:コンストラクタ
	Kim(LPDIRECT3DDEVICE9 d3d_device);
		
	// 処理:デストラクタ
	~Kim(void);

	// 処理:読み込み
	HRESULT Load(const char* file_name);

	// 処理:終了
	void Uninit(void);
	
	// 処理:更新
	void Update(void);

	// 処理:描画
	void Draw(void);

	// 処理:解放
	void Release(void);

	// 処理:ﾜｰﾙﾄﾞﾏﾄﾘｸｽのｾｯﾀ
	void SetWorld(D3DXMATRIX world){ world_ = world; };

	void SetView( D3DXMATRIX *view ){ view_ = *view ; }
	void SetProjection( D3DXMATRIX *projection ){ projection_ = *projection ; }

	LPDIRECT3DTEXTURE9 GetTexture( int i ){ return mesh_[ i ].texture_ ; }

	bool GetAnimarionPlay( int i ){ return animation_play_[ i ]; }	// trueで終わっている

	void SetOldKey( int i ){ old_key_ = i ; }
	void SetAnimeID( int id ){ anime_ID_ = id ; }
	void SetAnime( int start , int end , int repeat );
	void SetOldAnime( int start , int end , int repeat );

private:
	// 処理:ｼｪｰﾀﾞｰのｺﾝﾊﾟｲﾙ
	HRESULT CompileShader(void);

	// 処理:ﾎﾞｰﾝｲﾝﾃﾞｯｸｽの正規化
	void BoneIndexNormalize(int mesh_idx,VERTEX_KIM* vtx);

	// 処理:送信する頂点情報の設定
	void CreateVertexDecl(void);

	// 処理:ボーンの更新(行列変換)
	void UpdateBone(KIM_BONE_DATA* me, D3DXMATRIX *parentWorldMat);

	// 処理:ﾎﾞｰﾝ配列の初期位置の設定
	void CalcRelativeMat(KIM_BONE_DATA* me, D3DXMATRIX *parentoffsetMat);

	// ﾏﾃﾘｱﾙの設定
	void SetMaterial(D3DMATERIAL9 *material);

	// 複数ﾒｯｼｭ	自作ｼｪｰﾀﾞｰ用描画
	void MultiMeshMyShader(void);

	void Animation( void );
	void Animation( int i );

private : 
	LPDIRECT3DDEVICE9 d3d_device_;

	LPDIRECT3DVERTEXDECLARATION9 decl_;
	LPDIRECT3DPIXELSHADER9 pixel_shader_;
	LPDIRECT3DVERTEXSHADER9 vertex_shader_;

	LPDIRECT3DTEXTURE9 toon_map;
	KIM_MESH_DATA *mesh_;
	KIM_BONE_DATA *bone_;

	D3DXMATRIX world_;
	D3DXVECTOR3 light_directional;

	D3DXMATRIX view_ ;
	D3DXMATRIX projection_ ;

	int mesh_num_;
	int bone_num_;

	int current_anime_;	// 現在のｱﾆﾒｰｼｮﾝ番号
	int next_anime_;	// 次のｱﾆﾒｰｼｮﾝ番号

	int set_anime_;		// 次のｱﾆﾒｰｼｮﾝｽﾀｯｸ

	int draw_type_;

	D3DXVECTOR3 vertex_min_;
	D3DXVECTOR3 vertex_max_;

	int anime_ID_ ;
	int anime_speed = 1;
	float value_ = 0.0f;
	float times_ = 15.0f;
	int cursor_bone_ = 0;
	int cursor_mesh_ = 0;
	int anim_type_ = 0;
	int anime_value = 1;
	int all_vertex_num_ = 0;

	int old_key_ ;
	int current_key_ ;
	int next_key_ ;

	bool animation_ ;
	bool animation_play_[ 5 ];	// 新しいアニメーション終わったか

	int anime_data_[ 3 ];
	int old_anime_data_[ 3 ];

};

#endif // _SCENE_KIM_H_
// EOF
