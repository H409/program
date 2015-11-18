#include "mesh_cylinder.h"

Cylinder::~Cylinder()
{

}
Cylinder* Cylinder::Create(LPDIRECT3DDEVICE9 device)
{

	Cylinder* p=new Cylinder(device);
	p->Init(0.0f,0.0f,0.0f,0.0f,20,20,10.0f,10.0f);
	p->SetPosition(0.0f,200.0f,100.0f);
	return p;

}
HRESULT Cylinder::Init(	float posX,float posY,float posZ,float rotY,
							int nNumBlockX,int nNumBlockY,float fSizeBlockX,float fSizeBlockY)
{
	VERTEX_3D *pVtx;			//���_���
	WORD *pIndex;				//�C���f�b�N�X���

	//�@���o�b�t�@�̓��I�m��
	m_normalBuf = new D3DXVECTOR3[nNumBlockX*nNumBlockY*2];

	//�|�W�V����������
	m_pos=D3DXVECTOR3(posX,posY,posZ);

	//��](���W�A��)
	m_rot = D3DXVECTOR3(0.0f,rotY,0.0f);
	//�g��k��
	m_scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//�V�����_�[�̉~��
	m_circumference=nNumBlockX*fSizeBlockX;
	//�V�����_�[�̔��a
	m_radius=m_circumference/D3DX_PI/2;
	//�V�����_�[�̖ʈꖇ�̊p�x
	float facedigree=(D3DX_PI*2)/fSizeBlockX;

	//�C���f�b�N�X�ԍ��ő吔
	g_VtxIdxNum = SUM_INDEX(nNumBlockX,nNumBlockY);

	//���_���W�ԍ��ő吔
	g_NumVtx = (nNumBlockX+1)*(nNumBlockY+1);

	//�|���S����
	g_NumPolygon = ((nNumBlockX*2)*nNumBlockY)+((nNumBlockY-1)*4);


		//�C���f�b�N�X�o�b�t�@�̐���
	if(FAILED(pDevice->CreateIndexBuffer(	sizeof(WORD)*g_VtxIdxNum,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&g_pIndexBuff,
											NULL)))
	{
		return E_FAIL;
	}
	//���_�o�b�t�@�̐���
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*g_NumVtx,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&g_pD3DVtxBuff,
										NULL)))
	{
		return E_FAIL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(GetDevice(),"data/TEXTURE/tatemono.bmp",&g_pD3DTexture);

	//���_���W�̐ݒ�
	g_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);
	for(int y=0,num=0;y<nNumBlockY+1;y++)
	{
		for(int x=0;x<nNumBlockX+1;x++)
		{
			//pVtx[num].vtx = D3DXVECTOR3(-(nNumBlockX*fSizeBlockX/2)+(fSizeBlockX*x),(nNumBlockY*fSizeBlockY/2)+(-fSizeBlockY*y),0);
			pVtx[num].vtx = D3DXVECTOR3(-(cosf(facedigree*-x))*m_radius,(-fSizeBlockY*y),(sinf(facedigree*-x))*m_radius);
			pVtx[num].nor = D3DXVECTOR3(0,1.0f,0);
			pVtx[num].diffuse = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
			pVtx[num].tex = D3DXVECTOR2((float)x/5,(float)y/5);
			num++;
		}
	}
	//�@���o�b�t�@�̏�����(���b�V���t�B�[���h�`������A�e�|���S���̖@�������߁A�ۑ�����)
	D3DXVECTOR3 a,b;			//1�ʂ̈�ӕۑ�
	D3DXVECTOR3 c,d,e;			//�@���x�N�g���ۑ�
	for(int z = 0;z < nNumBlockY;z++)
	{
		for(int x = 0;x < nNumBlockX;x++)
		{
			//��1
			a=	pVtx[x+((nNumBlockX+1)*z)+1].vtx				-	pVtx[x+((nNumBlockX+1)*z)].vtx;
			b=	pVtx[x+((nNumBlockX+1)*z)+(nNumBlockX+1)].vtx	-	pVtx[x+((nNumBlockX+1)*z)].vtx;
			D3DXVec3Cross(&c,&a,&b);
			D3DXVec3Normalize(&c,&c);
			m_normalBuf[x*2+(z*nNumBlockX*2)]=c;

			//��2
			a=pVtx[x+((nNumBlockX+1)*z)+(nNumBlockX+1)].vtx	-	pVtx[x+((nNumBlockX+1)*z)+(nNumBlockX+2)].vtx;
			b=pVtx[x+((nNumBlockX+1)*z)+1].vtx				-	pVtx[x+((nNumBlockX+1)*z)+(nNumBlockX+2)].vtx;
			D3DXVec3Cross(&c,&a,&b);
			D3DXVec3Normalize(&c,&c);
			m_normalBuf[x*2+(z*nNumBlockX*2)+1]=c;
		}
	}
	//���_�@���̌v�Z
	//�����_�@���Ƃ͊e���_�̎��@���x�N�g���̂���
	//���_���l�p�`�̃|���S���̑Ίp�����Ȃ��Ă���ꍇ�A�אڂ��邷�ׂĂ̎O�p�|���S���̖@�����狁�߂�
	for(int x=0;x<(nNumBlockX+1)*(nNumBlockY+1);x++)
	{
		int VtxNum= x;
		//���_�ԍ�������ɂ���ꍇ
		if(VtxNum == 0)
		{
			pVtx[VtxNum].nor = D3DXVECTOR3(m_normalBuf[0]);
		}

		//���_�ԍ����E��ɂ���ꍇ
		else if(VtxNum == nNumBlockX)
		{
			D3DXVECTOR3 a = m_normalBuf[(nNumBlockX*2)-2];
			D3DXVECTOR3 b = m_normalBuf[(nNumBlockX*2)-1];
			D3DXVECTOR3 c = a+b;
			D3DXVec3Normalize(&c,&c);
			pVtx[VtxNum].nor=D3DXVECTOR3(c);
		}

		//���_�ԍ����E���ɂ���ꍇ
		else if(VtxNum == (nNumBlockX+1) * (nNumBlockY+1) - 1)
		{
			pVtx[VtxNum].nor = D3DXVECTOR3(m_normalBuf[(nNumBlockX+1)*(nNumBlockY+1)-1]);
		}

		//���_�ԍ��������ɂ���ꍇ
		else if(VtxNum == (nNumBlockX+1) * nNumBlockY)
		{
			D3DXVECTOR3 a = m_normalBuf[(nNumBlockX*2) * nNumBlockY];
			D3DXVECTOR3 b = m_normalBuf[(nNumBlockX*2) * nNumBlockY + 1];
			D3DXVECTOR3 c = a+b;
			D3DXVec3Normalize(&c,&c);
			pVtx[VtxNum].nor=D3DXVECTOR3(c);
		}
		//���_�ԍ�����[�ɂ���ꍇ
		else if(VtxNum < (nNumBlockX+1))
		{
			D3DXVECTOR3 a = m_normalBuf[VtxNum * 2 - 2];
			D3DXVECTOR3 b = m_normalBuf[VtxNum * 2 - 1];
			D3DXVECTOR3 c = m_normalBuf[VtxNum * 2];
			D3DXVECTOR3 d = a+b+c;
			D3DXVec3Normalize(&d,&d);
			pVtx[VtxNum].nor=D3DXVECTOR3(d);
		}
		//���_�ԍ������[�ɂ���ꍇ
		else if(VtxNum > (nNumBlockX+1) * nNumBlockY)
		{
			D3DXVECTOR3 a = m_normalBuf[(VtxNum * 2) - ((nNumBlockX*2)+(nNumBlockY*2)+1)];
			D3DXVECTOR3 b = m_normalBuf[(VtxNum * 2) - ((nNumBlockX*2)+(nNumBlockY*2)+1) + 1];
			D3DXVECTOR3 c = m_normalBuf[(VtxNum * 2) - ((nNumBlockX*2)+(nNumBlockY*2)+1) + 2];

			D3DXVECTOR3 d = a+b+c;
			D3DXVec3Normalize(&d,&d);
			pVtx[VtxNum].nor=D3DXVECTOR3(d);
		}
		//���_�ԍ������[�ɂ���ꍇ
		else if(VtxNum != 0 && VtxNum % (nNumBlockX+1) == 0)
		{
			D3DXVECTOR3 a = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - (nNumBlockX*2)];
			D3DXVECTOR3 b = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - (nNumBlockX*2)+1];
			D3DXVECTOR3 c = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2)];
			D3DXVECTOR3 d = a+b+c;
			D3DXVec3Normalize(&d,&d);
			pVtx[VtxNum].nor=D3DXVECTOR3(d);
		}	
		//���_�ԍ����E�[�ɂ���ꍇ
		else if((VtxNum - nNumBlockX) % (nNumBlockX+1) == 0)
		{
			D3DXVECTOR3 a = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - 1];
			D3DXVECTOR3 b = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - 1 + (nNumBlockX*2) - 1];
			D3DXVECTOR3 c = m_normalBuf[(VtxNum/(nNumBlockX+1)) * (nNumBlockX*2) - 1 + (nNumBlockX*2)];
			D3DXVECTOR3 d = a+b+c;
			D3DXVec3Normalize(&d,&d);
			pVtx[VtxNum].nor=D3DXVECTOR3(d);
		}
		//��L�ȊO
		else
		{
			D3DXVECTOR3 a = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1))];
			D3DXVECTOR3 b = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1)) +1];
			D3DXVECTOR3 c = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1)) + 2];
			D3DXVECTOR3 d = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1))+(nNumBlockX*2-1)];
			D3DXVECTOR3 e = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1))+(nNumBlockX*2-1) + 1];
			D3DXVECTOR3 f = m_normalBuf[(VtxNum*2) - (((VtxNum/nNumBlockX)*2) + (nNumBlockX+nNumBlockY+1))+(nNumBlockX*2-1) + 2];
			D3DXVECTOR3 g =a+b+c+d+e+f;
			D3DXVec3Normalize(&g,&g);
			pVtx[VtxNum].nor=D3DXVECTOR3(g);
		}
	}//for
	g_pD3DVtxBuff -> Unlock();

	//�C���f�b�N�X�o�b�t�@�ݒ�
	g_pIndexBuff->Lock(0,0,(void**)&pIndex,0);

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

	g_pIndexBuff->Unlock();

	return S_OK;
}

void Cylinder::Uninit(void)
{
	CScene3D::Uninit();
	//RELEASE_P(g_pIndexBuff)
	DELETE_P(m_normalBuf)
	Release();
}

void Cylinder::Update(void)
{

	if(m_rot.y>D3DX_PI)
	{
		m_rot.y=-D3DX_PI;
	}
	else if(m_rot.y<-D3DX_PI)
	{
		m_rot.y=D3DX_PI;
	}
}

void Cylinder::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//���ꂼ��̃}�g���N�X�̐ݒ�
	D3DXMatrixIdentity(&g_mtxWorld);

	D3DXMatrixScaling(&mtxScl,1.0f,1.0f,1.0f);							//�g��{��
	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);				//�X��//�ʓx�@�œ���� Y,X,Z
	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxRot);

	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);				//��Ԃ̕��s�ړ�
	D3DXMatrixMultiply(&g_mtxWorld,&g_mtxWorld,&mtxTranslate);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���\�[�X�Ƀo�C���h
	pDevice ->SetStreamSource(0,g_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	
	pDevice->SetIndices(g_pIndexBuff);
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice ->SetTexture(0,g_pD3DTexture);

	//�|���S���̕`��(�C���f�b�N�X�o�[�W����)
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,g_VtxIdxNum,0,g_NumPolygon);
}


//�A�N�Z�T�[
void Cylinder::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}
void Cylinder::SetPosition(float x,float y,float z)
{
	m_pos= D3DXVECTOR3(x,y,z);
}
void Cylinder::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}
void Cylinder::SetRotation(float x,float y,float z)
{
	m_rot= D3DXVECTOR3(x,y,z);
}