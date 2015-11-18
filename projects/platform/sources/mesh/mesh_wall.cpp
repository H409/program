#include "mesh_wall.h"
//=============================================================================
//
// メッシュウォール処理 [CMeshWall.cpp]
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
	//壁が最大数までに達した
	return 0;
}
HRESULT MeshWall::Init(	float posX,float posY,float posZ,float rotY,
							int nNumBlockX,int nNumBlockY,float fSizeBlockX,float fSizeBlockY)
{
	VERTEX_3D *pVtx;			//頂点情報
	WORD *pIndex;				//インデックス情報

	//インデックス番号最大数
	m_VtxIdxNum = SUM_INDEX(nNumBlockX,nNumBlockY);

	//頂点座標番号最大数
	m_NumVtx = (nNumBlockX+1)*(nNumBlockY+1);

	//ポリゴン数
	m_NumPolygon = ((nNumBlockX*2)*nNumBlockY)+((nNumBlockY-1)*4);

	//座標
	m_pos = D3DXVECTOR3(posX,posY,posZ);
	//回転(ラジアン)
	m_rot = D3DXVECTOR3(0.0f,rotY,0.0f);
	//拡大縮小
	m_scl = D3DXVECTOR3(1.0f,1.0f,1.0f);

	//壁の大きさ保存
	m_wallsizeX=nNumBlockX*fSizeBlockX;
	m_wallsizeY=nNumBlockY*fSizeBlockY;

	//壁から見た中心座標設定
	m_center.x=0.0f;
	m_center.y=0.0f;
	m_center.z=0.0f;

		//インデックスバッファの生成
	if(FAILED(pDevice->CreateIndexBuffer(	sizeof(WORD)*m_VtxIdxNum,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pIndexBuff,
											NULL)))
	{
		return E_FAIL;
	}
	//頂点バッファの生成
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_NumVtx,
										D3DUSAGE_WRITEONLY,
										FVF_VERTEX_3D,
										D3DPOOL_MANAGED,
										&m_pD3DVtxBuff,
										NULL)))
	{
		return E_FAIL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(GetDevice(),"data/TEXTURE/wall004.jpg",&m_pD3DTexture);

	//頂点座標の設定
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

	//インデックスバッファ設定
	m_pIndexBuff->Lock(0,0,(void**)&pIndex,0);

	//繰り返し管理変数
	int loopx=0;
	int VtxNo=0;
	int check=0;

	for(int y = 0;y<nNumBlockY;y++)
	{
		//右下の折り返し地点でのインデックスの保存
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
		//左上の折り返し地点でのインデックス保存
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
	//壁のY軸角度を、部屋中心からの回転に合わせる
	m_rot.y = m_rot_from_center.y;
	//位置を中心からの回転に合わせる
	m_pos.x = m_center.x + sinf(m_rot_from_center.y)*m_Length_From_CenterXZ;
	m_pos.z = m_center.z + cosf(m_rot_from_center.y)*m_Length_From_CenterXZ;
	//角位置の更新
	SetEdge();
	SetLength();
}

void MeshWall::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	//それぞれのマトリクスの設定
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMatrixScaling(&mtxScl,1.0f,1.0f,1.0f);							//拡大倍率
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);				//傾き//弧度法で入れる Y,X,Z
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);

	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);				//空間の平行移動
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//頂点バッファをデータストリームソースにバインド
	pDevice ->SetStreamSource(0,m_pD3DVtxBuff,0,sizeof(VERTEX_3D));
	
	pDevice->SetIndices(m_pIndexBuff);
	//頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice ->SetTexture(0,m_pD3DTexture);

	//ポリゴンの描画(インデックスバージョン)
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,m_VtxIdxNum,0,m_NumPolygon);
}


//アクセサー
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
//壁の角の座標セット
void MeshWall::SetEdge(void)
{
	//角の位置計算
	m_edge.x=m_pos.x-(cosf(m_rot.y)*(m_wallsizeX/2));
	m_edge.z=m_pos.z+(sinf(m_rot.y)*(m_wallsizeX/2));
	//角の位置保存
	m_edges[m_id].x=m_edge.x;
	m_edges[m_id].z=m_edge.z;
}
//特定の位置を中心とした、壁の特定の座標から中心までの距離算出
void MeshWall::SetLength(void)
{
	//壁の中心から
	m_Length_From_CenterXZ=sqrtf( (m_pos.x-m_center.x) * (m_pos.x-m_center.x) + (m_pos.z-m_center.z) * (m_pos.z-m_center.z));
	//壁の角から
	m_Length_Edge_From_CenterXZ=sqrtf((m_edge.x-m_center.x) * (m_edge.x-m_center.x) + (m_edge.z-m_center.z) * (m_edge.z-m_center.z));
}
