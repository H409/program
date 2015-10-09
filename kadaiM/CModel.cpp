//�w�b�_�[�C���N���[�h
#include "CModel.h"
#include "CRender.h"

//�쐬
CModel* CModel::Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename)
{
	CModel* pSceneX = new CModel(3);

	pSceneX->Init(pRender,pos,xfilename,ptexfilename,true);
	//pSceneX->Init(pRender);
	pSceneX->SetPosition(pos);
	

	return pSceneX;

}
//������
HRESULT CModel::Init(CRender* pRender)
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
HRESULT CModel::Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere)
{
	//�f�o�C�X�擾
	m_pRender = pRender;
	m_pD3DDevice = pRender->getDevice();
	m_pDepthTexture = pRender->GetRenderTexture();


	m_pos = pos;
	m_rot = D3DXVECTOR3(0,0,0);
	m_scl = D3DXVECTOR3(1,1,1);
	m_Vertex = D3DXVECTOR3(0,0,0);

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

	if(m_pTexName != NULL)
	{
		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();
		m_pMeshMaterials = new D3DMATERIAL9[m_nNumMatModel];
		m_pD3DTextureModel  = new LPDIRECT3DTEXTURE9[m_nNumMatModel];

		for(DWORD i=0; i<m_nNumMatModel; i++ )
		{ 
			m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;		
			m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
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
	
	m_initManager = true;

	return S_OK;

}
//�J��
void CModel::Uninit()
{
		//�e�N�X�`�����
	if(m_pTexName != NULL)
	{
		for(DWORD k = 0; k < m_nNumMatModel; k++)
		{		

			SAFE_RELEASE( m_pD3DTextureModel[k] );
				
			//__asm int 3
		}
		SAFE_DELETE_ARRAY(m_pD3DTextureModel);
		SAFE_DELETE_ARRAY(m_pMeshMaterials);
	}
	//�G�t�F�N�g�t�@�C�����
	SAFE_RELEASE( m_pEffect );
	//�}�e���A���J��
	SAFE_RELEASE(m_pD3DXBuffMatModel);
	
	//���b�V���J��
	SAFE_RELEASE(m_pD3DXMeshModel);
}
//�X�V
void CModel::Update()
{
	m_rot.y += D3DX_PI * 0.001f;
	
	SetRotNormalize();
}
//�`��
void CModel::Draw()
{
	//�ϐ��錾
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATRIX matRot;
	//���[���h�g�����X�t�H�[��
	D3DXMatrixIdentity(&m_mtxWorld);

	//�g�k
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	//D3DXMatrixMultiply(&matRot,&m_mtxRot,&mtxRot);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//���s�ړ�
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
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
	
	if(m_initManager)
	{
//		m_pEffect->SetFloat("TexWidth",800);
//		m_pEffect->SetFloat("TexHeight",600);

//		m_pEffect->SetTechnique("tecMakeDepthTexture");

		m_pEffect->Begin( NULL, 0 );

		for(int i = 0;i < (int)m_nNumMatModel;i++)
		{
			//m_pEffect->BeginPass(0);					
			//m_pEffect->SetMatrix("matWLP",&(m_mtxWorld * CLight::getInstance()->GetLightMatrix() * CCamera::getInstance()->GetMtxProjection()) );
			//m_pEffect->CommitChanges();
			
			m_pD3DDevice->SetMaterial(&pD3DMat[i].MatD3D);	//�}�e���A���ݒ�
			if(this->m_pTexName != NULL)
			{
				m_pD3DDevice->SetTexture(0,m_pD3DTextureModel[i]);				//Texture�ݒ�Ȃ����NULL
			}
			else
			{
				m_pD3DDevice->SetTexture(0,NULL);
			}
			//pDevice->SetTexture(0,NULL);
			m_pD3DXMeshModel->DrawSubset(i);			//�`��
			//m_pEffect->EndPass();
		}
		//m_pEffect->End();
		m_pD3DDevice->SetMaterial(&matDef);	//�f�t�H���g�ɖ߂�

		
	}
}
void CModel::DrawShade()
{

}