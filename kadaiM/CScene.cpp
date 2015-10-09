//�w�b�_�[�C���N���[�h
#include "CScene.h"
#include "CDebugProc.h"

//�ÓI�����o�ϐ��̏�����
CScene* CScene::m_pTop[PRIORITY_MAX] = {NULL};
CScene* CScene::m_pCur[PRIORITY_MAX] = {NULL};


//�����t��
CScene::CScene(int nPriority,OBJTYPE objtype)
: m_nPriority(nPriority),m_objType(objtype)
{
	m_bDeath = false;
	LinkList();
}
//�f�X�g���N�^
CScene::~CScene()
{

}
//�����N���X�g���X�g�֒ǉ�
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

	//�擪�ɒǉ�
	if(m_pTop[m_nPriority] == NULL)
	{
		m_pTop[m_nPriority] = this;
		
		//�擪
		m_pTop[m_nPriority]->m_pPrev = NULL;
//		m_pTop->m_pNext = this->m_pNext;
		
		//�I�[
//		m_pCur->m_pNext = NULL;
		
	}
	else
	{
		m_pCur[m_nPriority]->m_pPrev->m_pNext = this;
	}
	*/
}
//���X�g����폜
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
		
		//�O�̓z�̎����A���ɂ���B
		pScene->m_pPrev->m_pNext = pScene->m_pNext;
		//���̓z�̑O���A�O�ɂ���B
		pScene->m_pNext->m_pPrev = pScene->m_pPrev;
	}
	
}
//�폜
void CScene::Release()
{
//	UnlinkList();
	this->m_bDeath = true;
//	delete this;
}

//�S�X�V
void CScene::UpdateAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
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
//�S�J��
void CScene::ReleaseAll(void)
{

	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
		{
			pScene->Uninit();
			pNext = pScene->m_pNext;
			SAFE_DELETE(pScene);
			pScene = pNext;
		}
	}
}
//�S�`��
void CScene::DrawAll(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
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

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
		{
			pNext = pScene->m_pNext;
			pScene->DrawShade();
			pScene = pNext;

		}
	}
	
}

//�|�C���^�擾
CScene* CScene::GetTypePointer(OBJTYPE objtype)
{
	CScene* pRet = NULL;
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;
		

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
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
//���
void CScene::FreePhase(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
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
//�t�F�[�h�X�V
void CScene::UpdateFade(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
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
//�t�F�[�h�`��
void CScene::DrawFade(void)
{
	for(int i = 0;i < PRIORITY_MAX;i++)
	{
		CScene* pScene = m_pTop[i];
		CScene* pNext = NULL;

		while(pScene != NULL)	//NULL����Ȃ���Ώ���
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