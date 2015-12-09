//=============================================================================
//
// FBX��ϊ������Ǝ��`�����f������ : scene_kim.cpp
// Author : Kenji IIZUKA
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "kim.h"
#include "system/win_system.h"
#include "develop_tool/develop_tool.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int Kim::anime_data_[][ 3 ] = { //--  �����`���[  --//
								{ 31  , 60  , 0 } ,		// ���o��
								{ 61  , 150 , 1 } ,		// �ҋ@
								{ 151 , 180 , 1 } ,		// ����
								{ 181 , 240 , 0 } ,		// �s��
								{ 241 , 300 , 0 } ,		// �_���[�W

								//--  �V���b�g�K��  --//
								{ 331 , 360 , 0 } ,		// ���o��
								{ 361 , 450 , 1 } ,		// �ҋ@
								{ 451 , 480 , 1 } ,		// ����
								{ 481 , 510 , 0 } ,		// �s��
								{ 511 , 570 , 0 } ,		// �_���[�W

								//--  �N��  --//
								{ 601 , 630 , 0 } ,		// ���o��
								{ 631 , 720 , 1 } ,		// �ҋ@
								{ 721 , 750 , 1 } ,		// ����
								{ 751 , 810 , 0 } ,		// �s��
								{ 811 , 870 , 0 } };	// �_���[�W

//=============================================================================
// ���� : �R���X�g���N�^
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

	//--  �����ڰ�ܰ��p  --//
//	all_vertex_num_ = 0;

	old_anime_ = ANIME::WAIT ;
	anime_ = ANIME::WAIT ;
	wepon_ = WEAPON::GUN ;
	current_key_ = anime_data_[ NOW_ANIMETION ][ 0 ];
	animation_ = true ;

	memset( &animation_play_ , 0 , sizeof( animation_play_ ) );
}

//=============================================================================
// ���� : �f�X�g���N�^
//=============================================================================
Kim::~Kim( void )
{
}

//=============================================================================
// ���� : ����������
//=============================================================================
HRESULT Kim::Load(const char* file_name)
{
	// ̧�ك|�C���^
	FILE *file = NULL;

	// ̧�ٓǂݍ���(���s������I��)
	file = fopen(file_name, "rb");
	if (file == NULL)
		return true;

	// �擪�ɖ߂�
	fseek(file, 0, SEEK_SET);

	// ү�����ǂݍ���
	fread(&mesh_num_, sizeof(int), 1, file);

	// �ްݐ��ǂݍ���
	fread(&bone_num_, sizeof(int), 1, file);

	// ү��������������
	mesh_ = new KIM_MESH_DATA[mesh_num_];

	// ү�����̓ǂݍ���
	for (int i = 0; i < mesh_num_; i++)
	{
		// ���_���̓ǂݍ���
		fread(&mesh_[i].vertex_num_, sizeof(int), 1, file);

		// ���_�����O�Ȃ玟�̃��b�V����
		if (mesh_[i].vertex_num_ == 0)
			continue;

		// ���ޯ�����̓ǂݍ���
		fread(&mesh_[i].index_num_, sizeof(int), 1, file);

		// ø������̓ǂݍ���
		fread(&mesh_[i].texture_filename_, sizeof(char), 128, file);

		// ��رق̊l��
		fread(&mesh_[i].material_, sizeof(D3DMATERIAL9), 1, file);

		// �ި̰�ނ̃���0�̎�,��񔲂��̉\�������邽��,�S����1������
		if (mesh_[i].material_.Diffuse.a == 0.0f)
			mesh_[i].material_.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�o�b�t�@�̐���
		d3d_device_->CreateVertexBuffer(mesh_[i].vertex_num_ * sizeof(VERTEX_KIM), D3DUSAGE_SOFTWAREPROCESSING, NULL, D3DPOOL_MANAGED, &mesh_[i].vertex_buffer_, NULL);

		// ���_���̓ǂݍ��ݗp
		VERTEX_KIM* vtx;

		// ���_�o�b�t�@�̉��
		mesh_[i].vertex_buffer_->Lock(0, 0, (void**)&vtx, 0);

		// ���_���̓ǂݍ���
		fread(vtx, sizeof(VERTEX_KIM), mesh_[i].vertex_num_, file);

		// ���_���̃J�E���g
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

		// �ްݲ��ޯ���̐��K��
		if (draw_type_ > 1 && bone_num_ != 0)
			BoneIndexNormalize(i, vtx);

		// ���_�ޯ̧�̱�ۯ�
		mesh_[i].vertex_buffer_->Unlock();

		// ���ޯ���o�b�t�@�̐���
		if (FAILED(d3d_device_->CreateIndexBuffer(mesh_[i].index_num_ * sizeof(DWORD), D3DUSAGE_SOFTWAREPROCESSING, D3DFMT_INDEX32, D3DPOOL_MANAGED, &mesh_[i].index_buffer_, NULL)))
			MessageBox(NULL, "���ޯ���ޯ̧�̐����Ɏ��s���܂���", "���_�ޯ̧�̐����Ɏ��s���܂���", MB_OK);

		// index���̓ǂݍ���
		DWORD* workIndex(nullptr);
		mesh_[i].index_buffer_->Lock(0, 0, (void**)&workIndex, 0);

		// ���ޯ���ԍ�
		fread(workIndex, sizeof(DWORD), mesh_[i].index_num_, file);

		// ���ޯ���ޯ̧�̉��
		if (FAILED(mesh_[i].index_buffer_->Unlock()))
			MessageBox(NULL, "���ޯ���ޯ̧�̉���Ɏ��s���܂���", "���_�ޯ̧�̐����Ɏ��s���܂���", MB_OK);

		// ø����̐���
		D3DXCreateTextureFromFile(d3d_device_, mesh_[i].texture_filename_, &mesh_[i].texture_);
		//D3DXCreateTextureFromFile(d3d_device_, "resources/texture/ZZI_S_texture.jpg", &mesh_[i].texture_);
	}

	// �ްݏ��̓����ĂȂ����ق̏ꍇ�͓ǂݍ��܂Ȃ�
	if (bone_num_ != 0)
	{
		// �ް݂̐���
		bone_ = new KIM_BONE_DATA[bone_num_];
		int *chile_id = new int[bone_num_];
		int *sibling_id = new int[bone_num_];

		// �ްݏ��ǂݍ���
		for (int i = 0; i < bone_num_; i++)
		{
			bone_[i].anime_num = 1;
			//bone_[i].anime = new KIM_ANIMATION_DATA[bone_[i].anime_num];

			// �{�[����
			fread(bone_[i].name, sizeof(char), 64, file);
			// �{�[��ID
			fread(&bone_[i].id, sizeof(int), 1, file);
			// �q��ID
			fread(&chile_id[i], sizeof(int), 1, file);
			// �Z���ID
			fread(&sibling_id[i], sizeof(int), 1, file);
			// �����p����ظ�
			fread(&bone_[i].init_matrix, sizeof(D3DXMATRIX), 1, file);
			// �̾����ظ�
			fread(&bone_[i].offset_matrix, sizeof(D3DXMATRIX), 1, file);

			// ��Ұ��ݐ�
			fread(&bone_[i].anime_num, sizeof(int), 1, file);

			// ��Ұ��݂̐���
			bone_[i].anime = new KIM_ANIMATION_DATA[bone_[i].anime_num];

			// ��Ұ��݂̓ǂݍ���
			for (int anime_id = 0; anime_id < bone_[i].anime_num; anime_id++)
			{
				// �ő巰��
				fread(&bone_[i].anime[anime_id].num_key, sizeof(int), 1, file);

				// ���ڰт̐���
				bone_[i].anime[anime_id].keyframe = new KIM_KEY_FRAME[bone_[i].anime[anime_id].num_key];

				// ���ڰт̓ǂݍ���
				fread(bone_[i].anime[anime_id].keyframe, sizeof(KIM_KEY_FRAME), bone_[i].anime[anime_id].num_key, file);
			}
		}

		// �e�q�֌W�̐���
		for (int i = 0; i < bone_num_; i++)
		{
			// �e�q�֌W�̍\�z
			if (chile_id[i] >= 0)
				bone_[i].child = &bone_[chile_id[i]];
			if (sibling_id[i] >= 0)
				bone_[i].sibling = &bone_[sibling_id[i]];
		}

		// ۰��ID���̉��
		delete[] chile_id;
		delete[] sibling_id;

		// �ް݂�e�ɑ΂��Ă̑��Έʒu�Ɉړ�
		CalcRelativeMat(bone_, 0);
	}

	// �ǂݍ��݂̏I��
	fclose(file);

	// ���M���钸�_���̐ݒ�
	CreateVertexDecl();

	// �ꖇү���̒萔ڼ޽��𒴂���
	if (bone_num_ > BONE_MAX && draw_type_ == TYPE_ONE_MY)
	{
		MessageBox(NULL, "�ő咸�_���𒴂��܂���", "�ő咸�_���𒴂��܂���", MB_OK);
		return E_FAIL;
	}

	// ����ް�̺��߲�
	//if (draw_type_ == TYPE_ONE_MY || draw_type_ == TYPE_MULTI_MY)
		//return CompileShader();

	return S_OK ;
}

//=============================================================================
// ���� : �I������
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

	// ү�����̉��
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

	// �ްݏ��̉��
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
// ����:�X�V
//=============================================================================
void Kim::Update(void)
{

	//if (!GetAsyncKeyState('Y') & 0x0001)
	{
		//// �ް݂��Ȃ���΂������ཷ�ݸނ���ĂȂ�
		//if (bone_ == NULL)
		//	return;

		//// ��Ұ��݂������Ƃ��͑S�Ă��ް݂�P�ʍs��ɂ��Ƃ�
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

	//	// ���ʂ̱�Ұ���
	//	for (int i = 0; i < bone_num_; i++)
	//	{
	//		// ������
	//		D3DXMatrixIdentity(&bone_[i].bone_matrix);

	//		// �ǐ������o�C�̂������؂�p��
	//		KIM_BONE_DATA *dest_bone = &bone_[i];
	//			
	//		// �������Ȃ��ꍇ�͂����炭��Ұ��ݖ����̂ŏ����p�����������Ď�
	//		if (dest_bone->anime[ 0 ].num_key == 0)
	//		{
	//			bone_[i].bone_matrix *= bone_[i].init_matrix;
	//			continue;
	//		}

	//		// �ǐ������o�C�̂������؂�p��
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

	//		// ���`��ԂɎg�����Ԃ̌v�Z
	//		float t = (float)(dest_bone->current_time) / (float)next_flame->frame_chenge;

	//		// ���ꂼ��̕ϊ������`���
	//		D3DXVECTOR3 scaling = (1.0f - t)*cur_flame->scaling + (t * next_flame->scaling);
	//		D3DXVECTOR3 translation = (1.0f - t)*cur_flame->translation + (t * next_flame->translation);
	//		D3DXQUATERNION rotation = (1.0f - t)*cur_flame->rotation + (t * next_flame->rotation);

	//		// ���ꂼ��̍s��ϊ�
	//		D3DXMATRIX scl, rot, trans;
	//		D3DXMatrixScaling(&scl, scaling.x, scaling.y, scaling.z);
	//		D3DXMatrixRotationQuaternion(&rot, &rotation);
	//		D3DXMatrixTranslation(&trans, translation.x, translation.y, translation.z);

	//		// �s�񍇐�
	//		bone_[i].bone_matrix = scl * rot * trans * bone_[i].init_matrix;

	//		// �����ڰтɈړ�
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

	//		// ����i�߂�
	//		dest_bone->current_time += anime_speed;

	//}

		//for (int i = 0; i < bone_num_; i++)
		//{
		//	auto next_flame = bone_[i].anime[ 0 ].keyframe[1];

		//	// ���ꂼ��̕ϊ������`���
		//	D3DXVECTOR3 scaling = next_flame.scaling;
		//	D3DXVECTOR3 translation = next_flame.translation;
		//	D3DXQUATERNION rotation = next_flame.rotation;

		//	// ���ꂼ��̍s��ϊ�
		//	D3DXMATRIX scl, rot, trans;
		//	D3DXMatrixScaling(&scl, scaling.x, scaling.y, scaling.z);
		//	D3DXMatrixRotationQuaternion(&rot, &rotation);
		//	D3DXMatrixTranslation(&trans, translation.x, translation.y, translation.z);

		//	// �s�񍇐�
		//	bone_[i].bone_matrix = scl * rot * trans * bone_[i].init_matrix;
		//}

		// ���ʂ̱�Ұ���
		for( int i = 0 ; i < bone_num_ ; i++ )
		{
			// ������
			D3DXMatrixIdentity( &bone_[ i ].bone_matrix );

			// �ǐ������o�C�̂������؂�p��
			KIM_BONE_DATA *dest_bone = &bone_[ i ];
				
			//// �������Ȃ��ꍇ�͂����炭��Ұ��ݖ����̂ŏ����p�����������Ď�
			//if (dest_bone->anime[ 0 ].num_key == 0)
			//{
			//	bone_[i].bone_matrix *= bone_[i].init_matrix;
			//	continue;
			//}

			//dest_bone->anime[ 0 ].current_key = 1 ;
			//dest_bone->anime[ 0 ].num_key = 60 ;

			// �ǐ������o�C�̂������؂�p��
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

			// ���ꂼ��̕ϊ������`���
			D3DXVECTOR3 scaling = cur_flame->scaling ;
			D3DXVECTOR3 translation = cur_flame->translation ;
			D3DXQUATERNION rotation = cur_flame->rotation ;

			// ���ꂼ��̍s��ϊ�
			D3DXMATRIX scl , rot , trans ;
			D3DXMatrixScaling( &scl , scaling.x , scaling.y , scaling.z );
			D3DXMatrixRotationQuaternion( &rot , &rotation );
			D3DXMatrixTranslation( &trans , translation.x , translation.y , translation.z );

			// �s�񍇐�
			bone_[ i ].bone_matrix = scl * rot * trans * bone_[ i ].init_matrix ;

			// �����ڰтɈړ�
			//if( dest_bone->current_time >= 1 )
			{
				//dest_bone->current_time = 0;

			//	if ( 0  ==  0 )
				{
					auto a = NOW_ANIMETION ;
					auto b = anime_data_[ NOW_ANIMETION ][ 1 ] ;

					if( current_key_ >= anime_data_[ NOW_ANIMETION ][ 1 ] )
					{
						animation_play_[ ( int )anime_ ] = false ;	// �A�j���[�V�����I���

						//--  ���s�[�g����Ȃ�  --//
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

			/// ����i�߂�
			//dest_bone->current_time += anime_speed ;
		}

		//if( animation_ == true )
		{
			current_key_++;
		}


		// ���W�̍X�V:�|���鏇�Ԃ� �q �~ �e 
		auto world = world_;
		D3DXMatrixIdentity(&world);
		UpdateBone( bone_ , &world);
	}

	DEVELOP_DISPLAY( "current_key_ : %d\n" , current_key_ );

}

//=============================================================================
// ����:�{�[���̍X�V(�s��ϊ�)
//=============================================================================
void Kim::Draw(void)
{
	LPDIRECT3DVERTEXDECLARATION9 before_decl;
	d3d_device_->GetVertexDeclaration(&before_decl);

	// ���M���钸�_���̐ݒ�
	d3d_device_->SetVertexDeclaration(decl_);

	MultiMeshMyShader();

	d3d_device_->SetVertexDeclaration(before_decl);
}

//=============================================================================
// ����:���
//=============================================================================
void Kim::Release(void)
{
	Uninit();
	delete this;
}

//=============================================================================
// ����:�ްݲ��ޯ���̐��K��
//=============================================================================
void Kim::BoneIndexNormalize(int mesh_idx, VERTEX_KIM* vtx)
{
	//FILE *normalize_index = NULL;
	//normalize_index = fopen("data/log/normalize_index.txt", "w");

	// �ްݲ��ޯ������������
	int *bone_index_data = new int[mesh_[mesh_idx].vertex_num_ * 4];

	//fprintf(normalize_index, "��������index\n");
	// ���ޯ������int�^�ɂ��Ď����Ă���
	for (int idx_cnt = 0; idx_cnt < mesh_[mesh_idx].vertex_num_; idx_cnt++)
	{
		bone_index_data[0 + idx_cnt * 4] = (vtx[idx_cnt].bone_index & 0x000000ff);
		bone_index_data[1 + idx_cnt * 4] = (vtx[idx_cnt].bone_index & 0x0000ff00) >> 8;
		bone_index_data[2 + idx_cnt * 4] = (vtx[idx_cnt].bone_index & 0x00ff0000) >> 16;
		bone_index_data[3 + idx_cnt * 4] = (vtx[idx_cnt].bone_index & 0xff000000) >> 24;

		// �Ή����ޯ����0�̏ꍇ��-1�������ɗ�O����
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

	//fprintf(normalize_index, "��������weight\n");
	for (int idx_cnt = 0; idx_cnt < mesh_[mesh_idx].vertex_num_; idx_cnt++)
	{
		//fprintf(normalize_index, "[0]:%f   [1]:%f   [2]:%f   [3]:%f\n"
		//	, vtx[idx_cnt].weight[0]
		//	, vtx[idx_cnt].weight[1]
		//	, vtx[idx_cnt].weight[2]
		//	, vtx[idx_cnt].weight[3]);
	}
	// ��Œ��_���ɓ������ޯ��
	int *push_index = new int[bone_num_];
	memset(push_index, 0, sizeof(int) * bone_num_);

	// ����ү���Ɋ֘A�t������Ă�A���ޯ���Ƃ��̐��̏K��
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

	// �֘A�t��������ޯ���ɓo�^
	mesh_[mesh_idx].bind_index = new int[mesh_[mesh_idx].bind_weight];
	for (int j = 0; j < mesh_[mesh_idx].bind_weight; j++)
	{
		if (push_index[j] == -1)
			push_index[j] = 0;
		mesh_[mesh_idx].bind_index[j] = push_index[j];
	}

	// �����������e��K��
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

	// ۰�ُ��̍폜
	delete[] bone_index_data;
	delete[] push_index;

	//fclose(normalize_index);
}


//=============================================================================
// ����:�{�[���̍X�V(�s��ϊ�)
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
// ����:�ްݔz��̏����ʒu�̐ݒ�
//=============================================================================
void Kim::CalcRelativeMat(KIM_BONE_DATA* me, D3DXMATRIX *parentoffsetMat)
{
	// �����p����e�̏����p���𔽉f���������p���̐ݒ�(�e�ɑ΂����ΓI�ȏꏊ�ւɂ���)
	if (me->child)
		CalcRelativeMat(me->child, &me->offset_matrix);
	if (me->sibling)
		CalcRelativeMat(me->sibling, parentoffsetMat);
	if (parentoffsetMat)
		me->init_matrix *= *parentoffsetMat;
}

//=============================================================================
// ��رق̐ݒ�
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
// ����ү��	���켪��ް�p�`��
//=============================================================================
void Kim::MultiMeshMyShader(void)
{
	// ���݂̃V�F�[�_�[���̊m��
	//LPDIRECT3DVERTEXSHADER9 current_vertex_shader;
	//LPDIRECT3DPIXELSHADER9 current_pixelshader;
	//d3d_device_->GetVertexShader(&current_vertex_shader);
	//d3d_device_->GetPixelShader(&current_pixelshader);

	// �V�F�[�_�ݒ�
	//d3d_device_->SetVertexShader(vertex_shader_);
	//d3d_device_->SetPixelShader(pixel_shader_);

	// ���M���钸�_���̐ݒ�
	d3d_device_->SetVertexDeclaration(decl_);

	//// �ޭ�,��ۼު���݂̎擾
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

	// ܰ���,�ޭ�,��ۼު����,�w����ײď��̓]��
	d3d_device_->SetVertexShaderConstantF(0, static_cast<const float*>(world), 4);
	d3d_device_->SetVertexShaderConstantF(4, static_cast<const float*>(view), 4);
	d3d_device_->SetVertexShaderConstantF(8, static_cast<const float*>(projection), 4);

	//// ĩ��ϯ�߂̐ݒ�
	//d3d_device_->SetTexture(1, toon_map);

	// �Sү���̕`��
	for (int i = 0; i < mesh_num_; i++)
	{
		// GPU�ɑ��M����s��̐���
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
		d3d_device_->SetStreamSource(0, mesh_[i].vertex_buffer_, 0, sizeof(VERTEX_KIM));	// ���_�ޯ̧�����޲��Ɋ֘A�t��

		d3d_device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh_[i].vertex_num_, 0, mesh_[i].index_num_ / 3);
		// ���K�������ްݏ��̍폜
		delete[] export_bone;

	}

	// �O��̃V�F�[�_�[�ɖ߂�
//	d3d_device_->SetVertexShader(current_vertex_shader);
//	d3d_device_->SetPixelShader(current_pixelshader);

}


//=============================================================================
// ����:����ް�̺��߲�
//=============================================================================
HRESULT Kim::CompileShader(void)
{
	// �V�F�[�_�̃R���p�C���ƃV�F�[�_�쐬
	ID3DXBuffer *shader, *error;

	// �Ԃ�l�p�ϐ�
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
// ����:���M���钸�_���̐ݒ�
//=============================================================================
void Kim::CreateVertexDecl(void)
{
	// ���_�錾
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
	animation_play_[ ( int )anime_ ] = true ;	// �A�j���[�V�����I���
}


// EOF
