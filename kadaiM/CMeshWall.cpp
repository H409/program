//�w�b�_�[�C���N���[�h
#include "CMeshWall.h"
#include "CRender.h"
#include <cmath>
#include "CDebugProc.h"
//�}�N��
#define POS_MARGIN_X	(100)
#define POS_MARGIN_Y	(50)
D3DXVECTOR3	CMeshWall::m_rotVer[4];
int		CMeshWall::m_nCreateCnt = 0;
/*
//�R���X�g���N�^
CMeshWall::CMeshWall(){};
//�f�X�g���N�^
CMeshWall::~CMeshWall(){};
*/
//�쐬
CMeshWall* CMeshWall::Create(CRender* pRender,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CMeshWall* pSceneMeshWall = new CMeshWall();

	pSceneMeshWall->Init(pRender,1,1,500.f,100.f,pos,rot,"data\\Texture\\wall.jpg");

	pSceneMeshWall->SetPosition(pos);
//	pSceneMeshWall->SetRotate(D3DXVECTOR3(0,120,0));

	return pSceneMeshWall;

}
//������
HRESULT CMeshWall::Init(CRender* pRender)
{
	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\bg001.jpg",&m_pD3DTex);
	

	return S_OK;
}
//�������I�[�o�[���[�h
HRESULT CMeshWall::Init(CRender* pRender,int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY,D3DXVECTOR3 pos,D3DXVECTOR3 rot,char *pTexPath)
{
	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(m_pD3DDevice,pTexPath,&m_pD3DTex);

	//�����_��
	m_nNumVertex = (nNumBlockX+1) * (nNumBlockY+1);
	//�|���S����
	m_nNumPolygon = nNumBlockX*nNumBlockY*2+(nNumBlockY-1)*4;
	//�C���f�b�N�X����
	m_nNumVertexIndex = (nNumBlockX+1)*(nNumBlockY+1)+(nNumBlockY-1)*(3+nNumBlockX);

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
	VERTEX_3D *pVtx = NULL;

	float fPosX, fPosY;
	float fTexU, fTexV;
	int nNum = 0;
	//���b�N
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	// i�st��ɒ��_�ݒ�
	for(int i = 0; i <= nNumBlockY; i++)
	{
		fTexU = 0;
		fTexV = (float)i/2.0f;
		for(int j = 0; j <= nNumBlockX; j++)
		{
			nNum = i * (nNumBlockX+1) + j;
			fPosX = -fSizeBlockX * nNumBlockX/2 + j*fSizeBlockX;
			fPosY = fSizeBlockY * nNumBlockY/2 - i*fSizeBlockY;
			fTexU = (float)-j/2.0f;

			pVtx[nNum].vtx = D3DXVECTOR3(fPosX, fPosY, 0.0f);
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ���v��1.0f�ɂȂ�悤�ɂ��Ȃ��ƃ_��
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[nNum].tex = D3DXVECTOR2(float(j), float(i));
		}
	}
	//TODO�l����
	
	//�A�����b�N
	m_pD3DVtxBuff->Unlock();
	
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
//�X�V
void CMeshWall::Uninit()
{
//	SAFE_RELEASE(m_pD3DDevice);		//Direct3dDevice�I�u�W�F�N�g�̊J��
	SAFE_RELEASE(m_pD3DTex);		//�e�N�X�`���̊J��
	SAFE_RELEASE(m_pD3DVtxBuff);	//���_�o�b�t�@�̊J��
	SAFE_RELEASE(m_pD3DIndexBuff);	//�C���f�b�N�X�o�b�t�@�̊J��

	Release();

}
//�J��
void CMeshWall::Update()
{
/*
	m_rot.z -= D3DX_PI * 0.001f;

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
	CDebugProc::Print("wallX:%fwallY:%fwallZ:%f\n",m_rot.x,m_rot.y,m_rot.z);
	CDebugProc::Print("posX:%fposY:%fposZ:%f\n",m_pos.x,m_pos.y,m_pos.z);

	CDebugProc::Print("���_X:%f:Y:%f:Z:%f\n",m_Vertex.x,m_Vertex.y,m_Vertex.z);
}
//�`��
void CMeshWall::Draw()
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

//	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //�J�����O���Ȃ�
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pD3DDevice->SetIndices(m_pD3DIndexBuff);
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNumPolygon);
//	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ); //�J�����O����
}

void CMeshWall::DrawShade()
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

//	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //�J�����O���Ȃ�
	//�f�[�^��n��
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pD3DDevice->SetIndices(m_pD3DIndexBuff);
	//FVF�̐ݒ�
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//�e�N�X�`���̐ݒ�
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//�|���S���̐ݒ�
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertexIndex,0,m_nNumPolygon);

}

D3DXVECTOR3 CMeshWall::GetVertex()
{
	return m_Vertex;
}