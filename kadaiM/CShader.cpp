//=============================================================================
// �V�F�[�_�[�쐬���� [shader.h]
// Author : MASAHIRO YAMAGUCHI
// �V�F�[�_�[��������
//=============================================================================
//�w�b�_�[�C���N���[�h
#include "CShader.h"
#include <tchar.h>
#include "CRender.h"
//�V�F�[�_�֘A

//���V�F�[�_�N���X
//�쐬
bool CShader::Create2D(LPCSTR path)
{
	//�G���[�`�F�b�N
	if(m_pEffect != NULL)
	{
		Release();
	}
	
	try
	{
		HRESULT hr;
		D3DCAPS9 caps;
		m_pD3DDevice->GetDeviceCaps(&caps);
		
		//���_�V�F�[�_�A�s�N�Z���V�F�[�_���g�p�ł��邩���ׂ�
		if((caps.VertexShaderVersion < D3DVS_VERSION(2,0)) || 
			(caps.PixelShaderVersion < D3DPS_VERSION(2,0)))
		{
			::MessageBox(NULL,_T("�����p�̃O���t�B�b�N�X�{�[�h�̓v���O���}�u���V�F�[�_�ɑΉ����Ă���܂���B"),_T(""),MB_OK);
			throw 0;
		}

		//�t�@�C���̓ǂݍ���
		LPD3DXBUFFER pErrMessage = NULL;
		hr = D3DXCreateEffectFromFile(m_pD3DDevice,path,
					NULL,NULL,0,NULL,&m_pEffect,&pErrMessage);
		if(FAILED(hr))
		{
			//�G���[���b�Z�[�W�̕����R�[�h��ANSI
			::MessageBoxA(NULL,(LPCSTR)(pErrMessage->GetBufferPointer()),"",MB_OK);
			pErrMessage->Release();
			throw 0;
		}

		//�p�C�v���C���ɓn�����_�f�[�^�\�����`
		//2D
		//=============================================
		//1�ԍ����̓p�C�v���C���ԍ�
		//2�Ԗڂ�OFFSET�̒l(size�������)
		//3�Ԗڂ͒��_�v�f�̌^
		//4�Ԗڂ�DEFAULT����(D3DDECLMETHOD_DEFAULT)
		//5�Ԗڂ͗p�r
		//6�Ԗڂ͗p�r�ԍ�
		//=============================================
		D3DVERTEXELEMENT9 decl[] = 
		{
			{ 0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },	//�ʒu
			{ 0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},	//�F
			{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},	//�e�N�X�`�����W
			D3DDECL_END() //�Ō�ɕK��D3DDECL_END()������
		};
		hr = m_pD3DDevice->CreateVertexDeclaration(decl,&m_pVertexDeclaration);
		if(FAILED(hr))
		{
			throw 0;
		}
		
		//�V�F�[�_�֒��_��`���Z�b�g
		m_pD3DDevice->SetVertexDeclaration(m_pVertexDeclaration);

		//�V�F�[�_���g�p����e�N�j�b�N�i�V�F�[�_�v���O�����̑g�ݍ��킹�݂����ȕ��j���w��
		m_pEffect->SetTechnique(m_TecnuiqueName);

		//�V�F�[�_�v���O�����̃O���[�o���ϐ��n���h�����擾
		m_WorldViewProjection = m_pEffect->GetParameterByName( NULL, m_WVPtxName );
		m_Texture = m_pEffect->GetParameterByName( NULL, m_TexName);
	}
	catch(...)
	{	
		Release();
		return false;
	}
	return true;
}
//3D
bool CShader::Create3D(LPCSTR path)
{
	//�G���[�`�F�b�N
	if(m_pEffect != NULL)
	{
		Release();
	}
	
	try
	{
		HRESULT hr;
		D3DCAPS9 caps;
		m_pD3DDevice->GetDeviceCaps(&caps);
		
		//���_�V�F�[�_�A�s�N�Z���V�F�[�_���g�p�ł��邩���ׂ�
		if((caps.VertexShaderVersion < D3DVS_VERSION(2,0)) || 
			(caps.PixelShaderVersion < D3DPS_VERSION(2,0)))
		{
			::MessageBox(NULL,_T("�����p�̃O���t�B�b�N�X�{�[�h�̓v���O���}�u���V�F�[�_�ɑΉ����Ă���܂���B"),_T(""),MB_OK);
			throw 0;
		}

		//�t�@�C���̓ǂݍ���
		LPD3DXBUFFER pErrMessage = NULL;
		hr = D3DXCreateEffectFromFile(m_pD3DDevice,path,
					NULL,NULL,0,NULL,&m_pEffect,&pErrMessage);
		if(FAILED(hr))
		{
			//�G���[���b�Z�[�W�̕����R�[�h��ANSI
			::MessageBoxA(NULL,(LPCSTR)(pErrMessage->GetBufferPointer()),"",MB_OK);
			pErrMessage->Release();
			throw 0;
		}

		//�p�C�v���C���ɓn�����_�f�[�^�\�����`
		//3D
		//=============================================
		//1�ԍ����̓p�C�v���C���ԍ�
		//2�Ԗڂ�OFFSET�̒l(size�������)
		//3�Ԗڂ͒��_�v�f�̌^
		//4�Ԗڂ�DEFAULT����(D3DDECLMETHOD_DEFAULT)
		//5�Ԗڂ͗p�r
		//6�Ԗڂ͗p�r�ԍ�
		//=============================================

		D3DVERTEXELEMENT9 decl[ ] =   
		{
			{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
			{0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},
			{0,24,D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},
			{0,28,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
			D3DDECL_END()
		};
		hr = m_pD3DDevice->CreateVertexDeclaration(decl,&m_pVertexDeclaration);
		if(FAILED(hr))
		{
			throw 0;
		}
		//���_�f�[�^�ݒ�
		m_pD3DDevice->SetVertexDeclaration(m_pVertexDeclaration);

		//�V�F�[�_���g�p����e�N�j�b�N�i�V�F�[�_�v���O�����̑g�ݍ��킹�݂����ȕ��j���w��
		m_pEffect->SetTechnique(m_TecnuiqueName);

		//�V�F�[�_�v���O�����̃O���[�o���ϐ��n���h�����擾
		m_WorldViewProjection = m_pEffect->GetParameterByName( NULL, m_WVPtxName );
		m_Texture = m_pEffect->GetParameterByName( NULL, m_TexName);
	}
	catch(...)
	{	
		Release();
		return false;
	}
	return true;
}
//�p�X�ύX
void CShader::ChangePass(UINT pass)
{
	m_pass = pass;
}

//�V�F�[�_�v���O�����g�p�J�n��錾
//Begin��End�̊ԂɃ|���S����`�悷��
void CShader::Begin()
{
	//�G�t�F�N�g�J�n
	m_pEffect->Begin(NULL,0);

	//�g�p����p�X�I��
	m_pEffect->BeginPass(m_pass);
}
void CShader::End()
{
	//�p�X�I��
	m_pEffect->EndPass();
	//�G�t�F�N�g�I��
	m_pEffect->End();
}
//�V�F�[�_�K�p
void CShader::SetData(D3DXMATRIX *mat, LPDIRECT3DTEXTURE9 texture)
{
	//�V�F�[�_�̃O���[�o���ϐ��փf�[�^�Z�b�g
	m_pEffect->SetMatrix(m_WorldViewProjection,mat);
	m_pEffect->SetTexture(m_Texture,texture);
	
	//���O�Œ��ڃZ�b�g���邱�Ƃ��\
//	m_pEffect->SetMatrix("g_mWorldViewProjection", mat );
//	m_pEffect->SetTexture( "g_Texture", texture );
}

//�V�F�[�_���
void CShader::Release()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pVertexDeclaration);

	m_WorldViewProjection = NULL;
	m_Texture = NULL;
	m_pass = 0;
}
//�e�N�j�b�N��
void CShader::SetTecnuiqueName(char* pname)
{
	m_TecnuiqueName = pname;
}
//�e�N�X�`����
void CShader::SetTextureName(char* pname)
{
	m_TexName = pname;
}
//�}�g���b�N�X��
void CShader::SetMatrixName(char* pname)
{
	m_WVPtxName	 = pname;
}
//�f�o�C�X�擾
void CShader::GetDevice(CRender* pRender)
{
	m_pD3DDevice = pRender->getDevice();
}