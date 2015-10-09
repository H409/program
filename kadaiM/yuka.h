//=============================================================================
//
// �v���~�e�B�u�\������ [yuka.h]
// Author : MASAHIRO YAMAGUCHI
//
//=============================================================================
#ifndef __YUKA_H__
#define __YUKA_H__

//�w�b�_�[�C���N���[�h
#include "main.h"
#include "CSceneX.h"


//�O���錾
class CRender;

//�N���X��`
class CYuka:public CSceneX
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
	bool					m_initManager;

public:
	CYuka(int nPriority = 3):CSceneX(3,OBJTYPE_GIMMICK)
	{
		m_vtxMin = D3DXVECTOR3(0,0,0);
		m_vtxMax = D3DXVECTOR3(0,0,0);
	}
	virtual ~CYuka()
	{

	}
	static CYuka* Create(CRender* pRender,D3DXVECTOR3 pos);
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos);
	void Update();
	void Uninit();
	void Draw();

	//�Â����W�擾�E�ݒ�
	void SetPositionOld(D3DXVECTOR3 pos){m_posOld = pos;}
	D3DXVECTOR3 GetPositionOld(void){return m_posOld;}
	//�Â��p�x�擾�E�ݒ�
	void SetRotationOld(D3DXVECTOR3 rot){m_rotOld = rot;}
	D3DXVECTOR3 GetRotationOld(void){return m_rotOld;}
	//���_�ʒu�擾
	D3DXVECTOR3 GetVertexMin(void){return m_vtxMin;}
	D3DXVECTOR3 GetVertexMax(void){return m_vtxMax;}

};
#endif