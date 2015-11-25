//-----------------------------------------------------------------------------
//
// �v���C���[���� : player.h
// Author : sembon takanori
//
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_

//------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------
#include "../object/object.h"
#include "../fbx/kim.h"

//------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �\����
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �v���g�^�C�v�錾
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �O���Q��
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// �N���X
//------------------------------------------------------------------------
class Player : public Object
{
public : 
	enum STATE
	{
		NONE = -1 ,		// �Ȃ�
		WAIT ,			// �ҋ@
		WALK ,			// ����
		DASH ,			// ����
		DIG ,			// �@��
		SHOOT ,			// ����
		AIM ,			// �G�C��
		DOWN ,			// �_�E��
		MAX
	};

	Player( LPDIRECT3DDEVICE9 pDevice );		// �R���X�g���N�^
	~Player();									// �f�X�g���N�^

	void Init( float3 pos );		// ������
	void Update( void );				// �X�V
	void Draw( void );					// �`��
	void Uninit( void );				// �I��

	//--  kim�̃|�C���^  --//
	Kim* GetKimPointer( void ){ return pKim_ ; }
	
	STATE GetState( void ){ return state_ ; }
	STATE GetAnime( void ){ return anime_ ; }

	void SetID( int id ){ ID_ = id ; }
	int GetID( void ){ return ID_ ; }

	const float3& GetOldPosition( void ){ return old_position_ ; }
	void SetOldPosition( const float3& pos ){ old_position_ = pos ; }

	void SetMove(const float3& in_move) { move_ = in_move; }
	const float3& GetMove(void) { return move_; }
	//--  �ݒ�  --//
	void SetCameraVector( const float3& vec ){ camera_vector_ = vec ; }

	//--  �C���X�^���X����  --//
	//static Player* Create( LPDIRECT3DDEVICE9 pDevice , float3 pos );

private : 
	LPDIRECT3DDEVICE9 pDevice_ ;
	Kim* pKim_ ;

	float3 camera_vector_ ;		// �J��������
	float3 move_ ;				// �ړ���
	float3 speed_ ;				// ���x
	float3 rotDest_ ;			// �ړI�̌���
	float3 old_position_ ;		// �O�̈ʒu

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