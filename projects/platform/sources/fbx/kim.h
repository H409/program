#ifndef _SCENE_KIM_H_
#define _SCENE_KIM_H_
//=============================================================================
//
// FBX��ϊ������Ǝ��`�����f������ : scene_kim.h
// Author : Kenji IIZUKA
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "dx9_device.h"

//*****************************************************************************
// �\����
//*****************************************************************************
// ���b�V�����\����
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
// ���_���\����
struct VERTEX_KIM
{
	D3DXVECTOR3 coord;//���_
	D3DXVECTOR3 nor;
	D3DXVECTOR2 tex;
	D3DCOLOR diffuse;
	float weight[4];//�d��
	DWORD bone_index;//���_�C���f�b�N�X(���ʃo�C�g�����)
};

// ���ڰя��\����
struct KIM_KEY_FRAME
{
	int frame_chenge;			// �����ڰт܂ł̒���
	D3DXVECTOR3 translation;	// ���s�ړ�
	D3DXQUATERNION rotation;	// �̨ݏ��
	D3DXVECTOR3 scaling;		// �g�k���

};

struct KIM_ANIMATION_DATA{
	KIM_KEY_FRAME* keyframe;	// ���ڰя��
	int num_key;				// ����
	int current_key;			// ���ݷ�

	KIM_ANIMATION_DATA(){
		keyframe = NULL;
		num_key = 0;
		current_key = 0;
	}
};

// �ްݏ��\����
struct KIM_BONE_DATA
{
	char name[64];

	int id;
	KIM_BONE_DATA* child;
	KIM_BONE_DATA* sibling;

	D3DXMATRIX offset_matrix;	// ������Ԃ̃��[���h�}�g���b�N�X�̋t�s��
	D3DXMATRIX init_matrix;		// �����p��
	D3DXMATRIX bone_matrix;		// ���[�J���̕ϊ��s��(������GPU�ɑ���)
	D3DXMATRIX wold_matrix;		// ���[���h��̕ϊ��s��

	int current_time;			// ���݂̎���
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
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���Q��
//*****************************************************************************

//=============================================================================
// FBX��ϊ������Ǝ��`�����f���N���X
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

	// ����:�R���X�g���N�^
	Kim(LPDIRECT3DDEVICE9 d3d_device);
		
	// ����:�f�X�g���N�^
	~Kim(void);

	// ����:�ǂݍ���
	HRESULT Load(const char* file_name);

	// ����:�I��
	void Uninit(void);
	
	// ����:�X�V
	void Update(void);

	// ����:�`��
	void Draw(void);

	// ����:���
	void Release(void);

	// ����:ܰ�����ظ��̾��
	void SetWorld(D3DXMATRIX world){ world_ = world; };

	void SetView( D3DXMATRIX *view ){ view_ = *view ; }
	void SetProjection( D3DXMATRIX *projection ){ projection_ = *projection ; }

	LPDIRECT3DTEXTURE9 GetTexture( int i ){ return mesh_[ i ].texture_ ; }

	bool GetAnimarionPlay( int i ){ return animation_play_[ i ]; }	// true�ŏI����Ă���

	void SetOldKey( int i ){ old_key_ = i ; }
	void SetAnimeID( int id ){ anime_ID_ = id ; }
	void SetAnime( int start , int end , int repeat );
	void SetOldAnime( int start , int end , int repeat );

private:
	// ����:����ް�̺��߲�
	HRESULT CompileShader(void);

	// ����:�ްݲ��ޯ���̐��K��
	void BoneIndexNormalize(int mesh_idx,VERTEX_KIM* vtx);

	// ����:���M���钸�_���̐ݒ�
	void CreateVertexDecl(void);

	// ����:�{�[���̍X�V(�s��ϊ�)
	void UpdateBone(KIM_BONE_DATA* me, D3DXMATRIX *parentWorldMat);

	// ����:�ްݔz��̏����ʒu�̐ݒ�
	void CalcRelativeMat(KIM_BONE_DATA* me, D3DXMATRIX *parentoffsetMat);

	// ��رق̐ݒ�
	void SetMaterial(D3DMATERIAL9 *material);

	// ����ү��	���켪��ް�p�`��
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

	int current_anime_;	// ���݂̱�Ұ��ݔԍ�
	int next_anime_;	// ���̱�Ұ��ݔԍ�

	int set_anime_;		// ���̱�Ұ��ݽ���

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
	bool animation_play_[ 5 ];	// �V�����A�j���[�V�����I�������

	int anime_data_[ 3 ];
	int old_anime_data_[ 3 ];

};

#endif // _SCENE_KIM_H_
// EOF
