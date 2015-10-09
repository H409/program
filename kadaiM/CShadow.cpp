#include "CShdow.h"
#include "CRender.h"
#include "CDebugProc.h"
#include "CLight.h"
#include "CCamera.h"
#include "CInputKeyboard.h"


//�쐬
CShadow* CShadow::Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename)
{
	CShadow* pSceneX = new CShadow(1);

	pSceneX->Init(pRender,pos,xfilename,ptexfilename,true);
	//pSceneX->Init(pRender);
	pSceneX->SetPosition(pos);
	

	return pSceneX;

}
//������
HRESULT CShadow::Init(CRender* pRender)
{

	//�f�o�C�X�擾
	m_pD3DDevice = pRender->getDevice();

	if(FAILED(D3DXLoadMeshFromX("data\\Model\\airplane000.x",
								D3DXMESH_SYSTEMMEM,
								m_pD3DDevice,
								NULL,
								&m_pD3DXBuffMatModel,
								NULL,
								&m_nNumMatModel,
								&m_pD3DXMeshModel)))
	{
		MessageBox(NULL, "���f���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		return E_FAIL;
	}
	m_initManager = true;

	m_pos = D3DXVECTOR3(0,0,0);
	m_rot = D3DXVECTOR3(0,0,0);
	m_scl = D3DXVECTOR3(1,1,1);

	return S_OK;
}
//�������I�[�o�[���C�h
HRESULT CShadow::Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere)
{
	//�f�o�C�X�擾
	m_pRender = pRender;
	m_pD3DDevice = pRender->getDevice();

	m_pDepthTexture = pRender->GetRenderTexture();

	m_createSphere = createSphere;

	m_pos = pos;
	m_rot = D3DXVECTOR3(0,0,0);
	m_scl = D3DXVECTOR3(1,1,1);
	m_Vertex = D3DXVECTOR3(0,0,0);
	D3DXMatrixIdentity(&m_mtxRot);

	LPD3DXBUFFER error = NULL;

	//�o�b�t�@�[�G���[�\���p
	//�V�F�[�_�[��ǂݍ���
	if( FAILED(  D3DXCreateEffectFromFile(m_pD3DDevice, "data\\shader\\ShadowMap.fx", NULL, NULL,D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, NULL, &m_pEffect, &error)))
	{
		OutputDebugStringA((LPSTR)error->GetBufferPointer());	//�V���O���o�C�g�ŋA���Ă����OutputDebugStringA��������Ȃ��ƃ_��
		MessageBox(NULL,(LPSTR)error->GetBufferPointer(),"ERROR",MB_OK);
		//�J��
		SAFE_RELEASE(error);
		return E_FAIL;
	}
	

	if(ptexfilename != NULL)
	{
		m_pTexName = ptexfilename;
	}
	else
	{
		m_pTexName = NULL;
	}
	if(FAILED(D3DXLoadMeshFromX(pxfilename,
								D3DXMESH_SYSTEMMEM,
								m_pD3DDevice,
								NULL,
								&m_pD3DXBuffMatModel,
								NULL,
								&m_nNumMatModel,
								&m_pD3DXMeshModel)))
	{
		MessageBox(NULL, "���f���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
		return E_FAIL;
	}

	
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();
	m_pMeshMaterials = new D3DMATERIAL9[m_nNumMatModel];

	for(DWORD i=0; i<m_nNumMatModel; i++ )
	{ 

		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;		
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
	}

	if(m_pTexName != NULL)
	{
		m_pD3DTextureModel  = new LPDIRECT3DTEXTURE9[m_nNumMatModel];
		for(DWORD i=0; i<m_nNumMatModel; i++ )
		{ 
			
			m_pD3DTextureModel[i] = NULL;
			if( d3dxMaterials[i].pTextureFilename != NULL && 
				lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
			{
				if( FAILED( D3DXCreateTextureFromFile( m_pD3DDevice, 
													m_pTexName, 
													&m_pD3DTextureModel[i] ) ) )
				{
					MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				}
			}
		}
	}

	//�o�E���f�B���O�X�t�B�A������
	if(m_createSphere)
	{
		InitSphere();
	}
	else
	{
		m_bSphere = false;
		m_pSphereMesh = NULL;
		m_pSphereMeshMaterials = NULL;
	}
	this->m_pParent = NULL;

	m_LifeFlag = true;
	m_initManager = true;

//	CEffect::Create(m_pRender,m_pos);

	return S_OK;

}

HRESULT CShadow::InitAnim(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere)
{
	
	//�f�o�C�X�擾
	m_pRender = pRender;
	m_pD3DDevice = pRender->getDevice();

//	m_SkinMesh = new SKIN_MESH();

	// X�t�@�C������A�j���[�V�������b�V����ǂݍ��ݍ쐬����
//	m_SkinMesh->InitThing(m_pD3DDevice
	
	//�o�E���f�B���O�X�t�B�A������
	if(m_createSphere)
	{
		InitSphere();
	}

	return S_OK;
}
//���̏�����
HRESULT	CShadow::InitSphere(void)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;
	D3DXVECTOR3 vecCenter;
	FLOAT fRadius;


	m_bSphere = false;

	//���b�V���̒��_�o�b�t�@�[�����b�N����
	if(FAILED(m_pD3DXMeshModel->GetVertexBuffer( &pVB )))
	{
		return E_FAIL;
	}
	if(FAILED(pVB->Lock( 0, 0, &pVertices, 0 )))
	{
		SAFE_RELEASE( pVB );
		return E_FAIL;
	}
	// ���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����
	hr=D3DXComputeBoundingSphere( (D3DXVECTOR3*)pVertices, m_pD3DXMeshModel->GetNumVertices(), 
			D3DXGetFVFVertexSize(m_pD3DXMeshModel->GetFVF()), &vecCenter, 
			&fRadius );
	pVB->Unlock();
	SAFE_RELEASE( pVB );

	if(FAILED( hr ))
	{
		return hr;
	}		


	// ����ꂽ���S�Ɣ��a����Ƀ��b�V���Ƃ��ẴX�t�B�A���쐬����
	hr = D3DXCreateSphere(m_pD3DDevice,fRadius,24,24,&m_pSphereMesh,NULL);
	if(FAILED( hr ))
	{
		return hr;
	}	
	//�X�t�B�A���b�V���̃}�e���A���@���F�A�������A���� 
	m_pSphereMeshMaterials = new D3DMATERIAL9;
	m_pSphereMeshMaterials->Diffuse.r = 0.0f;
	m_pSphereMeshMaterials->Diffuse.g = 0.0f;
	m_pSphereMeshMaterials->Diffuse.b = 1.0f;	
	m_pSphereMeshMaterials->Diffuse.a = 0.3f;
	m_pSphereMeshMaterials->Ambient = m_pSphereMeshMaterials->Diffuse;	
	m_pSphereMeshMaterials->Specular.r = 1.0f;
	m_pSphereMeshMaterials->Specular.g = 1.0f;
	m_pSphereMeshMaterials->Specular.b = 1.0f;
	m_pSphereMeshMaterials->Emissive.r = 0.1f;
	m_pSphereMeshMaterials->Emissive.g = 0.1f;
	m_pSphereMeshMaterials->Emissive.b = 0.1f;
	m_pSphereMeshMaterials->Power = 120.0f;	

	return S_OK;
}
//�J��
void CShadow::Uninit()
{
	
	//�e�N�X�`�����
	if(m_pTexName != NULL)
	{
		for(DWORD k = 0; k < m_nNumMatModel; k++)
		{		

			SAFE_RELEASE( m_pD3DTextureModel[k] );
				
			//__asm int 3 //�u���[�N�|�C���g
		}
		SAFE_DELETE_ARRAY(m_pD3DTextureModel);

	}
	SAFE_DELETE_ARRAY(m_pMeshMaterials);
	//�G�t�F�N�g�t�@�C�����
	SAFE_RELEASE( m_pEffect );
	//�}�e���A���J��
	SAFE_RELEASE(m_pD3DXBuffMatModel);
	
	//���b�V���J��
	SAFE_RELEASE(m_pD3DXMeshModel);

	//anime
//	SAFE_DELETE(m_SkinMesh);

	//���̗p���b�V���J��
	SAFE_RELEASE( m_pSphereMesh );
	SAFE_DELETE(m_pSphereMeshMaterials);

	m_initManager = false;

	Release();
}

//�X�V
void CShadow::Update()
{
	
//	CLight::getInstance()->ShadeLight();
		

	//CEffect::SetVec(m_pos);

}

//�`��
void CShadow::Draw()
{
	if(m_LifeFlag)
	{
		

		//�ϐ��錾
		D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
		D3DXMATRIX matYaw,matPitch,matRoll;
		D3DXMATRIX matRot;
		//���[���h�g�����X�t�H�[��
		D3DXMatrixIdentity(&m_mtxWorld);

		D3DXMatrixIdentity(&matYaw);
		D3DXMatrixIdentity(&matPitch);
		D3DXMatrixIdentity(&matRoll);
		//�g�k
		D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
		//��]
		
		D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
		//D3DXMatrixMultiply(&matRot,&m_mtxRot,&mtxRot);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
		//CDebugProc::Print("rot.x%f:rot.y%f:rot.z%f\n",m_rot.x,m_rot.y,m_rot.z);
		//���s�ړ�
		D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
		//�e�q�֌W����Ȃ�
		if( m_pParent != NULL )
		{
			D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &m_pParent->m_mtxWorld );
		}

		//���[���h�ݒ�
		m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

		
		//�ϐ��錾
		D3DXMATERIAL*	pD3DMat;
		D3DMATERIAL9	matDef;


		if(m_pD3DXBuffMatModel != NULL)
		{
			pD3DMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();
			m_pD3DDevice->GetMaterial(&matDef);	//�}�e���A�����ۑ�
		}
		///*
		//�����_�[�X�e�[�g
		m_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
		
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);	//Z�o�b�t�@�ւ̏������ݖ���
		//m_pD3DDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
		m_pD3DDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0x00000000);	//�J���[�o�b�t�@�̏������ݖ���

		m_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);			//�S�č��i
		m_pD3DDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_ZERO);		//�X�e���V���e�X�g���i�AZ�e�X�g���i��0
		m_pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_INCR);		//���i�@�s���i += 1
		m_pD3DDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);		//�s���i�˂O
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);				//�J�����O�t����

		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );

		if(m_initManager)
		{
			
			for(int i = 0;i < (int)m_nNumMatModel;i++)
			{
				
			
				m_pD3DDevice->SetMaterial(&pD3DMat[i].MatD3D);	//�}�e���A���ݒ�
				if(this->m_pTexName != NULL)
				{
					m_pD3DDevice->SetTexture(0,m_pD3DTextureModel[i]);				//Texture�ݒ�Ȃ����NULL
				}
				else
				{
					m_pD3DDevice->SetTexture(0,NULL);
				}

				m_pD3DXMeshModel->DrawSubset(i);			//�`��
				
			}
			m_pD3DDevice->SetMaterial(&matDef);	//�f�t�H���g�ɖ߂�
		}
		//*/
		///*
		m_pD3DDevice->SetRenderState(D3DRS_STENCILREF,0x01);
		m_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);			//�S�č��i
		m_pD3DDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_ZERO);		//�X�e���V���e�X�g���i�AZ�e�X�g���i��0
		m_pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_INCR);		//���i�@�s���i += 1
		m_pD3DDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);		//�s���i�˂O
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);				//�J�����O

		if(m_initManager)
		{
			
			for(int i = 0;i < (int)m_nNumMatModel;i++)
			{
				
			
				m_pD3DDevice->SetMaterial(&pD3DMat[i].MatD3D);	//�}�e���A���ݒ�
				if(this->m_pTexName != NULL)
				{
					m_pD3DDevice->SetTexture(0,m_pD3DTextureModel[i]);				//Texture�ݒ�Ȃ����NULL
				}
				else
				{
					m_pD3DDevice->SetTexture(0,NULL);
				}

				m_pD3DXMeshModel->DrawSubset(i);			//�`��
				
			}
			m_pD3DDevice->SetMaterial(&matDef);	//�f�t�H���g�ɖ߂�
		}
		m_pD3DDevice->SetRenderState(D3DRS_STENCILREF,0x02);
		m_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);
		m_pD3DDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);		//�X�e���V���e�X�g���i�AZ�e�X�g���i��0
		m_pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);		//���i�@�s���i += 1
		m_pD3DDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_KEEP);		//�s���i�˂O

		m_pD3DDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_RED |
															D3DCOLORWRITEENABLE_GREEN |
															D3DCOLORWRITEENABLE_BLUE |
															D3DCOLORWRITEENABLE_ALPHA
			);	
		//*/
		//�J���[�o�b�t�@��߂�
		//2D���摜�`��
		struct COLOR_POINT
		{
			D3DXVECTOR4 vecCoord;
			DWORD dwColor;
		};
		BYTE bAlpha=150;
		COLOR_POINT ColorPoint[4]=	
		{ 
			D3DXVECTOR4(0,0,0,1),D3DCOLOR_ARGB(bAlpha,10,10,10),
			D3DXVECTOR4(800,0,0,1),D3DCOLOR_ARGB(bAlpha,10,10,10),
			D3DXVECTOR4(0,600,0,1),D3DCOLOR_ARGB(bAlpha,10,10,10),+
			D3DXVECTOR4(800,600,0,1),D3DCOLOR_ARGB(bAlpha,10,10,10)
		};	
		m_pD3DDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE );	
		m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2, ColorPoint, sizeof(COLOR_POINT));
		
		//���ɖ߂�
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
		//m_pD3DDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);
		m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
	}
}
void CShadow::DrawShade()
{

	D3DXMATRIX mTexSpace;
	ZeroMemory(&mTexSpace,sizeof(D3DXMATRIX));		
	mTexSpace._11=0.5;
	mTexSpace._22=-0.5;
	mTexSpace._33=1;
	mTexSpace._41=0.5;
	mTexSpace._42=0.5;
	mTexSpace._44=1;
	
	//�ϐ��錾
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
	
	//�e�q�֌W����Ȃ�
	if( m_pParent != NULL )
	{
		D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &m_pParent->m_mtxWorld );
	}
	//���[���h�ݒ�
//	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//�ϐ��錾
	D3DXMATERIAL*	pD3DMat;
	D3DMATERIAL9	matDef;

	

	if(m_pD3DXBuffMatModel != NULL)
	{
		pD3DMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();
		m_pD3DDevice->GetMaterial(&matDef);	//�}�e���A�����ۑ�
	}
//	D3DXVECTOR3 tmp = CLight::getInstance()->GetVecLight();
//	D3DXVECTOR3 tmp1 = CLight::getInstance()->GetVecLook();
//	D3DXVECTOR3 tmp2 = tmp1 - tmp;

	if(m_initManager)
	{
		m_pEffect->SetTechnique("tecRenderScene");
		m_pEffect->SetTexture("DepthTex",m_pDepthTexture);

		//�J�n
		m_pEffect->Begin( NULL, 0 );
		
		m_pEffect->BeginPass(0);
		m_pEffect->SetMatrix("matWCP",&(m_mtxWorld * CCamera::getInstance()->GetMtxView() * CCamera::getInstance()->GetMtxProjection()) );
		m_pEffect->SetMatrix("matWLP",&(m_mtxWorld * CLight::getInstance()->GetLightMatrix() * CCamera::getInstance()->GetMtxProjection()) );	
		m_pEffect->SetMatrix("matWLPT",&(m_mtxWorld * CLight::getInstance()->GetLightMatrix() * CCamera::getInstance()->GetMtxProjection() *mTexSpace ) );	
		m_pEffect->SetMatrix("matW",&m_mtxWorld);					
		m_pEffect->SetVector("vecLightDir",(D3DXVECTOR4*)&(CLight::getInstance()->GetVecLight()-CLight::getInstance()->GetVecLook()));
		m_pEffect->SetVector("vecEye",(D3DXVECTOR4*)&CLight::getInstance()->GetVecEye());
			
		
		
		for(int i = 0;i < (int)m_nNumMatModel;i++)
		{
		
			m_pD3DDevice->SetMaterial(&pD3DMat[i].MatD3D);	//�}�e���A���ݒ�
			if(this->m_pTexName != NULL)
			{
				m_pD3DDevice->SetTexture(0,m_pD3DTextureModel[i]);				//Texture�ݒ�Ȃ����NULL
				FLOAT fColor[4]={0};
				//m_pEffect->SetValue("Diffuse",fColor,sizeof(FLOAT)*4 );
				m_pEffect->SetTexture("DecalTexture",m_pD3DTextureModel[i]);
				m_pEffect->CommitChanges();
			}
			else
			{
				//FLOAT fColor[4]={0};
				m_pEffect->SetValue("Diffuse",&m_pMeshMaterials[i].Diffuse,sizeof(FLOAT)*4 );
				m_pEffect->CommitChanges();
				m_pD3DDevice->SetTexture(0,NULL);
			}
			
			m_pD3DXMeshModel->DrawSubset(i);			//�`��
			
		}
		//�I��
		m_pEffect->EndPass();
		m_pEffect->End();
		m_pD3DDevice->SetMaterial(&matDef);	//�f�t�H���g�ɖ߂�
	}

}
//���_��Ԃ�
D3DXVECTOR3* CShadow::FindVertex(DWORD dwIndex)
{
	//�ϐ��錾
	LPDIRECT3DVERTEXBUFFER9 pVB=NULL;
	DWORD NumVertices = m_pD3DXMeshModel->GetNumVertices();
	m_pD3DXMeshModel->GetVertexBuffer(&pVB);
	DWORD dwStride = m_pD3DXMeshModel->GetNumBytesPerVertex();	
	BYTE *pVertices = NULL;
	D3DXVECTOR3* pvVertex=NULL;
	D3DXVECTOR3  aposVertex[1000];
	D3DXVECTOR3 Vertex = D3DXVECTOR3(0,0,0);
	D3DXVECTOR3* ptmp = NULL;
	

	if(SUCCEEDED(pVB->Lock(0,0,(VOID**)&pVertices,0)))	
	{
		
		pVertices+=dwIndex*dwStride;
		pvVertex = (D3DXVECTOR3*)pVertices;			
		
		pVB->Unlock();
	}
	SAFE_RELEASE( pVB );
	m_Vertex.x = pvVertex->x;
	m_Vertex.y = pvVertex->y;
	m_Vertex.z = pvVertex->z;

	return pvVertex;
}
//�ő�l�ƍŏ��l�擾
//TODO:��ō�蒼��
void CShadow::CreateBBox(D3DXVECTOR3* pvecMax,D3DXVECTOR3* pvecMin)
{
	HRESULT hr = NULL;
	void* pVertices = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB=NULL;

	//���b�V���̒��_�o�b�t�@�[�����b�N����
	if(FAILED(m_pD3DXMeshModel->GetVertexBuffer( &pVB )))
	{
		return;
	}
	if(FAILED(pVB->Lock( 0, 0, &pVertices, 0 )))
	{
		SAFE_RELEASE( pVB );
		return;
	}

	// ���b�V�������_�ʒu�̍ő�ƍŏ�����������
	hr=D3DXComputeBoundingBox( (D3DXVECTOR3*)pVertices, m_pD3DXMeshModel->GetNumVertices(), 
									D3DXGetFVFVertexSize(m_pD3DXMeshModel->GetFVF()), pvecMin,pvecMax );

	pVB->Unlock();
	SAFE_RELEASE( pVB );

	if(FAILED( hr ))
	{
		return;
	}		
}