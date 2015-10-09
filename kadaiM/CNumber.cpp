//=============================================================================
//
// 数値を一個だけ処理 [CNumber.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CNumber.h"
#include "CRender.h"

//マクロ定義
#define NUM_MARGIN_X	(25)
#define NUM_MARGIN_Y	(25)

//生成
CNumber* CNumber::Create(CRender* pRender,const D3DXVECTOR3 pos)
{
	CNumber* pNumber = new CNumber();

	pNumber->Init(pRender);

	pNumber->SetPosition(pos);

	return pNumber;
}
//初期化
HRESULT CNumber::Init(CRender* pRender)
{
	//デバイス取得
	m_pD3DDevice = pRender->getDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\number.png",&m_pD3DTex);
	
	//ポリゴン設定
	if(FAILED(m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
											D3DUSAGE_WRITEONLY,
											FVF_VERTEX_2D,
											D3DPOOL_MANAGED,
											&m_pD3DVtxBuffer,
											NULL)))
	{
		return E_FAIL;
	}
	//m_pos = D3DXVECTOR3(300,200,0);	//座標
	m_rot = D3DXVECTOR3(0,0,0);		//回転
	//対角線の長さ
	m_fLength = sqrtf(NUM_MARGIN_X*NUM_MARGIN_X+NUM_MARGIN_Y*NUM_MARGIN_Y);
	//対角線の角度
	m_fAngle  = atan2((float)NUM_MARGIN_X,(float)NUM_MARGIN_Y);

	
	return S_OK;
}

//更新
void CNumber::Update(void)
{
	VERTEX_2D *pVtx = NULL;
	//ロック
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//左下
	pVtx[0].vtx.x = m_pos.x - sinf(-m_rot.z+m_fAngle)*m_fLength;
	pVtx[0].vtx.y = m_pos.y + cosf(-m_rot.z+m_fAngle)*m_fLength;
	//左上
	pVtx[1].vtx.x = m_pos.x - sinf(m_rot.z+m_fAngle)*m_fLength;
	pVtx[1].vtx.y = m_pos.y - cosf(m_rot.z+m_fAngle)*m_fLength;
	//右下
	pVtx[2].vtx.x = m_pos.x + sinf(m_rot.z+m_fAngle)*m_fLength;
	pVtx[2].vtx.y = m_pos.y + cosf(m_rot.z+m_fAngle)*m_fLength;
	//右上
	pVtx[3].vtx.x = m_pos.x + sinf(-m_rot.z+m_fAngle)*m_fLength;
	pVtx[3].vtx.y = m_pos.y - cosf(-m_rot.z+m_fAngle)*m_fLength;
	//座標変換後位置
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//色
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(m_Num*0.1f,1.0f);
	pVtx[1].tex = D3DXVECTOR2(m_Num*0.1f,0);
	pVtx[2].tex = D3DXVECTOR2(m_Num*0.1f+0.1f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_Num*0.1f+0.1f,0);
	//アンロック
	m_pD3DVtxBuffer->Unlock();
}

//開放
void CNumber::Uninit(void)
{
	SAFE_RELEASE(m_pD3DTex);		//テクスチャの開放
	SAFE_RELEASE(m_pD3DVtxBuffer);	//頂点バッファの開放
	//__asm int 3
}

//描画
void CNumber::Draw(void)
{
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
	//テクスチャの設定
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//ポリゴンの設定
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
void CNumber::DrawShade(void)
{
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
	//テクスチャの設定
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	//ポリゴンの設定
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
//変更
void CNumber::ChengeNumber(int Value)
{
	VERTEX_2D *pVtx = NULL;

	m_Num = Value;
}



//eof