//ヘッダーインクルード
#include "CScene2D.h"
#include "CRender.h"
#include <cmath>
//マクロ
#define POS_MARGIN_X	(100)
#define POS_MARGIN_Y	(50)

/*
//コンストラクタ
CScene2D::CScene2D(){};
//デストラクタ
CScene2D::~CScene2D(){};
*/
//作成
CScene2D* CScene2D::Create(CRender* pRender,D3DXVECTOR3 pos,char* ptexFileName,OBJTYPE objtype)
{
	CScene2D* pScene2D = new CScene2D(0,objtype);

	if(objtype == OBJTYPE_2D)
	{
		pScene2D->Init(pRender,pos,255,255,255,255,400,300,ptexFileName);
	}
	else if(objtype == OBJTYPE_2DGIM)
	{
		pScene2D->Init(pRender,pos,255,255,255,255,25,25,ptexFileName);
	}
	pScene2D->SetPosition(pos);

	return pScene2D;

}
//オーバーライド
CScene2D* CScene2D::Create(CRender* pRender,D3DXVECTOR3 pos,int nWidth,int nHeight,char* ptexFileName,OBJTYPE objtype)
{
	CScene2D* pScene2D = new CScene2D(0,objtype);

	pScene2D->Init(pRender,pos,255,255,255,255,nWidth,nHeight,ptexFileName);

	pScene2D->SetPosition(pos);

	return pScene2D;
}
//初期化
HRESULT CScene2D::Init(CRender* pRender)
{
	//デバイス取得
	m_pD3DDevice = pRender->getDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(m_pD3DDevice,"data\\Texture\\bg001.jpg",&m_pD3DTex);
	
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
	m_pRender = pRender;

	m_pos = D3DXVECTOR3(300,200,0);	//座標
	m_rot = D3DXVECTOR3(0,0,0);		//回転
	//対角線の長さ
	m_fLength = sqrtf(POS_MARGIN_X*POS_MARGIN_X+POS_MARGIN_Y*POS_MARGIN_Y);
	//対角線の角度
	m_fAngle  = atan2((float)POS_MARGIN_X,(float)POS_MARGIN_Y);

	return S_OK;
}
HRESULT CScene2D::Init(CRender* pRender,D3DXVECTOR3 pos,int nRed,int nGreen,int nBlue,int nalpha,int nWidth,int nHeight,char* pTexFileName)
{
	//デバイス取得
	m_pD3DDevice = pRender->getDevice();
	m_Red = nRed;
	m_Green = nGreen;
	m_Blue = nBlue;
	m_Alpha = nalpha;
	m_drawFlag = true;
	m_pTexName = pTexFileName;
	m_pRender = pRender;
	if(pTexFileName != NULL)
	{
		//テクスチャ読み込み
		D3DXCreateTextureFromFile(m_pD3DDevice,pTexFileName,&m_pD3DTex);
		/*
		if(pRender->GetMode() == MODE_GAME)
		{
			m_pD3DTex = pRender->GetRenderTexture();
		}
		*/
	}
	
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
	m_pos = pos;					//座標
	m_rot = D3DXVECTOR3(0,0,0);		//回転
	//対角線の長さ
	m_fLength = sqrtf((float)(nWidth*nWidth)+(float)(nHeight*nHeight));
	//対角線の角度
	m_fAngle  = atan2((float)nWidth,(float)nHeight);

	return S_OK;
}
//更新
void CScene2D::Uninit()
{
//	SAFE_RELEASE(m_pD3DDevice);		//Direct3dDeviceオブジェクトの開放
	if(m_pTexName != NULL)
	{
		SAFE_RELEASE(m_pD3DTex);		//テクスチャの開放
	}
	
	SAFE_RELEASE(m_pD3DVtxBuffer);	//頂点バッファの開放

	Release();

}
//開放
void CScene2D::Update()
{
	if(CScene::GetObjType() == OBJTYPE_2DGIM)
	{
		m_rot.z -= D3DX_PI * 0.01f;
	}
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

	VERTEX_2D *pVtx = NULL;
	if(m_pD3DVtxBuffer != NULL)
	{
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
		pVtx[0].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
		pVtx[1].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
		pVtx[2].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
		pVtx[3].diffuse = D3DCOLOR_RGBA(m_Red,m_Green,m_Blue,m_Alpha);
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0,1);
		pVtx[1].tex = D3DXVECTOR2(0,0);
		pVtx[2].tex = D3DXVECTOR2(1,1);
		pVtx[3].tex = D3DXVECTOR2(1,0);
		//アンロック
		m_pD3DVtxBuffer->Unlock();
	}
}
//描画
void CScene2D::Draw()
{
	if(m_drawFlag)
	{
		if(m_pRender->GetMode() == MODE_TITLE)
		{
			m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		}
		else if(m_pRender->GetMode() == MODE_GAME)
		{
			m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
		}
		// テクスチャステージステートの設定
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

		//データを渡す
		m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
		//FVFの設定
		m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
		if(m_pTexName != NULL)
		{
			//テクスチャの設定
			m_pD3DDevice->SetTexture(0,m_pD3DTex);

		}
		else
		{
			//テクスチャの設定
			m_pD3DDevice->SetTexture(0,NULL);
		}
		//ポリゴンの設定
		m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

		//テクスチャステージ
//		m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
//		m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
//		m_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);
		//αブレンド
		m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, FALSE );

		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	}
	//
}
void CScene2D::DrawShade()
{
	//データを渡す
	m_pD3DDevice->SetStreamSource(0,m_pD3DVtxBuffer,0,sizeof(VERTEX_2D));
	//FVFの設定
	m_pD3DDevice->SetFVF(FVF_VERTEX_2D);	
	if(m_pTexName != NULL)
	{
		//テクスチャの設定
		m_pD3DDevice->SetTexture(0,m_pD3DTex);

	}
	else
	{
		//テクスチャの設定
		m_pD3DDevice->SetTexture(0,NULL);
	}
	//ポリゴンの設定
	m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}
