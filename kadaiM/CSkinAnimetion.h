//=============================================================================
//
// スキンアニメーションの処理 [CSkinAnimetion.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
//多重定義防止
#ifndef __CSKINANIMETION_H__
#define __CSKINANIMETION_H__

//ヘッダーインクルード
#include "main.h"
#include "CScene.h"


//前方宣言
class CRender;
class CSceneX;

typedef struct THING
{	
	LPD3DXMESH pMesh;
	LPD3DXFRAME pFrameRoot;
	LPD3DXANIMATIONCONTROLLER pAnimController;
	D3DMATERIAL9* pMeshMaterials;
	LPDIRECT3DTEXTURE9* pMeshTextures; 
	DWORD dwNumMaterials;
	D3DXVECTOR3 vecPosition;
	D3DXMATRIX matRotation;
	D3DXMATRIX matWorld;

	THING()
	{
		ZeroMemory(this,sizeof(THING));
	}
}THING;


//派生フレーム構造体 (それぞれのメッシュ用の最終ワールド行列を追加する）
struct MYFRAME: public D3DXFRAME
{
    D3DXMATRIX CombinedTransformationMatrix;
};
//派生メッシュコンテナー構造体(
//コンテナーがテクスチャを複数持てるようにポインターのポインターを追加する）
struct MYMESHCONTAINER: public D3DXMESHCONTAINER
{
    LPDIRECT3DTEXTURE9*  ppTextures;
    DWORD dwWeight;//重みの個数（重みとは頂点への影響。）
	DWORD dwBoneAmt;//ボーンの数
    LPD3DXBUFFER pBoneBuffer;//ボーン・テーブル
    D3DXMATRIX** ppBoneMatrix;//全てのボーンのワールド行列の先頭ポインター
    D3DXMATRIX* pBoneOffsetMatrices;//フレームとしてのボーンのワールド行列のポインター
};
//Xファイル内のアニメーション階層を読み下してくれるクラスを派生させる。
//ID3DXAllocateHierarchyは派生すること想定して設計されている。
class MY_HIERARCHY: public ID3DXAllocateHierarchy
{
public:
	MY_HIERARCHY(){}
    STDMETHOD(CreateFrame)(THIS_ LPCSTR , LPD3DXFRAME *);
    STDMETHOD(CreateMeshContainer)(THIS_ LPCTSTR ,CONST D3DXMESHDATA* ,CONST D3DXMATERIAL* , 
		CONST D3DXEFFECTINSTANCE* , DWORD , CONST DWORD *, LPD3DXSKININFO , LPD3DXMESHCONTAINER *);
    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME );
    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER );	
};
//
//
//
class SKIN_MESH
{
public:
	HRESULT InitThing(LPDIRECT3DDEVICE9,THING *,LPSTR,D3DXVECTOR3*);
	HRESULT AllocateBoneMatrix( THING* , LPD3DXMESHCONTAINER  );
	HRESULT AllocateAllBoneMatrices(THING* ,  LPD3DXFRAME  );
	VOID RenderMeshContainer(LPDIRECT3DDEVICE9, MYMESHCONTAINER* ,MYFRAME* );
	VOID UpdateFrameMatrices(LPD3DXFRAME , LPD3DXMATRIX );
	VOID DrawFrame(LPDIRECT3DDEVICE9,LPD3DXFRAME );

	MY_HIERARCHY GetHierarchy(void)
	{
		return cHierarchy;
	}
protected:
	MY_HIERARCHY cHierarchy;

};


#endif