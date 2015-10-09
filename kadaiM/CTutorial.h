//=============================================================================
//
// �e�t�F�[�Y���� [CTutorial.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//���d��`
#ifndef __CTUTORIAL_H__
#define __CTUTORIAL_H__

//�w�b�_�[�C���N���[�h
#include "CPhase.h"
#include "Clogo.h"

//�O���錾
class CRender;

//�N���X��`
class CTutorial:public CPhase
{
private:
	bool  m_Cler;
	bool  m_pause;
	static CTutorial* m_instance;
	CRender* m_pRender;
	bool  m_initManager;
	Clogo* m_pPushLogo;
public:

	//�C���X�^���X����
	static CTutorial* getInstance();
	//�C���X�^���X���
	static void freeInstance();

	//�R���X�g���N�^
	CTutorial()
	{
		m_initManager = false;
		m_pPushLogo = NULL;
	}
	//�f�X�g���N�^
	~CTutorial()
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