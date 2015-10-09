//=============================================================================
// シェーダー作成処理 [shader.h]
// Author : MASAHIRO YAMAGUCHI
// シェーダー初期化等
//=============================================================================
//ヘッダーインクルード
#include "CShader.h"
#include <tchar.h>
#include "CRender.h"
//シェーダ関連

//▼シェーダクラス
//作成
bool CShader::Create2D(LPCSTR path)
{
	//エラーチェック
	if(m_pEffect != NULL)
	{
		Release();
	}
	
	try
	{
		HRESULT hr;
		D3DCAPS9 caps;
		m_pD3DDevice->GetDeviceCaps(&caps);
		
		//頂点シェーダ、ピクセルシェーダが使用できるか調べる
		if((caps.VertexShaderVersion < D3DVS_VERSION(2,0)) || 
			(caps.PixelShaderVersion < D3DPS_VERSION(2,0)))
		{
			::MessageBox(NULL,_T("ご利用のグラフィックスボードはプログラマブルシェーダに対応しておりません。"),_T(""),MB_OK);
			throw 0;
		}

		//ファイルの読み込み
		LPD3DXBUFFER pErrMessage = NULL;
		hr = D3DXCreateEffectFromFile(m_pD3DDevice,path,
					NULL,NULL,0,NULL,&m_pEffect,&pErrMessage);
		if(FAILED(hr))
		{
			//エラーメッセージの文字コードはANSI
			::MessageBoxA(NULL,(LPCSTR)(pErrMessage->GetBufferPointer()),"",MB_OK);
			pErrMessage->Release();
			throw 0;
		}

		//パイプラインに渡す頂点データ構造を定義
		//2D
		//=============================================
		//1番左側はパイプライン番号
		//2番目はOFFSETの値(size分ずれる)
		//3番目は頂点要素の型
		//4番目はDEFAULTこれ(D3DDECLMETHOD_DEFAULT)
		//5番目は用途
		//6番目は用途番号
		//=============================================
		D3DVERTEXELEMENT9 decl[] = 
		{
			{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },	//位置
			{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},	//色
			{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},	//テクスチャ座標
			D3DDECL_END() //最後に必ずD3DDECL_END()をつける
		};
		hr = m_pD3DDevice->CreateVertexDeclaration(decl,&m_pVertexDeclaration);
		if(FAILED(hr))
		{
			throw 0;
		}
		
		//シェーダへ頂点定義をセット
		m_pD3DDevice->SetVertexDeclaration(m_pVertexDeclaration);

		//シェーダが使用するテクニック（シェーダプログラムの組み合わせみたいな物）を指定
		m_pEffect->SetTechnique(m_TecnuiqueName);

		//シェーダプログラムのグローバル変数ハンドルを取得
		m_WorldViewProjection = m_pEffect->GetParameterByName( NULL, m_WVPtxName );
		m_Texture = m_pEffect->GetParameterByName( NULL, m_TexName);
	}
	catch(...)
	{	
		Release();
		return false;
	}
	return true;
}
//3D
bool CShader::Create3D(LPCSTR path)
{
	//エラーチェック
	if(m_pEffect != NULL)
	{
		Release();
	}
	
	try
	{
		HRESULT hr;
		D3DCAPS9 caps;
		m_pD3DDevice->GetDeviceCaps(&caps);
		
		//頂点シェーダ、ピクセルシェーダが使用できるか調べる
		if((caps.VertexShaderVersion < D3DVS_VERSION(2,0)) || 
			(caps.PixelShaderVersion < D3DPS_VERSION(2,0)))
		{
			::MessageBox(NULL,_T("ご利用のグラフィックスボードはプログラマブルシェーダに対応しておりません。"),_T(""),MB_OK);
			throw 0;
		}

		//ファイルの読み込み
		LPD3DXBUFFER pErrMessage = NULL;
		hr = D3DXCreateEffectFromFile(m_pD3DDevice,path,
					NULL,NULL,0,NULL,&m_pEffect,&pErrMessage);
		if(FAILED(hr))
		{
			//エラーメッセージの文字コードはANSI
			::MessageBoxA(NULL,(LPCSTR)(pErrMessage->GetBufferPointer()),"",MB_OK);
			pErrMessage->Release();
			throw 0;
		}

		//パイプラインに渡す頂点データ構造を定義
		//3D
		//=============================================
		//1番左側はパイプライン番号
		//2番目はOFFSETの値(size分ずれる)
		//3番目は頂点要素の型
		//4番目はDEFAULTこれ(D3DDECLMETHOD_DEFAULT)
		//5番目は用途
		//6番目は用途番号
		//=============================================

		D3DVERTEXELEMENT9 decl[ ] =   
		{
			{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
			{0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},
			{0,24,D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},
			{0,28,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
			D3DDECL_END()
		};
		hr = m_pD3DDevice->CreateVertexDeclaration(decl,&m_pVertexDeclaration);
		if(FAILED(hr))
		{
			throw 0;
		}
		//頂点データ設定
		m_pD3DDevice->SetVertexDeclaration(m_pVertexDeclaration);

		//シェーダが使用するテクニック（シェーダプログラムの組み合わせみたいな物）を指定
		m_pEffect->SetTechnique(m_TecnuiqueName);

		//シェーダプログラムのグローバル変数ハンドルを取得
		m_WorldViewProjection = m_pEffect->GetParameterByName( NULL, m_WVPtxName );
		m_Texture = m_pEffect->GetParameterByName( NULL, m_TexName);
	}
	catch(...)
	{	
		Release();
		return false;
	}
	return true;
}
//パス変更
void CShader::ChangePass(UINT pass)
{
	m_pass = pass;
}

//シェーダプログラム使用開始を宣言
//BeginとEndの間にポリゴンを描画する
void CShader::Begin()
{
	//エフェクト開始
	m_pEffect->Begin(NULL,0);

	//使用するパス選択
	m_pEffect->BeginPass(m_pass);
}
void CShader::End()
{
	//パス終了
	m_pEffect->EndPass();
	//エフェクト終了
	m_pEffect->End();
}
//シェーダ適用
void CShader::SetData(D3DXMATRIX *mat, LPDIRECT3DTEXTURE9 texture)
{
	//シェーダのグローバル変数へデータセット
	m_pEffect->SetMatrix(m_WorldViewProjection,mat);
	m_pEffect->SetTexture(m_Texture,texture);
	
	//名前で直接セットすることも可能
//	m_pEffect->SetMatrix("g_mWorldViewProjection", mat );
//	m_pEffect->SetTexture( "g_Texture", texture );
}

//シェーダ解放
void CShader::Release()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pVertexDeclaration);

	m_WorldViewProjection = NULL;
	m_Texture = NULL;
	m_pass = 0;
}
//テクニック名
void CShader::SetTecnuiqueName(char* pname)
{
	m_TecnuiqueName = pname;
}
//テクスチャ名
void CShader::SetTextureName(char* pname)
{
	m_TexName = pname;
}
//マトリックス名
void CShader::SetMatrixName(char* pname)
{
	m_WVPtxName	 = pname;
}
//デバイス取得
void CShader::GetDevice(CRender* pRender)
{
	m_pD3DDevice = pRender->getDevice();
}