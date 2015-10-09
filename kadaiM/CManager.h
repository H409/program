//���d��`�h�~
#ifndef __CMANAGER_H__
#define __CMANAGER_H__

//�w�b�_�[�C���N���[�h
#include "main.h"


//�O���錾
class CRender;
class CScene;
class CLight;
class CCamera;
class CInputKeyboard;
class CDebugProc;
class CSceneX;
class CPlayer;
class CFade;
class CTitle;
class CGame;
class CEnding;

//�N���X��`
class CManager
{
private:
	static CRender*		m_pRender;
	CScene*				m_pScenes;
	CLight*				m_pLight;
	CCamera*			m_pCamera;
	CDebugProc*			m_pDebugProc;
	CSceneX*			m_pDummy;
	static CPlayer*		m_pPlayer;
	static CFade*		m_pFade;
	CTitle*				m_pTitle;
	CGame*				m_pGame;
	CEnding*			m_pEnding;
	MODE				m_mode;
public:

	//�R���X�g���N�^
	CManager()
	{
		m_pPlayer = NULL;
		m_mode = MODE_TITLE;
	}
	//�f�X�g���N�^
	virtual ~CManager(){}
	//������
	HRESULT Init(HINSTANCE hInstance,HWND hWnd,bool bWindow);
	//�J��
	void Uninit(void);
	//�X�V
	void Updata(void);
	//�`��
	void Draw(void);

	//�Q�b�^�[
	static CRender* GetRender(void)
	{
		return m_pRender;
	}
	static CPlayer* GetPlayer(void)
	{
		return m_pPlayer;
	}

	static CFade* GetFade(void)
	{
		return m_pFade;
	}

};


#endif