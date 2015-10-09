//ヘッダーインクルード
#include "CMeshWall.h"
#include "CRender.h"
#include <cmath>
#include "CDebugProc.h"
//マクロ
#define POS_MARGIN_X	(100)
#define POS_MARGIN_Y	(50)
D3DXVECTOR3	CMeshWall::m_rotVer[4];
int		CMeshWall::m_nCreateCnt = 0;
/*
//コンストラクタ
CMeshWall::CMeshWall(){};
//デストラクタ
CMeshWall::~CMeshWall(){};
*/
//作成
CMeshWall* CMeshWall::Create(CRender* pRender,D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CMeshWall* pSceneMeshWall = new CMeshWall();

	pSceneMeshWall->Init(pRender,1,1,500.f,100.f,pos,rot,"data\\Texture\\wall.jpg");

	pSceneMeshWall->SetPosition(pos);
//	pSceneMeshWall->SetRotate(D3DXVECTOR3(0,120,0));

	return pSceneMeshWall;

}
//初期化
HRESULT CMeshWall::Init(CRender* pRender)
{
	//デバイス取得
	m_pD3DDevice = pRender->getDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\bg001.jpg",&m_pD3DTex);
	

	return S_OK;
}
//初期化オーバーロード
HRESULT CMeshWall::Init(CRender* pRender,int nNumBlockX, int nNumBlockY, float fSizeBlockX, float fSizeBlockY,D3DXVECTOR3 pos,D3DXVECTOR3 rot,char *pTexPath)
{
	//デバイス取得
	m_pD3DDevice = pRender->getDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,pTexPath,&m_pD3DTex);

	//総頂点数
	m_nNumVertex = (nNumBlockX+1) * (nNumBlockY+1);
	//ポリゴン数
	m_nNumPolygon = nNumBlockX*nNumBlockY*2+(nNumBlockY-1)*4;
	//インデックス総数
	m_nNumVertexIndex = (nNumBlockX+1)*(nNumBlockY+1)+(nNumBlockY-1)*(3+nNumBlockX);

	//地面ポリゴンの設定を初期化
	m_pos	= pos;
	m_rot	= rot;
	m_scl	= D3DXVECTOR3(1.0f,1.0f,1.0f);

	//ポリゴン設定
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_nNumVertex,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuff,
											NULL)))
	{
		return E_FAIL;
	}
	
	//インデックス初期化
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
	//ロック
	m_pD3DVtxBuff->Lock(0,0,(void**)&pVtx,0);

	// i行t列に頂点設定
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
			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 合計が1.0fになるようにしないとダメ
			pVtx[nNum].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[nNum].tex = D3DXVECTOR2(float(j), float(i));
		}
	}
	//TODO考える
	
	//アンロック
	m_pD3DVtxBuff->Unlock();
	
	//インデックス設定
	WORD *pIndex;
	// xIndex行xzIndex列
	int xIndex = 0;
	int yIndex = 0;



	m_pD3DIndexBuff->Lock(0,0,(void**)&pIndex,0);	//ロック
	
	for(int i = 0; i < m_nNumVertexIndex; i++)
	{
		// 縮退ポリゴン点
		if(i == 2*(nNumBlockX+1)+yIndex*(2*(nNumBlockX+1)+2))
		{
			pIndex[i] =  (xIndex -1) + yIndex*(nNumBlockX+1);
			pIndex[i+1] = xIndex + (yIndex+1)*(nNumBlockX+1);

			// 段が変わる
			i += 2;
			yIndex++;
			xIndex = 0;
		}

		// 下の点
		if(i % 2 == 0)
		{
			pIndex[i] = xIndex + (yIndex+1)*(nNumBlockX+1);

		}
		// 上の点
		else
		{
			pIndex[i] = xIndex + yIndex*(nNumBlockX+1);
			xIndex++;
		}
	}

	m_pD3DIndexBuff->Unlock();	//アンロック

	return S_OK;

}
//更新
void CMeshWall::Uninit()
{
//	SAFE_RELEASE(m_pD3DDevice);		//Direct3dDeviceオブジェクトの開放
	SAFE_RELEASE(m_pD3DTex);		//テクスチャの開放
	SAFE_RELEASE(m_pD3DVtxBuff);	//頂点バッファの開放
	SAFE_RELEASE(m_pD3DIndexBuff);	//インデックスバッファの開放

	Release();

}
//開放
void CMeshWall::Update()
{
/*
	m_rot.z -= D3DX_PI * 0.001f;

	//角度正規化
	if( m_rot.z < -D3DX_PI )
	{
		m_rot.z += 2 * D3DX_PI;
	}
	// 角度を正規化
	else if( m_rot.z > D3DX_PI )
	{
		m_rot.z -= 2 * D3DX_PI;
	}
*/
	CDebugProc::Print("wallX:%fwallY:%fwallZ:%f\n",m_rot.x,m_rot.y,m_rot.z);
	CDebugProc::Print("posX:%fposY:%fposZ:%f\n",m_pos.x,m_pos.y,m_pos.z);

	CDebugProc::Print("頂点X:%f:Y:%f:Z:%f\n",m_Vertex.x,m_Vertex.y,m_Vertex.z);
}
//描画
void CMeshWall::Draw()
{
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
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

//	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //カリングしない
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pD3DDevice->SetIndices(m_pD3DIndexBuff);
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//テクスチャの設定
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//ポリゴンの設定
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertex,0,m_nNumPolygon);
//	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW ); //カリングする
}

void CMeshWall::DrawShade()
{
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
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

//	pDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ); //カリングしない
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	m_pD3DDevice->SetIndices(m_pD3DIndexBuff);
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//テクスチャの設定
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//ポリゴンの設定
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_nNumVertexIndex,0,m_nNumPolygon);

}

D3DXVECTOR3 CMeshWall::GetVertex()
{
	return m_Vertex;
}