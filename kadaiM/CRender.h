//���d��`�h�~
#ifndef __CRENDER_H__
#define __CRENDER_H__

//�w�b�_�[
#include "main.h"

//�O���錾
class CScene;

//�N���X
class CRender
{
private:
	LPDIRECT3D9				m_pD3D;					// Direct3D �I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;			// Device�I�u�W�F�N�g(�`��ɕK�v)
	MODE					m_mode;

	IDirect3DSurface9* m_pBackBufferTexture;		//�e�N�X�`��
	IDirect3DTexture9* m_pRenderTexture;			//�����_�[�^�[�Q�b�g�p�̃e�N�X�`��
	IDirect3DSurface9* m_pRenderTexSurface;			//�e�N�X�`���T�[�t�F�C�X
	IDirect3DSurface9* m_pZBuffer;					//zMap

public:
	//�R���X�g���N�^
	CRender();
	//�f�X�g���N�^
	virtual ~CRender();
	//������
	HRESULT Init(HWND hWnd,BOOL bWindow);
	//�J��
	void Uninit(void);
	//�X�V
	void Update();
	//�`��
	void Draw();
	MODE GetMode()
	{
		return m_mode;
	}
	//�f�o�C�X�擾
	const LPDIRECT3DDEVICE9 getDevice()const
	{
		return m_pD3DDevice;
	}
	void SaveSceneToFIle(LPCTSTR szFileName,D3DXIMAGE_FILEFORMAT Format = D3DXIFF_BMP);
	
	IDirect3DTexture9* GetRenderTexture(void);	//�����_�[�e�N�X�`���̎擾
	void ChangeRenderTarget(void); 				//�����_�[�^�[�Q�b�g�̕ύX
	void ResetRenderTarget(void);				//�����_�[�^�[�Q�b�g�����ɖ߂�(�X�ł̖߂��͒ʏ�̃o�b�N�o�b�t�@�ɖ߂�Ƃ�������)
	IDirect3DSurface9* GetRenderSurface(void)
	{
		return m_pRenderTexSurface;
	}
};


#endif