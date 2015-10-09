//多重定義防止
#ifndef __DEBUG_H__
#define __DEBUG_H__

//メモリリークチェック
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


//メモリリーク場所チェック
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW	new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define new DBG_NEW
#endif
#endif	//＿DEBUG

#endif