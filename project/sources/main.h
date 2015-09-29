//*****************************************************************************
//
// main
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

/******************************************************************************
// ヘッダファイルの例

//*****************************************************************************
//
// main
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#prama once
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "main.h"

//*****************************************************************************
// library link
//*****************************************************************************
#pragma comment(lib,"main.lib")

//*****************************************************************************
// macro definition
//*****************************************************************************
#define MAIN

//*****************************************************************************
// constant definition
//*****************************************************************************
const u32 MAIN = 0;

//*****************************************************************************
// forward declaration
//*****************************************************************************
class Main;

//*****************************************************************************
// class definition
//*****************************************************************************
class Main : public Basic
{
public:
	// constructor
	Main(void);

	// destructor
	virtual ~Main(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	const u32& main(void)const{return main_;}
	void main(const u32& in_main){main_ = in_main;}
protected:

private:
	u32 main_;
};

#endif // _MAIN_H_

//---------------------------------- EOF --------------------------------------

******************************************************************************/

/******************************************************************************
// 命名規則

//---------------------------------------------------------
// 変数名

全て小文字にする
単語の繋がりは_で区切る
クラスのメンバー変数には最後に_を付ける
構造体のメンバー変数には最初に_を付ける

//---------------------------------------------------------
// 定数名

全て大文字にする
単語の繋がりは_で区切る

//---------------------------------------------------------
// 関数名

先頭と単語の繋がりは大文字にする
他は全て小文字にする
ただし、アクセサに関しては最初に__を付けメンバ変数と同名にし最後の_を取る

//---------------------------------------------------------
// 引数名

基本的に変数名と同じ
ただし、データを返す場合はout_を付け、受け取る場合はin_を付ける

//---------------------------------------------------------
// クラス名

先頭と単語の繋がりは大文字にする
他は全て小文字にする

//---------------------------------------------------------
// 構造体名

全て大文字にする
単語の繋がりは_で区切る

//---------------------------------------------------------
// 列挙名

全て大文字にする
単語の繋がりは_で区切る

******************************************************************************/

//---------------------------------- EOF --------------------------------------
