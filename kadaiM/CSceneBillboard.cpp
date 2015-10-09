//ヘッダーインクルード
#include "CSceneBillboard.h"
#include "CRender.h"
#include "CCamera.h"

//作成
CSceneBillboard* CSceneBillboard::Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,float fsize)
{
	CSceneBillboard* pBillboard = new CSceneBillboard(2);

	pBillboard->Init(pRender,xfilename,0,fsize);

	pBillboard->SetPosition(pos);

	return pBillboard;

}
//初期化
HRESULT CSceneBillboard::Init(CRender* pRender)
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
	VERTEX_3D *pVtx = NULL;
	//ロック
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//頂点
	pVtx[0].vtx = D3DXVECTOR3(-50.0f,50.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(50.0f,50.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-50.0f,-50.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(50.0f,-50.0f,0.0f);

	//座標変換後位置
	pVtx[0].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0,0.0f,-1.0f);

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

HRESULT CSceneBillboard::Init(CRender* pRender,char* ptexfilename,float fangle,float fsize)
{
	//デバイス取得
	m_pD3DDevice = pRender->getDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,ptexfilename,&m_pD3DTex);
	
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
	//m_pos = D3DXVECTOR3(0,0,0);		//座標
	m_rot = D3DXVECTOR3(0,fangle,0);		//回転
	m_scl = D3DXVECTOR3(1,1,1);
	VERTEX_3D *pVtx = NULL;
	//ロック
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//頂点
	pVtx[0].vtx = D3DXVECTOR3(0.0f,fsize,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(fsize,fsize,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(fsize,0.0f,0.0f);

	//座標変換後位置
	pVtx[0].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0,0.0f,-1.0f);

	//色
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0,0);
	pVtx[1].tex = D3DXVECTOR2(1,0);
	pVtx[2].tex = D3DXVECTOR2(0,1);
	pVtx[3].tex = D3DXVECTOR2(1,1);
	//アンロック
	m_pD3DVtxBuffer->Unlock();
	return S_OK;
}

HRESULT CSceneBillboard::InitAnime(CRender* pRender,char* ptexfilename)
{
	//デバイス取得
	m_pD3DDevice = pRender->getDevice();

	//アニメーション用テクスチャ間隔
	m_fTexU = 1.0f/static_cast<float>(ANIM_PTN);

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,ptexfilename,&m_pD3DTex);
	
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
	VERTEX_3D *pVtx = NULL;
	//ロック
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//頂点
	pVtx[0].vtx = D3DXVECTOR3(0.0f,15.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3(15.0f,15.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3(15.0f,0.0f,0.0f);

	//座標変換後位置
	pVtx[0].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[1].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[2].nor = D3DXVECTOR3(0,0.0f,-1.0f);
	pVtx[3].nor = D3DXVECTOR3(0,0.0f,-1.0f);

	//色
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_fTexU,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_fTexU,1.0f);
	
	//アンロック
	m_pD3DVtxBuffer->Unlock();

	m_bFlag = true;
	m_nAnimCnt = 0;
	return S_OK;
}
//開放
void CSceneBillboard::Uninit()
{
//	SAFE_RELEASE(m_pD3DDevice);		//Direct3dDeviceオブジェクトの開放
	SAFE_RELEASE(m_pD3DTex);		//テクスチャの開放
	SAFE_RELEASE(m_pD3DVtxBuffer);	//頂点バッファの開放
	
	Release();
}
//更新
void CSceneBillboard::Update()
{
	/*
	m_rot.y -= D3DX_PI * 0.001f;

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

void CSceneBillboard::UpdateAnime()
{

	VERTEX_3D *pVtx = NULL;

	if(m_bFlag)
	{

		///*
		//カウンタプラス
		m_nAnimCnt++;
		//テクスチャ座標計算
		m_fTexUt = (U_POSITION*(m_nAnimCnt/ANIM_WAIT%ANIM_PTN))/10.f;

		//ロック
		m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);
			
		pVtx[0].tex = D3DXVECTOR2(m_fTexUt,0.0f);
		pVtx[1].tex = D3DXVECTOR2(m_fTexUt+m_fTexU,0.0f);
		pVtx[2].tex = D3DXVECTOR2(m_fTexUt,1.0f);
		pVtx[3].tex = D3DXVECTOR2(m_fTexUt+m_fTexU,1.0f);
			
		//アンロック
		m_pD3DVtxBuffer->Unlock();
		//*/
		if(m_nAnimCnt >= EXPROSION_ENDCNT)
		{
			m_nAnimCnt = 0;
			m_bFlag = false;
			Uninit();
		}
	}
}
//描画
void CSceneBillboard::Draw()
{
	//変数宣言
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxView;
	//ビューマトリックス取得
	mtxView = GetMtxView();
	
	D3DXMatrixIdentity(&m_mtxWorld);

	//αテスト
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF,0);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_ALWAYS);
/*	
	//回転
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
*/
	//拡縮
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//ビルボード
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	//ワールドトランスフォーム
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//ライト切る
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_3D));
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//テクスチャの設定
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//ポリゴンの設定
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//元に戻す
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//ライト付ける
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
}
void CSceneBillboard::DrawShade()
{
		//変数宣言
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxView;
	//ビューマトリックス取得
	mtxView = GetMtxView();
	
	D3DXMatrixIdentity(&m_mtxWorld);

	//αテスト
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF,0);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_ALWAYS);
/*	
	//回転
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
*/
	//拡縮
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//ビルボード
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	//ワールドトランスフォーム
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	//ライト切る
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_3D));
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
	//テクスチャの設定
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//ポリゴンの設定
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//元に戻す
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
	//ライト付ける
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL);
}
void CSceneBillboard::DrawAnime(void)
{
	//変数宣言
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate,mtxView;

	//αテスト
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAREF,0);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);

	//ビューマトリックス取得
	mtxView = GetMtxView();
	D3DXMatrixIdentity(&m_mtxWorld);

/*	
	//回転
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
*/
	//拡縮
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//ビルボード
	D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	//ワールドトランスフォーム
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	if(m_bFlag)
	{
		//データを渡す
		m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_3D));
		//FVFの設定
		m_pD3DDevice->SetFVF(FVF_VERTEX_3D);	
		//テクスチャの設定
		m_pD3DDevice->SetTexture(0,m_pD3DTex);
		//ポリゴンの設定
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
	}
	//元に戻す
	m_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
}

