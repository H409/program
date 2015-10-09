//=============================================================================
// シェーダー作成処理 [shader.h]
// Author : MASAHIRO YAMAGUCHI
// シェーダー初期化等
//=============================================================================
//多重定義
#ifndef __CSHADER_H__
#define __CSHADER_H__

//ヘッダーインクルード
#include "main.h"

//前方宣言
class CRender;

//シェーダークラス
class CShader
{
private:
	LPD3DXEFFECT m_pEffect;
	LPDIRECT3DVERTEXDECLARATION9 m_pVertexDeclaration;
	LPDIRECT3DDEVICE9			m_pD3DDevice;			// デバイス

	//シェーダのグローバル変数ハンドル
	D3DXHANDLE	m_WorldViewProjection;	//座標変換行列
	D3DXHANDLE	m_Texture;				//テクスチャ
	
	UINT		m_pass;					//パスインデックス
	char*		m_TecnuiqueName;		//テクニック名
	char*		m_WVPtxName;			//行列名
	char*		m_TexName;				//テクスチャ名

	
public:
	
	//コンストラクタ
	CShader()
	:	m_pEffect(NULL),
	m_pVertexDeclaration(NULL),
	m_WorldViewProjection(NULL),
	m_Texture(NULL),
	m_pass(0)
	{

	}

	//デストラクタ
	virtual ~CShader()
	{
		Release();
	}
	//シェーダ作成（シェーダプログラムファイル読み込み）
	bool Create2D(LPCSTR path);
	bool Create3D(LPCSTR path); 
	//パスインデックスをセット（シェーダプログラムの組み合わせを切り替える）
	void ChangePass(UINT pass);
	//頂点データを取得
	const LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration()const
	{
		return m_pVertexDeclaration;
	}
	//シェーダ適用
	void Begin();
	//シェーダのグローバル変数に値をセット
	void SetData(D3DXMATRIX* mat,LPDIRECT3DTEXTURE9 texture);
	//テクニック名設定
	void SetTecnuiqueName(char* pname);
	//行列名
	void SetMatrixName(char* pname);
	//テクスチャ名
	void SetTextureName(char* pname);
	//シェーダ終了
	void End();
	//取得
	LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration(void)
	{
		return m_pVertexDeclaration;
	}
	void GetDevice(CRender* pRender);

	//解放
	void Release();
};


#endif

//eof