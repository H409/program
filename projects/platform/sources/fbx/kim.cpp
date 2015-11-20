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

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
int anime_speed = 1;
float value_ = 0.0f;
float times_ = 15.0f;
int cursor_bone_ = 0;
int cursor_mesh_ = 0;
int anim_type_ = 0;
int anime_value = 1;
int all_vertex_num_ = 0;

LPSTR debug_string[4] =
{ "������Ұ���", "Y����]", "X����]", "Z����]" };
LPSTR type_string[2] =
{ "FBX", "�Ǝ��`��" };


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
	next_anime_ = 0;
	set_anime_ = 0;

	draw_type_ = TYPE_MULTI_MY;

	light_directional = D3DXVECTOR3(0.5f, -0.5f, 0.5f);
	D3DXVec3Normalize(&light_directional, &light_directional);

	D3DXMatrixIdentity(&world_);

	//--  �����ڰ�ܰ��p  --//
	all_vertex_num_ = 0;
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
	if (draw_type_ == TYPE_ONE_MY || draw_type_ == TYPE_MULTI_MY)
		return CompileShader();

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

#ifdef _DEBUG
	if (DebugUpdate() == false)
		return;
#endif

	if (!GetAsyncKeyState('Y') & 0x0001)
	{
		// �ް݂��Ȃ���΂������ཷ�ݸނ���ĂȂ�
		if (bone_ == NULL)
			return;

		// ��Ұ��݂������Ƃ��͑S�Ă��ް݂�P�ʍs��ɂ��Ƃ�
		if (bone_[cursor_bone_].anime_num == 0)
		{
			for (int i = 0; i < bone_num_; i++)
			{
				D3DXMatrixIdentity(&bone_[i].bone_matrix);
				bone_[i].bone_matrix *= bone_[i].init_matrix;
			}
			UpdateBone(bone_, &world_);
			return;
		}

		if (bone_->current_time == 1)
			next_anime_ = set_anime_;

	//	// ���ʂ̱�Ұ���
	//	for (int i = 0; i < bone_num_; i++)
	//	{
	//		// ������
	//		D3DXMatrixIdentity(&bone_[i].bone_matrix);

	//		// �ǐ������o�C�̂������؂�p��
	//		KIM_BONE_DATA *dest_bone = &bone_[i];
	//			
	//		// �������Ȃ��ꍇ�͂����炭��Ұ��ݖ����̂ŏ����p�����������Ď�
	//		if (dest_bone->anime[current_anime_].num_key == 0)
	//		{
	//			bone_[i].bone_matrix *= bone_[i].init_matrix;
	//			continue;
	//		}

	//		// �ǐ������o�C�̂������؂�p��
	//		int current_key = dest_bone->anime[current_anime_].current_key;
	//		int next_key = (dest_bone->anime[next_anime_].current_key + 1) % (dest_bone->anime[next_anime_].num_key);

	//		KIM_KEY_FRAME *cur_flame = &dest_bone->anime[current_anime_].keyframe[current_key];
	//		KIM_KEY_FRAME *next_flame;

	//		if (next_anime_ == current_anime_)
	//		{
	//			next_flame = &dest_bone->anime[next_anime_].keyframe[next_key];
	//		}
	//		else
	//		{
	//			next_flame = &dest_bone->anime[next_anime_].keyframe[0];
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

	//			if (current_anime_ == next_anime_)
	//			{
	//				dest_bone->anime[current_anime_].current_key++;

	//				if (dest_bone->anime[current_anime_].current_key >= dest_bone->anime[next_anime_].num_key)
	//				{
	//					dest_bone->anime[current_anime_].current_key = next_key;
	//					dest_bone->anime[current_anime_].current_key %= dest_bone->anime[next_anime_].num_key;
	//				}
	//			}
	//			else
	//			{
	//				dest_bone->anime[current_anime_].current_key = 0;
	//				dest_bone->anime[next_anime_].current_key = 0;

	//				if (i == bone_num_-1)
	//				{
	//					current_anime_ = next_anime_;
	//				}
	//			}
	//		}

	//		// ����i�߂�
	//		dest_bone->current_time += anime_speed;

	//}

		//for (int i = 0; i < bone_num_; i++)
		//{
		//	auto next_flame = bone_[i].anime[next_anime_].keyframe[1];

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
		for (int i = 0; i < bone_num_; i++)
		{
			// ������
			D3DXMatrixIdentity(&bone_[i].bone_matrix);

			// �ǐ������o�C�̂������؂�p��
			KIM_BONE_DATA *dest_bone = &bone_[i];
				
			//// �������Ȃ��ꍇ�͂����炭��Ұ��ݖ����̂ŏ����p�����������Ď�
			//if (dest_bone->anime[current_anime_].num_key == 0)
			//{
			//	bone_[i].bone_matrix *= bone_[i].init_matrix;
			//	continue;
			//}

			// �ǐ������o�C�̂������؂�p��
			int current_key = dest_bone->anime[current_anime_].current_key;
			int next_key = (dest_bone->anime[next_anime_].current_key + 1) % (dest_bone->anime[next_anime_].num_key);

			KIM_KEY_FRAME *cur_flame = &dest_bone->anime[current_anime_].keyframe[current_key];
			KIM_KEY_FRAME *next_flame;

			//if (next_anime_ == current_anime_)
			{
				next_flame = &dest_bone->anime[next_anime_].keyframe[next_key];
			}

			// ���ꂼ��̕ϊ������`���
			D3DXVECTOR3 scaling = cur_flame->scaling ;
			D3DXVECTOR3 translation = cur_flame->translation ;
			D3DXQUATERNION rotation = cur_flame->rotation ;

			// ���ꂼ��̍s��ϊ�
			D3DXMATRIX scl, rot, trans;
			D3DXMatrixScaling(&scl, scaling.x, scaling.y, scaling.z);
			D3DXMatrixRotationQuaternion(&rot, &rotation);
			D3DXMatrixTranslation(&trans, translation.x, translation.y, translation.z);

			// �s�񍇐�
			bone_[i].bone_matrix = scl * rot * trans * bone_[i].init_matrix;

			// �����ڰтɈړ�
			if (dest_bone->current_time >= next_flame->frame_chenge)
			{
				dest_bone->current_time = 0;

			//	if (current_anime_ == next_anime_)
				{
					dest_bone->anime[current_anime_].current_key++;

					if (dest_bone->anime[current_anime_].current_key >= dest_bone->anime[next_anime_].num_key)
					{
						dest_bone->anime[current_anime_].current_key = 31;		// 
						//dest_bone->anime[current_anime_].current_key %= dest_bone->anime[next_anime_].num_key;
					}
				}
			}

			// ����i�߂�
			dest_bone->current_time += anime_speed;
		}

		// ���W�̍X�V:�|���鏇�Ԃ� �q �~ �e 
		UpdateBone(bone_, &world_);

	}
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

#ifdef _DEBUG
	static bool _bone = false ;

	// ү���̕`��
	if (GetAsyncKeyState('B'))
	{
		_bone = !_bone ;
	}
#endif
	if( !GetAsyncKeyState('N') )
	{
		switch (draw_type_)
		{
		case TYPE_MULTI_MY:
			MultiMeshMyShader();
			break;

		case TYPE_STATIC_MESH:
			StaticMesh();
			break;
		}
	}
#ifdef _DEBUG
	
	if( _bone == true )
	{
		DrawBone();
	}
#endif

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
// 1ү��	���켪��ް�p�`��
//=============================================================================
void Kim::OneMeshMyShader(void)
{
}

//=============================================================================
// ����ү��	���켪��ް�p�`��
//=============================================================================
void Kim::MultiMeshMyShader(void)
{
	// ���݂̃V�F�[�_�[���̊m��
	LPDIRECT3DVERTEXSHADER9 current_vertex_shader;
	LPDIRECT3DPIXELSHADER9 current_pixelshader;
	d3d_device_->GetVertexShader(&current_vertex_shader);
	d3d_device_->GetPixelShader(&current_pixelshader);

	// �V�F�[�_�ݒ�
	d3d_device_->SetVertexShader(vertex_shader_);
	d3d_device_->SetPixelShader(pixel_shader_);

	// ���M���钸�_���̐ݒ�
	d3d_device_->SetVertexDeclaration(decl_);

	//// �ޭ�,��ۼު���݂̎擾
	//D3DXMATRIX view, proj;
	//d3d_device_->GetTransform(D3DTS_VIEW, &view);
	//d3d_device_->GetTransform(D3DTS_PROJECTION, &proj);

	//D3DXMatrixTranspose(&view, &view);
	//D3DXMatrixTranspose(&proj, &proj);

	D3DXMatrixTranspose( &view_, &view_ );
	D3DXMatrixTranspose( &projection_ , &projection_ );

	// ܰ���,�ޭ�,��ۼު����,�w����ײď��̓]��
	d3d_device_->SetVertexShaderConstantF(0, static_cast<const float*>(world_), 4);
	d3d_device_->SetVertexShaderConstantF(4, static_cast<const float*>(view_), 4);
	d3d_device_->SetVertexShaderConstantF(8, static_cast<const float*>(projection_), 4);
	d3d_device_->SetVertexShaderConstantF(16, static_cast<const float*>(light_directional), 4);

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
		d3d_device_->SetVertexShaderConstantF(18, static_cast<const float*>(*export_bone), 4 * mesh_[i].bind_weight);

		SetMaterial(&mesh_[i].material_);
		d3d_device_->SetTexture(0, mesh_[i].texture_);
		d3d_device_->SetIndices(mesh_[i].index_buffer_);
		d3d_device_->SetStreamSource(0, mesh_[i].vertex_buffer_, 0, sizeof(VERTEX_KIM));	// ���_�ޯ̧�����޲��Ɋ֘A�t��

		d3d_device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh_[i].vertex_num_, 0, mesh_[i].index_num_ / 3);
		// ���K�������ްݏ��̍폜
		delete[] export_bone;

	}

	// �O��̃V�F�[�_�[�ɖ߂�
	d3d_device_->SetVertexShader(current_vertex_shader);
	d3d_device_->SetPixelShader(current_pixelshader);

}

//=============================================================================
// 1ү��	�Œ輪��ް�p�`��
//=============================================================================
void Kim::OneMeshOriginShader(void)
{

}

//=============================================================================
// ����ү��	�Œ輪��ް�p�`��
//=============================================================================
void Kim::MultiMeshOriginShader(void)
{
}

//=============================================================================
// �ÓIү���̕`��
//=============================================================================
void Kim::StaticMesh(void)
{
	// ���݂̃V�F�[�_�[���̊m��
	LPDIRECT3DVERTEXSHADER9 current_vertex_shader;
	LPDIRECT3DPIXELSHADER9 current_pixelshader;
	d3d_device_->GetVertexShader(&current_vertex_shader);
	d3d_device_->GetPixelShader(&current_pixelshader);

	// �V�F�[�_�ݒ�
	d3d_device_->SetVertexShader(vertex_shader_);
	d3d_device_->SetPixelShader(pixel_shader_);

	// ���M���钸�_���̐ݒ�
	d3d_device_->SetVertexDeclaration(decl_);

	// �ޭ�,��ۼު���݂̎擾
	D3DXMATRIX view, proj;
	d3d_device_->GetTransform(D3DTS_VIEW, &view);
	d3d_device_->GetTransform(D3DTS_PROJECTION, &proj);

	D3DXMatrixTranspose(&view, &view);
	D3DXMatrixTranspose(&proj, &proj);

	// ܰ���,�ޭ�,��ۼު����,�w����ײď��̓]��
	d3d_device_->SetVertexShaderConstantF(0, static_cast<const float*>(world_), 4);
	d3d_device_->SetVertexShaderConstantF(4, static_cast<const float*>(view), 4);
	d3d_device_->SetVertexShaderConstantF(8, static_cast<const float*>(proj), 4);
	d3d_device_->SetVertexShaderConstantF(16, static_cast<const float*>(light_directional), 4);

	// ĩ��ϯ�߂̐ݒ�
	d3d_device_->SetTexture(1, toon_map);

	// �Sү���̕`��
	for (int i = 0; i < mesh_num_; i++)
	{
		SetMaterial(&mesh_[i].material_);
		d3d_device_->SetTexture(0, mesh_[i].texture_);
		d3d_device_->SetIndices(mesh_[i].index_buffer_);
		d3d_device_->SetStreamSource(0, mesh_[i].vertex_buffer_, 0, sizeof(VERTEX_KIM));	// ���_�ޯ̧�����޲��Ɋ֘A�t��
		d3d_device_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh_[i].vertex_num_, 0, mesh_[i].index_num_ / 3);

	}

	// �O��̃V�F�[�_�[�ɖ߂�
	d3d_device_->SetVertexShader(current_vertex_shader);
	d3d_device_->SetPixelShader(current_pixelshader);


}

//=============================================================================
// ����:�ް݂̕`��
//=============================================================================
void Kim::DrawBone(void)
{
	// �Œ輪��ނ̒��_�����ނ�؂�
	d3d_device_->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE);

	for (int i = 0; i < bone_num_; i++)
	{
		ID3DXMesh *boneObj;
		D3DXCreateCylinder(d3d_device_, 0.2f, 0.5f, 5.0f, 16, 1, &boneObj, 0);

		D3DMATERIAL9 material = { { 1.0f, 1.0f, 1.0f, 1.0f } }; material.Power = 10.0f;
		D3DLIGHT9 light = { D3DLIGHT_DIRECTIONAL, { 1.0f, 0.7f, 0.5f, 1.0f } };
		light.Direction = (D3DVECTOR)D3DXVECTOR3(1.0f, 1.0f, 1.0f);

		d3d_device_->SetLight(0, &light);
		d3d_device_->LightEnable(0, TRUE);
		d3d_device_->SetRenderState(D3DRS_LIGHTING, TRUE);
		d3d_device_->SetMaterial(&material);
		d3d_device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		d3d_device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		D3DXMATRIX boneObjRot;
		D3DXMatrixRotationY(&boneObjRot, D3DXToRadian(-90.0f));
		d3d_device_->SetTransform(D3DTS_WORLD, &(boneObjRot * bone_[i].bone_matrix));
		boneObj->DrawSubset(0);
		boneObj->Release();
	}
}

//=============================================================================
// ���ޯ�ޗp�֐�
//=============================================================================
bool Kim::DebugUpdate(void)
{
	bool return_data = true;

	//CDebugProc::Print("F5:�ēǂݍ���\n");
	//CDebugProc::Print("//--  ���b�V���n  --//\n");
	//CDebugProc::Print("�����_��:%d\n", all_vertex_num_);
	//CDebugProc::Print("�ŏ����_ x:%f y:%f z:%f\n", vertex_max_.x, vertex_max_.y, vertex_max_.z);
	//CDebugProc::Print("�ő咸�_ x:%f y:%f z:%f\n", vertex_min_.x, vertex_min_.y, vertex_min_.z);
	//CDebugProc::Print("P:��ݸނ�؂� O:ܲ԰�ڰ�\n");
	//CDebugProc::Print("//--  �J�����n  --//\n");
	//CDebugProc::Print("W,S:��ׂ̉��� Q,E:��ׂ̍��E��荞��\n");
	//CDebugProc::Print("R,F:��ׂ̍�������\n");
	//CDebugProc::Print("//--  �{�[���n  --//\n");
	//CDebugProc::Print("B:�ް݂̕`�� M:�ް݂̉ғ�\n");
	//CDebugProc::Print("���E:�I���ް݂̕ύX\n");
	//CDebugProc::Print("//--  ��Ұ��݌n  --//\n");
	//CDebugProc::Print("T,G:��Ұ��ݑ��x�̑���\n");
	//CDebugProc::Print("�㉺:Ӱ������߂̕ύX\n");

	////switch (draw_type_)
	////{
	////case TYPE_ONE_MY:
	////	CDebugProc::Print("1ү��	���켪��ް\n");
	////	break;
	////case TYPE_ONE_ORIGINE:
	////	CDebugProc::Print("1ү��	�Œ輪��ް\n");
	////	break;
	////case TYPE_MULTI_MY:
	////	CDebugProc::Print("����ү��	���켪��ް\n");
	////	break;
	////case TYPE_MULTI_ORIGINE:
	////	CDebugProc::Print("����ү��	�Œ輪��ް\n");
	////	break;
	////}
	//
	//if (bone_ != NULL)
	//{
	//	CDebugProc::Print("��Ұ��ݕύX:�����L�[\n");
	//	CDebugProc::Print("���݂̱��:%d ���x:%d\n", current_anime_, anime_speed);
	//	CDebugProc::Print("���݂̓�������:%s\n", debug_string[anim_type_]);
	//	CDebugProc::Print("���ڰѐ�:%d ����:%d\n", bone_[cursor_bone_].anime[current_anime_].current_key, bone_[cursor_bone_].current_time);
	//	CDebugProc::Print("�ްݐ�:%d ү����:%d\n", bone_num_, mesh_num_);
	//	CDebugProc::Print("���E:�I���ް݂̕ύX\n");
	//	CDebugProc::Print("���݂��ްݔԍ�:%d\n", cursor_bone_);
	//	CDebugProc::Print("���݂��ް�:%s\n", bone_[cursor_bone_].name);
	//	if (bone_[cursor_bone_].anime_num != 0)
	//	{
	//		CDebugProc::Print("���݂��ް݂̈ړ�: x:%f y:%f z:%f\n",
	//			bone_[cursor_bone_].anime[current_anime_].keyframe[bone_[cursor_bone_].anime[current_anime_].current_key].translation.x,
	//			bone_[cursor_bone_].anime[current_anime_].keyframe[bone_[cursor_bone_].anime[current_anime_].current_key].translation.y,
	//			bone_[cursor_bone_].anime[current_anime_].keyframe[bone_[cursor_bone_].anime[current_anime_].current_key].translation.z);
	//		CDebugProc::Print("���݂��ް݂̉�]: x:%e y:%e z:%e\n",
	//			bone_[cursor_bone_].anime[current_anime_].keyframe[bone_[cursor_bone_].anime[current_anime_].current_key].rotation.x,
	//			bone_[cursor_bone_].anime[current_anime_].keyframe[bone_[cursor_bone_].anime[current_anime_].current_key].rotation.y,
	//			bone_[cursor_bone_].anime[current_anime_].keyframe[bone_[cursor_bone_].anime[current_anime_].current_key].rotation.z);
	//	}

	//	if (GetAsyncKeyState('M'))
	//	{	// ���ޯ�ޗp
	//		value_ += 0.03f;
	//		float temp = D3DXToRadian(sinf(value_) * times_);

	//		for (int i = 0; i < bone_num_; i++)
	//		{
	//			D3DXMatrixIdentity(&bone_[i].bone_matrix);
	//			bone_[i].bone_matrix *= bone_[i].init_matrix;
	//			switch (anim_type_)
	//			{
	//			case 0:
	//				D3DXMatrixRotationYawPitchRoll(&bone_[cursor_bone_].bone_matrix, temp, temp, temp);
	//				break;
	//			case 1:
	//				D3DXMatrixRotationX(&bone_[cursor_bone_].bone_matrix, temp);
	//				break;
	//			case 2:
	//				D3DXMatrixRotationY(&bone_[cursor_bone_].bone_matrix, temp);
	//				break;
	//			case 3:
	//				D3DXMatrixRotationZ(&bone_[cursor_bone_].bone_matrix, temp);
	//				break;
	//			default:
	//				break;
	//			}
	//			bone_[cursor_bone_].bone_matrix *= bone_[cursor_bone_].init_matrix;
	//		}
	//		CDebugProc::Print("����������:%f\n", temp);
	//		UpdateBone(bone_, &world_);
	//		return_data = false;
	//	}
	//}

	//d3d_device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	//d3d_device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);				// ���ʂ��J�����O

	//if (GetAsyncKeyState('P'))
	//{
	//	d3d_device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O
	//}
	//if (GetAsyncKeyState('O'))
	//{
	//	d3d_device_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);				// ���ʂ��J�����O
	//}

	//if (GetAsyncKeyState('T') & 0x0001)
	//	anime_speed++;
	//if (GetAsyncKeyState('G') & 0x0001)
	//	anime_speed--;
	//
	//if (GetAsyncKeyState(VK_UP) & 0x0001)
	//	anim_type_++;
	//if (GetAsyncKeyState(VK_DOWN) & 0x0001)
	//	anim_type_--;

	//if (!GetAsyncKeyState(VK_LSHIFT))
	//{
	//	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	//		cursor_bone_++;
	//	if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	//		cursor_bone_--;
	//}
	//else
	//{
	//	CDebugProc::Print("���E:�I��ү���̕ύX\n");
	//	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	//		cursor_mesh_++;
	//	if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	//		cursor_mesh_--;
	//}

	//if (cursor_bone_ < 0)
	//	cursor_bone_ = bone_num_ - 1;
	//if (cursor_bone_ == bone_num_)
	//	cursor_bone_ = 0;

	//if (cursor_mesh_ < 0)
	//	cursor_mesh_ = mesh_num_ - 1;
	//if (cursor_mesh_ == mesh_num_)
	//	cursor_mesh_ = 0;

	//if (anim_type_ < 0)
	//	anim_type_ = 3;
	//if (anim_type_ > 3)
	//	anim_type_ = 0;

	//for (int i = 48; i < 58; i++)
	//{
	//	if (GetAsyncKeyState(i))
	//	{
	//		set_anime_ = i - 48;
	//	}
	//}

	//if (bone_ != NULL)
	//{
	//	if (set_anime_ >= bone_->anime_num)
	//	{
	//		set_anime_ = bone_->anime_num - 1;
	//	}

	//}

	return return_data;
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

//=============================================================================
// ����:����
//=============================================================================
Kim* Kim::Create(LPDIRECT3DDEVICE9 d3d_device, const char* file_name)
{
	Kim* obj = new Kim(d3d_device);
	obj->Load(file_name);

	return obj;

}

// EOF
