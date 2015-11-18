#include "mesh_wall.h"
//=============================================================================
//
// ���b�V���E�H�[������ [CMeshWall.cpp]
// Author : EYUU YUMINAGA
//
//=============================================================================
int MeshWall::m_WallSum=0;
D3DXVECTOR3 MeshWall::m_edges[WALL_MAX];
/*
CMeshWall::CMeshWall(LPDIRECT3DDEVICE9 device)
{
	pDevice=device;
}
*/
MeshWall::~MeshWall()
{

}
MeshWall* MeshWall::Create(LPDIRECT3DDEVICE9 device,float posX,float posY,float posZ,float rotY,
							int nNumBlockX,int nNumBlockY,float fSizeBlockX,float fSizeBlockY)
{
	if(m_WallSum<WALL_MAX)
	{
		MeshWall* p=new MeshWall(device);
		p->Init(posX,posY,posZ,rotY,nNumBlockX,nNumBlockY,fSizeBlockX,fSizeBlockY);
		p->m_id=m_WallSum;
		m_WallSum++;
		return p;
	}
	//�ǂ��ő吔�܂łɒB����
	return 0;
}
HRESULT MeshWall::Init(	float posX,float posY,float posZ,float rotY,
							int nNumBlockX,int nNumBlockY,float fSizeBlockX,float fSizeBlockY)
{
	VERTEX_3D *pVtx;			//���_���
	WORD *pIndex;				//�C���f�b�N�X���

	//�C���f�b�N�X�ԍ��ő吔
	m_VtxIdxNum = SUM_INDEX(nNumBlockX,nNumBlockY);

	//���_���W�ԍ��ő吔
	m_NumVtx = (nNumBlockX+1)*(nNumBlockY+1);

	//�|���S����
	m_NumPolygon = ((nNumBlockX*2)*nNumBlockY)+((nNumBlockY-1)*4);

	//���W
	m_pos = D3DXVECTOR3(posX,posY,posZ);
	//��](���W�A��)
	m_rot = D3DXVECTOR3(0.0f,rotY,0.0f);
	//�g��k��
	m_scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//�ǂ̑傫���ۑ�
	m_wallsizeX=nNumBlockX*fSizeBlockX;
	m_wallsizeY=nNumBlockY*fSizeBlockY;

	//�ǂ��猩�����S���W�ݒ�
	m_center.x=0.0f;
	m_center.y=0.0f;
	m_center.z=0.0f;

		//�C���f�b�N�X�o�b�t�@�̐���
	if(FAILED(pDevice->CreateIndexBuffer(	sizeof(WORD)*m_VtxIdxNum,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pIndexBuff,
											NULL)))
	{
		return E_FAIL;
	}
	//���_�o�b�t�@�̐���
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_NumVtx,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pD3DVtxBuff,
										NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(GetDevice(),"data/TEXTURE/wall004.jpg",&m_pD3DTexture);

	//���_���W�̐ݒ�
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);
	for(int y=0,num=0;y<nNumBlockY+1;y++)
	{
		for(int x=0;x<nNumBlockX+1;x++)
		{
			pVtx[num].vtx = D3DXVECTOR3(-(nNumBlockX*fSizeBlockX/2)+(fSizeBlockX*x),(nNumBlockY*fSizeBlockY/2)+(-fSizeBlockY*y),0);
			pVtx[num].nor = D3DXVECTOR3(0,1.0f,0);
			pVtx[num].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[num].tex = D3DXVECTOR2((float)x/5,(float)y/5);
			num++;
		}
	}
	m_pD3DVtxBuff -> Unlock();

	//�C���f�b�N�X�o�b�t�@�ݒ�
	m_pIndexBuff->Lock(0,0,(void**)&pIndex,0);

	//�J��Ԃ��Ǘ��ϐ�
	int loopx=0;
	int VtxNo=0;
	int check=0;

	for(int y = 0;y<nNumBlockY;y++)
	{
		//�E���̐܂�Ԃ��n�_�ł̃C���f�b�N�X�̕ۑ�
		if(y != 0)
		{
			loopx = 0;
			check =				(y*(nNumBlockX+1))+(((loopx+3)%2)*(nNumBlockX+1)+(loopx/2));

			pIndex[VtxNo] =		(y*(nNumBlockX+1))+(((loopx+1)%2)*(nNumBlockX+1)+(loopx/2));
			VtxNo++;
		}
		for(loopx = 0;loopx<(nNumBlockX+1)*2;loopx++)
		{
			check =				(y*(nNumBlockX+1))+(((loopx+3)%2)*(nNumBlockX+1)+(loopx/2));

			pIndex[VtxNo] =		(y*(nNumBlockX+1))+(((loopx+1)%2)*(nNumBlockX+1)+(loopx/2));
			VtxNo++;
		}
		//����̐܂�Ԃ��n�_�ł̃C���f�b�N�X�ۑ�
		pIndex[VtxNo] = pIndex[VtxNo-1];
		VtxNo++;
	}

	m_pIndexBuff->Unlock();

	return S_OK;
}

void MeshWall::Uninit(void)
{
	CScene3D::Uninit();
	m_WallSum--;
	//RELEASE_P(m_pIndexBuff)
}

void MeshWall::Update(void)
{
	//m_rot_from_center.y+=0.005f;

	if(m_rot.y>D3DX_PI)
	{
		m_rot.y=-D3DX_PI;
	}
	else if(m_rot.y<-D3DX_PI)
	{
		m_rot.y=D3DX_PI;
	}
	//�ǂ�Y���p�x���A�������S����̉�]�ɍ��킹��
	m_rot.y = m_rot_from_center.y;
	//�ʒu�𒆐S����̉�]�ɍ��킹��
	m_pos.x = m_center.x + sinf(m_rot_from_center.y)*m_Length_From_CenterXZ;
	m_pos.z = m_center.z + cosf(m_rot_from_center.y)*m_Length_From_CenterXZ;
	//�p�ʒu�̍X�V
	SetEdge();
	SetLength();
}

void MeshWall::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//���ꂼ��̃}�g���N�X�̐ݒ�
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMatrixScaling(&mtxScl,1.0f,1.0f,1.0f);							//�g��{��
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);				//�X��//�ʓx�@�œ���� Y,X,Z
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);

	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);				//��Ԃ̕��s�ړ�
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���\�[�X�Ƀo�C���h
	pDevice ->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	
	pDevice->SetIndices(m_pIndexBuff);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice ->SetTexture(0,m_pD3DTexture);

	//�|���S���̕`��(�C���f�b�N�X�o�[�W����)
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_VtxIdxNum,0,m_NumPolygon);
}


//�A�N�Z�T�[
void MeshWall::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}
void MeshWall::SetPosition(float x,float y,float z)
{
	m_pos= D3DXVECTOR3(x,y,z);
}
void MeshWall::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}
void MeshWall::SetRotation(float x,float y,float z)
{
	m_rot= D3DXVECTOR3(x,y,z);
}
//�ǂ̊p�̍��W�Z�b�g
void MeshWall::SetEdge(void)
{
	//�p�̈ʒu�v�Z
	m_edge.x=m_pos.x-(cosf(m_rot.y)*(m_wallsizeX/2));
	m_edge.z=m_pos.z+(sinf(m_rot.y)*(m_wallsizeX/2));
	//�p�̈ʒu�ۑ�
	m_edges[m_id].x=m_edge.x;
	m_edges[m_id].z=m_edge.z;
}
//����̈ʒu�𒆐S�Ƃ����A�ǂ̓���̍��W���璆�S�܂ł̋����Z�o
void MeshWall::SetLength(void)
{
	//�ǂ̒��S����
	m_Length_From_CenterXZ=sqrtf( (m_pos.x-m_center.x) * (m_pos.x-m_center.x) + (m_pos.z-m_center.z) * (m_pos.z-m_center.z));
	//�ǂ̊p����
	m_Length_Edge_From_CenterXZ=sqrtf((m_edge.x-m_center.x) * (m_edge.x-m_center.x) + (m_edge.z-m_center.z) * (m_edge.z-m_center.z));
}
