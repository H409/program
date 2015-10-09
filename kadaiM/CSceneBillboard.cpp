//�w�b�_�[�C���N���[�h
#include "CSceneBillboard.h"
#include "CRender.h"
#include "CCamera.h"

//�쐬
CSceneBillboard* CSceneBillboard::Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,float fsize)
{
	CSceneBillboard* pBillboard = new CSceneBillboard(2);

	pBillboard->Init(pRender,xfilename,0,fsize);

	pBillboard->SetPosition(pos);

	return pBillboard;

}
//������
HRESULT CSceneBillboard::Init(CRender* pRender)
{
	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\bg001.jpg",&m_pD3DTex);
	
	//�|���S���ݒ�
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffer,
											NULL)))
	{
		return E_FAIL;
	}
	m_pos = D3DXVECTOR3(0,0,0);		//���W
	m_rot = D3DXVECTOR3(0,0,0);		//��]
	m_scl = D3DXVECTOR3(1,1,1);
	VERTEX_3D *pVtx = NULL;
	//���b�N
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//���_
	pVtx[0].vtx = D3DXVECTOR3(-50.0f,50.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(50.0f,50.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-50.0f,-50.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(50.0f,-50.0f,0.0f);

	//���W�ϊ���ʒu
	pVtx[0].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0,0.0f,-1.0f);

	//�F
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0,1);
	pVtx[1].tex = D3DXVECTOR2(0,0);
	pVtx[2].tex = D3DXVECTOR2(1,1);
	pVtx[3].tex = D3DXVECTOR2(1,0);
	//�A�����b�N
	m_pD3DVtxBuffer->Unlock();
	return S_OK;
}

HRESULT CSceneBillboard::Init(CRender* pRender,char* ptexfilename,float fangle,float fsize)
{
	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,ptexfilename,&m_pD3DTex);
	
	//�|���S���ݒ�
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffer,
											NULL)))
	{
		return E_FAIL;
	}
	//m_pos = D3DXVECTOR3(0,0,0);		//���W
	m_rot = D3DXVECTOR3(0,fangle,0);		//��]
	m_scl = D3DXVECTOR3(1,1,1);
	VERTEX_3D *pVtx = NULL;
	//���b�N
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//���_
	pVtx[0].vtx = D3DXVECTOR3(0.0f,fsize,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(fsize,fsize,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(fsize,0.0f,0.0f);

	//���W�ϊ���ʒu
	pVtx[0].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0,0.0f,-1.0f);

	//�F
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0,0);
	pVtx[1].tex = D3DXVECTOR2(1,0);
	pVtx[2].tex = D3DXVECTOR2(0,1);
	pVtx[3].tex = D3DXVECTOR2(1,1);
	//�A�����b�N
	m_pD3DVtxBuffer->Unlock();
	return S_OK;
}

HRESULT CSceneBillboard::InitAnime(CRender* pRender,char* ptexfilename)
{
	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	//�A�j���[�V�����p�e�N�X�`���Ԋu
	m_fTexU = 1.0f/static_cast<float>(ANIM_PTN);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,ptexfilename,&m_pD3DTex);
	
	//�|���S���ݒ�
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffer,
											NULL)))
	{
		return E_FAIL;
	}
	m_pos = D3DXVECTOR3(0,0,0);		//���W
	m_rot = D3DXVECTOR3(0,0,0);		//��]
	m_scl = D3DXVECTOR3(1,1,1);
	VERTEX_3D *pVtx = NULL;
	//���b�N
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//���_
	pVtx[0].vtx = D3DXVECTOR3(0.0f,15.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(15.0f,15.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(15.0f,0.0f,0.0f);

	//���W�ϊ���ʒu
	pVtx[0].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0,0.0f,-1.0f);

	//�F
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fTexU,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fTexU,1.0f);
	
	//�A�����b�N
	m_pD3DVtxBuffer->Unlock();

	m_bFlag = true;
	m_nAnimCnt = 0;
	return S_OK;
}
//�J��
void CSceneBillboard::Uninit()
{
//	SAFE_RELEASE(m_pD3DDevice);		//Direct3dDevice�I�u�W�F�N�g�̊J��
	SAFE_RELEASE(m_pD3DTex);		//�e�N�X�`���̊J��
	SAFE_RELEASE(m_pD3DVtxBuffer);	//���_�o�b�t�@�̊J��
	
	Release();
}
//�X�V
void CSceneBillboard::Update()
{
	/*
	m_rot.y -= D3DX_PI * 0.001f;

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

	*/
}

void CSceneBillboard::UpdateAnime()
{

	VERTEX_3D *pVtx = NULL;

	if(m_bFlag)
	{

		///*
		//�J�E���^�v���X
		m_nAnimCnt++;
		//�e�N�X�`�����W�v�Z
		m_fTexUt = (U_POSITION*(m_nAnimCnt/ANIM_WAIT%ANIM_PTN))/10.f;

		//���b�N
		m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);
			
		pVtx[0].tex = D3DXVECTOR2(m_fTexUt,0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_fTexUt+m_fTexU,0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_fTexUt,1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_fTexUt+m_fTexU,1.0f);
			
		//�A�����b�N
		m_pD3DVtxBuffer->Unlock();
		//*/
		if(m_nAnimCnt >= EXPROSION_ENDCNT)
		{
			m_nAnimCnt = 0;
			m_bFlag = false;
			Uninit();
		}
	}
}
//�`��
void CSceneBillboard::Draw()
{
	//�ϐ��錾
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxView;
	//�r���[�}�g���b�N�X�擾
	mtxView = GetMtxView();
	
	D3DXMatrixIdentity(&m_mtxWorld);

	//���e�X�g
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF,0);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_ALWAYS);
/*	
	//��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
*/
	//�g�k
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//�r���{�[�h
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	//���[���h�g�����X�t�H�[��
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//���C�g�؂�
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_3D));
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//���ɖ߂�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//���C�g�t����
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
}
void CSceneBillboard::DrawShade()
{
		//�ϐ��錾
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxView;
	//�r���[�}�g���b�N�X�擾
	mtxView = GetMtxView();
	
	D3DXMatrixIdentity(&m_mtxWorld);

	//���e�X�g
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF,0);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_ALWAYS);
/*	
	//��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
*/
	//�g�k
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//�r���{�[�h
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	//���[���h�g�����X�t�H�[��
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//���C�g�؂�
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_3D));
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//���ɖ߂�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//���C�g�t����
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
}
void CSceneBillboard::DrawAnime(void)
{
	//�ϐ��錾
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxView;

	//���e�X�g
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF,0);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	//�r���[�}�g���b�N�X�擾
	mtxView = GetMtxView();
	D3DXMatrixIdentity(&m_mtxWorld);

/*	
	//��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
*/
	//�g�k
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//�r���{�[�h
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	//���[���h�g�����X�t�H�[��
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	if(m_bFlag)
	{
		//�f�[�^��n��
		m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_3D));
		//FVF�̐ݒ�
		m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
		//�e�N�X�`���̐ݒ�
		m_pD3DDevice->SetTexture(0,m_pD3DTex);
		//�|���S���̐ݒ�
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
	//���ɖ߂�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
}

