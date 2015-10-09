//ヘッダーインクルード
#include "CScene.h"
#include "CDebugProc.h"

//静的メンバ変数の初期化
CScene* CScene::m_pTop[PRIORITY_MAX] = {NULL};
CScene* CScene::m_pCur[PRIORITY_MAX] = {NULL};


//引数付き
CScene::CScene(int nPriority,OBJTYPE objtype)
: m_nPriority(nPriority),m_objType(objtype)
{
	m_bDeath = false;
	LinkList();
}
//デストラクタ
CScene::~CScene()
{

}
//リンクリストリストへ追加
void CScene::LinkList(void)
{
	
	if(m_pTop[m_nPriority] == NULL)
	{
		m_pTop[m_nPriority] = this;
		m_pCur[m_nPriority] = this;
		this->m_pPrev = NULL;
		this->m_pNext = NULL;
	}
	else
	{
		this->m_pPrev = m_pCur[m_nPriority];
		m_pCur[m_nPriority]->m_pNext = this;
		this->m_pNext = NULL;
		m_pCur[m_nPriority] = this;
	}
	
	/*
	this->m_pPrev = m_pCur[m_nPriority];
	this->m_pNext = NULL;
	m_pCur[m_nPriority] = this;

	//先頭に追加
	if(m_pTop[m_nPriority] == NULL)
	{
		m_pTop[m_nPriority] = this;
		
		//先頭
		m_pTop[m_nPriority]->m_pPrev = NULL;
//		m_pTop->m_pNext = this->m_pNext;
		
		//終端
//		m_pCur->m_pNext = NULL;
		
	}
	else
	{
		m_pCur[m_nPriority]->m_pPrev->m_pNext = this;
	}
	*/
}
//リストから削除
void CScene::UnlinkList(CScene* pScene)
{
	
	
	if(pScene == m_pTop[m_nPriority])
	{
		if(pScene == m_pCur[m_nPriority])
		{
			m_pTop[m_nPriority] = NULL;
			m_pCur[m_nPriority] = NULL;
			m_pNext = NULL;
			m_pPrev = NULL;
		}
		else
		{
			m_pTop[m_nPriority] = pScene->m_pNext;
			m_pTop[m_nPriority]->m_pPrev = NULL;
		}
	}
	else if(pScene == m_pCur[m_nPriority])
	{
		pScene->m_pPrev->m_pNext = NULL;
		m_pCur[m_nPriority] = pScene->m_pPrev;
	}
	else
	{
		
		//前の奴の次を、次にする。
		pScene->m_pPrev->m_pNext = pScene->m_pNext;
		//次の奴の前を、前にする。
		pScene->m_pNext->m_pPrev = pScene->m_pPrev;
	}
	
}
//削除
void CScene::Release()
{
//	UnlinkList();
	this->m_bDeath = true;
//	delete this;
}

//全更新
void CScene::UpdateAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULLじゃなければ処理
		{
			pNext = pScene->m_pNext;
			
			if(pScene->m_bDeath)
			{
				pScene->Uninit();
				pScene->UnlinkList(pScene);
				SAFE_DELETE(pScene);

			}
			else
			{
				pScene->Update();		
			}
			pScene = pNext;
			
		}
	}
}
//全開放
void CScene::ReleaseAll(void)
{

	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULLじゃなければ処理
		{
			pScene->Uninit();
			pNext = pScene->m_pNext;
			SAFE_DELETE(pScene);
			pScene = pNext;
		}
	}
}
//全描画
void CScene::DrawAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULLじゃなければ処理
		{
			pNext = pScene->m_pNext;
			pScene->Draw();
			pScene = pNext;

		}
	}
	
}
void CScene::DrawShadeAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULLじゃなければ処理
		{
			pNext = pScene->m_pNext;
			pScene->DrawShade();
			pScene = pNext;

		}
	}
	
}

//ポインタ取得
CScene* CScene::GetTypePointer(OBJTYPE objtype)
{
	CScene* pRet = NULL;
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;
		

		while(pScene != NULL)	//NULLじゃなければ処理
		{
			pNext = pScene->m_pNext;
			
			if(pScene->m_objType == objtype)
			{
				return pScene;
			}
			pScene = pNext;

		}
	}
	return pRet;
}
//解放
void CScene::FreePhase(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULLじゃなければ処理
		{
			pScene->Release();
			pNext = pScene->m_pNext;
			
			if(pScene->m_bDeath)
			{
				pScene->Uninit();
				pScene->UnlinkList(pScene);
				SAFE_DELETE(pScene);
			}
			if(pNext != NULL)
			{
				
				pScene = pNext;
			}
		}
	}
}
//フェード更新
void CScene::UpdateFade(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULLじゃなければ処理
		{
			pNext = pScene->m_pNext;
			if(pScene->GetObjType() == OBJTYPE_FADE)
			{
				
				pScene->Update();
				
			}			
			pScene = pNext;
		}
	}
}
//フェード描画
void CScene::DrawFade(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULLじゃなければ処理
		{
			pNext = pScene->m_pNext;
			if(pScene->GetObjType() == OBJTYPE_FADE)
			{
				
				pScene->Draw();
				
			}
			pScene = pNext;
		}
	}
}
//eof