//=============================================================================
//
// パーティクルの処理 [CPaticle.cpp]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================

//ヘッダーインクルード
#include "CPaticle.h"
#include "CRender.h"
#include <cmath>
#include "CPlayer.h"

inline DWORD GET_ADDRESS( FLOAT f ) { return *((DWORD*)&f); }
#define SPRITE_WIDTH	(256)
#define SPRITE_HEIGHT	(256)
#define COLOR_MAX	(255)

//生成
CPaticle* CPaticle::Create(CRender* pRender,D3DXVECTOR3 pos,char* ptexfilename)
{
	CPaticle* pPaticle = new CPaticle(4);

	pPaticle->Init(pRender,pos,ptexfilename);

	pPaticle->SetPosition(pos);

	return pPaticle; 
}

//初期化
HRESULT	CPaticle::Init( CRender* pRender)
{
	return S_OK;
}
//オーバーロード
HRESULT CPaticle::Init(CRender* pRender,D3DXVECTOR3 pos,char *ptexfilename)
{
	m_pRender = pRender;
	m_pD3DDevice = pRender->getDevice();
	

	m_pos = pos;
	m_rot = D3DXVECTOR3(0,0,0);
	m_scl = D3DXVECTOR3(10,10,10);
	m_DeleteCnt = 0;
	m_continueTime = 1000.0f;
	//バーテックスバッファ
	MY_VERTEX_1* pv;
	
	if( FAILED( m_pD3DDevice->CreateVertexBuffer( PATICLE_MAX * sizeof(MY_VERTEX_1), 
												D3DUSAGE_WRITEONLY, FVF_VERTEX_MINE, 
												D3DPOOL_MANAGED, &m_pVBuffer, NULL ) ) ) 
	{
		return E_FAIL;
	}
	m_pVBuffer->Lock( 0, 0, (LPVOID*)&pv, 0 );
	for(int i = 0; i < PATICLE_MAX; i++)
	{
		pv[i].color  = (DWORD)D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	m_pVBuffer->Unlock();
//	D3DXCreateTextureFromFile(m_pD3DDevice,ptexfilename,&m_pTexture);
	//テクスチャ読み込み
	D3DXCreateTextureFromFileEx(m_pD3DDevice, ptexfilename,0,0,0,0,D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR,
			0xFF000000 , NULL, NULL, &m_pTexture);


	/*
	for(int i = 0;i < PATICLE_MAX;i++)
	{
		m_paticle[i].m_vector.x = ( (float)rand() /(float)RAND_MAX * 4 )-2;// -2 ～ 2
		m_paticle[i].m_vector.y	= ( (float)rand() /(float)RAND_MAX * 4 )-2;// -2 ～ 2
		m_paticle[i].m_vector.z = ( (float)rand() /(float)RAND_MAX * 40 )+30;// 30 ～ 70

		m_paticle[i].m_fScale = 10.0f;
		m_paticle[i].m_dwColor = D3DCOLOR_ARGB(255,255,255,255);
	}
	*/

	DWORD time = ::timeGetTime();

	if(m_pRender->GetMode() == MODE_TITLE)
	{
		for(int i = 0;i < PATICLE_MAX;i++)
		{
			// ポイントスプライトの初期位置
			m_post[i].pos =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ポイントスプライトの初速度とその方向
			m_post[i].vec.x = ((float)rand() / (float)RAND_MAX)*30.0f - 15.0f; 
			m_post[i].vec.y = ((float)rand() / (float)RAND_MAX)*30.0f + 30.0f;
			m_post[i].vec.z = ((float)rand() / (float)RAND_MAX)*30.0f - 15.0f;

			// ポイントスプライトのサイズ
			m_post[i].psize =  ((float)rand() / (float)RAND_MAX)*4.0f + 8.0f; 

			// ポイントスプライトの継続時間
			m_post[i].duration = ((float)rand() / (float)RAND_MAX)*2.0f+2.0f; 

			// ポイントスプライトの開始時間
			m_post[i].start_time = time  - (DWORD)(((float)rand() / (float)RAND_MAX)*2.0f*1000.0f);
		}
	}

	if(m_pRender->GetMode() == MODE_GAME)
	{
		for(int i = 0; i < PATICLE_MAX; i++)
		{
			// ポイントスプライトの位置
			m_post[i].pos =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// ポイントスプライトの初速度とその方向
			m_post[i].vec.x = ((float)rand() / (float)RAND_MAX)*0.50f - 0.25f; 
			m_post[i].vec.y = ((float)rand() / (float)RAND_MAX)*1.00f + 1.00f;
			m_post[i].vec.z = ((float)rand() / (float)RAND_MAX)*0.50f - 0.25f;

			// ポイントスプライトのサイズ
			m_post[i].psize =  ((float)rand() / (float)RAND_MAX)*4.0f + 8.0f; 

			// ポイントスプライトの継続時間
			m_post[i].duration = ((float)rand() / (float)RAND_MAX)*1.0f + 5.0f; 

			//ポイントスプライトの 開始時間
			m_post[i].start_time = time -  (DWORD)(((float)rand() / (float)RAND_MAX)*5000.0f);

		}
	}
	return S_OK;
}
//更新
void CPaticle::Update(void)
{
	
	m_DeleteCnt++;
	

	float t;	
	float alpha;
	DWORD time = timeGetTime();
	MY_VERTEX_1* pv;

	if(m_pRender->GetMode() == MODE_TITLE)
	{
		m_pVBuffer->Lock( 0, 0, (LPVOID*)&pv, 0 );
		for(int i=0; i < PATICLE_MAX; i++)
		{

			// 経過時間を計算
			t = (float(time - m_post[i].start_time ))/1000.0f;

			// 継続時間を越えていたら初期化する
			if(t > m_post[i].duration)
			{
				m_post[i].pos =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				m_post[i].start_time = time;
				m_post[i].duration = ((float)rand() / (float)RAND_MAX)*2.0f + 2.0f; 
				t = 0.0f;
			}
			// ポイントスプライトの位置の計算
			pv[i].p.x = m_post[i].pos.x + m_post[i].vec.x*t + 0.5f * ( 0.0f) * t * t;
			pv[i].p.y = m_post[i].pos.y + m_post[i].vec.y*t + 0.5f * (-9.8f) * t * t;
			pv[i].p.z = m_post[i].pos.z + m_post[i].vec.z*t + 0.5f * ( 0.0f) * t * t;

			// ポイントスプライトのサイズを設定
			pv[i].p_size = m_post[i].psize;
		}
		m_pVBuffer->Unlock();
	}

	if(m_pRender->GetMode() == MODE_GAME)
	{
		m_pVBuffer->Lock( 0, 0, (LPVOID*)&pv, 0 );
		if(m_DeleteCnt < PATICLE_DELETE_CNT)
		{
			for(int i=0; i < PATICLE_MAX; i++)
			{
		
				// 継続時間を計算
				t = (float(time - m_post[i].start_time ))/m_continueTime;
		
				// 継続時間を超えていたら初期化する
				if(t > m_post[i].duration)
				{
					m_post[i].pos =  m_pos;
					m_post[i].start_time = time;
					m_post[i].duration = ((float)rand() / (float)RAND_MAX)*1.0f + 5.0f;
					t = 0.0f;
				}
		
				// ポイントスプライトの位置の計算
				pv[i].p.x = m_post[i].pos.x + m_post[i].vec.x*t + 0.5f * ( 5.0f) * t * t;
				pv[i].p.y = m_post[i].pos.y + m_post[i].vec.y*t + 0.5f * ( 0.0f) * t * t;
				pv[i].p.z = m_post[i].pos.z + m_post[i].vec.z*t + 0.5f * ( 0.0f) * t * t;
			
				// 透明度とサイズの計算
				alpha = 1.0f - t/m_post[i].duration;
				pv[i].color = (DWORD)D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
				pv[i].p_size = m_post[i].psize + t/m_post[i].duration*8.0f;
			}
		}
		if(m_DeleteCnt >= PATICLE_DELETE_CNT)
		{
			m_continueTime = 800.0f;
			for(int i=0; i < PATICLE_MAX; i++)
			{
		
				// 継続時間を計算
				t = (float(time - m_post[i].start_time ))/m_continueTime;
		
				// 継続時間を超えていたら初期化する
				if(t > m_post[i].duration)
				{
					m_post[i].pos =  m_pos;
					m_post[i].start_time = time;
					m_post[i].duration = ((float)rand() / (float)RAND_MAX)*1.0f + 5.0f;
					t = 0.0f;
				}
		
				// ポイントスプライトの位置の計算
				pv[i].p.x = m_post[i].pos.x + m_post[i].vec.x*t + 0.5f * ( 5.0f) * t * t;
				pv[i].p.y = m_post[i].pos.y + m_post[i].vec.y*t + 0.5f * ( 0.0f) * t * t;
				pv[i].p.z = m_post[i].pos.z + m_post[i].vec.z*t + 0.5f * ( 0.0f) * t * t;
			
				// 透明度とサイズの計算
				alpha = 1.0f - t/m_post[i].duration;
				pv[i].color = (DWORD)D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha);
				pv[i].p_size = m_post[i].psize + t/m_post[i].duration*8.0f;
			}
		
		}
		m_pVBuffer->Unlock();
		if(m_DeleteCnt >= PATICLE_DELETE_CNT)
		{
			CPaticle::Uninit();
		}
	}	
}
//開放
void CPaticle::Uninit(void)
{
	SAFE_RELEASE(m_pTexture);		//テクスチャの開放
	SAFE_RELEASE(m_pVBuffer);
	Release();
}
//描画
void CPaticle::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMatrixIdentity(&m_mtxWorld);
///*
	//拡縮
	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//回転
	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//平行移動
	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);
//*/
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	if(m_pRender->GetMode() == MODE_GAME)
	{
	//FOG切る
		m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}
	// 両面描画モードの指定
//	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ライト計算をしない
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// Ｚ比較を行なわない
//	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	// ディザリングを行なう（高品質描画）
	m_pD3DDevice->SetRenderState( D3DRS_DITHERENABLE,   TRUE );
	
	// テクスチャステージの設定 
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	
	// アルファブレンディングを行う
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE);
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	
	// テクスチャフィルターの設定
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	// ポイントスプライトの設定
	m_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE,TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSIZE,Float2DWORD(1.0f));		
	m_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN,Float2DWORD(0.0f));
	
	//ポイントスケールの係数
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A,Float2DWORD(0.0f));
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B,Float2DWORD(0.0f));
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C,Float2DWORD(1.0f));
/*
	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_ALWAYS);
	//それぞれが1頂点のみでスプライトになる
	m_pD3DDevice->SetRenderState( D3DRS_POINTSPRITEENABLE ,TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  TRUE );	
	m_pD3DDevice->SetRenderState( D3DRS_POINTSIZE_MAX, GET_ADDRESS(100.0f));

	m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, TRUE );

	//αブレンド
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, D3DBLENDOP_ADD );	
	m_pD3DDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_ONE );


	//ライティング計算はしない。　深度バッファには書き込まない
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);  
//	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
//*/
	

	//ポイントスプライト用のテクスチャをセット
	m_pD3DDevice->SetTexture(0,m_pTexture);

	// オブジェクトの描画
	m_pD3DDevice->SetStreamSource( 0, m_pVBuffer, 0, sizeof(MY_VERTEX_1) );
	m_pD3DDevice->SetFVF( FVF_VERTEX_MINE );
	m_pD3DDevice->DrawPrimitive( D3DPT_POINTLIST, 0, PATICLE_MAX);
/*
	//頂点の型をセット
	m_pD3DDevice->SetFVF(FVF_VERTEX_PATCLE);
	//レンダリング　今回は2つのポイントスプライトのみ
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, PATICLE_MAX, m_paticle, sizeof(PATICLE));
*/
	//ライト付ける
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	//αブレンド
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, FALSE );

	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	
	//ポイントスプライトの設定
	m_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE,FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE,FALSE);

	// テクスチャフィルターの設定
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
	m_pD3DDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );

	// テクスチャステージの設定 
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	//カリング
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

	m_pD3DDevice->SetRenderState( D3DRS_DITHERENABLE, FALSE );
	//深度バッファに書き込む
	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	//FOG書き込む
	if(m_pRender->GetMode() == MODE_GAME)
	{
		m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}
}

void CPaticle::DrawShade()
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMatrixIdentity(&m_mtxWorld);

	//拡縮
//	D3DXMatrixScaling(&mtxScl,m_scl.x,m_scl.y,m_scl.z);
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxScl);
	//回転
//	D3DXMatrixRotationYawPitchRoll(&mtxRot,m_rot.y,m_rot.x,m_rot.z);
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxRot);
	//平行移動
//	D3DXMatrixTranslation(&mtxTranslate,m_pos.x,m_pos.y,m_pos.z);
//	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld,&mtxTranslate);

	m_pD3DDevice->SetTransform(D3DTS_WORLD,&m_mtxWorld);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_ALWAYS);
	//それぞれが1頂点のみでスプライトになる
	m_pD3DDevice->SetRenderState( D3DRS_POINTSPRITEENABLE ,TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_POINTSCALEENABLE,  TRUE );	
	m_pD3DDevice->SetRenderState( D3DRS_POINTSIZE_MAX, GET_ADDRESS(100.0f));

	m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, TRUE );

	//αブレンド
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, D3DBLENDOP_ADD );	
	m_pD3DDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_ONE );


	//ライティング計算はしない。　深度バッファには書き込まない
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,FALSE);  
//	m_pD3DDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
	//ポイントスプライト用のテクスチャをセット
	m_pD3DDevice->SetTexture(0,m_pTexture);

	//頂点の型をセット
	m_pD3DDevice->SetFVF(FVF_VERTEX_MINE);
	//レンダリング　今回は2つのポイントスプライトのみ
	m_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST, PATICLE_MAX, m_post, sizeof(MY_VERTEX_1));

	//ライト付ける
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING,TRUE);
	//αブレンド
	m_pD3DDevice->SetRenderState ( D3DRS_ALPHATESTENABLE, FALSE );

	m_pD3DDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);

	m_pD3DDevice->SetRenderState( D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

}
//eof