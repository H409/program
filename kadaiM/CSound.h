//=============================================================================
//
// ���b�V���ǂ̏��� [CSound.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//���d��`�h�~
#ifndef __CSOUND_H__
#define __CSOUND_H__

//�w�b�_�[�C���N���[�h
#include "main.h"

typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
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

class CSound
{
public:
	
	
	

	static CSound* getInstance();
	static void Release();

	CSound();
	virtual ~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	static CSound*	m_instance;

	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	PARAM m_aParam[SOUND_LABEL_MAX];

};


#endif
//eof