//ヘッダーインクルード
#include "CDebugProc.h"
#include <stdio.h>
#include <sstream>
//警告制限無視
#pragma warning(disable:4996)

//静的メンバ変数の初期化
LPD3DXFONT CDebugProc::m_pD3DXFont = NULL;
char	   CDebugProc::m_aStr[LENGTH_STRING_BUFF] = {0};
bool	   CDebugProc::m_bDisp = true;
RECT	   CDebugProc::m_rect = {0,0,0,0};
//初期化
void CDebugProc::Init(CRender* pRender)
{

	//フォントの初期化
	D3DXCreateFont(pRender->getDevice(), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "ＭＳ Ｐゴシック", &m_pD3DXFont);
	//バッファのクリア
	memset(m_aStr,0,sizeof(char)*LENGTH_STRING_BUFF);
	
	m_rect.bottom = 0;
	m_rect.left = 0;
	m_rect.right = 0;
	m_rect.top = 0;
}
//開放
void CDebugProc::Uninit(void)
{
	SAFE_RELEASE(m_pD3DXFont);
}

//描画
void CDebugProc::Draw(void)
{
	//文字列のサイズを計算
	m_pD3DXFont->DrawText(NULL,m_aStr,-1,&m_rect,DT_CALCRECT,NULL);
	// テキスト描画
	m_pD3DXFont->DrawText(NULL, m_aStr, -1, &m_rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	//バッファのクリア
	memset(m_aStr,0,sizeof(char)*1024);
}
//デバッグ表示の登録
void CDebugProc::Print(const char *fmt,...)
{
#ifdef _DEBUG
	char str[256];
	va_list lpValist = NULL;	//可変長引数リストアクセス用
	
	m_rect.left = 0;
	m_rect.top = 20;
	m_rect.bottom = 0;
	m_rect.right = 0;

	//エラーチェック
	if(!fmt)return;

	//可変長引数リストへのアクセスを開始する
	//第1引数はva_list型変数を指定する
	//第2引数は最後の固定引数を指定
	va_start(lpValist,fmt);

	//可変長引数リストから値を取得し、表示する文字列として配列に格納する
	vsprintf(str,fmt,lpValist);

	//可変長引数リストを解放する
	va_end(lpValist);
	//連結
	strcat(m_aStr,str);
#endif
}
bool CDebugProc::IsEnableDisp(void)
{
	return m_bDisp;
}
void CDebugProc::EnableDisp(bool bDisp)
{

	m_bDisp = bDisp;
}