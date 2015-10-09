//�w�b�_�[�C���N���[�h
#include "Clogo.h"
#include "CGame.h"
#include "CRender.h"

//������
HRESULT Clogo::Init(CRender* pRender,D3DXVECTOR3 pos,int nWidth,int nHeight,char* ptexFileName)
{

	m_pRender = pRender;

	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();
	
	

	m_pTexName = ptexFileName;

	if(m_pTexName != NULL)
	{
		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(m_pD3DDevice,m_pTexName,&m_pD3DTex);
	
	}
	
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

	m_pos = pos;					//���W
	m_rot = D3DXVECTOR3(0,0,0);		//��]
	m_Red = 255;
	m_Green = 255;
	m_Blue = 255;
	m_Alpha = 255;
	m_drawFlag = true;
	//�Ίp���̒���
	m_fLength = sqrtf((float)(nWidth*nWidth)+(float)(nHeight*nHeight));
	//�Ίp���̊p�x
	m_fAngle  = atan2((float)nWidth,(float)nHeight);

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
	pVtx[0].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
	pVtx[1].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
	pVtx[2].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
	pVtx[3].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0,1);
	pVtx[1].tex = D3DXVECTOR2(0,0);
	pVtx[2].tex = D3DXVECTOR2(1,1);
	pVtx[3].tex = D3DXVECTOR2(1,0);
	//�A�����b�N
	m_pD3DVtxBuffer->Unlock();

	m_cnt = 0;

	return S_OK;
}
//�X�V
void Clogo::Update()
{
	m_cnt++;
	if(m_cnt % 10 == 0)
	{
		m_cnt = 0;
		m_Alpha-=20;
		if(m_Alpha <= 0)
		{
			m_Alpha = 255;
		}
	}
	VERTEX_2D *pVtx = NULL;
	//���b�N
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//�F
	pVtx[0].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
	pVtx[1].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
	pVtx[2].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
	pVtx[3].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);

	//�A�����b�N
	m_pD3DVtxBuffer->Unlock();

}
//�J��
void Clogo::Uninit()
{
	if(m_pTexName != NULL)
	{
		SAFE_RELEASE(m_pD3DTex);		//�e�N�X�`���̊J��
	}
	
	SAFE_RELEASE(m_pD3DVtxBuffer);	//���_�o�b�t�@�̊J��
}
//�`��
void Clogo::Draw()
{
	if(m_drawFlag)
	{
	
		if(m_pRender->GetMode() == MODE_TITLE)
		{
			m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		}
		// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

		//�f�[�^��n��
		m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
		//FVF�̐ݒ�
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
		if(m_pTexName != NULL)
		{
			//�e�N�X�`���̐ݒ�
			m_pD3DDevice->SetTexture(0,m_pD3DTex);

		}
		else
		{
			//�e�N�X�`���̐ݒ�
			m_pD3DDevice->SetTexture(0,NULL);
		}
		//�|���S���̐ݒ�
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

		//�e�N�X�`���X�e�[�W
		m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		m_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);
		//���u�����h
		m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, FALSE );

		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	}
}



