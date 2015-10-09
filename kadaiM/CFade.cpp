//=============================================================================
//
// フェード処理 [CFade.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CFade.h"
#include "CRender.h"
#include <process.h>

//マクロ
#define POS_MARGIN_FADE_X	(400)
#define POS_MARGIN_FADE_Y	(300)

//メンバ変数
CFade* CFade::m_instance = NULL;

CFade* CFade::getinstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CFade();
	}
	return m_instance;
}

void CFade::Release()
{
	if(m_instance != NULL)
	{
		delete m_instance;
		m_instance = NULL;
	}
}

//初期化
HRESULT CFade::Init(CRender* pRender)
{
	m_pRender = pRender;
	m_FadeMode = FADE_NONE;

	//デバイス取得
	m_pD3DDevice = pRender->getDevice();

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
	//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\fade.png",&m_pD3DTex);

	m_pos = D3DXVECTOR3(400,300,0);	//座標
	m_rot = D3DXVECTOR3(0,0,0);		//回転
	//対角線の長さ
	m_fLength = sqrtf(POS_MARGIN_FADE_X*POS_MARGIN_FADE_X+POS_MARGIN_FADE_Y*POS_MARGIN_FADE_Y);
	//対角線の角度
	m_fAngle  = atan2((float)POS_MARGIN_FADE_X,(float)POS_MARGIN_FADE_Y);

	_beginthreadex( NULL, 0, FadeThread, NULL, 0, NULL );
	return S_OK;
}
//開放
void CFade::Uninit()
{
	SAFE_RELEASE(m_pD3DVtxBuffer);	//頂点バッファの開放
	SAFE_RELEASE(m_pD3DTex);
}
//更新
void CFade::Update()
{
	if(m_FadeMode == FADE_OUT)
	{
		if(FadeOut())
		{
			m_FadeMode = FADE_OUT_FINISH;
			
		}
	}
	
	if(m_FadeMode == FADE_IN)
	{
		if(FadeIn())
		{
			m_FadeMode = FADE_NONE;
			
		}
	}
	VERTEX_2D *pVtx = NULL;
	//ロック
	m_pD3DVtxBuffer->Lock(0,0,(void**)&pVtx,0);

	//頂点
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
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,m_Alpha);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0,1);
	pVtx[1].tex = D3DXVECTOR2(0,0);
	pVtx[2].tex = D3DXVECTOR2(1,1);
	pVtx[3].tex = D3DXVECTOR2(1,0);
	//アンロック
	m_pD3DVtxBuffer->Unlock();
}

//描画
void CFade::Draw()
{
	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
	
	//テクスチャの設定
	m_pD3DDevice->SetTexture(0,m_pD3DTex);
	
	//ポリゴンの設定
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

	//テクスチャステージ
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);


}
//フェードアウト
bool CFade::FadeOut()
{
	if(m_FadeMode == FADE_OUT)
	{
		m_Alpha+=15;
		
		if(m_Alpha >= 255)
		{
			m_Alpha = 255;
			
			return true;
		}
	}
	return false;
}
//フェードイン
bool CFade::FadeIn()
{
	if(m_FadeMode == FADE_IN)
	{
		
		m_Alpha-=15;
		
		if(m_Alpha <= 0)
		{
			m_Alpha = 0;
			
			return true;
		}
	}
	return false;
}
//スレッド
unsigned int __stdcall CFade::FadeThread(LPVOID Param)
{

	return 0;
}
//eof