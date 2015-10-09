#include "CScene3D.h"
#include "CRender.h"

D3DXVECTOR3 g_vec[4];
//作成
CScene3D* CScene3D::Create(CRender* pRender,D3DXVECTOR3 pos)
{
	CScene3D* pScene3D = new CScene3D(1);

	pScene3D->Init(pRender);

	pScene3D->SetPosition(pos);

	return pScene3D;

}
//初期化
HRESULT CScene3D::Init(CRender* pRender)
{
	//デバイス取得
	m_pD3DDevice = pRender->getDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\bg001.jpg",&m_pD3DTex);
	
	//ポリゴン設定
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_3D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffer,
											NULL)))
	{
		return E_FAIL;
	}
	m_pos = D3DXVECTOR3(0,0,0);		//座標
	m_rot = D3DXVECTOR3(0,0,0);		//回転
	m_scl = D3DXVECTOR3(1,1,1);


	D3DXVECTOR3 vpF[4];
	D3DXVECTOR3 out,out1,nor;
	VERTEX_3D *pVtx = NULL;
	//ロック
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);
/*
	pVtx[0].vtx = D3DXVECTOR3(-15.0f,0.0f,-15.0f);
	pVtx[1].vtx = D3DXVECTOR3(-15.0f,20.0f,15.0f);	//
	pVtx[2].vtx = D3DXVECTOR3(15.0f,20.0f,-15.0f);	//
	pVtx[3].vtx = D3DXVECTOR3(15.0f,0.0f,15.0f);
	pVtx[4].vtx = D3DXVECTOR3(15.0f,20.0f,-15.0f);	//
	pVtx[5].vtx = D3DXVECTOR3(-15.0f,20.0f,15.0f);	//
	
	//面法線
	vpF[0] = pVtx[1].vtx-pVtx[0].vtx;
	vpF[1] = pVtx[2].vtx-pVtx[0].vtx;
	vpF[2] = pVtx[5].vtx-pVtx[3].vtx;
	vpF[3] = pVtx[4].vtx-pVtx[3].vtx;
	

	//外積算出
	D3DXVec3Cross(&out,&vpF[0],&vpF[1]);
	D3DXVec3Cross(&out1,&vpF[2],&vpF[3]);
	out1.y*=-1;
	//正規化
	D3DXVec3Normalize(&out,&out);
	D3DXVec3Normalize(&out1,&out1);
	
	nor = (out+out1)/2;
	D3DXVec3Normalize(&nor,&nor);
	//法線
	pVtx[0].nor = out;
	pVtx[1].nor = nor;
	pVtx[2].nor = nor;
	pVtx[3].nor = out1;
	pVtx[4].nor = nor;
	pVtx[5].nor = nor;

	//色
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[4].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[5].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0,1);
	pVtx[1].tex = D3DXVECTOR2(0,0);
	pVtx[2].tex = D3DXVECTOR2(1,1);
	pVtx[3].tex = D3DXVECTOR2(1,0);
	pVtx[4].tex = D3DXVECTOR2(1,0);
	pVtx[5].tex = D3DXVECTOR2(1,0);
*/
	//頂点
	
	
	pVtx[0].vtx = D3DXVECTOR3(-50.0f,0.0f,50.0f);
	pVtx[1].vtx = D3DXVECTOR3(50.0f,20.0f,50.0f);	//
	pVtx[2].vtx = D3DXVECTOR3(-50.0f,20.0f,-50.0f);	//
	pVtx[3].vtx = D3DXVECTOR3(50.0f,0.0f,-50.0f);

	for(int i = 0;i < 4;i++)
	{
		g_vec[i] = pVtx[i].vtx;
	}

	//面法線
	vpF[0] = pVtx[1].vtx-pVtx[0].vtx;
	vpF[1] = pVtx[2].vtx-pVtx[0].vtx;
	vpF[2] = pVtx[1].vtx-pVtx[3].vtx;
	vpF[3] = pVtx[2].vtx-pVtx[3].vtx;
	

	//外積算出
	D3DXVec3Cross(&out,&vpF[0],&vpF[1]);
	D3DXVec3Cross(&out1,&vpF[2],&vpF[3]);
	out1.y*=-1;
	//正規化
	D3DXVec3Normalize(&out,&out);
	D3DXVec3Normalize(&out1,&out1);
	
	nor = (out+out1)/2;
	D3DXVec3Normalize(&nor,&nor);

	//座標変換後位置
	pVtx[0].nor = out;
	pVtx[1].nor = nor;
	pVtx[2].nor = nor;
	pVtx[3].nor = out1;

	pVtx[0].nor = D3DXVECTOR3(0,1,0);
	pVtx[1].nor = D3DXVECTOR3(0,1,0);
	pVtx[2].nor = D3DXVECTOR3(0,1,0);
	pVtx[3].nor = D3DXVECTOR3(0,1,0);
	//色
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0,1);
	pVtx[1].tex = D3DXVECTOR2(0,0);
	pVtx[2].tex = D3DXVECTOR2(1,1);
	pVtx[3].tex = D3DXVECTOR2(1,0);

	//アンロック
	m_pD3DVtxBuffer->Unlock();

	return S_OK;
}
//更新
void CScene3D::Uninit()
{
	SAFE_RELEASE(m_pD3DTex);		//テクスチャの開放
	SAFE_RELEASE(m_pD3DVtxBuffer);	//頂点バッファの開放

	Release();
}
//開放
void CScene3D::Update()
{
/*
	m_rot.y -= D3DX_PI * 0.01f;

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

}
//描画
void CScene3D::Draw()
{

	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

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


//	D3DXMatrixRotationY( &m_mtxWorld, timeGetTime()/3000.0f );
//	D3DXMatrixRotationX( &mtxRot, 0.5f );
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);

	//平行移動
//	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//ワイヤーフレーム表示
//	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_3D));
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//テクスチャの設定
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//m_pD3DDevice->SetTexture(0,NULL);
	//ポリゴンの設定
//	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	
}
void CScene3D::DrawShade()
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

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


//	D3DXMatrixRotationY( &m_mtxWorld, timeGetTime()/3000.0f );
//	D3DXMatrixRotationX( &mtxRot, 0.5f );
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);

	//平行移動
//	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//ワイヤーフレーム表示
//	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_3D));
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//テクスチャの設定
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//m_pD3DDevice->SetTexture(0,NULL);
	//ポリゴンの設定
//	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
float GetHeight(D3DXVECTOR3 pos,D3DXVECTOR3* pNormal)
{
	D3DXVECTOR3 Vec0,Vec1;
	
	Vec0 = g_vec[1] - g_vec[0];
	Vec1 = pos - g_vec[0];

	//左側
	if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
	{
		Vec0 = g_vec[2] - g_vec[1];
		Vec1 = pos - g_vec[1];
		if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
		{
			Vec0 = g_vec[0] - g_vec[2];
			Vec1 = pos - g_vec[2];
			if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
			{
				return GetHeightPolygon(g_vec[0],g_vec[1],g_vec[2],pos,pNormal);
			}
		}
	}
	//右側
	Vec0 = g_vec[3] - g_vec[1];
	Vec1 = pos - g_vec[1];
	
	if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
	{
		Vec0 = g_vec[2] - g_vec[3];
		Vec1 = pos - g_vec[3];
		if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
		{
			Vec0 = g_vec[1] - g_vec[2];
			Vec1 = pos - g_vec[2];
			if(Vec0.z * Vec1.x - Vec0.x * Vec1.z >= 0)
			{
				return GetHeightPolygon(g_vec[3],g_vec[1],g_vec[2],pos,pNormal);
			}
		}
	}
	return 0.0f;

}
//高さ取得
float GetHeightPolygon(D3DXVECTOR3& p0,D3DXVECTOR3& p1,D3DXVECTOR3& p2,D3DXVECTOR3& pos,D3DXVECTOR3* pNormal)
{
	D3DXVECTOR3 Vec0,Vec1;

	Vec0 = p1 - p0;
	Vec1 = p2 - p0;
	float fHeight = 0.0f;

	//外積
	D3DXVec3Cross(pNormal,&Vec0,&Vec1);
	//正規化
	D3DXVec3Normalize(pNormal,pNormal);

	if(pNormal->y == 0.0f)
	{
		return 0.0f;
	}
	fHeight = p0.y - (pNormal->x*(pos.x-p0.x)+pNormal->z*(pos.z-p0.z))/pNormal->y;

	return fHeight;
}