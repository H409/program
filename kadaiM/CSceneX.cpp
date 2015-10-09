#include "CSceneX.h"
#include "CRender.h"
#include "CDebugProc.h"
#include "CLight.h"
#include "CCamera.h"
#include "CInputKeyboard.h"

//作成
CSceneX* CSceneX::Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename)
{
	CSceneX* pSceneX = new CSceneX(3);

	pSceneX->Init(pRender,pos,xfilename,ptexfilename,true);
	//pSceneX->Init(pRender);
	pSceneX->SetPosition(pos);
	

	return pSceneX;

}
//初期化
HRESULT CSceneX::Init(CRender* pRender)
{

	//デバイス取得
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
		MessageBox(NULL, "モデルの読み込みに失敗しました", NULL, MB_OK);
		return E_FAIL;
	}
	m_initManager = true;

	m_pos = D3DXVECTOR3(0,0,0);
	m_rot = D3DXVECTOR3(0,0,0);
	m_scl = D3DXVECTOR3(1,1,1);

	return S_OK;
}
//初期化オーバーライド
HRESULT CSceneX::Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere)
{
	//デバイス取得
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

	//バッファーエラー表示用
	//シェーダーを読み込む
	if( FAILED(  D3DXCreateEffectFromFile(m_pD3DDevice, "data\\shader\\ShadowMap.fx", NULL, NULL,D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, NULL, &m_pEffect, &error)))
	{
		OutputDebugStringA((LPSTR)error->GetBufferPointer());	//シングルバイトで帰ってくる為OutputDebugStringAこうじゃないとダメ
		MessageBox(NULL,(LPSTR)error->GetBufferPointer(),"ERROR",MB_OK);
		//開放
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
		MessageBox(NULL, "モデルの読み込みに失敗しました", NULL, MB_OK);
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
					MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
				}
			}
		}
	}

	//バウンディングスフィア初期化
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
	m_LifeFlag = true;
	m_initManager = true;
	return S_OK;

}

HRESULT CSceneX::InitAnim(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename,bool createSphere)
{
	
	//デバイス取得
	m_pRender = pRender;
	m_pD3DDevice = pRender->getDevice();

//	m_SkinMesh = new SKIN_MESH();

	// Xファイルからアニメーションメッシュを読み込み作成する
//	m_SkinMesh->InitThing(m_pD3DDevice
	
	//バウンディングスフィア初期化
	if(m_createSphere)
	{
		InitSphere();
	}

	return S_OK;
}
//球体初期化
HRESULT	CSceneX::InitSphere(void)
{
	HRESULT hr = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB = NULL;
	VOID* pVertices = NULL;
	D3DXVECTOR3 vecCenter;
	FLOAT fRadius;


	m_bSphere = false;

	//メッシュの頂点バッファーをロックする
	if(FAILED(m_pD3DXMeshModel->GetVertexBuffer( &pVB )))
	{
		return E_FAIL;
	}
	if(FAILED(pVB->Lock( 0, 0, &pVertices, 0 )))
	{
		SAFE_RELEASE( pVB );
		return E_FAIL;
	}
	// メッシュの外接円の中心と半径を計算する
	hr=D3DXComputeBoundingSphere( (D3DXVECTOR3*)pVertices, m_pD3DXMeshModel->GetNumVertices(), 
			D3DXGetFVFVertexSize(m_pD3DXMeshModel->GetFVF()), &vecCenter, 
			&fRadius );
	pVB->Unlock();
	SAFE_RELEASE( pVB );

	if(FAILED( hr ))
	{
		return hr;
	}		
	m_Sphere.vecCenter = vecCenter;
	m_Sphere.fRadius = fRadius;


	// 得られた中心と半径を基にメッシュとしてのスフィアを作成する
	hr = D3DXCreateSphere(m_pD3DDevice,fRadius,24,24,&m_pSphereMesh,NULL);
	if(FAILED( hr ))
	{
		return hr;
	}	
	//スフィアメッシュのマテリアル　白色、半透明、光沢強 
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
//開放
void CSceneX::Uninit()
{
	
	//テクスチャ解放
	if(m_pTexName != NULL)
	{
		for(DWORD k = 0; k < m_nNumMatModel; k++)
		{		

			SAFE_RELEASE( m_pD3DTextureModel[k] );
				
			//__asm int 3
		}
		SAFE_DELETE_ARRAY(m_pD3DTextureModel);
		
	}
	SAFE_DELETE_ARRAY(m_pMeshMaterials);
	//エフェクトファイル解放
	SAFE_RELEASE( m_pEffect );
	//マテリアル開放
	SAFE_RELEASE(m_pD3DXBuffMatModel);
	
	//メッシュ開放
	SAFE_RELEASE(m_pD3DXMeshModel);

	//anime
//	SAFE_DELETE(m_SkinMesh);

	//球体用メッシュ開放
	SAFE_RELEASE( m_pSphereMesh );
	SAFE_DELETE(m_pSphereMeshMaterials);

	m_initManager = false;

	Release();
}

//更新
void CSceneX::Update()
{
	
	CLight::getInstance()->ShadeLight();
	
	
}

//描画
void CSceneX::Draw()
{
	if(m_LifeFlag)
	{
		//変数宣言
		D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
		D3DXMATRIX matRot;
		//ワールドトランスフォーム
		D3DXMatrixIdentity(&m_mtxWorld);

		//拡縮
		D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
		//回転
		D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
		//D3DXMatrixMultiply(&matRot,&m_mtxRot,&mtxRot);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
		//平行移動
		D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
		//ワールド設定
		m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

		m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE);

		//変数宣言
		D3DXMATERIAL*	pD3DMat;
		D3DMATERIAL9	matDef;


		if(m_pD3DXBuffMatModel != NULL)
		{
			pD3DMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();
			m_pD3DDevice->GetMaterial(&matDef);	//マテリアル情報保存
		}
	
		if(m_initManager)
		{
	//		m_pEffect->SetTechnique("tecMakeDepthTexture");

			m_pEffect->Begin( NULL, 0 );

			for(int i = 0;i < (int)m_nNumMatModel;i++)
			{
				//m_pEffect->BeginPass(0);					
				//m_pEffect->SetMatrix("matWLP",&(m_mtxWorld * CLight::getInstance()->GetLightMatrix() * CCamera::getInstance()->GetMtxProjection()) );
				//m_pEffect->CommitChanges();
			
				m_pD3DDevice->SetMaterial(&pD3DMat[i].MatD3D);	//マテリアル設定
				if(this->m_pTexName != NULL)
				{
					m_pD3DDevice->SetTexture(0,m_pD3DTextureModel[i]);				//Texture設定なければNULL
				}
				else
				{
					m_pD3DDevice->SetTexture(0,NULL);
				}
				//pDevice->SetTexture(0,NULL);
				m_pD3DXMeshModel->DrawSubset(i);			//描画
				//m_pEffect->EndPass();
			}
			//m_pEffect->End();
			///*
			//デバッグ用
			if(CInputKeyboard::getInstance()->GetKeyboardTrigger(DIK_O))
			{
				m_bSphere ^= true;
			}
			if(m_bSphere)
			{
				m_pD3DDevice->SetTexture( 0,NULL ); 
				m_pD3DDevice->SetMaterial( m_pSphereMeshMaterials);
				m_pSphereMesh->DrawSubset( 0 );
			}
			//*/
			m_pD3DDevice->SetMaterial(&matDef);	//デフォルトに戻す

			m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,FALSE);
		}
	}
}
void CSceneX::DrawShade()
{

	D3DXMATRIX mTexSpace;
	ZeroMemory(&mTexSpace,sizeof(D3DXMATRIX));		
	mTexSpace._11=0.5;
	mTexSpace._22=-0.5;
	mTexSpace._33=1;
	mTexSpace._41=0.5;
	mTexSpace._42=0.5;
	mTexSpace._44=1;
	
	//変数宣言
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	
	//ワールドトランスフォーム
	D3DXMatrixIdentity(&m_mtxWorld);

	//拡縮
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//回転
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
	
	//ワールド設定
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//変数宣言
	D3DXMATERIAL*	pD3DMat;
	D3DMATERIAL9	matDef;

	

	if(m_pD3DXBuffMatModel != NULL)
	{
		pD3DMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();
		m_pD3DDevice->GetMaterial(&matDef);	//マテリアル情報保存
	}
	
	if(m_initManager)
	{
		m_pEffect->SetFloat("TexWidth",800);
		m_pEffect->SetFloat("TexHeight",600);
		m_pEffect->SetTechnique("tecRenderScene");
		m_pEffect->SetTexture("DepthTex",m_pDepthTexture);

		m_pEffect->Begin( NULL, 0 );
		
		m_pEffect->BeginPass(0);
		for(int i = 0;i < (int)m_nNumMatModel;i++)
		{
		
			m_pD3DDevice->SetMaterial(&pD3DMat[i].MatD3D);	//マテリアル設定
			if(this->m_pTexName != NULL)
			{
				//m_pD3DDevice->SetTexture(0,m_pD3DTextureModel[i]);				//Texture設定なければNULL
				FLOAT fColor[4]={0};
				m_pEffect->SetValue("Diffuse",fColor,sizeof(FLOAT)*4 );
				m_pEffect->SetTexture("DecalTexture",m_pD3DTextureModel[i]);
			}
			else
			{
				FLOAT fColor[4]={0};
				//m_pEffect->SetValue("Diffuse",&pD3DMat->MatD3D.Diffuse,sizeof(FLOAT)*4 );
				m_pEffect->SetValue("Diffuse",fColor,sizeof(FLOAT)*4 );
				//m_pD3DDevice->SetTexture(0,NULL);
			}
			m_pEffect->SetMatrix("matWCP",&(m_mtxWorld * CCamera::getInstance()->GetMtxView() * CCamera::getInstance()->GetMtxProjection()) );
			m_pEffect->SetMatrix("matWLP",&(m_mtxWorld * CLight::getInstance()->GetLightMatrix() * CCamera::getInstance()->GetMtxProjection()) );	
			m_pEffect->SetMatrix("matWLPT",&(m_mtxWorld * CLight::getInstance()->GetLightMatrix() * CCamera::getInstance()->GetMtxProjection() *mTexSpace ) );	
			m_pEffect->SetMatrix("matW",&m_mtxWorld);					
			m_pEffect->SetVector("vecLightDir",(D3DXVECTOR4*)&(CLight::getInstance()->GetVecLight()-CLight::getInstance()->GetVecLook()));
			m_pEffect->SetVector("vecEye",(D3DXVECTOR4*)&CLight::getInstance()->GetVecEye());
			
	
			m_pEffect->CommitChanges();
			m_pD3DXMeshModel->DrawSubset(i);			//描画
			m_pEffect->EndPass();
		}
		m_pEffect->End();
		m_pD3DDevice->SetMaterial(&matDef);	//デフォルトに戻す
	}

}
//頂点を返す
D3DXVECTOR3* CSceneX::FindVertex(DWORD dwIndex)
{
	//変数宣言
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
//最大値と最小値取得
//TODO:後で作り直す
void CSceneX::CreateBBox(D3DXVECTOR3* pvecMax,D3DXVECTOR3* pvecMin)
{
	HRESULT hr = NULL;
	void* pVertices = NULL;
	LPDIRECT3DVERTEXBUFFER9 pVB=NULL;

	//メッシュの頂点バッファーをロックする
	if(FAILED(m_pD3DXMeshModel->GetVertexBuffer( &pVB )))
	{
		return;
	}
	if(FAILED(pVB->Lock( 0, 0, &pVertices, 0 )))
	{
		SAFE_RELEASE( pVB );
		return;
	}

	// メッシュ内頂点位置の最大と最小を検索する
	hr=D3DXComputeBoundingBox( (D3DXVECTOR3*)pVertices, m_pD3DXMeshModel->GetNumVertices(), 
									D3DXGetFVFVertexSize(m_pD3DXMeshModel->GetFVF()), pvecMin,pvecMax );

	pVB->Unlock();
	SAFE_RELEASE( pVB );

	if(FAILED( hr ))
	{
		return;
	}		
}