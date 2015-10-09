//=============================================================================
// シェーダー作成処理 [CSkyBox.h]
// Author : MASAHIRO YAMAGUCHI
// スカイボックス初期化等
//=============================================================================
//ヘッダーインクルード
#include "CSkyBox.h"
#include "CRender.h"
#include "CDebugProc.h"
#include "CLight.h"
#include "CCamera.h"
#include "CInputKeyboard.h"

TLVERTEX ver1[CUBE_VERTEX]=     //前面 
{ { -500, -500,  500, 0xffffffff,1,1  },
  {  500, -500,  500, 0xffffffff,0,1   },
  { -500,  500,  500, 0xffffffff,1,0  },
  {  500,  500,  500, 0xffffffff,0,0   } };
TLVERTEX ver2[CUBE_VERTEX]=     //右側面
{ {  500, -500,  500, 0xffffffff,1,1  },
  {  500, -500, -500, 0xffffffff,0,1   },
  {  500,  500,  500, 0xffffffff,1,0  },
  {  500,  500, -500, 0xffffffff,0,0   } };
TLVERTEX ver3[CUBE_VERTEX]=     //下面
{ { -500, -500, -500, 0xffffffff,0,1  },
  {  500, -500, -500, 0xffffffff,1,1   },
  { -500, -500,  500, 0xffffffff,0,0  },
  {  500, -500,  500, 0xffffffff,1,0   } };
TLVERTEX ver4[CUBE_VERTEX]=     //左側面
{ { -500,  500,  500, 0xffffffff,0,0  },
  { -500,  500, -500, 0xffffffff,1,0  },
  { -500, -500,  500, 0xffffffff,0,1  },
  { -500, -500, -500, 0xffffffff,1,1  } };
TLVERTEX ver5[CUBE_VERTEX]=     //裏面 
{ { -500,  500, -500, 0xffffffff,0,0  },
  {  500,  500, -500, 0xffffffff,1,0  },
  { -500, -500, -500, 0xffffffff,0,1  },
  {  500, -500, -500, 0xffffffff,1,1  } };
TLVERTEX ver6[CUBE_VERTEX]=     //上面
{ {  500,  500, -500, 0xffffffff,1,1  },
  { -500,  500, -500, 0xffffffff,0,1  },
  {  500,  500,  500, 0xffffffff,1,0  },
  { -500,  500,  500, 0xffffffff,0,0  } };

//生成
CSkyBox* CSkyBox::Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,char* ptexfilename)
{
	CSkyBox* pSceneX = new CSkyBox(3);

	pSceneX->Init(pRender,pos,xfilename,ptexfilename);
	//pSceneX->Init(pRender);
	pSceneX->SetPosition(pos);
	

	return pSceneX;
}

//初期化
HRESULT CSkyBox::Init(CRender* pRender)
{
	return S_OK;
}
HRESULT CSkyBox::Init(CRender* pRender,D3DXVECTOR3 pos,char* pxfilename,char *ptexfilename)
{
	//デバイス取得
	HRESULT	hr = NULL;
	m_pRender = pRender;
	m_pD3DDevice = pRender->getDevice();

	m_pCubeEnvMap=NULL; 
	m_pCubeRender=NULL; 
	m_pBackBuffer = NULL;
	m_pZBuffer = NULL;
	for(int i = 0;i < CUBE_FACE;i++)
	{
		m_pCubeZBuffer[i] = NULL;
	}

	m_pos = pos;
	m_rot = D3DXVECTOR3(0,0,0);
	m_scl = D3DXVECTOR3(1,1,1);
	m_Vertex = D3DXVECTOR3(0,0,0);

	if(ptexfilename != NULL)
	{
		m_pTexName = ptexfilename;
	}
	else
	{
		m_pTexName = NULL;
	}

	//D3DXCreateBox(m_pD3DDevice,100,100,100,&m_pD3DXMeshModel,&m_pD3DXBuffMatModel);
	
/*	
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
	
			if( FAILED( D3DXCreateTextureFromFile( m_pD3DDevice, 
												m_pTexName, 
												&m_pD3DTextureModel[i] ) ) )
			{
				MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
			}
		}
	}
*/
	const LPSTR file[CUBE_FACE] = 
	{
		{"data\\Texture\\center.png"},	
		{"data\\Texture\\reverse.png"},	
		{"data\\Texture\\down.png"},	
		{"data\\Texture\\left.png"},
		{"data\\Texture\\right.png"},
		{"data\\Texture\\up.png"},

	};
	for(int i = 0;i < CUBE_FACE;i++)
	{
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(m_pD3DDevice,file[i],&m_pD3DTex[i]);
	}
	for(int i = 0;i < CUBE_VERTEX;i++)
	{
		m_Ver1[i] = ver1[i];
		m_Ver2[i] = ver2[i];
		m_Ver3[i] = ver3[i];
		m_Ver4[i] = ver4[i];
		m_Ver5[i] = ver5[i];
		m_Ver6[i] = ver6[i];

	}
/*
	//ビデオカードがキューブマップをサポートしているかどうか
	D3DCAPS9 Caps;	
	m_pD3DDevice->GetDeviceCaps(&Caps);
	if( (Caps.TextureCaps & D3DPTEXTURECAPS_CUBEMAP)==0 )
	{
		MessageBox(0,"ビデオカードがキューブマップをサポートしていません","",MB_OK);
		return E_FAIL;
	}

	D3DDISPLAYMODE ds;
	m_pD3DDevice->GetDisplayMode(0,&ds);
	
	
	if(FAILED(D3DXCreateCubeTextureFromFile(m_pD3DDevice,m_pTexName,&m_pCubeEnvMap)))
	{
		MessageBox(0,"キューブテクスチャ作成失敗","",MB_OK);
		return E_FAIL;
	}
	
	LPDIRECT3DCUBETEXTURE9 pCubeEnvMap;

	if(FAILED(D3DXCreateCubeTextureFromFileEx(m_pD3DDevice,"data\\Texture\\sky005.dds",D3DX_DEFAULT,D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,ds.Format,D3DPOOL_DEFAULT,D3DX_DEFAULT,
		D3DX_DEFAULT,0xFF000000,NULL,NULL,&pCubeEnvMap)))
	{
		MessageBox(0,"キューブテクスチャ作成失敗","",MB_OK);
		return E_FAIL;
	}
	m_pCubeEnvMap = pCubeEnvMap;
/*
	//”背景のキューブマッピング用”キューブマップイメージを読み込む	
	if(FAILED(D3DXCreateCubeTextureFromFileEx(m_pD3DDevice,"data\\Texture\\Town.dds",D3DX_DEFAULT,D3DX_DEFAULT,
		D3DUSAGE_RENDERTARGET,ds.Format,D3DPOOL_DEFAULT,D3DX_DEFAULT,
		D3DX_DEFAULT,0xFF000000,NULL,NULL,&m_pCubeEnvMap)))
	{
		MessageBox(0,"キューブテクスチャ作成失敗","",MB_OK);
		return E_FAIL;
	}

	//”周囲のメッシュのレンダリング先”としてのキューブマップイメージを読み込む	
	if(FAILED(m_pD3DDevice->CreateCubeTexture(CUBEMAP_DIMENSION,0,D3DUSAGE_RENDERTARGET,ds.Format,
		D3DPOOL_DEFAULT,&m_pCubeRender,NULL)))
	{
		MessageBox(0,"キューブテクスチャ作成失敗","",MB_OK);
		return E_FAIL;
	}
	
	//テクスチャをレンダリングターゲットにする際のZバッファを作成
	D3DSURFACE_DESC desc;
	for(DWORD i=0;i<6;i++)
	{
		LPDIRECT3DSURFACE9 pCubeFace=NULL;			
		
		m_pCubeRender->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &pCubeFace);	
		pCubeFace->GetDesc(&desc);

		if(FAILED(m_pD3DDevice->CreateDepthStencilSurface(desc.Width,desc.Height, 
			D3DFMT_D16,D3DMULTISAMPLE_NONE, 0, TRUE, &m_pCubeZBuffer[i], NULL))) return E_FAIL;

		SAFE_RELEASE(pCubeFace);
	}
*/
	return S_OK;
}
//更新
void CSkyBox::Update()
{
	
}
//開放
void CSkyBox::Uninit()
{
	//テクスチャ解放
/*
	if(m_pTexName != NULL)
	{
		for(DWORD k = 0; k < m_nNumMatModel; k++)
		{		

			SAFE_RELEASE( m_pD3DTextureModel[k] );
				
			//__asm int 3
		}
		SAFE_DELETE_ARRAY(m_pD3DTextureModel);
		
	}
*/
//	SAFE_DELETE_ARRAY(m_pMeshMaterials);
	//エフェクトファイル解放
	//SAFE_RELEASE( m_pEffect );
	//マテリアル開放
//	SAFE_RELEASE(m_pD3DXBuffMatModel);
	
	//メッシュ開放
//	SAFE_RELEASE(m_pD3DXMeshModel);
	
	for(int i = 0;i < CUBE_FACE;i++)
	{
		SAFE_RELEASE(m_pD3DTex[i]);
	}
	m_initManager = false;

	Release();
}
//描画
void CSkyBox::Draw()
{
	//変数宣言
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	D3DXMATRIX matRot;
/*	
	//▼キューブマップ
	// 現在のビュー行列とプロジェクション行列を保存しておく（この後一時的に変更するため）
	D3DXMATRIX matProjHold, matViewHold;
	m_pD3DDevice->GetTransform(D3DTS_VIEW, &matViewHold);
	m_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjHold);
	//通常時のバックバッファ、Ｚバッファを保存していく（後でもとのレンダリングターゲットに戻す際に必要）
	m_pD3DDevice->GetRenderTarget(0,&m_pBackBuffer);
	m_pD3DDevice->GetDepthStencilSurface(&m_pZBuffer);
	// キューブマップ上へのレンダリング用にプロジェクション行列を作成
	D3DXMATRIX matProj;		
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/2, 1.0f, 1.01f, 1000.0f);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
	 // キューブ マップ内、 6 つの面それぞれに見合ったビュー行列を作成
	for(DWORD i=0; i < CUBE_FACE-1; i++)
	{
		D3DXVECTOR3 vecEye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vecLookat, vecUp;
		switch(i)
		{
		case D3DCUBEMAP_FACE_POSITIVE_X:
			vecLookat = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			break;
		case D3DCUBEMAP_FACE_NEGATIVE_X:
			vecLookat = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			vecUp = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
			break;
		case D3DCUBEMAP_FACE_POSITIVE_Y:
			vecLookat = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vecUp = D3DXVECTOR3(0.0f, 0.0f,-1.0f);
			break;
		case D3DCUBEMAP_FACE_NEGATIVE_Y:
			vecLookat = D3DXVECTOR3(0.0f,-1.0f, 0.0f);
			vecUp = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			break;
		case D3DCUBEMAP_FACE_POSITIVE_Z:
			vecLookat = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);
			vecUp = D3DXVECTOR3( 0.0f, 1.0f, 0.0f);
			break;
		case D3DCUBEMAP_FACE_NEGATIVE_Z:
			vecLookat = D3DXVECTOR3(0.0f, 0.0f,-1.0f);
			vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			break;
		}
		D3DXMATRIX matView;			
		D3DXMatrixLookAtLH(&matView, &vecEye, &vecLookat, &vecUp);			
		m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);			
		// キューブマップ内の任意の面のサーフェイスを得る（それをレンダリングターゲットとして設定する）		
		LPDIRECT3DSURFACE9 pCubeFace;			
		m_pCubeRender->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &pCubeFace);				 
		m_pD3DDevice->SetRenderTarget (0,pCubeFace );
		m_pD3DDevice->SetDepthStencilSurface(m_pCubeZBuffer[i]); 
		SAFE_RELEASE(pCubeFace);
	}
//*/
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

	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //カリングしない
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	m_pD3DDevice->SetFVF(FVF_VERTEX_PATCLE);
	m_pD3DDevice->SetTexture(0,m_pD3DTex[0]);
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver1,sizeof(TLVERTEX));
	m_pD3DDevice->SetTexture(0,m_pD3DTex[1]);
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver2,sizeof(TLVERTEX));
	m_pD3DDevice->SetTexture(0,m_pD3DTex[2]);
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver3,sizeof(TLVERTEX));
	m_pD3DDevice->SetTexture(0,m_pD3DTex[3]);
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver4,sizeof(TLVERTEX));
	m_pD3DDevice->SetTexture(0,m_pD3DTex[4]);
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver5,sizeof(TLVERTEX));
	m_pD3DDevice->SetTexture(0,m_pD3DTex[5]);
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,ver6,sizeof(TLVERTEX));
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ); //カリングする

	//変数宣言
//	D3DXMATERIAL*	pD3DMat;
//	D3DMATERIAL9	matDef;

/*
	if(m_pD3DXBuffMatModel != NULL)
	{
		pD3DMat = (D3DXMATERIAL*)m_pD3DXBuffMatModel->GetBufferPointer();
		m_pD3DDevice->GetMaterial(&matDef);	//マテリアル情報保存
	}
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //カリングしない
	m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE); 
	if(m_initManager)
	{
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
		m_pD3DDevice->SetMaterial(&matDef);	//デフォルトに戻す
	}
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ); //カリングする
	m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,FALSE); 
*/
/*
	// レンダリングターゲットを元に戻す
	m_pD3DDevice->SetRenderTarget(0,m_pBackBuffer);		
	SAFE_RELEASE(m_pBackBuffer);			
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffer); 		
	SAFE_RELEASE(m_pZBuffer);	 
	// 保存しておいたビュー行列とプロジェクション行列により、変換行列を元に戻す
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matViewHold);
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProjHold);

	//キューブマップ用のテクスチャ座標を自動生成するよう指示	
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX,D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR );
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //カリングしない
	m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,TRUE); 
	if(m_initManager)
	{
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
			m_pD3DDevice->SetTexture( 0, m_pCubeEnvMap );
			//m_pD3DDevice->SetTexture( 0, m_pCubeRender );
			//pDevice->SetTexture(0,NULL);
			m_pD3DXMeshModel->DrawSubset(i);			//描画
			//m_pEffect->EndPass();
		}
		//m_pEffect->End();
		m_pD3DDevice->SetMaterial(&matDef);	//デフォルトに戻す
	}
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ); //カリングする
	m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,FALSE); 

//*/	

	
}
void CSkyBox::DrawShade()
{

}

//eof