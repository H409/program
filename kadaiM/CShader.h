//=============================================================================
// �V�F�[�_�[�쐬���� [shader.h]
// Author : MASAHIRO YAMAGUCHI
// �V�F�[�_�[��������
//=============================================================================
//���d��`
#ifndef __CSHADER_H__
#define __CSHADER_H__

//�w�b�_�[�C���N���[�h
#include "main.h"

//�O���錾
class CRender;

//�V�F�[�_�[�N���X
class CShader
{
private:
	LPD3DXEFFECT m_pEffect;
	LPDIRECT3DVERTEXDECLARATION9 m_pVertexDeclaration;
	LPDIRECT3DDEVICE9			m_pD3DDevice;			// �f�o�C�X

	//�V�F�[�_�̃O���[�o���ϐ��n���h��
	D3DXHANDLE	m_WorldViewProjection;	//���W�ϊ��s��
	D3DXHANDLE	m_Texture;				//�e�N�X�`��
	
	UINT		m_pass;					//�p�X�C���f�b�N�X
	char*		m_TecnuiqueName;		//�e�N�j�b�N��
	char*		m_WVPtxName;			//�s��
	char*		m_TexName;				//�e�N�X�`����

	
public:
	
	//�R���X�g���N�^
	CShader()
	:	m_pEffect(NULL),
	m_pVertexDeclaration(NULL),
	m_WorldViewProjection(NULL),
	m_Texture(NULL),
	m_pass(0)
	{

	}

	//�f�X�g���N�^
	virtual ~CShader()
	{
		Release();
	}
	//�V�F�[�_�쐬�i�V�F�[�_�v���O�����t�@�C���ǂݍ��݁j
	bool Create2D(LPCSTR path);
	bool Create3D(LPCSTR path); 
	//�p�X�C���f�b�N�X���Z�b�g�i�V�F�[�_�v���O�����̑g�ݍ��킹��؂�ւ���j
	void ChangePass(UINT pass);
	//���_�f�[�^���擾
	const LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration()const
	{
		return m_pVertexDeclaration;
	}
	//�V�F�[�_�K�p
	void Begin();
	//�V�F�[�_�̃O���[�o���ϐ��ɒl���Z�b�g
	void SetData(D3DXMATRIX* mat,LPDIRECT3DTEXTURE9 texture);
	//�e�N�j�b�N���ݒ�
	void SetTecnuiqueName(char* pname);
	//�s��
	void SetMatrixName(char* pname);
	//�e�N�X�`����
	void SetTextureName(char* pname);
	//�V�F�[�_�I��
	void End();
	//�擾
	LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclaration(void)
	{
		return m_pVertexDeclaration;
	}
	void GetDevice(CRender* pRender);

	//���
	void Release();
};


#endif

//eof