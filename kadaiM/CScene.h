//���d��`�h�~
#ifndef __CSCENE_H__
#define __CSCENE_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CInputKeyboard.h"

//�}�N����`
#define PRIORITY_MAX	(8)

//�O���錾
class CRender;

//���
typedef enum
{
	OBJTYPE_NONE = 0,
	OBJTYPE_2D,
	OBJTYPE_3D,
	OBJTYPE_X,
	OBJTYPE_BILLBOARD,
	OBJTYPE_GIMMICK,
	OBJTYPE_FADE,
	OBJTYPE_PAUSE,
	OBJTYPE_2DGIM,
	OBJTYPE_MAX
}OBJTYPE;

//�N���X��`
class CScene
{

private:
	
	static CScene*		m_pTop[PRIORITY_MAX];	//���X�g�̐擪�A�h���X
	static CScene*		m_pCur[PRIORITY_MAX];	//���X�g�̌��݈ʒu�A�h���X
	CScene*				m_pNext;				//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene*				m_pPrev;				//���̃I�u�W�F�N�g�ւ̃|�C���^

	CScene*				m_DummyHead;			//�_�~�[�w�b�h
	CScene*				m_DummyTail;			//�_�~�[�e�C��
	const int			m_nPriority;			//�v���C�I���e�B
	bool				m_bDeath;				//�I�u�W�F�N�g�폜�t���O
	OBJTYPE				m_objType;				//�I�u�W�F���
public:

	//�R���X�g���N�^
	CScene(int nPriority = 3,OBJTYPE objtype = OBJTYPE_NONE);
	//�f�X�g���N�^
	virtual ~CScene();
	//������
	virtual HRESULT Init(CRender* pRender) = 0;
	//�X�V
	virtual void Update() = 0;
	//�J��
	virtual void Uninit() = 0;
	//�`��
	virtual void Draw() = 0;
	virtual void DrawShade() = 0;
	//���W�擾
	virtual D3DXVECTOR3 GetPosition(void) = 0;

	//���W�ݒ�
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;
		
	virtual D3DXVECTOR3 GetRotate(void) = 0;
	
	//��]�ݒ�
	virtual void SetRotate(D3DXVECTOR3 rot) = 0;
	
	//�Â����W�擾�E�ݒ�
	virtual void SetPositionOld(D3DXVECTOR3 pos){}
	virtual D3DXVECTOR3 GetPositionOld(void){return D3DXVECTOR3(0.0f,0.0f,0.0f);}
	//�Â��p�x�擾�E�ݒ�
	virtual void SetRotationOld(D3DXVECTOR3 rot){}
	virtual D3DXVECTOR3 GetRotationOld(void){return D3DXVECTOR3(0,0,0);}
	//���_�ʒu�擾
	virtual D3DXVECTOR3 GetVertexMin(void){return D3DXVECTOR3(0,0,0);}
	virtual D3DXVECTOR3 GetVertexMax(void){return D3DXVECTOR3(0,0,0);}

	//OBJ��ގ擾
	OBJTYPE GetObjType(void){return m_objType;}
	CScene* GetTypePointer(OBJTYPE objtype);
	//�����X�g�n
	void Release(void);
	void LinkList(void);
	void UnlinkList(CScene* pScene);
	static void DrawAll(void);
	static void DrawShadeAll(void);
	static void UpdateAll(void);
	static void ReleaseAll(void);
	static void UpdateFade(void);
	static void DrawFade(void);
	static void FreePhase(void);
	CScene* GetNext(void)
	{
		return m_pNext;
	}
	static CScene* GetTopNode(int nIndex)
	{
		return m_pTop[nIndex];
	}
};
#endif