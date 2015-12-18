//=============================================================================
//
// �T�E���h�̏��� [sound.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//���d��`�h�~
#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__

//�w�b�_�[�C���N���[�h
#include <xaudio2.h>

typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// TITLE
	SOUND_LABEL_BGM001,			// TUTORIAL
	SOUND_LABEL_BGM002,			// GAME
	SOUND_LABEL_BGM003,			// RESULT
	SOUND_LABEL_BGM004,			// GAME
	SOUND_LABEL_SE_YES,			// �I�����艹
	SOUND_LABEL_SE_SCENE,		// �V�[���؂�ւ���
	SOUND_LABEL_SE_SHOT,		// �j��
	SOUND_LABEL_SE_CYANCEL,		// �L�����Z����0
	SOUND_LABEL_SE_EXPRODE,		// ������1
	SOUND_LABEL_SE_MOVE,		// �J�[�\���ړ���
	SOUND_LABEL_SE_PAUSE,		// ���b�N�I����
	SOUND_LABEL_MAX,
} SOUND_LABEL;

typedef struct
{
	char *pFilename;	// �t�@�C����
	bool bLoop;			// ���[�v���邩�ǂ���
} PARAM;

//�N���X��`
class Sound
{
public:

	static const int SE_MAX = 8;

	//�C���X�^���X
	static Sound& Instance(void)
	{
		static Sound instance;
		return instance;
	}
	
	Sound();
	virtual ~Sound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	HRESULT PlaySeSound(SOUND_LABEL label, int index);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	void StopSeSound(SOUND_LABEL label);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	
	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	IXAudio2SourceVoice *m_apSeVoice[SOUND_LABEL_MAX][SE_MAX];
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	PARAM m_aParam[SOUND_LABEL_MAX];
	BYTE se_index_;
	SOUND_LABEL label_;
};


#endif
//eof