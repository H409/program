//=============================================================================
//
// �e�t�F�[�Y���� [CEnding.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//���d��`�h�~
#ifndef __CENDING_H__
#define __CENDING_H__

//�w�b�_�[�C���N���[�h
#include "CPhase.h"
#include "Clogo.h"
#include "CNumber.h"

//�}�N����`
#define RANK_MAX	(4)
#define RANK_DIGIT	(5)
//�O���錾
class CRender;

//�N���X��`
class CEnding:public CPhase
{
private:
	bool  m_Cler;
	bool  m_pause;
	static CEnding* m_instance;
	CRender*	m_pRender;
	bool	m_initManager;
	Clogo* m_pPushLogo;
	int m_Rank[RANK_MAX];
	CNumber*			m_pRank1[RANK_DIGIT];
	CNumber*			m_pRank2[RANK_DIGIT];
	CNumber*			m_pRank3[RANK_DIGIT];
	int					m_EndCnt;
public:
	//�C���X�^���X����
	static CEnding* getInstance();
	//�C���X�^���X���
	static void freeInstance();

	//�R���X�g���N�^
	CEnding()
	{
		m_pPushLogo = NULL;
		m_initManager = false;
	}
	//�f�X�g���N�^
	~CEnding()
	{
		if(m_pPushLogo != NULL)
		{
			m_pPushLogo->Uninit();
			SAFE_DELETE(m_pPushLogo);
		}
	}
	bool SaveRanking(void);
	bool LoadRanking(void);
	void SetRank(int iNum);
	int  GetRank(int iNum);
	//�e�V�[��
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);
	virtual bool DrawShade(void *lpArgs = NULL);
};

#endif