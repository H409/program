//�w�b�_�[�C���N���[�h
#include "CScene2D.h"
#include "CRender.h"
#include <cmath>
//�}�N��
#define POS_MARGIN_X	(100)
#define POS_MARGIN_Y	(50)

/*
//�R���X�g���N�^
CScene2D::CScene2D(){};
//�f�X�g���N�^
CScene2D::~CScene2D(){};
*/
//�쐬
CScene2D* CScene2D::Create(CRender* pRender,D3DXVECTOR3 pos,char* ptexFileName,OBJTYPE objtype)
{
	CScene2D* pScene2D = new CScene2D(0,objtype);

	if(objtype == OBJTYPE_2D)
	{
		pScene2D->Init(pRender,pos,255,255,255,255,400,300,ptexFileName);
	}
	else if(objtype == OBJTYPE_2DGIM)
	{
		pScene2D->Init(pRender,pos,255,255,255,255,25,25,ptexFileName);
	}
	pScene2D->SetPosition(pos);

	return pScene2D;

}
//�I�[�o�[���C�h
CScene2D* CScene2D::Create(CRender* pRender,D3DXVECTOR3 pos,int nWidth,int nHeight,char* ptexFileName,OBJTYPE objtype)
{
	CScene2D* pScene2D = new CScene2D(0,objtype);

	pScene2D->Init(pRender,pos,255,255,255,255,nWidth,nHeight,ptexFileName);

	pScene2D->SetPosition(pos);

	return pScene2D;
}
//������
HRESULT CScene2D::Init(CRender* pRender)
{
	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\bg001.jpg",&m_pD3DTex);
	
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
	m_pRender = pRender;

	m_pos = D3DXVECTOR3(300,200,0);	//���W
	m_rot = D3DXVECTOR3(0,0,0);		//��]
	//�Ίp���̒���
	m_fLength = sqrtf(POS_MARGIN_X*POS_MARGIN_X+POS_MARGIN_Y*POS_MARGIN_Y);
	//�Ίp���̊p�x
	m_fAngle  = atan2((float)POS_MARGIN_X,(float)POS_MARGIN_Y);

	return S_OK;
}
HRESULT CScene2D::Init(CRender* pRender,D3DXVECTOR3 pos,int nRed,int nGreen,int nBlue,int nalpha,int nWidth,int nHeight,char* pTexFileName)
{
	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();
	m_Red = nRed;
	m_Green = nGreen;
	m_Blue = nBlue;
	m_Alpha = nalpha;
	m_drawFlag = true;
	m_pTexName = pTexFileName;
	m_pRender = pRender;
	if(pTexFileName != NULL)
	{
		//�e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(m_pD3DDevice,pTexFileName,&m_pD3DTex);
		/*
		if(pRender->GetMode() == MODE_GAME)
		{
			m_pD3DTex = pRender->GetRenderTexture();
		}
		*/
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
	//�Ίp���̒���
	m_fLength = sqrtf((float)(nWidth*nWidth)+(float)(nHeight*nHeight));
	//�Ίp���̊p�x
	m_fAngle  = atan2((float)nWidth,(float)nHeight);

	return S_OK;
}
//�X�V
void CScene2D::Uninit()
{
//	SAFE_RELEASE(m_pD3DDevice);		//Direct3dDevice�I�u�W�F�N�g�̊J��
	if(m_pTexName != NULL)
	{
		SAFE_RELEASE(m_pD3DTex);		//�e�N�X�`���̊J��
	}
	
	SAFE_RELEASE(m_pD3DVtxBuffer);	//���_�o�b�t�@�̊J��

	Release();

}
//�J��
void CScene2D::Update()
{
	if(CScene::GetObjType() == OBJTYPE_2DGIM)
	{
		m_rot.z -= D3DX_PI * 0.01f;
	}
	//�p�x���K��
	if( m_rot.z < -D3DX_PI )
	{
		m_rot.z += 2 * D3DX_PI;
	}
	// �p�x�𐳋K��
	else if( m_rot.z > D3DX_PI )
	{
		m_rot.z -= 2 * D3DX_PI;
	}

	VERTEX_2D *pVtx = NULL;
	if(m_pD3DVtxBuffer != NULL)
	{
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
	}
}
//�`��
void CScene2D::Draw()
{
	if(m_drawFlag)
	{
		if(m_pRender->GetMode() == MODE_TITLE)
		{
			m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		}
		else if(m_pRender->GetMode() == MODE_GAME)
		{
			m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
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
//		m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
//		m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//		m_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);
		//���u�����h
		m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, FALSE );

		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	}
	//
}
void CScene2D::DrawShade()
{
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

}
