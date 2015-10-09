//=============================================================================
// �����_�[�e�N�X�`������ [RenderTexture.cpp]
// Author : MASAHIRO YAMAGUCHI
// ���A���^�C���Ƀe�N�X�`���ɕ`�挋�ʂ��������ނ��Ƃ��o���܂��B
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "RenderTarget.h"

//���N���X��`
//=============================================================================
//�R���X�g���N�^
//=============================================================================
CRenderTarget::CRenderTarget()
{
	
	//�P�D�����_�[�^�[�Q�b�g�p�̃e�N�X�`���쐬
	D3DXCreateTexture(getDevice(),//�f�o�C�X
				 800,//�e�N�X�`���ɕ`�挋�ʂ��������ގ��̂��̃e�N�X�`���̕�
				 600,//�e�N�X�`���ɕ`�挋�ʂ��������ގ��̂��̃e�N�X�`���̍���
				 0,//�~�b�v�}�b�v���x��
				 D3DUSAGE_RENDERTARGET,//���̒萔�������_�[�^�[�Q�b�g������
				 //D3DFMT_G16R16,//�J���[�t�H�[�}�b�g
				 //D3DFMT_R8G8B8,
				 D3DFMT_A16B16G16R16,
				 D3DPOOL_DEFAULT,
				 &m_pRenderTexture);//�����_�[�e�N�X�`���|�C���^
	
	//2 �o�b�N�o�b�t�@���|�C���^�Ɏ��O�ɓ���Ă���
	getDevice()->GetRenderTarget(0,&m_pBackBufferTexture);



	//3�����_�[�^�[�Q�b�g�Ƃ��č쐬�����e�N�X�`���̃T�[�t�F�C�X���擾
	m_pRenderTexture->GetSurfaceLevel(0,&m_pRenderTexSurface);
	
	//Z�o�b�t�@
	getDevice()->CreateDepthStencilSurface(800,600,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,FALSE,&m_pZBuffer,NULL);
//	GetDevice()->CreateDepthStencilSurface(800,600,D3DFMT_D16,D3DMULTISAMPLE_NONE,0,TRUE,&g_pZBuffer,NULL);

}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CRenderTarget::~CRenderTarget()
{
	SAFE_RELEASE(m_pBackBufferTexture);
	SAFE_RELEASE(m_pRenderTexture);
	SAFE_RELEASE(m_pRenderTexSurface);
	SAFE_RELEASE(m_pZBuffer);
}


//=============================================================================
// �����_�[�e�N�X�`���̎擾����
// �߂�l�FLPDIRECT3DTEXTURE9		�F�����_�[�e�N�X�`���|�C���^
// �����P�Fvoid						�F�Ȃ�
//=============================================================================
IDirect3DTexture9* CRenderTarget::GetRenderTexture(void)
{
	//���ʂ�LPDIRECT3DTEXTURE9 �e�N�X�`���̃|�C���^���ւ񂫂Ⴍ�����OK
	return m_pRenderTexture;
}
//=============================================================================
// �����_�[�^�[�Q�b�g�̕ύX����
// �߂�l�Fvoid						�F�Ȃ�
// �����P�Fvoid						�F�Ȃ�
//=============================================================================
void CRenderTarget::ChangeRenderTarget(void)
{
	
	if(FAILED(getDevice()->SetRenderTarget(0, m_pRenderTexSurface)))
	{
		MessageBox(NULL,"�����_�[�^�[�Q�b�g�ύX���s","�x��",MB_OK);
	}
	//�Z�b�g
	getDevice()->SetDepthStencilSurface(m_pZBuffer);
	
}

//=============================================================================
// �����_�[�^�[�Q�b�g�̃��Z�b�g����
// �߂�l�Fvoid						�F�Ȃ�
// �����P�Fvoid						�F�Ȃ�
// ���Z�b�g�Ƃ�����茵���ɂ̓o�b�N�o�b�t�@��
// �����_�[�^�[�Q�b�g��߂��Ă��邾��
//=============================================================================
void CRenderTarget::ResetRenderTarget(void)
{
	
	if(FAILED(getDevice()->SetRenderTarget(0, m_pBackBufferTexture)))
	{
		MessageBox(NULL,"�����_�[�^�[�Q�b�g���Z�b�g���s","�x��",MB_OK);
	}
	//Z�o�b�t�@�[�Z�b�g
	getDevice()->SetDepthStencilSurface(m_pZBuffer);
	
}

//EOF