//=============================================================================
//
// FBXを変換した独自形式モデル処理 : scene_kim.cpp
// Author : Kenji IIZUKA
//
//=============================================================================

//*****************************************************************************
// インクルード
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "kim.h"
#include "system/win_system.h"
#include "develop_tool/develop_tool.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int Kim::anime_data_[][ 3 ] = { //--  ランチャー  --//
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

//=============================================================================
// 役割 : コンストラクタ
//=============================================================================
Kim::Kim(LPDIRECT3DDEVICE9 d3d_device)
{
	d3d_device_ = d3d_device;

	toon_map = NULL ;
	mesh_ = NULL;
	bone_ = NULL;
	decl_ = NULL;

	vertex_shader_ = NULL;
	pixel_shader_ = NULL;

	mesh_num_ = 0;
	bone_num_ = 0;

	current_anime_ = 0;
	next_anime_  = 0;
	set_anime_ = 0;

	draw_type_ = TYPE_MULTI_MY;

	light_directional = D3DXVECTOR3(0.5f, -0.5f, 0.5f);
	D3DXVec3Normalize(&light_directional, &light_directional);

	D3DXMatrixIdentity(&world_);

	//--  このﾌﾚｰﾑﾜｰｸ用  --//
//	all_vertex_num_ = 0;

	old_anime_ = ANIME::WAIT ;
	anime_ = ANIME::WAIT ;
	wepon_ = WEAPON::GUN ;
	current_key_ = anime_data_[ NOW_ANIMETION ][ 0 ];
	animation_ = true ;

	memset( &animation_play_ , 0 , sizeof( animation_play_ ) );
}

//=============================================================================
// 役割 : デストラクタ
//=============================================================================
Kim::~Kim( void )
{
}

//=============================================================================
// 役割 : 初期化処理
//=============================================================================
HRESULT Kim::Load(const char* file_name)
{
	// ﾌｧｲﾙポインタ
	FILE *file = NULL;

	// ﾌｧｲﾙ読み込み(失敗したら終了)
	file = fopen(file_name, "rb");
	if (file == NULL)
		return true;

	// 先頭に戻る
	fseek(file, 0, SEEK_SET);

	// ﾒｯｼｭ数読み込み
	fread(&mesh_num_, sizeof(int), 1, file);

	// ﾎﾞｰﾝ数読み込み
	fread(&bone_num_, sizeof(int), 1, file);

	// ﾒｯｼｭ数分だけ生成
	mesh_ = new KIM_MESH_DATA[mesh_num_];

	// ﾒｯｼｭ情報の読み込み
	for (int i = 0; i < mesh_num_; i++)
	{
		// 頂点数の読み込み
		fread(&mesh_[i].vertex_num_, sizeof(int), 1, file);

		// 頂点数が０なら次のメッシュへ
		if (mesh_[i].vertex_num_ == 0)
			continue;

		// ｲﾝﾃﾞｯｸｽ数の読み込み
		fread(&mesh_[i].index_num_, sizeof(int), 1, file);

		// ﾃｸｽﾁｬ名の読み込み
		fread(&mesh_[i].texture_filename_, sizeof(char), 128, file);

		// ﾏﾃﾘｱﾙの獲得
		fread(&mesh_[i].material_, sizeof(D3DMATERIAL9), 1, file);

		// ﾃﾞｨﾌｰｽﾞのαが0の時,情報抜けの可能性があるため,全部に1を入れる
		if (mesh_[i].material_.Diffuse.a == 0.0f)
			mesh_[i].material_.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点バッファの生成
		d3d_device_->CreateVertexBuffer(mesh_[i].vertex_num_ * sizeof(VERTEX_KIM), D3DUSAGE_SOFTWAREPROCESSING, NULL, D3DPOOL_MANAGED, &mesh_[i].vertex_buffer_, NULL);

		// 頂点情報の読み込み用
		VERTEX_KIM* vtx;

		// 頂点バッファの解放
		mesh_[i].vertex_buffer_->Lock(0, 0, (void**)&vtx, 0);

		// 頂点情報の読み込み
		fread(vtx, sizeof(VERTEX_KIM), mesh_[i].vertex_num_, file);

		// 頂点数のカウント
		all_vertex_num_ += mesh_[i].vertex_num_;

		for (int j = 0; j < mesh_[i].vertex_num_; j++)
		{
			if (vertex_max_.x < vtx[j].coord.x)
			{
				vertex_max_.x = vtx[j].coord.x;
			}

			if (vertex_min_.x > vtx[j].coord.x)
			{
				vertex_min_.x = vtx[j].coord.x;
			}

			if (vertex_max_.y < vtx[j].coord.y)
			{
				vertex_max_.y = vtx[j].coord.y;
			}

			if (vertex_min_.y > vtx[j].coord.y)
			{
				vertex_min_.y = vtx[j].coord.y;
			}

			if (vertex_max_.z < vtx[j].coord.z)
			{
				vertex_max_.z = vtx[j].coord.z;
			}

			if (vertex_min_.z > vtx[j].coord.z)
			{
				vertex_min_.z = vtx[j].coord.z;
			}

		}

		// ﾎﾞｰﾝｲﾝﾃﾞｯｸｽの正規化
		if (draw_type_ > 1 && bone_num_ != 0)
			BoneIndexNormalize(i, vtx);

		// 頂点ﾊﾞｯﾌｧのｱﾝﾛｯｸ
		mesh_[i].vertex_buffer_->Unlock();

		// ｲﾝﾃﾞｯｸｽバッファの生成
		if (FAILED(d3d_device_->CreateIndexBuffer(mesh_[i].index_num_ * sizeof(DWORD), D3DUSAGE_SOFTWAREPROCESSING, D3DFMT_INDEX32, D3DPOOL_MANAGED, &mesh_[i].index_buffer_, NULL)))
			MessageBox(NULL, "ｲﾝﾃﾞｯｸｽﾊﾞｯﾌｧの生成に失敗しました", "頂点ﾊﾞｯﾌｧの生成に失敗しました", MB_OK);

		// index情報の読み込み
		DWORD* workIndex(nullptr);
		mesh_[i].index_buffer_->Lock(0, 0, (void**)&workIndex, 0);

		// ｲﾝﾃﾞｯｸｽ番号
		fread(workIndex, sizeof(DWORD), mesh_[i].index_num_, file);

		// ｲﾝﾃﾞｯｸｽﾊﾞｯﾌｧの解放
		if (FAILED(mesh_[i].index_buffer_->Unlock()))
			MessageBox(NULL, "ｲﾝﾃﾞｯｸｽﾊﾞｯﾌｧの解放に失敗しました", "頂点ﾊﾞｯﾌｧの生成に失敗しました", MB_OK);

		// ﾃｸｽﾁｬの生成
		D3DXCreateTextureFromFile(d3d_device_, mesh_[i].texture_filename_, &mesh_[i].texture_);
		//D3DXCreateTextureFromFile(d3d_device_, "resources/texture/ZZI_S_texture.jpg", &mesh_[i].texture_);
	}

	// ﾎﾞｰﾝ情報の入ってないﾓﾃﾞﾙの場合は読み込まない
	if (bone_num_ != 0)
	{
		// ﾎﾞｰﾝの生成
		bone_ = new KIM_BONE_DATA[bone_num_];
		int *chile_id = new int[bone_num_];
		int *sibling_id = new int[bone_num_];

		// ﾎﾞｰﾝ情報読み込み
		for (int i = 0; i < bone_num_; i++)
		{
			bone_[i].anime_num = 1;
			//bone_[i].anime = new KIM_ANIMATION_DATA[bone_[i].anime_num];

			// ボーン名
			fread(bone_[i].name, sizeof(char), 64, file);
			// ボーンID
			fread(&bone_[i].id, sizeof(int), 1, file);
			// 子のID
			fread(&chile_id[i], sizeof(int), 1, file);
			// 兄弟のID
			fread(&sibling_id[i], sizeof(int), 1, file);
			// 初期姿勢ﾏﾄﾘｸｽ
			fread(&bone_[i].init_matrix, sizeof(D3DXMATRIX), 1, file);
			// ｵﾌｾｯﾄﾏﾄﾘｸｽ
			fread(&bone_[i].offset_matrix, sizeof(D3DXMATRIX), 1, file);

			// ｱﾆﾒｰｼｮﾝ数
			fread(&bone_[i].anime_num, sizeof(int), 1, file);

			// ｱﾆﾒｰｼｮﾝの生成
			bone_[i].anime = new KIM_ANIMATION_DATA[bone_[i].anime_num];

			// ｱﾆﾒｰｼｮﾝの読み込み
			for (int anime_id = 0; anime_id < bone_[i].anime_num; anime_id++)
			{
				// 最大ｷｰ数
				fread(&bone_[i].anime[anime_id].num_key, sizeof(int), 1, file);

				// ｷｰﾌﾚｰﾑの生成
				bone_[i].anime[anime_id].keyframe = new KIM_KEY_FRAME[bone_[i].anime[anime_id].num_key];

				// ｷｰﾌﾚｰﾑの読み込み
				fread(bone_[i].anime[anime_id].keyframe, sizeof(KIM_KEY_FRAME), bone_[i].anime[anime_id].num_key, file);
			}
		}

		// 親子関係の生成
		for (int i = 0; i < bone_num_; i++)
		{
			// 親子関係の構築
			if (chile_id[i] >= 0)
				bone_[i].child = &bone_[chile_id[i]];
			if (sibling_id[i] >= 0)
				bone_[i].sibling = &bone_[sibling_id[i]];
		}

		// ﾛｰｶﾙID情報の解放
		delete[] chile_id;
		delete[] sibling_id;

		// ﾎﾞｰﾝを親に対しての相対位置に移動
		CalcRelativeMat(bone_, 0);
	}

	// 読み込みの終了
	fclose(file);

	// 送信する頂点情報の設定
	CreateVertexDecl();

	// 一枚ﾒｯｼｭの定数ﾚｼﾞｽﾀを超えた
	if (bone_num_ > BONE_MAX && draw_type_ == TYPE_ONE_MY)
	{
		MessageBox(NULL, "最大頂点数を超えました", "最大頂点数を超えました", MB_OK);
		return E_FAIL;
	}

	// ｼｪｰﾀﾞｰのｺﾝﾊﾟｲﾙ
	//if (draw_type_ == TYPE_ONE_MY || draw_type_ == TYPE_MULTI_MY)
		//return CompileShader();

	return S_OK ;
}

//=============================================================================
// 役割 : 終了処理
//=============================================================================
void Kim::Uninit( void )
{
	if (toon_map)
	{
		toon_map->Release();
		toon_map = NULL;
	}


	if (decl_)
	{
		decl_->Release();
		decl_ = NULL;
	}

	if (vertex_shader_)
	{
		vertex_shader_->Release();
		vertex_shader_ = NULL;
	}

	if (pixel_shader_)
	{
		pixel_shader_->Release();
		pixel_shader_ = NULL;
	}

	// ﾒｯｼｭ情報の解放
	for (int i = 0; i < mesh_num_; i++)
	{
		if (mesh_[i].vertex_buffer_ != NULL)
			mesh_[i].vertex_buffer_->Release();
		if (mesh_[i].index_buffer_ != NULL)
			mesh_[i].index_buffer_->Release();
		if (mesh_[i].texture_ != NULL)
			mesh_[i].texture_->Release();
		if (mesh_[i].bind_index != NULL)
			delete[] mesh_[i].bind_index;
	}
	if (mesh_ != NULL)
		delete[] mesh_;

	// ﾎﾞｰﾝ情報の解放
	for (int i = 0; i < bone_num_; i++)
	{
		for (int j = 0; j < bone_[i].anime_num; j++)
		{
			if (bone_[i].anime[j].keyframe != NULL)
			{
				delete[] bone_[i].anime[j].keyframe;
				bone_[i].anime[j].keyframe = NULL;
			}
		}

		delete[] bone_[i].anime;

	}

	if (bone_ != NULL)
		delete[] bone_;
}

//=============================================================================
// 処理:更新
//=============================================================================
void Kim::Update(void)
{

	//if (!GetAsyncKeyState('Y') & 0x0001)
	{
		//// ﾎﾞｰﾝがなければそもそもｽｷﾆﾝｸﾞされてない
		//if (bone_ == NULL)
		//	return;

		//// ｱﾆﾒｰｼｮﾝが無いときは全てのﾎﾞｰﾝを単位行列にしとく
		//if (bone_[cursor_bone_].anime_num == 0)
		//{
		//	for (int i = 0; i < bone_num_; i++)
		//	{
		//		D3DXMatrixIdentity(&bone_[i].bone_matrix);
		//		bone_[i].bone_matrix *= bone_[i].init_matrix;
		//	}
		//	UpdateBone(bone_, &world_);
		//	return;
		//}

		//if (bone_->current_time == 1)
		//	 0  = set_anime_;

	//	// 普通のｱﾆﾒｰｼｮﾝ
	//	for (int i = 0; i < bone_num_; i++)
	//	{
	//		// 初期化
	//		D3DXMatrixIdentity(&bone_[i].bone_matrix);

	//		// 可読性がヤバイのでﾃﾝﾎﾟﾗﾘを用意
	//		KIM_BONE_DATA *dest_bone = &bone_[i];
	//			
	//		// ｷｰ数がない場合はおそらくｱﾆﾒｰｼｮﾝ無いので初期姿勢だけかけて次
	//		if (dest_bone->anime[ 0 ].num_key == 0)
	//		{
	//			bone_[i].bone_matrix *= bone_[i].init_matrix;
	//			continue;
	//		}

	//		// 可読性がヤバイのでﾃﾝﾎﾟﾗﾘを用意
	//		int current_key = dest_bone->anime[ 0 ].current_key;
	//		int next_key = (dest_bone->anime[ 0 ].current_key + 1) % (dest_bone->anime[ 0 ].num_key);

	//		KIM_KEY_FRAME *cur_flame = &dest_bone->anime[ 0 ].keyframe[current_key];
	//		KIM_KEY_FRAME *next_flame;

	//		if ( 0  ==  0 )
	//		{
	//			next_flame = &dest_bone->anime[ 0 ].keyframe[next_key];
	//		}
	//		else
	//		{
	//			next_flame = &dest_bone->anime[ 0 ].keyframe[0];
	//		}

	//		// 線形補間に使う時間の計算
	//		float t = (float)(dest_bone->current_time) / (float)next_flame->frame_chenge;

	//		// それぞれの変換情報線形補間
	//		D3DXVECTOR3 scaling = (1.0f - t)*cur_flame->scaling + (t * next_flame->scaling);
	//		D3DXVECTOR3 translation = (1.0f - t)*cur_flame->translation + (t * next_flame->translation);
	//		D3DXQUATERNION rotation = (1.0f - t)*cur_flame->rotation + (t * next_flame->rotation);

	//		// それぞれの行列変換
	//		D3DXMATRIX scl, rot, trans;
	//		D3DXMatrixScaling(&scl, scaling.x, scaling.y, scaling.z);
	//		D3DXMatrixRotationQuaternion(&rot, &rotation);
	//		D3DXMatrixTranslation(&trans, translation.x, translation.y, translation.z);

	//		// 行列合成
	//		bone_[i].bone_matrix = scl * rot * trans * bone_[i].init_matrix;

	//		// 次のﾌﾚｰﾑに移動
	//		if (dest_bone->current_time >= next_flame->frame_chenge)
	//		{
	//			dest_bone->current_time = 0;

	//			if ( 0  ==  0 )
	//			{
	//				dest_bone->anime[ 0 ].current_key++;

	//				if (dest_bone->anime[ 0 ].current_key >= dest_bone->anime[ 0 ].num_key)
	//				{
	//					dest_bone->anime[ 0 ].current_key = next_key;
	//					dest_bone->anime[ 0 ].current_key %= dest_bone->anime[ 0 ].num_key;
	//				}
	//			}
	//			else
	//			{
	//				dest_bone->anime[ 0 ].current_key = 0;
	//				dest_bone->anime[ 0 ].current_key = 0;

	//				if (i == bone_num_-1)
	//				{
	//					 0  =  0 ;
	//				}
	//			}
	//		}

	//		// 時を進める
	//		dest_bone->current_time += anime_speed;

	//}

		//for (int i = 0; i < bone_num_; i++)
		//{
		//	auto next_flame = bone_[i].anime[ 0 ].keyframe[1];

		//	// それぞれの変換情報線形補間
		//	D3DXVECTOR3 scaling = next_flame.scaling;
		//	D3DXVECTOR3 translation = next_flame.translation;
		//	D3DXQUATERNION rotation = next_flame.rotation;

		//	// それぞれの行列変換
		//	D3DXMATRIX scl, rot, trans;
		//	D3DXMatrixScaling(&scl, scaling.x, scaling.y, scaling.z);
		//	D3DXMatrixRotationQuaternion(&rot, &rotation);
		//	D3DXMatrixTranslation(&trans, translation.x, translation.y, translation.z);

		//	// 行列合成
		//	bone_[i].bone_matrix = scl * rot * trans * bone_[i].init_matrix;
		//}

		// 普通のｱﾆﾒｰｼｮﾝ
		for( int i = 0 ; i < bone_num_ ; i++ )
		{
			// 初期化
			D3DXMatrixIdentity( &bone_[ i ].bone_matrix );

			// 可読性がヤバイのでﾃﾝﾎﾟﾗﾘを用意
			KIM_BONE_DATA *dest_bone = &bone_[ i ];
				
			//// ｷｰ数がない場合はおそらくｱﾆﾒｰｼｮﾝ無いので初期姿勢だけかけて次
			//if (dest_bone->anime[ 0 ].num_key == 0)
			//{
			//	bone_[i].bone_matrix *= bone_[i].init_matrix;
			//	continue;
			//}

			//dest_bone->anime[ 0 ].current_key = 1 ;
			//dest_bone->anime[ 0 ].num_key = 60 ;

			// 可読性がヤバイのでﾃﾝﾎﾟﾗﾘを用意
		//	int current_key = dest_bone->anime[ 0 ].current_key ;
		//	int next_key = ( dest_bone->anime[ 0 ].current_key + 1 ) % ( dest_bone->anime[ 0 ].num_key );

			//current_key_ = anime_data_[ anime_ ][ 0 ];
			next_key_ = ( current_key_ + 1 ) % ( anime_data_[ NOW_ANIMETION ][ 1 ] );

			KIM_KEY_FRAME *cur_flame = &dest_bone->anime[ 0 ].keyframe[ current_key_ ];
			KIM_KEY_FRAME *next_flame ;

			//if ( 0  ==  0 )
			{
				next_flame = &dest_bone->anime[ 0 ].keyframe[ next_key_ ];
			}

			// それぞれの変換情報線形補間
			D3DXVECTOR3 scaling = cur_flame->scaling ;
			D3DXVECTOR3 translation = cur_flame->translation ;
			D3DXQUATERNION rotation = cur_flame->rotation ;

			// それぞれの行列変換
			D3DXMATRIX scl , rot , trans ;
			D3DXMatrixScaling( &scl , scaling.x , scaling.y , scaling.z );
			D3DXMatrixRotationQuaternion( &rot , &rotation );
			D3DXMatrixTranslation( &trans , translation.x , translation.y , translation.z );

			// 行列合成
			bone_[ i ].bone_matrix = scl * rot * trans * bone_[ i ].init_matrix ;

			// 次のﾌﾚｰﾑに移動
			//if( dest_bone->current_time >= 1 )
			{
				//dest_bone->current_time = 0;

			//	if ( 0  ==  0 )
				{
					auto a = NOW_ANIMETION ;
					auto b = anime_data_[ NOW_ANIMETION ][ 1 ] ;

					if( current_key_ >= anime_data_[ NOW_ANIMETION ][ 1 ] )
					{
						animation_play_[ ( int )anime_ ] = false ;	// アニメーション終わり

						//--  リピートありなら  --//
						if( anime_data_[ NOW_ANIMETION ][ 2 ] == 1 )
						{
							current_key_ = anime_data_[ NOW_ANIMETION ][ 0 ];
						}
						else
						{
							current_key_ = anime_data_[ OLD_ANIMETION ][ 0 ];
							anime_ = old_anime_ ;
							//animation_ = false ;
						}

						//dest_bone->anime[ 0 ].current_key %= dest_bone->anime[ 0 ].num_key;
					}
				}
			}

			/// 時を進める
			//dest_bone->current_time += anime_speed ;
		}

		//if( animation_ == true )
		{
			current_key_++;
		}


		// 座標の更新:掛ける順番は 子 × 親 
		auto world = world_;
		D3DXMatrixIdentity(&world);
		UpdateBone( bone_ , &world);
	}

	DEVELOP_DISPLAY( "current_key_ : %d\n" , current_key_ );

}

//=============================================================================
// 処理:ボーンの更新(行列変換)
//=============================================================================
void Kim::Draw(void)
{
	LPDIRECT3DVERTEXDECLARATION9 before_decl;
	d3d_device_->GetVertexDeclaration(&before_decl);

	// 送信する頂点情報の設定
	d3d_device_->SetVertexDeclaration(decl_);

	MultiMeshMyShader();

	d3d_device_->SetVertexDeclaration(before_decl);
}

//=============================================================================
// 処理:解放
//=============================================================================
void Kim::Release(void)
{
	Uninit();
	delete this;
}

//=============================================================================
// 処理:ﾎﾞｰﾝｲﾝﾃﾞｯｸｽの正規化
//=============================================================================
void Kim::BoneIndexNormalize(int mesh_idx, VERTEX_KIM* vtx)
{
	//FILE *normalize_index = NULL;
	//normalize_index = fopen("data/log/normalize_index.txt", "w");

	// ﾎﾞｰﾝｲﾝﾃﾞｯｸｽ情報のﾃﾝﾎﾟﾗﾘ
	int *bone_index_data = new int[mesh_[mesh_idx].vertex_num_ * 4];

	//fprintf(normalize_index, "ここからindex\n");
	// ｲﾝﾃﾞｯｸｽ情報をint型にして持っておく
	for (int idx_cnt = 0; idx_cnt < mesh_[mesh_idx].vertex_num_; idx_cnt++)
	{
		bone_index_data[0 + idx_cnt * 4] = (vtx[idx_cnt].bone_index & 0x000000ff);
		bone_index_data[1 + idx_cnt * 4] = (vtx[idx_cnt].bone_index & 0x0000ff00) >> 8;
		bone_index_data[2 + idx_cnt * 4] = (vtx[idx_cnt].bone_index & 0x00ff0000) >> 16;
		bone_index_data[3 + idx_cnt * 4] = (vtx[idx_cnt].bone_index & 0xff000000) >> 24;

		// 対応ｲﾝﾃﾞｯｸｽが0の場合は-1を入れる後に例外処理
		if (vtx[idx_cnt].bone_index == 0)
		{
			for (int weight_cnt = 0; weight_cnt < 4; weight_cnt++)
			{
				if (vtx[idx_cnt].weight[weight_cnt] > 0.0f)
				{
					if (bone_index_data[weight_cnt + idx_cnt * 4] == 0)
					{
						bone_index_data[weight_cnt + idx_cnt * 4] = -1;
					}

				}
			}
		}

		//fprintf(normalize_index, "[0]:%d   [1]:%d   [2]:%d   [3]:%d\n"
		//	, bone_index_data[0 + idx_cnt * 4]
		//	, bone_index_data[1 + idx_cnt * 4]
		//	, bone_index_data[2 + idx_cnt * 4]
		//	, bone_index_data[3 + idx_cnt * 4]);
	}

	//fprintf(normalize_index, "ここからweight\n");
	for (int idx_cnt = 0; idx_cnt < mesh_[mesh_idx].vertex_num_; idx_cnt++)
	{
		//fprintf(normalize_index, "[0]:%f   [1]:%f   [2]:%f   [3]:%f\n"
		//	, vtx[idx_cnt].weight[0]
		//	, vtx[idx_cnt].weight[1]
		//	, vtx[idx_cnt].weight[2]
		//	, vtx[idx_cnt].weight[3]);
	}
	// 後で頂点情報に入れるｲﾝﾃﾞｯｸｽ
	int *push_index = new int[bone_num_];
	memset(push_index, 0, sizeof(int) * bone_num_);

	// このﾒｯｼｭに関連付けされてる、ｲﾝﾃﾞｯｸｽとその数の習得
	for (int vtx_cnt = 0; vtx_cnt < mesh_[mesh_idx].vertex_num_ * 4; vtx_cnt++)
	{
		int bind_weight = mesh_[mesh_idx].bind_weight;

		if (push_index[bind_weight] != bone_index_data[vtx_cnt])
		{
			bool is_push = true;
			for (int idx_cnt = 0; idx_cnt < bind_weight; idx_cnt++)
			{
				if (push_index[idx_cnt] == bone_index_data[vtx_cnt])
				{
					is_push = false;
				}
			}
			if (is_push && bone_index_data[vtx_cnt] != 0)
			{
				push_index[bind_weight] = bone_index_data[vtx_cnt];
				mesh_[mesh_idx].bind_weight++;
			}
		}
	}

	// 関連付け情報をｲﾝﾃﾞｯｸｽに登録
	mesh_[mesh_idx].bind_index = new int[mesh_[mesh_idx].bind_weight];
	for (int j = 0; j < mesh_[mesh_idx].bind_weight; j++)
	{
		if (push_index[j] == -1)
			push_index[j] = 0;
		mesh_[mesh_idx].bind_index[j] = push_index[j];
	}

	// 分割した内容を適応
	for (int idx_cnt = 0; idx_cnt < mesh_[mesh_idx].vertex_num_; idx_cnt++)
	{
		DWORD bone_index = 0;
		DWORD index_array_dword = vtx[idx_cnt].bone_index;

		for (int digit = 0; digit < 4; digit++)
		{
			for (int push_num = 0; push_num < mesh_[mesh_idx].bind_weight; push_num++)
			{
				if (bone_index_data[digit + idx_cnt * 4] == mesh_[mesh_idx].bind_index[push_num])
				{
					bone_index |= push_num << (8 * digit);
					break;
				}
			}
		}

		vtx[idx_cnt].bone_index = bone_index;
	}

	// ﾛｰｶﾙ情報の削除
	delete[] bone_index_data;
	delete[] push_index;

	//fclose(normalize_index);
}


//=============================================================================
// 処理:ボーンの更新(行列変換)
//=============================================================================
void Kim::UpdateBone(KIM_BONE_DATA* me, D3DXMATRIX *parentWorldMat)
{
	me->bone_matrix *= *parentWorldMat;

	if (me->child)
		UpdateBone(me->child, &me->bone_matrix);
	if (me->sibling)
		UpdateBone(me->sibling, parentWorldMat);

	me->wold_matrix = me->offset_matrix * me->bone_matrix;
}

//=============================================================================
// 処理:ﾎﾞｰﾝ配列の初期位置の設定
//=============================================================================
void Kim::CalcRelativeMat(KIM_BONE_DATA* me, D3DXMATRIX *parentoffsetMat)
{
	// 初期姿勢を親の初期姿勢を反映した初期姿勢の設定(親に対し相対的な場所へにする)
	if (me->child)
		CalcRelativeMat(me->child, &me->offset_matrix);
	if (me->sibling)
		CalcRelativeMat(me->sibling, parentoffsetMat);
	if (parentoffsetMat)
		me->init_matrix *= *parentoffsetMat;
}

//=============================================================================
// ﾏﾃﾘｱﾙの設定
//=============================================================================
void Kim::SetMaterial(D3DMATERIAL9 *material)
{
	if (draw_type_ == TYPE_ONE_MY || draw_type_ == TYPE_MULTI_MY || draw_type_ == TYPE_STATIC_MESH)
	{
		d3d_device_->SetVertexShaderConstantF(12, (float*)(&material->Diffuse), 1);
		d3d_device_->SetVertexShaderConstantF(13, (float*)(&material->Ambient), 1);
		d3d_device_->SetVertexShaderConstantF(14, (float*)(&material->Emissive), 1);
		d3d_device_->SetVertexShaderConstantF(15, (float*)(&material->Specular), 1);

	}
	else
	{
		d3d_device_->SetMaterial(material);
	}
}

//=============================================================================
// 複数ﾒｯｼｭ	自作ｼｪｰﾀﾞｰ用描画
//=============================================================================
void Kim::MultiMeshMyShader(void)
{
	// 現在のシェーダー情報の確保
	//LPDIRECT3DVERTEXSHADER9 current_vertex_shader;
	//LPDIRECT3DPIXELSHADER9 current_pixelshader;
	//d3d_device_->GetVertexShader(&current_vertex_shader);
	//d3d_device_->GetPixelShader(&current_pixelshader);

	// シェーダ設定
	//d3d_device_->SetVertexShader(vertex_shader_);
	//d3d_device_->SetPixelShader(pixel_shader_);

	// 送信する頂点情報の設定
	d3d_device_->SetVertexDeclaration(decl_);

	//// ﾋﾞｭｰ,ﾌﾟﾛｼﾞｪｸｼｮﾝの取得
	//D3DXMATRIX view, proj;
	//d3d_device_->GetTransform(D3DTS_VIEW, &view);
	//d3d_device_->GetTransform(D3DTS_PROJECTION, &proj);

	//D3DXMatrixTranspose(&view, &view);
	//D3DXMatrixTranspose(&proj, &proj);

	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&world,&world_);
	D3DXMatrixTranspose( &view, &view_ );
	D3DXMatrixTranspose(&projection,&projection_);

	// ﾜｰﾙﾄﾞ,ﾋﾞｭｰ,ﾌﾟﾛｼﾞｪｸｼｮﾝ,指向性ﾗｲﾄ情報の転送
	d3d_device_->SetVertexShaderConstantF(0, static_cast<const float*>(world), 4);
	d3d_device_->SetVertexShaderConstantF(4, static_cast<const float*>(view), 4);
	d3d_device_->SetVertexShaderConstantF(8, static_cast<const float*>(projection), 4);

	//// ﾄｩｰﾝﾏｯﾌﾟの設定
	//d3d_device_->SetTexture(1, toon_map);

	// 全ﾒｯｼｭの描画
	for (int i = 0; i < mesh_num_; i++)
	{
		// GPUに送信する行列の生成
		D3DXMATRIX *export_bone = new D3DXMATRIX[mesh_[i].bind_weight];
		for (int cnt = 0; cnt < mesh_[i].bind_weight; cnt++)
		{
			if (bone_num_ > mesh_[i].bind_index[cnt])
			{
				export_bone[cnt] = bone_[mesh_[i].bind_index[cnt]].wold_matrix;
				D3DXMatrixTranspose(&export_bone[cnt], &export_bone[cnt]);
			}
		}
		d3d_device_->SetVertexShaderConstantF(155, static_cast<const float*>(*export_bone), 4 * mesh_[i].bind_weight);

		SetMaterial(&mesh_[i].material_);
		d3d_device_->SetTexture(0, mesh_[i].texture_);
		d3d_device_->SetIndices(mesh_[i].index_buffer_);
		d3d_device_->SetStreamSource(0, mesh_[i].vertex_buffer_, 0, sizeof(VERTEX_KIM));	// 頂点ﾊﾞｯﾌｧをﾃﾞﾊﾞｲｽに関連付け

		d3d_device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh_[i].vertex_num_, 0, mesh_[i].index_num_ / 3);
		// 正規化したﾎﾞｰﾝ情報の削除
		delete[] export_bone;

	}

	// 前回のシェーダーに戻す
//	d3d_device_->SetVertexShader(current_vertex_shader);
//	d3d_device_->SetPixelShader(current_pixelshader);

}


//=============================================================================
// 処理:ｼｪｰﾀﾞｰのｺﾝﾊﾟｲﾙ
//=============================================================================
HRESULT Kim::CompileShader(void)
{
	// シェーダのコンパイルとシェーダ作成
	ID3DXBuffer *shader, *error;

	// 返り値用変数
	HRESULT res;

	if (bone_num_ != 0)
	{
		res = D3DXCompileShaderFromFile("resources/shader/skining_shader.hlsl", NULL, 0, "vs_main", "vs_3_0", 0, &shader, &error, 0);
	}
	else
	{
		draw_type_ = TYPE_STATIC_MESH;
		res = D3DXCompileShaderFromFile("resources/shader/static_fbx.hlsl", NULL, 0, "vs_main", "vs_3_0", 0, &shader, &error, 0);
	}

	if (FAILED(res)) {
		MessageBox(NULL, (LPSTR)error->GetBufferPointer(), NULL, 0);
		return E_FAIL;
	};

	d3d_device_->CreateVertexShader((const DWORD*)shader->GetBufferPointer(), &vertex_shader_);
	shader->Release();

	res = D3DXCompileShaderFromFile("resources/shader/skining_shader.hlsl", NULL, 0, "ps_main", "ps_3_0", 0, &shader, &error, 0);
	if (FAILED(res)) {
		MessageBox(NULL, (LPSTR)error->GetBufferPointer(), NULL, 0);
		return E_FAIL;
	};

	d3d_device_->CreatePixelShader((const DWORD*)shader->GetBufferPointer(), &pixel_shader_);
	shader->Release();

	D3DXCreateTextureFromFile(d3d_device_, "data/texture/mapping_textrue/toon_map.png", &toon_map);
	//toon_map = NULL ;

	return S_OK ;
}

//=============================================================================
// 処理:送信する頂点情報の設定
//=============================================================================
void Kim::CreateVertexDecl(void)
{
	// 頂点宣言
	D3DVERTEXELEMENT9 declAry[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
			{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			{ 0, 32, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0 },
			{ 0, 36, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
			{ 0, 52, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0 },
			D3DDECL_END()
	};

	d3d_device_->CreateVertexDeclaration(declAry, &decl_);
}


//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void Kim::SetAnime( const ANIME& anime )
{ 
	if( anime_ == anime )
	{
		return ;
	}

 	old_anime_ = anime_ ;

	anime_ = anime ;

	current_key_ = anime_data_[ NOW_ANIMETION ][ 0 ];

	animation_ = true ; 

	memset( &animation_play_ , 0 , sizeof( animation_play_ ) );
	animation_play_[ ( int )anime_ ] = true ;	// アニメーション終わり
}


// EOF
