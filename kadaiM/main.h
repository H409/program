//=============================================================================
//
// プリミティブ表示処理 [main.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_


//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)    // 警告対策用
#include "dinput.h"
#include "debug.h"
#include "xaudio2.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment(lib,"winmm.lib")

//計算速度上昇
#pragma intrinsic(sqrt,pow,sin,cos,tan,asin,acos,atan)


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME		"GM31"				// ウインドウのキャプション名
#define SCREEN_WIDTH	(800)
#define SCREEN_HEIGHT	(600)
#define SAFE_RELEASE(p)	{if(p != NULL){(p)->Release(); (p) = NULL;}}
#define SAFE_DELETE(p)	{if(p != NULL){delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p != NULL){delete [] (p); (p) = NULL;}}
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1 )
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//パーティクル
#define FVF_VERTEX_PATCLE	(D3DFVF_XYZ |  D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define FVF_VERTEX_MINE		(D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE)
//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct 
{
	D3DXVECTOR3 vtx;	//頂点座標
	float rhw;
	D3DCOLOR diffuse;	//反射光
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;
// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 vtx;						// 頂点座標
	D3DXVECTOR3 nor;						// 法線ベクトル
	D3DCOLOR diffuse;						// 反射光
	D3DXVECTOR2 tex;						// テクスチャ座標

} VERTEX_3D;
// 頂点フォーマットの定義
typedef struct _TLVERTEX
{
	float		x,y,z;
	D3DCOLOR	color;
	float		tu,tv;
}TLVERTEX,*LPTLVERTEX;

typedef enum
{
	MODE_TITLE,
	MODE_TUTOLIAL,
	MODE_GAME,
	MODE_RESULT,
//	MODE_GAMEOVER,
//	MODE_RANKING,
	MODE_MAX
}MODE;

//▼stdを使用する
//using namespace std;

//カッコイイ！！　SAFE_RELEASE関数！！ defineマクロなんてもう古い
template <class Interface>	//引数がダブルポインタなので＆をつける
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if(*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease)->Relase();
		(*ppInterfaceToRelease) = nullptr;
	}
}
int GetFPS(void);


/*
//クラス
class List
{
public:
	struct Node
	{
		Node* mNext;
		Node* mPrev;
		double mValue;
	};
	List();
	~List();
	//追加 全て場所を返す
	Node* addBefore( Node* , double value ); //指定場所の前に追加
	Node* addAfter( Node*, double value ); //指定場所の後に追加
	Node* addHead( double value ); //先頭追加
	Node* addTail( double value ); //末尾追加
	//削除
	void remove( Node* ); //指定場所を削除
	void removeHead(); //先頭を削除
	void removeTail(); //末尾を削除
	//取得系
	double value( Node* ) const;
	Node* next( Node* ) const;
	Node* previous( Node* ) const;
	Node* first() const;
	Node* last() const;
private:
	Node mDummyHead;
	Node mDummyTail;
};
//先頭と末尾が特別扱いされないようにちょっと工夫をしている。
List::List(){
	//最初よりさらに前にあるダミー要素
	mDummyHead.mNext = &mDummyTail;
	mDummyHead.mPrev = 0;
	mDummyHead.mValue = 0.0;
	//最後の要素のさらに後にあるダミー要素。
	mDummyTail.mNext = 0;
	mDummyTail.mPrev = &mDummyHead;
	mDummyTail.mValue = 0.0;
}

List::~List(){
	//全部消して回らないといけない
	Node* p = first();
	while ( p )
	{
		Node* nxt = next( p );
		delete p;
		p = nxt;
	}
}

List::Node* List::addAfter( Node* cur, double v )
{
	Node* e = new Node();
	//次の奴を取り出す
	Node* nxt = cur->mNext;
	//値格納
	e->mValue = v;
	e->mPrev = cur; //指定場所が前に
	e->mNext = nxt; //指定の次のが次に
	//指定の奴は前になるので、次は足した奴になる
	cur->mNext = e;
	//指定の次の奴は後になるので、前は足した奴になる
	nxt->mPrev = e;

	return e;
}

List::Node* List::addBefore( Node* cur, double v )
{
	Node* e = new Node();
	//前の奴を取り出す
	Node* prev = cur->mPrev;
	//値格納
	e->mValue = v;
	e->mPrev = prev; //指定の前の奴が前
	e->mNext = cur; //指定の奴が次
	//指定の奴は後になるので、前は足した奴になる
	cur->mPrev = e;
	//指定の前の奴は前になるので、後は足した奴になる
	prev->mNext = e;

	return e;
}

List::Node* List::addHead( double v )
{
	return addBefore( first(), v ); //ダミー要素のおかげでこう書ける。
}

List::Node* List::addTail( double v )
{
	return addAfter( last(), v ); //ダミー要素のおかげでこう書ける
}

void List::remove( Node* cur )
{
	//次
	Node* nxt = cur->mNext;
	//前
	Node* prev = cur->mPrev;
	//前の奴の次を、次にする。
	prev->mNext = nxt;
	//次の奴の前を、前にする。
	nxt->mPrev = prev;
	//消す
	delete cur;
	cur = 0;
}

void List::removeHead()
{ //これはほとんど別名。
	remove( first() );
}

void List::removeTail()
{ //これはほとんど別名。
	remove( last() );
}

double List::value( Node* p ) const 
{
	return p->mValue;
}

List::Node* List::next( Node* p ) const 
{
	Node* r = p->mNext;
	if ( r == &mDummyHead || r == &mDummyTail )
	{
		return 0;
	}
	else
	{
		return r;
	}
}

List::Node* List::previous( Node* p ) const 
{
	Node* r = p->mPrev;
	if ( r == &mDummyHead || r == &mDummyTail )
	{
		return 0;
	}
	else
	{
		return r;
	}
}

List::Node* List::first() const 
{
	return mDummyHead.mNext; //ダミー先頭の次が本当の先頭
}

List::Node* List::last() const 
{
	return mDummyTail.mPrev; //ダミー末尾の前が本当の末尾
}
*/
#endif