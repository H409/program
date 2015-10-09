//�w�b�_�[�C���N���[�h
#include "CMeshDome.h"
#include "CRender.h"

#define CLD_TEX_SIZE_X		(4)			// �e�N�X�`���̃T�C�Y�̓|���S�������u���b�N����
#define CLD_TEX_SIZE_Y		(1)			// �e�N�X�`���̃T�C�Y�̓|���S���c���u���b�N����


CMeshDome* CMeshDome::Create(CRender* pRender,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CMeshDome* pMeshDome = new CMeshDome(3);

	pMeshDome->Init(pRender,50,50,100,50,pos,rot,"data\\Texture\\sky006.jpg",500.0f);

	pMeshDome->SetPosition(pos);

	return pMeshDome; 
}
HRESULT CMeshDome::Init(CRender* pRender)
{
	return S_OK;
}
HRESULT CMeshDome::Init(CRender* pRender,int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY,D3DXVECTOR3 pos,D3DXVECTOR3 rot,char *pTexPath,float fSizeRadius)
{
	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,pTexPath,&m_pD3DTex);


	// �����_��(�e�N�X�`�����邽�߂�X��1����)
	m_nNumVertex = (nNumBlockX+1)*(nNumBlockY+1);

	// ���|���S����
	m_nNumPolygon = nNumBlockX*nNumBlockY*2+(nNumBlockY-1)*4;

	int n = 0;
	// ���_�̑��C���f�b�N�X��
	//										���_��					  +				 �_�u���Ă�_				+ �n�_�ɖ߂�_	+ �k�ރ|���S���p�_�u��
	//m_nNumVertexIndex =  (nNumBlockX)*(nNumBlockY+1) + (nNumBlockX)*(nNumBlockY-1) + (nNumBlockY)*2 + (nNumBlockY-1)*2;
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

	// ���_���̃Z�b�g
	// �z��ԍ�
	int nNum = 0;

	// ���_���v�Z�p
	float fPosX = 0.0f, fPosZ = 0.0f, fPosY = 0.0f;
	float fTexU = 1.0f/static_cast<float>(nNumBlockX), fTexV = 1.0f / static_cast<float>(nNumBlockY);
	float fRad = 0.0f;
	float fRadY = 0.0f;
	float fArc = D3DX_PI*2 / static_cast<float>(nNumBlockX);
	float fArcY = D3DX_PI/2 / static_cast<float>(nNumBlockY);
	float fLengthXZ = 0.0f;
	// i�st��
	int j = 0;
	int i = 0;

	// ���_���Z�b�g
	VERTEX_3D *pVtx;


	float fRadiusSub = fSizeBlockY;
//==== ���_���ݒ� ====//
	//���b�N
	m_pD3DVtxBuff -> Lock(0, 0, (void**)&pVtx, 0);

	// ���ƂłȂ����Ƃ�
	// i �_ t�i�ڂɎ��v���Œ��_�ݒ�
	for(i = 0; i <= nNumBlockY; i++)
	{
		fTexU = 0;

		//�@�㉺�t�ɂȂ�̂�-�ɂ���
		fTexV = static_cast<float>(i)/nNumBlockY;
		
		fLengthXZ = cosf(fArcY*i)*fSizeRadius;
		fPosY = sinf(fArcY*i)*fSizeRadius*1.0f;

		for(j = 0; j <= nNumBlockX; j++)
		{
			nNum = i * (nNumBlockX+1) + j;
	
			fPosX = sinf(fArc*j)*fLengthXZ;			
			fPosZ = cosf(fArc*j)*fLengthXZ;

	
			fTexU = static_cast<float>(j)/nNumBlockX;

			pVtx[nNum].vtx = D3DXVECTOR3(fPosX, fPosY, fPosZ);
			// �ʂ��Ƃɖ@���ݒ�
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, sinf(fArcY*i), -cosf(fArc*j));
			//pVtx[nNum].nor = D3DXVECTOR3(sinf(fArc*j), sinf(fArcY*i), cosf(fArc*j));
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			//pVtx[nNum].tex = D3DXVECTOR2(1.0f+fTexU*static_cast<float>(i), 1.0f+fTexV*static_cast<float>(j));
			pVtx[nNum].tex = D3DXVECTOR2(-fTexU,-fTexV);
			//pVtx[nNum].tex = D3DXVECTOR2(static_cast<float>(j), static_cast<float>(i));
		}
	}

	// �A�����b�N
	m_pD3DVtxBuff -> Unlock();
	
	//�C���f�b�N�X�ݒ�
	WORD *pIndex;
	// xIndex�sxzIndex��
	int xIndex = 0;
	int yIndex = 0;



	m_pD3DIndexBuff->Lock(0,0,(void**)&pIndex,0);	//���b�N
	
	for(int i = 0; i < m_nNumVertexIndex; i++)
	{
		// �k�ރ|���S���_
		if(i == 2*(nNumBlockX+1)+yIndex*(2*(nNumBlockX+1)+2))
		{
			pIndex[i] =  (xIndex -1) + yIndex*(nNumBlockX+1);
			pIndex[i+1] = xIndex + (yIndex+1)*(nNumBlockX+1);

			// �i���ς��
			i += 2;
			yIndex++;
			xIndex = 0;
		}

		// ���̓_
		if(i % 2 == 0)
		{
			pIndex[i] = xIndex + (yIndex+1)*(nNumBlockX+1);

		}
		// ��̓_
		else
		{
			pIndex[i] = xIndex + yIndex*(nNumBlockX+1);
			xIndex++;
		}
	}

	m_pD3DIndexBuff->Unlock();	//�A�����b�N

	return S_OK;
}

void CMeshDome::Uninit()
{

	SAFE_RELEASE(m_pD3DTex);		//�e�N�X�`���̊J��
	SAFE_RELEASE(m_pD3DVtxBuff);	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_pD3DIndexBuff);	//�C���f�b�N�X�o�b�t�@�̊J��

	Release();
}

void CMeshDome::Update()
{

}

void CMeshDome::Draw()
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
//	m_pD3DDevice->SetTexture(0,NULL);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNumPolygon);
	
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ); //�J�����O����
}
void CMeshDome::DrawShade()
{

}
/*
	for(t = 0; t <= nNumBlockY; t++)
	{
		fTexU = 0;

		//�@�㉺�t�ɂȂ�̂�-�ɂ���
		fTexV = static_cast<float>(-t)/nNumBlockY;
		fRad = 0.0f;
		for(i = 0; i <= nNumBlockX; i++)
		{
			nNum = t * (nNumBlockX+1) + i;
			//fRad += nArc;
			fRad = nArc* i * D3DX_PI / 180.0f;
			//fLengthXZ = cosf(fRad*i)*fSizeRadius;
			//fPosX = sinf(fRad*i)*fLengthXZ;
			//fPosY = sinf(fRad*t)*fSizeRadius*1.0f;
			//fPosZ = cosf(fRad*i)*fLengthXZ;

			fPosX = fSizeRadius*-sinf(fRad)*cosf(fRadY);
			fPosZ = fSizeRadius*-cosf(fRad) * cosf(fRadY);
			fPosY = fSizeRadius*-sinf(fRadY);

			fTexU = static_cast<float>(-i)/nNumBlockX;

			pVtx[nNum].vtx = D3DXVECTOR3(fPosX, fPosY, fPosZ);
			// �ʂ��Ƃɖ@���ݒ�
			//pVtx[nNum].nor = D3DXVECTOR3(0.0f, -sinf(fRad), cosf(fRad));
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, sinf(fRad), -cosf(fRad));
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[nNum].tex = D3DXVECTOR2(1.0f+fTexU*static_cast<float>(i), 1.0f+fTexV*static_cast<float>(t));
			//pVtx[nNum].tex = D3DXVECTOR2(fTexU,fTexV);
		}
		//fSizeRadius -= fRadiusSub;
		fRadY += fArcY;
	}
//*/


	//for(t = 0; t <= nNumBlockY; t++)
	//{
	//	fTexU = 0;

	//	//�@�㉺�t�ɂȂ�̂�-�ɂ���
	//	fTexV = static_cast<float>(-t)/nNumBlockY;
	//	fRad = 0.0f;
	//	for(i = 0; i <= nNumBlockX; i++)
	//	{
	//		nNum = t * (nNumBlockX+1) + i;
	//		fRad = nArc* i * D3DX_PI / 180.0f;
	//		
	//		fPosX = -sinf(fRad)*fSizeRadius;
	//		fPosZ = -cosf(fRad)*fSizeRadius;
	//		fPosY = t*fSizeRadius; 
	//		//fPosY = sinf(fRad*t)*fSizeBlockY;
	//		fTexU = static_cast<float>(-i)/nNumBlockX;

	//		pVtx[nNum].vtx = D3DXVECTOR3(fPosX, fPosY, fPosZ);
	//		// �ʂ��Ƃɖ@���ݒ�
	//		//pVtx[nNum].nor = D3DXVECTOR3(0.0f, -sinf(fRad), cosf(fRad));
	//		pVtx[nNum].nor = D3DXVECTOR3(0.0f, sinf(fRad), -cosf(fRad));
	//		pVtx[nNum].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	//		//pVtx[nNum].tex = D3DXVECTOR2(static_cast<float>(-i), static_cast<float>(-t));
	//		//pVtx[nNum].tex = D3DXVECTOR2(fTexU,fTexV);
	//		pVtx[nNum].tex = D3DXVECTOR2(1.0f+fTexU*static_cast<float>(i), 1.0f+fTexV*static_cast<float>(t));
	//	}
	//	fSizeRadius -= fRadiusSub;
	//	if(fSizeRadius <= 0 )
	//	{
	//		fSizeRadius = 0;
	//	}
	//}
