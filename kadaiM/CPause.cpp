//=============================================================================
//
// �|�[�Y���� [CPause.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CPause.h"
#include "CRender.h"
#include "CInputKeyboard.h"
#include "CGame.h"

//�ÓI�����o�ϐ�
CPause* CPause::m_instance = NULL;

CPause* CPause::getInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CPause();
	}
	return m_instance;
}

void CPause::Resease()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}
//������
HRESULT CPause::Init(CRender* pRender)
{

	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\Tutorial.png",&m_pD3DTex);

	//�o�[�e�b�N�X�o�b�t�@
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffer,
											NULL)))
	{
		return E_FAIL;
	}

	//�J�[�\���p
	LPSTR filename[3] = 
	{
		{"data\\Texture\\BackToGame.bmp"},
		{"data\\Texture\\Retry.bmp"},
		{"data\\Texture\\BackToTitle.bmp"},

	};
	for(int i = 0;i < 3;i++)
	{
		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(m_pD3DDevice,filename[i],&m_pD3DTexCur[i]);
	}

	//�o�[�e�b�N�X�o�b�t�@
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4*3,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBufferCur,
											NULL)))
	{
		return E_FAIL;
	}

	CURSOL cur[3] =
	{									//�J�[�\���p
		{{420.f,450.f},250,25,0,0,0,0,FALSE},
		{{420.f,510.f},250,25,1,0,0,0,FALSE},
		{{420.f,560.f},250,25,2,0,0,0,FALSE},
	};
	
	for(int i = 0;i < 3;i++)
	{
		m_Cursor[i] = cur[i];
	}

		//�J�[�\��������
	for(int i = 0;i < 3;i++)
	{
		m_Cursor[i].fLength = sqrtf((float)(m_Cursor[i].Width*m_Cursor[i].Width+m_Cursor[i].Height*m_Cursor[i].Height));
		m_Cursor[i].fAngle  = atan2((float)m_Cursor[i].Width,(float)m_Cursor[i].Height);
		m_Cursor[i].fSubLength = m_Cursor[i].fLength;
		m_Cursor[i].bFlag = FALSE;
	}

	//�|���S��������
	VERTEX_2D *pVtx = NULL;
	VERTEX_2D *pVtx1 = NULL;

	m_pD3DVtxBufferCur->Lock(0,0,(void**)&pVtx,0);
	
	for(int i = 0; i < 3;i++)
	{
		pVtx[0].vtx = D3DXVECTOR3(m_Cursor[i].pos.x-m_Cursor[i].Width,m_Cursor[i].pos.y+m_Cursor[i].Height,0);
		pVtx[1].vtx = D3DXVECTOR3(m_Cursor[i].pos.x-m_Cursor[i].Width,m_Cursor[i].pos.y-m_Cursor[i].Height,0);
		pVtx[2].vtx = D3DXVECTOR3(m_Cursor[i].pos.x+m_Cursor[i].Width,m_Cursor[i].pos.y+m_Cursor[i].Height,0);
		pVtx[3].vtx = D3DXVECTOR3(m_Cursor[i].pos.x+m_Cursor[i].Width,m_Cursor[i].pos.y-m_Cursor[i].Height,0);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,0);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,0);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,0);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,0);

		pVtx[0].tex = D3DXVECTOR2(0,1);
		pVtx[1].tex = D3DXVECTOR2(0,0);
		pVtx[2].tex = D3DXVECTOR2(1,1);
		pVtx[3].tex = D3DXVECTOR2(1,0);

		pVtx+=4;
	}
	m_pD3DVtxBufferCur->Unlock();

	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx1,0);

	pVtx1[0].vtx = D3DXVECTOR3(0,600,0);
	pVtx1[1].vtx	= D3DXVECTOR3(0,0,0);
	pVtx1[2].vtx	= D3DXVECTOR3(800,600,0);
	pVtx1[3].vtx	= D3DXVECTOR3(800,0,0);

	pVtx1[0].rhw = 1.0f;
	pVtx1[1].rhw = 1.0f;
	pVtx1[2].rhw = 1.0f;
	pVtx1[3].rhw = 1.0f;

	pVtx1[0].diffuse = D3DCOLOR_RGBA(255,255,255,0);
	pVtx1[1].diffuse = D3DCOLOR_RGBA(255,255,255,0);
	pVtx1[2].diffuse = D3DCOLOR_RGBA(255,255,255,0);
	pVtx1[3].diffuse = D3DCOLOR_RGBA(255,255,255,0);

	pVtx1[0].tex = D3DXVECTOR2(0,1);
	pVtx1[1].tex = D3DXVECTOR2(0,0);
	pVtx1[2].tex = D3DXVECTOR2(1,1);
	pVtx1[3].tex = D3DXVECTOR2(1,0);
	
	m_pD3DVtxBuffer->Unlock();

	m_Red = 255;
	m_Green = 255;
	m_Blue = 255;

	m_curf = 0;
	m_type = 0;
	
	m_Alpha[0] = 0;
	m_Alpha[1] = 0;
	m_Alpha[2] = 0;

	m_modechange = MODE_NONE;

	return S_OK;
}
//�X�V 
void CPause::Update()
{
	//�ϐ��錾
	VERTEX_2D *pVtx = NULL;
	
	//��
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_W))
	{
		m_curf--;
		
		if(m_curf < 0)
		{
			m_curf = 3-1;
		}
		
	}
	//��
	if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_S))
	{
		m_curf++;

		if(m_curf >= 3)
		{
			m_curf = 0;
		}
	}
	//�Q�[���ɖ߂�
	if(m_curf == MODE_CONTINUE)
	{
		m_Alpha[0]++;
		if(m_Alpha[0] >= 255)
		{
			m_Alpha[0] = 0;
		}
		/*
		m_Red++;
		if(m_Red >= 255)
		{
			m_Red = 0;
		}
		m_Blue = 255;
		m_Green = 255;
		*/
		m_Cursor[MODE_CONTINUE].bFlag = TRUE;
		m_Cursor[MODE_RESET].bFlag = FALSE;
		m_Cursor[MODE_QUIT].bFlag = FALSE;
		m_type = 0;
		if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_RETURN))
		{
			m_modechange = MODE_CONTINUE;
			CGame::getInstance()->SetPauseFlag(false);
		}
	}
	//�Q�[���ŏ�����
	if(m_curf == MODE_RESET)
	{
		m_Alpha[1]++;
		if(m_Alpha[1] >= 255)
		{
			m_Alpha[1] = 0;
		}
		/*
		m_Green++;
		if(m_Green >= 255)
		{
			m_Green = 0;
		}
		m_Red = 255;
		m_Blue = 255;
		*/
		m_Cursor[MODE_RESET].bFlag = TRUE;
		m_Cursor[MODE_CONTINUE].bFlag = FALSE;
		m_Cursor[MODE_QUIT].bFlag = FALSE;
		m_type = 1;
		if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_RETURN))
		{
			m_modechange = MODE_RESET;
		}
	}
	//�^�C�g��
	if(m_curf == MODE_QUIT)
	{
		m_Alpha[2]++;
		if(m_Alpha[2] >= 255)
		{
			m_Alpha[2] = 0;
		}
		/*
		m_Blue++;
		if(m_Blue >= 255)
		{
			m_Blue = 0;
		}
		*/
		m_Red = 255;
		m_Green = 255;

		m_Cursor[MODE_QUIT].bFlag = TRUE;
		m_Cursor[MODE_RESET].bFlag = FALSE;
		m_Cursor[MODE_CONTINUE].bFlag = FALSE;
		m_type = 2;
		
		if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_RETURN))
		{
			m_modechange = MODE_QUIT;
		}
	}

	//�X�V�p
	if(m_Cursor[m_curf].bFlag)
	{
		m_Cursor[m_curf].fLength++;
		
		if(m_Cursor[m_curf].fLength >= 300)
		{
			m_Cursor[m_curf].fLength = m_Cursor[m_curf].fSubLength;
		}
	}
	for(int i = 0;i < MODE_CHANGE_MAX;i++)
	{
		if(!m_Cursor[i].bFlag)
		{
			if(m_Cursor[i].fLength != m_Cursor[i].fSubLength)
			{
				m_Cursor[i].fLength--;
				if(m_Cursor[i].fLength <= m_Cursor[i].fSubLength)
				{
					m_Cursor[i].fLength = m_Cursor[i].fSubLength;
				}
			}
		}
	}
	//���b�N�J�n
	m_pD3DVtxBufferCur->Lock(0,0,(void**)&pVtx,0);

	for(int i = 0;i < 3;i++)
	{

		//����
		pVtx[0].vtx.x = m_Cursor[i].pos.x - sinf(-0+m_Cursor[i].fAngle)*m_Cursor[i].fLength;
		pVtx[0].vtx.y = m_Cursor[i].pos.y + cosf(-0+m_Cursor[i].fAngle)*m_Cursor[i].fLength;
		//����
		pVtx[1].vtx.x = m_Cursor[i].pos.x - sinf(0+m_Cursor[i].fAngle)*m_Cursor[i].fLength;
		pVtx[1].vtx.y = m_Cursor[i].pos.y - cosf(0+m_Cursor[i].fAngle)*m_Cursor[i].fLength;
		//�E��
		pVtx[2].vtx.x = m_Cursor[i].pos.x + sinf(0+m_Cursor[i].fAngle)*m_Cursor[i].fLength;
		pVtx[2].vtx.y = m_Cursor[i].pos.y + cosf(0+m_Cursor[i].fAngle)*m_Cursor[i].fLength;
		//�E��
		pVtx[3].vtx.x = m_Cursor[i].pos.x + sinf(-0+m_Cursor[i].fAngle)*m_Cursor[i].fLength;
		pVtx[3].vtx.y = m_Cursor[i].pos.y - cosf(-0+m_Cursor[i].fAngle)*m_Cursor[i].fLength;

		switch(m_curf)
		{
			case MODE_CONTINUE:
				//D3DXCOLOR
				pVtx[0].diffuse = D3DCOLOR_ARGB(m_Alpha[0],255,255,255);
				pVtx[1].diffuse = D3DCOLOR_ARGB(m_Alpha[0],255,255,255);
				pVtx[2].diffuse = D3DCOLOR_ARGB(m_Alpha[0],255,255,255);
				pVtx[3].diffuse = D3DCOLOR_ARGB(m_Alpha[0],255,255,255);
				break;
			case MODE_RESET:
				pVtx[0].diffuse = D3DCOLOR_ARGB(m_Alpha[1],255,255,255);
				pVtx[1].diffuse = D3DCOLOR_ARGB(m_Alpha[1],255,255,255);
				pVtx[2].diffuse = D3DCOLOR_ARGB(m_Alpha[1],255,255,255);
				pVtx[3].diffuse = D3DCOLOR_ARGB(m_Alpha[1],255,255,255);
				break;
			case MODE_QUIT:
				pVtx[0].diffuse = D3DCOLOR_ARGB(m_Alpha[2],255,255,255);
				pVtx[1].diffuse = D3DCOLOR_ARGB(m_Alpha[2],255,255,255);
				pVtx[2].diffuse = D3DCOLOR_ARGB(m_Alpha[2],255,255,255);
				pVtx[3].diffuse = D3DCOLOR_ARGB(m_Alpha[2],255,255,255);
				break;
			default:
				break;
		}
	
		pVtx+=4;
	}

	//���b�N�J��
	m_pD3DVtxBufferCur->Unlock();
}
//�J��
void CPause::Uninit()
{
	SAFE_RELEASE(m_pD3DTex);
	SAFE_RELEASE(m_pD3DVtxBuffer);
	for(int i = 0;i < 3;i++)
	{
		SAFE_RELEASE(m_pD3DTexCur[i]);
	}
	SAFE_RELEASE(m_pD3DVtxBufferCur);
}
//�`��
void CPause::Draw()
{
	//���e�X�g
//	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
//	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF,0);
//	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	//�e�N�X�`����\�����|���S�����������ɂ������ꍇ
//	m_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);
//	m_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);

///*
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//m_pD3DDevice->SetTexture(0,NULL);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

//*/
	for(int i = 0; i < 3;i++)
	{

		//�f�[�^��n��
		m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBufferCur,0,sizeof(VERTEX_2D));
		//FVF�̐ݒ�
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
		//�e�N�X�`���̐ݒ�
		m_pD3DDevice->SetTexture(0,m_pD3DTexCur[i]);
		//m_pD3DDevice->SetTexture(0,NULL);
		//�|���S���̐ݒ�
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,i*4,2);
	}

	//���ɖ߂�
//	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
}

//eof