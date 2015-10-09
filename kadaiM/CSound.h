//=============================================================================
//
// メッシュ壁の処理 [CSound.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//多重定義防止
#ifndef __CSOUND_H__
#define __CSOUND_H__

//ヘッダーインクルード
#include "main.h"

typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_SE_YES,			// 選択決定音
	SOUND_LABEL_SE_SCENE,		// シーン切り替え音
	SOUND_LABEL_SE_SHOT,		// 破壊音
	SOUND_LABEL_SE_CYANCEL,		// キャンセル音0
	SOUND_LABEL_SE_EXPRODE,		// 爆発音1
	SOUND_LABEL_SE_MOVE,		// カーソル移動音
	SOUND_LABEL_SE_PAUSE,		// ロックオン音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

typedef struct
{
	char *pFilename;	// ファイル名
	bool bLoop;			// ループするかどうか
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

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	PARAM m_aParam[SOUND_LABEL_MAX];

};


#endif
//eof