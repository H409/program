//=============================================================================
//
// ���l����������� [CNumber.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CNumber.h"
#include "CRender.h"

//�}�N����`
#define NUM_MARGIN_X	(25)
#define NUM_MARGIN_Y	(25)

//����
CNumber* CNumber::Create(CRender* pRender,const D3DXVECTOR3 pos)
{
	CNumber* pNumber = new CNumber();

	pNumber->Init(pRender);

	pNumber->SetPosition(pos);

	return pNumber;
}
//������
HRESULT CNumber::Init(CRender* pRender)
{
	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\number.png",&m_pD3DTex);
	
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
	//m_pos = D3DXVECTOR3(300,200,0);	//���W
	m_rot = D3DXVECTOR3(0,0,0);		//��]
	//�Ίp���̒���
	m_fLength = sqrtf(NUM_MARGIN_X*NUM_MARGIN_X+NUM_MARGIN_Y*NUM_MARGIN_Y);
	//�Ίp���̊p�x
	m_fAngle  = atan2((float)NUM_MARGIN_X,(float)NUM_MARGIN_Y);

	
	return S_OK;
}

//�X�V
void CNumber::Update(void)
{
	VERTEX_2D *pVtx = NULL;
	//���b�N
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

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
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(m_Num*0.1f,1.0f);
	pVtx[1].tex = D3DXVECTOR2(m_Num*0.1f,0);
	pVtx[2].tex = D3DXVECTOR2(m_Num*0.1f+0.1f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_Num*0.1f+0.1f,0);
	//�A�����b�N
	m_pD3DVtxBuffer->Unlock();
}

//�J��
void CNumber::Uninit(void)
{
	SAFE_RELEASE(m_pD3DTex);		//�e�N�X�`���̊J��
	SAFE_RELEASE(m_pD3DVtxBuffer);	//���_�o�b�t�@�̊J��
	//__asm int 3
}

//�`��
void CNumber::Draw(void)
{
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
void CNumber::DrawShade(void)
{
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
//�ύX
void CNumber::ChengeNumber(int Value)
{
	VERTEX_2D *pVtx = NULL;

	m_Num = Value;
}



//eof