//�w�b�_�[�C���N���[�h
#include "CMeshCylinder.h"
#include "CRender.h"

#define CLD_TEX_SIZE_X		(4)			// �e�N�X�`���̃T�C�Y�̓|���S�������u���b�N����
#define CLD_TEX_SIZE_Y		(1)			// �e�N�X�`���̃T�C�Y�̓|���S���c���u���b�N����


CMeshCylinder* CMeshCylinder::Create(CRender* pRender,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CMeshCylinder* pMeshCylinder = new CMeshCylinder(3);

	pMeshCylinder->Init(pRender,20,20,100,100,pos,rot,"data\\Texture\\mountain.jpg",400.0f);

	pMeshCylinder->SetPosition(pos);

	return pMeshCylinder; 
}
HRESULT CMeshCylinder::Init(CRender* pRender)
{
	return S_OK;
}
HRESULT CMeshCylinder::Init(CRender* pRender,int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY,D3DXVECTOR3 pos,D3DXVECTOR3 rot,char *pTexPath,float fSizeRadius)
{
	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,pTexPath,&m_pD3DTex);


	// �����_��(�e�N�X�`�����邽�߂�X��1����)
	m_nNumVertex = (nNumBlockX+1)*(nNumBlockY+1);

	// ���|���S����
	m_nNumPolygon = nNumBlockX*nNumBlockY*2+(nNumBlockY-1)*4;

	// ���_�̑��C���f�b�N�X��
	//										���_��					  +				 �_�u���Ă�_				+ �n�_�ɖ߂�_	+ �k�ރ|���S���p�_�u��
	//g_nCldNumVertexIdx =  (nNumBlockX)*(nNumBlockY+1) + (nNumBlockX)*(nNumBlockY-1) + (nNumBlockY)*2 + (nNumBlockY-1)*2;
	m_nNumVertexIndex =  (nNumBlockX)*(2*nNumBlockY) + 2*(2*nNumBlockY-1);


	//�n�ʃ|���S���̐ݒ��������
	m_pos	= pos;
	m_rot	= rot;
	m_scl	= D3DXVECTOR3(1.0f,1.0f,1.0f);

	//�|���S���ݒ�
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}
	
	//�C���f�b�N�X������
	if(FAILED(m_pD3DDevice->CreateIndexBuffer(sizeof(WORD)*m_nNumVertexIndex,
										D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX16,
										D3DPOOL_MANAGED,
										&m_pD3DIndexBuff,
										NULL)))
	{
		return E_FAIL;
	}

	// �z��ԍ�
	int nNum = 0;

	// ���_���v�Z�p
	float fPosX = 0.0f, fPosZ = 0.0f, fPosY = 0.0f;
	float fTexU = 0.0f, fTexV = 0.0f;
	float fRad = 0.0f;
	float fArc = 360.0f / static_cast<float>(nNumBlockX);
	float fArc1 = D3DX_PI*2 / static_cast<float>(nNumBlockX);
	// i�st��
	int t = 0;
	int i = 0;

	// ���_���Z�b�g
	VERTEX_3D *pVtx;

	// �C���f�b�N�X���̃Z�b�g
	WORD *pIndex;

	
//==== ���_���ݒ� ====//
	//���b�N
	m_pD3DVtxBuff -> Lock(0, 0, (void**)&pVtx, 0);

	// ���ƂłȂ����Ƃ�
	// i �_ t�i�ڂɎ��v���Œ��_�ݒ�
	for(t = 0; t <= nNumBlockY; t++)
	{
		fTexU = 0;

		//�@�㉺�t�ɂȂ�̂�-�ɂ���
		fTexV = static_cast<float>(t)/nNumBlockY;
		fRad = 0.0f;
		for(i = 0; i <= nNumBlockX; i++)
		{
			nNum = t * (nNumBlockX+1) + i;
			
			fRad = fArc1* i ;
			
			fPosX = cosf(fRad)*fSizeRadius;
			fPosZ = sinf(fRad)*fSizeRadius;
			fPosY = static_cast<float>(t)*fSizeBlockY; 

			fTexU = static_cast<float>(i)/nNumBlockX;

			pVtx[nNum].vtx = D3DXVECTOR3(fPosX, fPosY, fPosZ);
			// �ʂ��Ƃɖ@���ݒ�
			//pVtx[nNum].nor = D3DXVECTOR3(sinf(fRad), sinf(fRad), -cosf(fRad));
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, sinf(fRad), -cosf(fRad));
			//pVtx[nNum].nor = D3DXVECTOR3(0.0f, sinf(fRad), -cosf(fRad));
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			//pVtx[nNum].tex = D3DXVECTOR2(static_cast<float>(-i), static_cast<float>(-t));
			pVtx[nNum].tex = D3DXVECTOR2(-fTexU,-fTexV);
		}
	}

	// �A�����b�N
	m_pD3DVtxBuff -> Unlock();

//===== ���_�C���f�b�N�X�ݒ�@====//
	// ���b�N
	m_pD3DIndexBuff -> Lock(0, 0, (void**)&pIndex, 0);


	// i �_ t �i��
	t = 0;
	i = 0;
	// i �_ t �i�ڂɎ��v���Œ��_�ݒ肵�Ă���
	for(int j = 0; j < m_nNumVertexIndex; ++j)
	{

		// �k�ރ|���S���_
		if(j ==2*(nNumBlockX+1)+t*(2*(nNumBlockX+1)+2) )
		{
			pIndex[j] =   i-1 + t*(nNumBlockX+1);
			pIndex[j+1] = (t+2)*(nNumBlockX+1);

			// �i���ς��
			j += 2;
			t++;
			i = 0;
		}

		// ��̓_
		if(j % 2 == 0)
		{
			pIndex[j] = i + (t+1)*(nNumBlockX+1);
			
		}
		// ���̓_
		else
		{
			pIndex[j] = i + t*(nNumBlockX+1);
			++i;
		}

	} 

	// �A�����b�N
	m_pD3DIndexBuff -> Unlock();

	return S_OK;
}

void CMeshCylinder::Uninit()
{
	SAFE_RELEASE(m_pD3DVtxBuff);	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_pD3DIndexBuff);	//�C���f�b�N�X�o�b�t�@�̊J��
	SAFE_RELEASE(m_pD3DTex);		//�e�N�X�`���̊J��
	

	Release();
}

void CMeshCylinder::Update()
{

}

void CMeshCylinder::Draw()
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//���[���h�g�����X�t�H�[��
	D3DXMatrixIdentity(&m_mtxWorld);
	//�g�k
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

//	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //�J�����O���Ȃ�
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pD3DDevice->SetIndices(m_pD3DIndexBuff);
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNumPolygon);
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ); //�J�����O����
//	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
}
void CMeshCylinder::DrawShade()
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//���[���h�g�����X�t�H�[��
	D3DXMatrixIdentity(&m_mtxWorld);
	//�g�k
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

//	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //�J�����O���Ȃ�
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pD3DDevice->SetIndices(m_pD3DIndexBuff);
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertexIndex,0,m_nNumPolygon);
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ); //�J�����O����


}

