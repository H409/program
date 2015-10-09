#ifndef __CSCENE2D_H__
#define __CSCENE2D_H__

#include "main.h"
#include "CScene.h"

//�O���錾
class CRender;

//�N���X��`
class CScene2D:public CScene
{
private:
	LPDIRECT3DTEXTURE9		m_pD3DTex;				// �e�N�X�`�����ǂݍ��ݗp
	LPDIRECT3DVERTEXBUFFER9	m_pD3DVtxBuffer;		// ���_�o�b�t�@
	D3DXVECTOR3				m_pos;					// ���W
	D3DXVECTOR3				m_rot;					// ��]
	float					m_fLength;				// ���S���璸�_�܂ł̒���
	float					m_fAngle;				// ���S���璸�_�ւ̊p�x
	int						m_Red;
	int						m_Green;
	int						m_Blue;
	int						m_Alpha;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	char*					m_pTexName;
	bool					m_drawFlag;
	CRender*				m_pRender;
public:
	CScene2D(int nPriority = 3,OBJTYPE objtype = OBJTYPE_2D):CScene(nPriority,objtype)
	{
		m_pD3DVtxBuffer = NULL;
		m_pD3DTex = NULL;
	}
	virtual ~CScene2D(){}

	//������
	HRESULT Init(CRender* pRender);
	HRESULT Init(CRender* pRender,D3DXVECTOR3 pos,int nRed,int nGreen,int nBlue,int nalpha,int nWidth,int nHeight,char* pTexFileName);
	//�X�V
	void Update();
	//�J��
	void Uninit();
	//�`��
	void Draw();
	void DrawShade();
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
	bool GetDrawFlag(void)
	{
		return m_drawFlag;
	}
	void SetDrawFlag(bool flag)
	{
		m_drawFlag = flag;
	}
	void SetAlpha(int nAlpha)
	{
		m_Alpha = nAlpha;
	}
	void SetRed(int nRed)
	{
		m_Red = nRed;
	}
	void SetBlue(int nBlue)
	{
		m_Blue = nBlue;
	}
	void SetGreen(int nGreen)
	{
		m_Green = nGreen;
	}
	static CScene2D* Create(CRender* pRender,D3DXVECTOR3 pos,char* ptexFileName,OBJTYPE objtype);
	static CScene2D* Create(CRender* pRender,D3DXVECTOR3 pos,int nWidth,int nHeight,char* ptexFileName,OBJTYPE objtype);
};
#endif