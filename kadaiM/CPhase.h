//=============================================================================
//
// �e�t�F�[�Y���� [CPhase.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//���d��`�h�~
#ifndef __CPHASE_H__
#define __CPHASE_H__

#include <windows.h>
#include <stdio.h>
#include "main.h"
///// �\���̒�` /////
typedef struct _PHASEINFO
{
	DWORD dwScene;
	DWORD dwSubScene;
	int   nCount;
}PHASEINFO,*LPPHASEINFO;




//�V�[���Ǘ��p�N���X
class CPhase
{
protected:
	PHASEINFO	m_PhaseInfo;
	bool(CPhase::*m_lpPhase[3])(void *lpArgs);
public:
	
	//�R���X�g���N�^
	CPhase();	
	//�f�X�g���N�^
	~CPhase();


	static const BYTE	PHASE_INIT;
	static const BYTE	PHASE_MAIN;
	static const BYTE	PHASE_RELEASE;
	//�V�[�����擾�p
	PHASEINFO GetPhaseInfo(void)const
	{
		return this->m_PhaseInfo;
	}
	//�V�[���ԍ��ݒ�
	void SetPhase(DWORD dwScene)
	{
		this->m_PhaseInfo.dwScene = dwScene;
	}
	//�T�u�V�[���ԍ��ݒ�
	void SetSubPhase(DWORD dwSubScene)
	{
		this->m_PhaseInfo.dwSubScene = dwSubScene;
	}
	//�e�V�[���̌Ăяo���p�֐�
	bool Phase(void *lpArgs = NULL);


	//�e�V�[��
	virtual bool Init(void *lpArgs = NULL) = 0;
	virtual bool Update(void *lpArgs = NULL) = 0;
	virtual bool Release(void *lpArgs = NULL) = 0;
	virtual bool Draw(void *lpArgs = NULL) = 0;
	virtual bool DrawShade(void *lpArgs = NULL) = 0;

};

#endif
//eof