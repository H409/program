//*****************************************************************************
//
// directx9 device
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_device.h"
#include "texture/dx9_texture_loader.h"
#include "shader/dx9_vertex_shader.h"
#include "shader/dx9_pixel_shader.h"
#include "shader/dx9_vertex_shader_loader.h"
#include "shader/dx9_pixel_shader_loader.h"
#include "texture/dx9_texture.h"
#include "texture/dx9_render_texture_factory.h"
#include "math/math.h"

namespace graphic {
namespace directx9 {
//=============================================================================
// constructor
//=============================================================================
DX9Device::DX9Device(const HWND& in_hwnd)
	:hwnd_(in_hwnd)
	,direct3ddevice9_(nullptr)
	,direct3d9_(nullptr)
	,default_render_target_(nullptr)
	,default_depthStencil_(nullptr)
{
}

//=============================================================================
// constructor
//=============================================================================
DX9Device::DX9Device(const HWND& in_hwnd,const u16& in_width,const u16& in_height)
	:DX9Device(in_hwnd)
{
	// Direct3D�I�u�W�F�N�g�̍쐬
	direct3d9_ = Direct3DCreate9(D3D_SDK_VERSION);

	// Direct3D�I�u�W�F�N�g�̎��s
	if(direct3d9_ == nullptr)
	{
		DEBUG_ASSERT("Direct3D�I�u�W�F�N�g�̐����Ɏ��s���܂���");
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if(FAILED(direct3d9_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddisplaymode_)))
	{
		DEBUG_ASSERT("�f�B�X�v���C���[�h�̎擾�Ɏ��s���܂���");
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpresent_parameters_,sizeof(d3dpresent_parameters_));

	// �o�b�N�o�b�t�@�̐�
	d3dpresent_parameters_.BackBufferCount = 1;

	// �Q�[����ʃT�C�Y(��)
	d3dpresent_parameters_.BackBufferWidth = in_width;

	// �Q�[����ʃT�C�Y(����)
	d3dpresent_parameters_.BackBufferHeight = in_height;

	// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpresent_parameters_.BackBufferFormat = d3ddisplaymode_.Format;

	// �f���M���ɓ������ăt���b�v����
	d3dpresent_parameters_.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// �E�B���h�E���[�h
	d3dpresent_parameters_.Windowed = true;

	// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpresent_parameters_.EnableAutoDepthStencil = TRUE;

	// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpresent_parameters_.AutoDepthStencilFormat = D3DFMT_D16;

	// �}���`�T���v�����g�p
	d3dpresent_parameters_.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;
	direct3d9_->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,D3DFMT_R5G6B5,true,D3DMULTISAMPLE_4_SAMPLES,&d3dpresent_parameters_.MultiSampleQuality);
	d3dpresent_parameters_.MultiSampleQuality -= 1;

	// �E�B���h�E���[�h
	if(d3dpresent_parameters_.Windowed)
	{
		// ���t���b�V�����[�g
		d3dpresent_parameters_.FullScreen_RefreshRateInHz = 0;

		// �C���^�[�o��
		d3dpresent_parameters_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	// �t���X�N���[�����[�h
	else
	{
		// �o�b�N�o�b�t�@
		d3dpresent_parameters_.BackBufferFormat = D3DFMT_R5G6B5;

		// ���t���b�V�����[�g
		d3dpresent_parameters_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		// �C���^�[�o��
		d3dpresent_parameters_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	if(FAILED(direct3d9_->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,in_hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,&d3dpresent_parameters_,&direct3ddevice9_)))
	{
		DEBUG_ASSERT("�f�o�C�X�̐����Ɏ��s���܂���");
	}

	// �����_�[�X�e�[�g�̐ݒ�
	SetDefaultRenderState_();

	// �T���v���[�X�e�[�g�̐ݒ�
	SetDefaultSamplerState_();

	// �e�N�X�`���[�X�e�[�W�X�e�[�g�̐ݒ�
	SetDefaultTextureStageState_();

	direct3ddevice9_->GetRenderTarget(0,&default_render_target_);
	direct3ddevice9_->GetDepthStencilSurface(&default_depthStencil_);

	texture_loader_ = std::make_shared<texture::DX9TextureLoader>(direct3ddevice9_);
	vertex_shader_loader_ = std::make_shared<shader::DX9VertexShaderLoader>(direct3ddevice9_);
	pixel_shader_loader_ = std::make_shared<shader::DX9PixelShaderLoader>(direct3ddevice9_);
}

//=============================================================================
// destructor
//=============================================================================
DX9Device::~DX9Device(void)
{
	SafeRelease(default_render_target_);
	SafeRelease(default_depthStencil_);
	SafeRelease(direct3ddevice9_);
	SafeRelease(direct3d9_);
}

//=============================================================================
// begin rendering
//=============================================================================
bool DX9Device::BeginRendering(void)
{
	return direct3ddevice9_->BeginScene() == S_OK;
}

//=============================================================================
// end rendering
//=============================================================================
bool DX9Device::EndRendering(void)
{
	if(!(direct3ddevice9_->EndScene() == S_OK))
	{
		return false;
	}


	if((direct3ddevice9_->Present(nullptr,nullptr,hwnd_,nullptr) == D3DERR_DEVICELOST))
	{
		if(direct3ddevice9_->TestCooperativeLevel() != D3DERR_DEVICENOTRESET)
		{
			return false;
		}

		if(direct3ddevice9_->Reset(&d3dpresent_parameters_) != D3D_OK)
		{
			return false;
		}

		return false;
	}

	return true;
}

//=============================================================================
// clear
//=============================================================================
bool DX9Device::Clear(const float4& in_color)
{
	return direct3ddevice9_->Clear(0,nullptr,D3DCLEAR_TARGET,D3DXCOLOR(in_color._r,in_color._g,in_color._b,in_color._a),1.0f,0) == S_OK;
}

//=============================================================================
// clear
//=============================================================================
bool DX9Device::Clear(const float4& in_color,const f32& in_z)
{
	return direct3ddevice9_->Clear(0,nullptr,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DXCOLOR(in_color._r,in_color._g,in_color._b,in_color._a),in_z,0) == S_OK;
}

//=============================================================================
// clear
//=============================================================================
bool DX9Device::Clear(const float4& in_color,const f32& in_z,const u32& in_stencil)
{
	return direct3ddevice9_->Clear(0,nullptr,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,D3DXCOLOR(in_color._r,in_color._g,in_color._b,in_color._a),in_z,in_stencil) == S_OK;
}

//=============================================================================
// get direct device
//=============================================================================
LPDIRECT3DDEVICE9 DX9Device::GetDevice(void)
{
	return direct3ddevice9_;
}

//=============================================================================
// load texture
//=============================================================================
DX9Device::TTexture DX9Device::LoadTexture(const std::string & in_path)
{
	return texture_loader_->Load(in_path);
}

//=============================================================================
// create texture
//=============================================================================
DX9Device::TTexture DX9Device::CreateTexture(const u16 & in_width,const u16 & in_height,const D3DFORMAT & in_format)
{
	return std::make_shared<texture::DX9Texture>(in_width,in_height,in_format,direct3ddevice9_);
}

//=============================================================================
// set render target
//=============================================================================
void DX9Device::SetRenderTarget(const u32& in_index,TTexture in_texture)
{
	if(in_texture != nullptr)
	{
		direct3ddevice9_->SetRenderTarget(in_index,in_texture->GetSurface());
		return;
	}

	direct3ddevice9_->SetRenderTarget(in_index,nullptr);

}

//=============================================================================
// get render target
//=============================================================================
DX9Device::TTexture DX9Device::GetRenderTarget(const u32 & in_index)
{
	LPDIRECT3DSURFACE9 direct3dsurface9 = nullptr;

	direct3ddevice9_->GetRenderTarget(in_index,&direct3dsurface9);

	return std::make_shared<texture::DX9Texture>(direct3dsurface9);
}

//=============================================================================
// load vertex shader
//=============================================================================
DX9Device::TVertexShader DX9Device::LoadVertexShader(const std::string & in_path)
{
	return vertex_shader_loader_->Load(in_path);
}

//=============================================================================
// load vertex shader
//=============================================================================
DX9Device::TVertexShader DX9Device::LoadVertexShader(const std::string & in_path,const std::string & in_function,const std::string & in_version)
{
	return vertex_shader_loader_->Load(in_path , in_function , in_version );
}

//=============================================================================
// load pixel shader
//=============================================================================
DX9Device::TPixelShader DX9Device::LoadPixelShader(const std::string & in_path)
{
	return pixel_shader_loader_->Load(in_path);
}

//=============================================================================
// load pixel shader
//=============================================================================
DX9Device::TPixelShader DX9Device::LoadPixelShader(const std::string & in_path,const std::string & in_function,const std::string & in_version)
{
	pixel_shader_loader_->Load(in_path , in_function , in_version );
	return nullptr;
}

//=============================================================================
// set vertex shader
//=============================================================================
void DX9Device::SetVertexShader(TVertexShader in_vertex_shader)
{
	direct3ddevice9_->SetVertexShader(in_vertex_shader->GetShader());
}

//=============================================================================
// set pixel shader
//=============================================================================
void DX9Device::SetPixelShader(TPixelShader in_pixel_shader)
{
	direct3ddevice9_->SetPixelShader(in_pixel_shader->GetShader());
}

//=============================================================================
// �f�t�H���g�����_�[�X�e�[�g�̐ݒ�
//=============================================================================
void DX9Device::SetDefaultRenderState_(void)
{
	direct3ddevice9_->SetRenderState(D3DRS_LIGHTING,FALSE);
	//direct3ddevice9_->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	direct3ddevice9_->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);					// ���ʂ��J�����O
	direct3ddevice9_->SetRenderState(D3DRS_ZENABLE,TRUE);							// Z�o�b�t�@���g�p
	direct3ddevice9_->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);				// ���u�����h���s��
	direct3ddevice9_->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);			// ���\�[�X�J���[�̎w��
	direct3ddevice9_->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);		// ���f�X�e�B�l�[�V�����J���[�̎w��
	direct3ddevice9_->SetRenderState(D3DRS_ALPHAREF,1);
	direct3ddevice9_->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	direct3ddevice9_->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATEREQUAL);
}

//=============================================================================
// �f�t�H���g�T���v���[�X�e�[�g�̐ݒ�
//=============================================================================
void DX9Device::SetDefaultSamplerState_(void)
{
	direct3ddevice9_->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);		// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	direct3ddevice9_->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);		// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	direct3ddevice9_->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);		// �e�N�X�`���k���t�B���^���[�h��ݒ�
	direct3ddevice9_->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);		// �e�N�X�`���g��t�B���^���[�h��ݒ�
}

//=============================================================================
// �f�t�H���g�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
//=============================================================================
void DX9Device::SetDefaultTextureStageState_(void)
{
	direct3ddevice9_->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	direct3ddevice9_->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	direct3ddevice9_->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
}

} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
