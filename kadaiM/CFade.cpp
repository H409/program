//=============================================================================
//
// �t�F�[�h���� [CFade.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CFade.h"
#include "CRender.h"
#include <process.h>

//�}�N��
#define POS_MARGIN_FADE_X	(400)
#define POS_MARGIN_FADE_Y	(300)

//�����o�ϐ�
CFade* CFade::m_instance = NULL;

CFade* CFade::getinstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CFade();
	}
	return m_instance;
}

void CFade::Release()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

//������
HRESULT CFade::Init(CRender* pRender)
{
	m_pRender = pRender;
	m_FadeMode = FADE_NONE;

	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	//�|���S���ݒ�
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffer,
											NULL)))
	{
		return E_FAIL;
	}
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\fade.png",&m_pD3DTex);

	m_pos = D3DXVECTOR3(400,300,0);	//���W
	m_rot = D3DXVECTOR3(0,0,0);		//��]
	//�Ίp���̒���
	m_fLength = sqrtf(POS_MARGIN_FADE_X*POS_MARGIN_FADE_X+POS_MARGIN_FADE_Y*POS_MARGIN_FADE_Y);
	//�Ίp���̊p�x
	m_fAngle  = atan2((float)POS_MARGIN_FADE_X,(float)POS_MARGIN_FADE_Y);

	_beginthreadex( NULL, 0, FadeThread, NULL, 0, NULL );
	return S_OK;
}
//�J��
void CFade::Uninit()
{
	SAFE_RELEASE(m_pD3DVtxBuffer);	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_pD3DTex);
}
//�X�V
void CFade::Update()
{
	if(m_FadeMode == FADE_OUT)
	{
		if(FadeOut())
		{
			m_FadeMode = FADE_OUT_FINISH;
			
		}
	}
	
	if(m_FadeMode == FADE_IN)
	{
		if(FadeIn())
		{
			m_FadeMode = FADE_NONE;
			
		}
	}
	VERTEX_2D *pVtx = NULL;
	//���b�N
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//���_
	//����
	pVtx[0].vtx.x = m_pos.x - sinf(-m_rot.z+m_fAngle)*m_fLength;
	pVtx[0].vtx.y = m_pos.y + cosf(-m_rot.z+m_fAngle)*m_fLength;
	//����
	pVtx[1].vtx.x = m_pos.x - sinf(m_rot.z+m_fAngle)*m_fLength;
	pVtx[1].vtx.y = m_pos.y - cosf(m_rot.z+m_fAngle)*m_fLength;
	//�E��
	pVtx[2].vtx.x = m_pos.x + sinf(m_rot.z+m_fAngle)*m_fLength;
	pVtx[2].vtx.y = m_pos.y + cosf(m_rot.z+m_fAngle)*m_fLength;
	//�E��
	pVtx[3].vtx.x = m_pos.x + sinf(-m_rot.z+m_fAngle)*m_fLength;
	pVtx[3].vtx.y = m_pos.y - cosf(-m_rot.z+m_fAngle)*m_fLength;
	//���W�ϊ���ʒu
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//�F
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0,1);
	pVtx[1].tex = D3DXVECTOR2(0,0);
	pVtx[2].tex = D3DXVECTOR2(1,1);
	pVtx[3].tex = D3DXVECTOR2(1,0);
	//�A�����b�N
	m_pD3DVtxBuffer->Unlock();
}

//�`��
void CFade::Draw()
{
	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//�e�N�X�`���X�e�[�W
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);


}
//�t�F�[�h�A�E�g
bool CFade::FadeOut()
{
	if(m_FadeMode == FADE_OUT)
	{
		m_Alpha+=15;
		
		if(m_Alpha >= 255)
		{
			m_Alpha = 255;
			
			return true;
		}
	}
	return false;
}
//�t�F�[�h�C��
bool CFade::FadeIn()
{
	if(m_FadeMode == FADE_IN)
	{
		
		m_Alpha-=15;
		
		if(m_Alpha <= 0)
		{
			m_Alpha = 0;
			
			return true;
		}
	}
	return false;
}
//�X���b�h
unsigned int __stdcall CFade::FadeThread(LPVOID Param)
{

	return 0;
}
//eof