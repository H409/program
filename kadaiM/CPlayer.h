//���d��`�h�~
#ifndef __CPLAYER_H__
#define __CPLAYER_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CSceneX.h"

#define PLAYER_LIFE	(3)

//�O���錾
class CRender;
class AnimationLinear;
class CScene2D;

//�N���X��`
class CPlayer:public CSceneX
{
private:
	D3DXVECTOR3				m_vecDir;
	static CSceneX*			m_pSceneXDummy;
	CRender*				m_pRender;
	D3DXVECTOR3				m_vecMove;	//�ړ�
	float					m_fangleModel;
	D3DXVECTOR3				m_rotDest;	//�p�x
	D3DXVECTOR3				m_vtxMin;
	D3DXVECTOR3				m_vtxMax;
	D3DXVECTOR3				m_posOld;
	D3DXVECTOR3				m_rotOld;
	bool					m_notGravity;
	CScene*					m_pSceneLink;
	AnimationLinear*		m_pAnim;
	// �N�I�[�^�j�I��
	D3DXQUATERNION m_q1; // ���f���̍ŏ��̎p��
	D3DXQUATERNION m_q2; // ���f���̍Ō�̎p��
	D3DXQUATERNION m_q3; // ���f���̍Ō�̎p��
	D3DXMATRIX				m_rotmat;
	char					m_lifeCnt;
	static CScene2D*		m_pScene2D[PLAYER_LIFE];

public:
	CPlayer(int nPriority = 3):CSceneX(3)
	{
		m_notGravity = true;
		m_pSceneLink = NULL;
	}
	virtual ~CPlayer()
	{

	}
	static CPlayer* Create(CRender* pRender,D3DXVECTOR3 pos);
	HRESULT Init(CRender* pRender);
	void Update();
	void Uninit();
	void Draw();

	CScene* GetSceneLink(void){return m_pSceneLink;}

	//�Â����W�擾�E�ݒ�
	void SetPositionOld(D3DXVECTOR3 pos){m_posOld = pos;}
	D3DXVECTOR3 GetPositionOld(void){return m_posOld;}
	//�Â��p�x�擾�E�ݒ�
	void SetRotationOld(D3DXVECTOR3 rot){m_rotOld = rot;}
	D3DXVECTOR3 GetRotationOld(void){return m_rotOld;}
	//���_�ʒu�擾
	D3DXVECTOR3 GetVertexMin(void){return m_vtxMin;}
	D3DXVECTOR3 GetVertexMax(void){return m_vtxMax;}

	char GetLifeCnt(void)
	{
		return m_lifeCnt;
	}
	void SetLifeCnt(char lifecnt)
	{
		m_lifeCnt = lifecnt;
	}


};

class CPlayerLife:public CScene
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// �e�N�X�`�����ǂݍ��ݗp
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// ���_�o�b�t�@
	D3DXVECTOR3				m_pos;					// ���W
	D3DXVECTOR3				m_rot;					// ��]
	float					m_fLength;				// ���S���璸�_�܂ł̒���
	float					m_fAngle;				// ���S���璸�_�ւ̊p�x
	D3DXVECTOR2				m_Tex;					// �e�N�X�`�����W
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	int						m_Num;
	bool					m_DrawFlag;
public:
	CPlayerLife(){}
	virtual ~CPlayerLife(){}

	//������
	HRESULT Init(CRender* pRender);
	//�X�V
	void Update();
	//�J��
	void Uninit();
	//�`��
	void Draw();
	void DrawShade();

	bool GetDrawFlag(void)
	{
		return m_DrawFlag;
	}
	void SetDrwaFlag(bool flag)
	{
		m_DrawFlag = flag;
	}
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

	//����
	static CPlayerLife* Create(CRender* pRender,const D3DXVECTOR3 pos);
};

D3DXVECTOR3 GetVelocity(void);
D3DXVECTOR3 GetPos(void);
D3DXVECTOR3 GetRot(void);
#endif