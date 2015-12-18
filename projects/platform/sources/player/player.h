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
#define NOW_ANIMETION ( int )wepon_ * ( int )ANIME::MAX + ( int )anime_
#define OLD_ANIMETION ( int )wepon_ * ( int )ANIME::MAX + ( int )old_anime_

	enum class STATE
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

	enum class WEAPON
	{
		LAUNCHER = 0 ,
		GUN ,
		HOE ,
		MAX
	};

	enum class ANIME
	{
		NONE = -1 ,		// �Ȃ�
		TAKE_OUT ,		// ���o��
		WAIT ,			// �ҋ@
		WALK ,			// ����
		ACTION ,		// �s��
		DAMAGE ,		// �_���[�W
		//DASH ,		// ���� 

		MAX
	};

	Player( LPDIRECT3DDEVICE9 pDevice );		// �R���X�g���N�^
	~Player();									// �f�X�g���N�^

	void Init( float3 pos );			// ������
	void Update( void );				// �X�V
	void Draw( void );					// �`��
	void Uninit( void );				// �I��

	//--  kim�̃|�C���^  --//
	Kim* GetKimPointer( void ){ return pKim_ ; }
	
	STATE GetState( void ){ return state_ ; }

	void SetID( const int& id ){ ID_ = id ; }
	int GetID( void ){ return ID_ ; }

	const float3& GetOldPosition( void ){ return old_position_ ; }
	void SetOldPosition( const float3& pos ){ old_position_ = pos ; }

	void SetMove(const float3& in_move) { move_ = in_move; }
	const float3& GetMove(void) { return move_; }
	
	//--  �ݒ�  --//
	void SetCameraVector( const float3& vec ){ camera_vector_ = vec ; }

	ANIME GetAnime( void ){ return anime_ ; }
	void SetAnime( const ANIME& anime );

	ANIME GetOldAnime( void ){ return anime_ ; }
	void SetOldAnime( const ANIME& anime ){ old_anime_ = anime ; };

	WEAPON GetWepon( void ){ return wepon_ ; };
	void SetWepon( const WEAPON& wepon ){ wepon_ = wepon ; };

	//void SetActionAnimationEnd( const int& id ){ ID_ = id ; }
	bool GetActionAnimationEnd( void ){ return action_animation_end_ ; }
	bool GetAction( void ){ return action_ ; }
	//void SetAction( bool b ){ action_ = b ; }

	bool GetHit( void ){ return hit_ ; }
	void SetHit( bool b ){ hit_ = b ; }

	float GetCameraRotY( void ){ return camera_rot_y ; }

private : 
	static int player_anime_data_[][ 3 ];

	LPDIRECT3DDEVICE9 pDevice_ ;
	Kim* pKim_ ;

	float3 camera_vector_ ;		// �J��������
	float3 move_ ;				// �ړ���
	float3 speed_ ;				// ���x
	float3 rotDest_ ;			// �ړI�̌���
	float3 old_position_ ;		// �O�̈ʒu

	int ID_ ;
	bool action_animation_end_ ;
	bool action_ ;
	bool hit_ ;

	STATE state_ ;

	float camera_rot_y ;

	ANIME anime_ ;
	ANIME old_anime_ ;
	WEAPON wepon_ ;		// 0 : �����`���[ , 1 : �e , 2 : �N��

	void Control( void );
	void UpdateKimMatrix( void );
	void ControlKeyBorad( void );
	void ControlJoypad( void );
	
protected : 
};

#endif // _PLAYER_H_

// END