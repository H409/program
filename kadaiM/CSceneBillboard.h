#ifndef __CSCENEBILLBOARD_H__
#define __CSCENEBILLBOARD_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CScene.h"

//�}�N����`
#define ANIM_PTN			(8)
#define ANIM_WAIT			(10)
#define U_POSITION			(1.25f)
#define V_POSITION			(5)
#define EXPROSION_ENDCNT	(80)

//�N���X��`
class CSceneBillboard:public CScene
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// �e�N�X�`�����ǂݍ��ݗp
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// ���_�o�b�t�@
	D3DXVECTOR3				m_pos;					// ���W
	D3DXVECTOR3				m_rot;					// ��]
	D3DXVECTOR3				m_scl;					// �g�k
	D3DXMATRIX				m_mtxWorld;				// ���[���h�}�g���b�N�X
	float					m_fLength;				// ���S���璸�_�܂ł̒���
	float					m_fAngle;				// ���S���璸�_�ւ̊p�x
	bool					m_bFlag;
	float					m_fTexU;
	float					m_fTexUt;
	int						m_nAnimCnt;

	LPDIRECT3DDEVICE9       m_pD3DDevice;			// �f�o�C�X
public:
	//�R���X�g���N�^
	CSceneBillboard(int nPriority = 3):CScene(nPriority){}
	//�f�X�g���N�^
	virtual ~CSceneBillboard(){}

	//������
	HRESULT Init(CRender* pRender);

	HRESULT Init(CRender* pRender,char* ptexfilename,float fangle,float fsize);

	HRESULT	InitAnime(CRender* pRender,char* ptexfilename);
	//�X�V
	void Update();
	void UpdateAnime();
	//�J��
	void Uninit();
	//�`��
	void Draw();
	void DrawShade();
	void DrawAnime();
	//���W�擾
	D3DXVECTOR3 GetPosition(void)
	{
		return m_pos;
	}
	//���W�ݒ�
	void SetPosition(D3DXVECTOR3 pos)
	{
		m_pos = pos;	
	}
	//��]�擾
	D3DXVECTOR3 GetRotate(void)
	{
		return m_rot;
	}
	//��]�ݒ�
	void SetRotate(D3DXVECTOR3 rot)
	{
		m_rot = rot;	
	}
	static CSceneBillboard* Create(CRender* pRender,D3DXVECTOR3 pos,char* xfilename,float fsize);
};


#endif