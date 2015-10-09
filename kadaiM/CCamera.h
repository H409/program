//���d��`�h�~
#ifndef __CCAMERA_H__
#define __CCAMERA_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CInputKeyboard.h"
#include "CRender.h"
//�O���錾
class CRender;

//�N���X��`
class CCamera
{
private:
	D3DXVECTOR3  m_posCameraP;		// ���_
	D3DXVECTOR3  m_posCameraR;		// �����_
	D3DXVECTOR3  m_vecCameraU;		// ������x�N�g��
	D3DXMATRIX   m_mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX	 m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3	 m_rotCamera;		// �J�����̌���
	float		 m_fLengthCameraXZ;	// ���_���璍���_�܂ł̋���( x, z )
	D3DXVECTOR3  m_posCameraPDest;	// ���_�̐�
	D3DXVECTOR3  m_posCameraRDest;	// �����_�̐�
	D3DVIEWPORT9 m_viewport;		// �r���[�|�[�g
	float		 m_faglView;		// ��p�p�i�Y�[���j
	D3DXVECTOR3  m_vecSpeed;		// �X�s�[�h
	D3DXMATRIX   m_mtxRot;			// ��]�p�s��
	float		 m_fAngle;			// �p�x
	LPDIRECT3DDEVICE9	m_pDevice;		
	CInputKeyboard*		m_pInputKeyboard;
	D3DXVECTOR3	m_plpos;			//
	bool		m_bFlag;			//��]���ړ�
	bool		m_initManager;
	bool		m_stopFlag;	
	MODE		m_mode;
	static CCamera* m_instance;
public:
	
	static CCamera* getInstance();
	static void Release();

	CCamera(){}
	virtual ~CCamera(){}
	HRESULT Init(CRender* pRender);
	HRESULT TitleInit(CRender* pRender);
	void Update(void);
	void TitleUpdate(void);
	void UpdateDebug(void);
	void Uninit(void);
	void SetCamera(void);
	D3DXMATRIX GetMtxView()
	{
		return m_mtxView;
	}
	D3DXMATRIX GetMtxProjection()
	{
		return m_mtxProjection;
	}
	
	void SetKeyBoard(CInputKeyboard* pInputKeyboard)
	{
		m_pInputKeyboard = pInputKeyboard;
	}
	

};
D3DXMATRIX GetMtxView();
float GetAngleYaw(void);
#endif