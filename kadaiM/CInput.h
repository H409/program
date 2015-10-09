//���d��`�h�~
#ifndef __CINPUT_H__
#define __CINPUT_H__

//�w�b�_�[�C���N���[�h
#include "main.h"

//�N���X��`
class CInput
{
protected:
	static LPDIRECTINPUT8	m_pDInput;
	LPDIRECTINPUTDEVICE8	m_pDIDevice;
	LPDIRECTINPUTDEVICE8	m_pDIDeviceJoyPad;
	LPDIRECTINPUTDEVICE8	m_pDIDeviceMouse;
public:
	//�R���X�g���N�^
	CInput()
	{
		m_pDInput = NULL;
		m_pDIDevice = NULL;
	}
	//�f�X�g���N�^
	virtual ~CInput(){}
	//������
	virtual HRESULT Init(HINSTANCE hInstance,HWND hWnd);
	//�J��
	virtual void Uninit(void);
	//�X�V
	virtual void Update(void) = 0;

};
#endif