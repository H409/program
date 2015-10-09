//=============================================================================
//
// �e�t�F�[�Y���� [CTitle.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//���d��`
#ifndef __CTITLE_H__
#define __CTITLE_H__

//�w�b�_�[�C���N���[�h
#include "CPhase.h"
#include "Clogo.h"

//�O���錾
class CRender;
class Clogo;

//�N���X��`
class CTitle:public CPhase
{
private:
	bool  m_Cler;
	bool  m_pause;
	static CTitle* m_instance;
	CRender* m_pRender;
	bool  m_initManager;
	Clogo* m_pPushLogo;
	Clogo* m_pTitleLogo;
public:

	//�C���X�^���X����
	static CTitle* getInstance();
	//�C���X�^���X���
	static void freeInstance();

	//�R���X�g���N�^
	CTitle()
	{
		m_initManager = false;
		m_pPushLogo = NULL;
	}
	//�f�X�g���N�^
	~CTitle()
	{
		if(m_pPushLogo != NULL)
		{
			m_pPushLogo->Uninit();
			SAFE_DELETE(m_pPushLogo);
		}
	}
	//�e�V�[��
	virtual bool Init(void *lpArgs = NULL);
	virtual bool Update(void *lpArgs = NULL);
	virtual bool Release(void *lpArgs = NULL);
	virtual bool Draw(void *lpArgs = NULL);
	virtual bool DrawShade(void *lpArgs = NULL);
};

#endif