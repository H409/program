//=============================================================================
//
// �p�[�e�B�N���̏��� [CPaticle.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//�w�b�_�[�C���N���[�h
#include "CPaticle.h"
#include "CRender.h"
#include <cmath>
#include "CPlayer.h"

inline DWORD GET_ADDRESS( FLOAT f ) { return *((DWORD*)&f); }
#define SPRITE_WIDTH	(256)
#define SPRITE_HEIGHT	(256)
#define COLOR_MAX	(255)

//����
CPaticle* CPaticle::Create(CRender* pRender,D3DXVECTOR3 pos,char* ptexfilename)
{
	CPaticle* pPaticle = new CPaticle(4);

	pPaticle->Init(pRender,pos,ptexfilename);

	pPaticle->SetPosition(pos);

	return pPaticle; 
}

//������
HRESULT	CPaticle::Init( CRender* pRender)
{
	return S_OK;
}
//�I�[�o�[���[�h
HRESULT CPaticle::Init(CRender* pRender,D3DXVECTOR3 pos,char *ptexfilename)
{
	m_pRender = pRender;
	m_pD3DDevice = pRender->getDevice();
	

	m_pos = pos;
	m_rot = D3DXVECTOR3(0,0,0);
	m_scl = D3DXVECTOR3(10,10,10);
	m_DeleteCnt = 0;
	m_continueTime = 1000.0f;
	//�o�[�e�b�N�X�o�b�t�@
	MY_VERTEX_1* pv;
	
	if( FAILED( m_pD3DDevice->CreateVertexBuffer( PATICLE_MAX * sizeof(MY_VERTEX_1), 
												D3DUSAGE_WRITEONLY, FVF_VERTEX_MINE, 
												D3DPOOL_MANAGED, &m_pVBuffer, NULL ) ) ) 
	{
		return E_FAIL;
	}
	m_pVBuffer->Lock( 0, 0, (LPVOID*)&pv, 0 );
	for(int i = 0; i < PATICLE_MAX; i++)
	{
		pv[i].color  = (DWORD)D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	m_pVBuffer->Unlock();
//	D3DXCreateTextureFromFile(m_pD3DDevice,ptexfilename,&m_pTexture);
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFileEx(m_pD3DDevice, ptexfilename,0,0,0,0,D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR,
			0xFF000000 , NULL, NULL, &m_pTexture);


	/*
	for(int i = 0;i < PATICLE_MAX;i++)
	{
		m_paticle[i].m_vector.x = ( (float)rand() /(float)RAND_MAX * 4 )-2;// -2 �` 2
		m_paticle[i].m_vector.y	= ( (float)rand() /(float)RAND_MAX * 4 )-2;// -2 �` 2
		m_paticle[i].m_vector.z = ( (float)rand() /(float)RAND_MAX * 40 )+30;// 30 �` 70

		m_paticle[i].m_fScale = 10.0f;
		m_paticle[i].m_dwColor = D3DCOLOR_ARGB(255,255,255,255);
	}
	*/

	DWORD time = ::timeGetTime();

	if(m_pRender->GetMode() == MODE_TITLE)
	{
		for(int i = 0;i < PATICLE_MAX;i++)
		{
			// �|�C���g�X�v���C�g�̏����ʒu
			m_post[i].pos =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �|�C���g�X�v���C�g�̏����x�Ƃ��̕���
			m_post[i].vec.x = ((float)rand() / (float)RAND_MAX)*30.0f - 15.0f; 
			m_post[i].vec.y = ((float)rand() / (float)RAND_MAX)*30.0f + 30.0f;
			m_post[i].vec.z = ((float)rand() / (float)RAND_MAX)*30.0f - 15.0f;

			// �|�C���g�X�v���C�g�̃T�C�Y
			m_post[i].psize =  ((float)rand() / (float)RAND_MAX)*4.0f + 8.0f; 

			// �|�C���g�X�v���C�g�̌p������
			m_post[i].duration = ((float)rand() / (float)RAND_MAX)*2.0f+2.0f; 

			// �|�C���g�X�v���C�g�̊J�n����
			m_post[i].start_time = time  - (DWORD)(((float)rand() / (float)RAND_MAX)*2.0f*1000.0f);
		}
	}

	if(m_pRender->GetMode() == MODE_GAME)
	{
		for(int i = 0; i < PATICLE_MAX; i++)
		{
			// �|�C���g�X�v���C�g�̈ʒu
			m_post[i].pos =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �|�C���g�X�v���C�g�̏����x�Ƃ��̕���
			m_post[i].vec.x = ((float)rand() / (float)RAND_MAX)*0.50f - 0.25f; 
			m_post[i].vec.y = ((float)rand() / (float)RAND_MAX)*1.00f + 1.00f;
			m_post[i].vec.z = ((float)rand() / (float)RAND_MAX)*0.50f - 0.25f;

			// �|�C���g�X�v���C�g�̃T�C�Y
			m_post[i].psize =  ((float)rand() / (float)RAND_MAX)*4.0f + 8.0f; 

			// �|�C���g�X�v���C�g�̌p������
			m_post[i].duration = ((float)rand() / (float)RAND_MAX)*1.0f + 5.0f; 

			//�|�C���g�X�v���C�g�� �J�n����
			m_post[i].start_time = time -  (DWORD)(((float)rand() / (float)RAND_MAX)*5000.0f);

		}
	}
	return S_OK;
}
//�X�V
void CPaticle::Update(void)
{
	
	m_DeleteCnt++;
	

	float t;	
	float alpha;
	DWORD time = timeGetTime();
	MY_VERTEX_1* pv;

	if(m_pRender->GetMode() == MODE_TITLE)
	{
		m_pVBuffer->Lock( 0, 0, (LPVOID*)&pv, 0 );
		for(int i=0; i < PATICLE_MAX; i++)
		{

			// �o�ߎ��Ԃ��v�Z
			t = (float(time - m_post[i].start_time ))/1000.0f;

			// �p�����Ԃ��z���Ă����珉��������
			if(t > m_post[i].duration)
			{
				m_post[i].pos =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_post[i].start_time = time;
				m_post[i].duration = ((float)rand() / (float)RAND_MAX)*2.0f + 2.0f; 
				t = 0.0f;
			}
			// �|�C���g�X�v���C�g�̈ʒu�̌v�Z
			pv[i].p.x = m_post[i].pos.x + m_post[i].vec.x*t + 0.5f * ( 0.0f) * t * t;
			pv[i].p.y = m_post[i].pos.y + m_post[i].vec.y*t + 0.5f * (-9.8f) * t * t;
			pv[i].p.z = m_post[i].pos.z + m_post[i].vec.z*t + 0.5f * ( 0.0f) * t * t;

			// �|�C���g�X�v���C�g�̃T�C�Y��ݒ�
			pv[i].p_size = m_post[i].psize;
		}
		m_pVBuffer->Unlock();
	}

	if(m_pRender->GetMode() == MODE_GAME)
	{
		m_pVBuffer->Lock( 0, 0, (LPVOID*)&pv, 0 );
		if(m_DeleteCnt < PATICLE_DELETE_CNT)
		{
			for(int i=0; i < PATICLE_MAX; i++)
			{
		
				// �p�����Ԃ��v�Z
				t = (float(time - m_post[i].start_time ))/m_continueTime;
		
				// �p�����Ԃ𒴂��Ă����珉��������
				if(t > m_post[i].duration)
				{
					m_post[i].pos =  m_pos;
					m_post[i].start_time = time;
					m_post[i].duration = ((float)rand() / (float)RAND_MAX)*1.0f + 5.0f;
					t = 0.0f;
				}
		
				// �|�C���g�X�v���C�g�̈ʒu�̌v�Z
				pv[i].p.x = m_post[i].pos.x + m_post[i].vec.x*t + 0.5f * ( 5.0f) * t * t;
				pv[i].p.y = m_post[i].pos.y + m_post[i].vec.y*t + 0.5f * ( 0.0f) * t * t;
				pv[i].p.z = m_post[i].pos.z + m_post[i].vec.z*t + 0.5f * ( 0.0f) * t * t;
			
				// �����x�ƃT�C�Y�̌v�Z
				alpha = 1.0f - t/m_post[i].duration;
				pv[i].color = (DWORD)D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
				pv[i].p_size = m_post[i].psize + t/m_post[i].duration*8.0f;
			}
		}
		if(m_DeleteCnt >= PATICLE_DELETE_CNT)
		{
			m_continueTime = 800.0f;
			for(int i=0; i < PATICLE_MAX; i++)
			{
		
				// �p�����Ԃ��v�Z
				t = (float(time - m_post[i].start_time ))/m_continueTime;
		
				// �p�����Ԃ𒴂��Ă����珉��������
				if(t > m_post[i].duration)
				{
					m_post[i].pos =  m_pos;
					m_post[i].start_time = time;
					m_post[i].duration = ((float)rand() / (float)RAND_MAX)*1.0f + 5.0f;
					t = 0.0f;
				}
		
				// �|�C���g�X�v���C�g�̈ʒu�̌v�Z
				pv[i].p.x = m_post[i].pos.x + m_post[i].vec.x*t + 0.5f * ( 5.0f) * t * t;
				pv[i].p.y = m_post[i].pos.y + m_post[i].vec.y*t + 0.5f * ( 0.0f) * t * t;
				pv[i].p.z = m_post[i].pos.z + m_post[i].vec.z*t + 0.5f * ( 0.0f) * t * t;
			
				// �����x�ƃT�C�Y�̌v�Z
				alpha = 1.0f - t/m_post[i].duration;
				pv[i].color = (DWORD)D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
				pv[i].p_size = m_post[i].psize + t/m_post[i].duration*8.0f;
			}
		
		}
		m_pVBuffer->Unlock();
		if(m_DeleteCnt >= PATICLE_DELETE_CNT)
		{
			CPaticle::Uninit();
		}
	}	
}
//�J��
void CPaticle::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);		//�e�N�X�`���̊J��
	SAFE_RELEASE(m_pVBuffer);
	Release();
}
//�`��
void CPaticle::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMatrixIdentity(&m_mtxWorld);
///*
	//�g�k
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
//*/
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	if(m_pRender->GetMode() == MODE_GAME)
	{
	//FOG�؂�
		m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}
	// ���ʕ`�惂�[�h�̎w��
//	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ���C�g�v�Z�����Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// �y��r���s�Ȃ�Ȃ�
//	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// �f�B�U�����O���s�Ȃ��i���i���`��j
	m_pD3DDevice->SetRenderState( D3DRS_DITHERENABLE,   TRUE );
	
	// �e�N�X�`���X�e�[�W�̐ݒ� 
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	
	// �A���t�@�u�����f�B���O���s��
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE);
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	
	// �e�N�X�`���t�B���^�[�̐ݒ�
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	// �|�C���g�X�v���C�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSIZE,Float2DWORD(1.0f));		
	m_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN,Float2DWORD(0.0f));
	
	//�|�C���g�X�P�[���̌W��
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A,Float2DWORD(0.0f));
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B,Float2DWORD(0.0f));
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C,Float2DWORD(1.0f));
/*
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_ALWAYS);
	//���ꂼ�ꂪ1���_�݂̂ŃX�v���C�g�ɂȂ�
	m_pD3DDevice->SetRenderState( D3DRS_POINTSPRITEENABLE ,TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  TRUE );	
	m_pD3DDevice->SetRenderState( D3DRS_POINTSIZE_MAX, GET_ADDRESS(100.0f));

	m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, TRUE );

	//���u�����h
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, D3DBLENDOP_ADD );	
	m_pD3DDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_ONE );


	//���C�e�B���O�v�Z�͂��Ȃ��B�@�[�x�o�b�t�@�ɂ͏������܂Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);  
//	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
//*/
	

	//�|�C���g�X�v���C�g�p�̃e�N�X�`�����Z�b�g
	m_pD3DDevice->SetTexture(0,m_pTexture);

	// �I�u�W�F�N�g�̕`��
	m_pD3DDevice->SetStreamSource( 0, m_pVBuffer, 0, sizeof(MY_VERTEX_1) );
	m_pD3DDevice->SetFVF( FVF_VERTEX_MINE );
	m_pD3DDevice->DrawPrimitive( D3DPT_POINTLIST, 0, PATICLE_MAX);
/*
	//���_�̌^���Z�b�g
	m_pD3DDevice->SetFVF(FVF_VERTEX_PATCLE);
	//�����_�����O�@�����2�̃|�C���g�X�v���C�g�̂�
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, PATICLE_MAX, m_paticle, sizeof(PATICLE));
*/
	//���C�g�t����
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	//���u�����h
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, FALSE );

	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	
	//�|�C���g�X�v���C�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE,FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE,FALSE);

	// �e�N�X�`���t�B���^�[�̐ݒ�
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );

	// �e�N�X�`���X�e�[�W�̐ݒ� 
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//�J�����O
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

	m_pD3DDevice->SetRenderState( D3DRS_DITHERENABLE, FALSE );
	//�[�x�o�b�t�@�ɏ�������
	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	//FOG��������
	if(m_pRender->GetMode() == MODE_GAME)
	{
		m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}
}

void CPaticle::DrawShade()
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMatrixIdentity(&m_mtxWorld);

	//�g�k
//	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//��]
//	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//���s�ړ�
//	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_ALWAYS);
	//���ꂼ�ꂪ1���_�݂̂ŃX�v���C�g�ɂȂ�
	m_pD3DDevice->SetRenderState( D3DRS_POINTSPRITEENABLE ,TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  TRUE );	
	m_pD3DDevice->SetRenderState( D3DRS_POINTSIZE_MAX, GET_ADDRESS(100.0f));

	m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, TRUE );

	//���u�����h
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, D3DBLENDOP_ADD );	
	m_pD3DDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_ONE );


	//���C�e�B���O�v�Z�͂��Ȃ��B�@�[�x�o�b�t�@�ɂ͏������܂Ȃ�
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);  
//	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	//�|�C���g�X�v���C�g�p�̃e�N�X�`�����Z�b�g
	m_pD3DDevice->SetTexture(0,m_pTexture);

	//���_�̌^���Z�b�g
	m_pD3DDevice->SetFVF(FVF_VERTEX_MINE);
	//�����_�����O�@�����2�̃|�C���g�X�v���C�g�̂�
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, PATICLE_MAX, m_post, sizeof(MY_VERTEX_1));

	//���C�g�t����
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	//���u�����h
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, FALSE );

	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

}
//eof