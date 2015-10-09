//=============================================================================
// �����_�[�e�N�X�`������ [RenderTexture.h]
// Author : MASAHIRO YAMAGUCHI
// ���A���^�C���Ƀe�N�X�`���ɕ`�挋�ʂ��������ނ��Ƃ��o���܂��B
//=============================================================================
#ifndef _RENDERTEXTURE_H_
#define _RENDERTEXTURE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CRender.h"

//�N���X��`
class CRenderTarget : public CRender
{
private:
	IDirect3DSurface9* m_pBackBufferTexture;		//�e�N�X�`��
	IDirect3DTexture9* m_pRenderTexture;			//�����_�[�^�[�Q�b�g�p�̃e�N�X�`��
	IDirect3DSurface9* m_pRenderTexSurface;			//�e�N�X�`���T�[�t�F�C�X
	IDirect3DSurface9* m_pZBuffer;					//zMap

public:
	//�R���X�g���N�^
	CRenderTarget();
	//�f�X�g���N�^
	virtual ~CRenderTarget();

	IDirect3DTexture9* GetRenderTexture(void);	//�����_�[�e�N�X�`���̎擾
	void ChangeRenderTarget(void); 				//�����_�[�^�[�Q�b�g�̕ύX
	void ResetRenderTarget(void);				//�����_�[�^�[�Q�b�g�����ɖ߂�(�X�ł̖߂��͒ʏ�̃o�b�N�o�b�t�@�ɖ߂�Ƃ�������)
};

#endif