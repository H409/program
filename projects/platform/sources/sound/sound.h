//=============================================================================
//
// サウンドの処理 [sound.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//多重定義防止
#pragma once
#ifndef __SOUND_H__
#define __SOUND_H__

//ヘッダーインクルード
#include <xaudio2.h>

typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// TITLE
	SOUND_LABEL_BGM001,			// TUTORIAL
	SOUND_LABEL_BGM002,			// GAME
	SOUND_LABEL_BGM003,			// RESULT
	SOUND_LABEL_BGM004,			// GAME
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

//クラス定義
class Sound
{
public:

	static const int SE_MAX = 8;

	//インスタンス
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
	
	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	IXAudio2SourceVoice *m_apSeVoice[SOUND_LABEL_MAX][SE_MAX];
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	PARAM m_aParam[SOUND_LABEL_MAX];
	BYTE se_index_;
	SOUND_LABEL label_;
};


#endif
//eof