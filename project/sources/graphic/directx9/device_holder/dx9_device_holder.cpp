//*****************************************************************************
//
// directx9 device holder
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "dx9_device_holder.h"
#include "../texture/dx9_texture_loader.h"
#include "../shader/dx9_shader_loader.h"
#include "../texture/dx9_texture.h"
#include "../texture/dx9_render_texture_factory.h"
#include "../depth_buffer/dx9_depth_buffer.h"
#include "../depth_buffer/dx9_depth_buffer_factory.h"

namespace graphic
{
namespace directx9
{
namespace device_holder
{
//*****************************************************************************
// constant definition
//*****************************************************************************

//=============================================================================
// constructor
//=============================================================================
DX9DeviceHolder::DX9DeviceHolder(void)
	:BaseDeviceHolder()
	,hwnd_(nullptr)
	,direct3ddevice9_(nullptr)
	,direct3d9_(nullptr)
	,default_render_target_(nullptr)
	,default_depthStencil_(nullptr)
{
}

//=============================================================================
// constructor
//=============================================================================
DX9DeviceHolder::DX9DeviceHolder(const HWND& in_hwnd,const u16& in_width,const u16& in_height)
	:DX9DeviceHolder()
{
	hwnd_ = in_hwnd;

	// Direct3Dオブジェクトの作成
	direct3d9_ = Direct3DCreate9(D3D_SDK_VERSION);

	// Direct3Dオブジェクトの失敗
	if(direct3d9_ == nullptr)
	{
		DEBUG_ASSERT("Direct3Dオブジェクトの生成に失敗しました");
	}

	// 現在のディスプレイモードを取得
	if(FAILED(direct3d9_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddisplaymode_)))
	{
		DEBUG_ASSERT("ディスプレイモードの取得に失敗しました");
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpresent_parameters_,sizeof(d3dpresent_parameters_));

	// バックバッファの数
	d3dpresent_parameters_.BackBufferCount = 1;

	// ゲーム画面サイズ(幅)
	d3dpresent_parameters_.BackBufferWidth = in_width;

	// ゲーム画面サイズ(高さ)
	d3dpresent_parameters_.BackBufferHeight = in_height;

	// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpresent_parameters_.BackBufferFormat = d3ddisplaymode_.Format;

	// 映像信号に同期してフリップする
	d3dpresent_parameters_.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// ウィンドウモード
	d3dpresent_parameters_.Windowed = true;

	// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpresent_parameters_.EnableAutoDepthStencil = TRUE;

	// デプスバッファとして16bitを使う
	d3dpresent_parameters_.AutoDepthStencilFormat = D3DFMT_D16;

	// ウィンドウモード
	if(d3dpresent_parameters_.Windowed)
	{
		// リフレッシュレート
		d3dpresent_parameters_.FullScreen_RefreshRateInHz = 0;

		// インターバル
		d3dpresent_parameters_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	// フルスクリーンモード
	else
	{
		// バックバッファ
		d3dpresent_parameters_.BackBufferFormat = D3DFMT_R5G6B5;

		// リフレッシュレート
		d3dpresent_parameters_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		// インターバル
		d3dpresent_parameters_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	// デバイスオブジェクトの生成
	if(FAILED(direct3d9_->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,in_hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,&d3dpresent_parameters_,&direct3ddevice9_)))
	{
		DEBUG_ASSERT("デバイスの生成に失敗しました");
	}

	// レンダーステートの設定
	SetDefaultRenderState_();

	// サンプラーステートの設定
	SetDefaultSamplerState_();

	// テクスチャーステージステートの設定
	SetDefaultTextureStageState_();

	direct3ddevice9_->GetRenderTarget(0,&default_render_target_);
	direct3ddevice9_->GetDepthStencilSurface(&default_depthStencil_);

	// create texture loader
	texture_loader_ = std::make_shared<texture::DX9TextureLoader>(direct3ddevice9_);

	// create shader loader
	shader_loader_ = std::make_shared<shader::DX9ShaderLoader>(direct3ddevice9_);

	// create render texture factory
	render_texture_factory_ = std::make_shared<texture::DX9RenderTextureFactory>(direct3ddevice9_);

	// create depth buufer factory
	depth_buffer_factory_ = std::make_shared<depth_buffer::DX9DepthBufferFactory>(direct3ddevice9_);

}

//=============================================================================
// destructor
//=============================================================================
DX9DeviceHolder::~DX9DeviceHolder(void)
{
	SafeRelease(default_render_target_);
	SafeRelease(default_depthStencil_);
	SafeRelease(direct3ddevice9_);
	SafeRelease(direct3d9_);
}

//=============================================================================
// begin draw
//=============================================================================
bool DX9DeviceHolder::BeginDraw_(void)
{
	return direct3ddevice9_->BeginScene();
}

//=============================================================================
// end draw
//=============================================================================
bool DX9DeviceHolder::EndDraw_(void)
{
	if(FAILED(direct3ddevice9_->EndScene()))
	{
		return false;
	}

	if(FAILED(direct3ddevice9_->Present(NULL,NULL,hwnd_,NULL)))
	{
		return false;
	}

	return true;
}

//=============================================================================
// clear
//=============================================================================
bool DX9DeviceHolder::Clear_(const u32& in_count,const float4* in_rects,const u32& in_target,const float4& in_color,const f32& in_z,const u32& in_stencil)
{
	std::vector<D3DRECT> rects;
	D3DRECT* rects_addr = nullptr;

	if(in_count > 0)
	{
		rects.reserve(in_count);

		for(int i = 0;in_count;++i)
		{
			rects.emplace_back(ConvertD3DRECTFromFloat4_(in_rects[i]));
		}

		rects_addr = &rects[0];
	}

	D3DCOLOR color = ConvertD3DCOLORFromFloat4_(in_color);

	u32 target = ConvertFlagsFromClearTarget_(in_target);

	return direct3ddevice9_->Clear(in_count,rects_addr,target,color,in_z,in_stencil);
}

//=============================================================================
// set render target
//=============================================================================
bool DX9DeviceHolder::SetRenderTarget_(const u32& in_index,TRenderTexture in_render_texture)
{
	return direct3ddevice9_->SetRenderTarget(in_index,(LPDIRECT3DSURFACE9)in_render_texture->GetFrameBuffer());
}

//=============================================================================
// set depth buffer
//=============================================================================
bool DX9DeviceHolder::SetDepthBuffer_(TDepthBuffer in_depth_buffer)
{
	return direct3ddevice9_->SetDepthStencilSurface((LPDIRECT3DSURFACE9)in_depth_buffer->GetBuffer());
}

//=============================================================================
// set depth stencil surface
//=============================================================================
bool DX9DeviceHolder::SetDepthStencilSurface_(LPDIRECT3DSURFACE9 in_direct3dsurface9)
{
	return direct3ddevice9_->SetDepthStencilSurface(in_direct3dsurface9);
}

//=============================================================================
// デフォルトレンダーステートの設定
//=============================================================================
void DX9DeviceHolder::SetDefaultRenderState_(void)
{
	direct3ddevice9_->SetRenderState(D3DRS_LIGHTING,FALSE);
	//direct3ddevice9_->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	direct3ddevice9_->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);					// 裏面をカリング
	direct3ddevice9_->SetRenderState(D3DRS_ZENABLE,TRUE);							// Zバッファを使用
	direct3ddevice9_->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);				// αブレンドを行う
	direct3ddevice9_->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);			// αソースカラーの指定
	direct3ddevice9_->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);		// αデスティネーションカラーの指定
}

//=============================================================================
// デフォルトサンプラーステートの設定
//=============================================================================
void DX9DeviceHolder::SetDefaultSamplerState_(void)
{
	direct3ddevice9_->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);		// テクスチャアドレッシング方法(U値)を設定
	direct3ddevice9_->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);		// テクスチャアドレッシング方法(V値)を設定
	direct3ddevice9_->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);		// テクスチャ縮小フィルタモードを設定
	direct3ddevice9_->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);		// テクスチャ拡大フィルタモードを設定
}

//=============================================================================
// デフォルトテクスチャステージステートの設定
//=============================================================================
void DX9DeviceHolder::SetDefaultTextureStageState_(void)
{
	direct3ddevice9_->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	direct3ddevice9_->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);	// 最初のアルファ引数
	direct3ddevice9_->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);	// ２番目のアルファ引数
}

//=============================================================================
// convert D3DRECT from float4
//=============================================================================
D3DRECT DX9DeviceHolder::ConvertD3DRECTFromFloat4_(const float4& in_rect)const
{
	D3DRECT d3drect;

	d3drect.x1 = (LONG)in_rect._left;
	d3drect.y1 = (LONG)in_rect._top;
	d3drect.x2 = (LONG)in_rect._right;
	d3drect.y2 = (LONG)in_rect._bottom;

	return d3drect;
}

//=============================================================================
// convert D3DCOLOR from float4
//=============================================================================
D3DCOLOR DX9DeviceHolder::ConvertD3DCOLORFromFloat4_(const float4& in_color)const
{
	return D3DXCOLOR(in_color._r,in_color._g,in_color._b,in_color._a);
}

//=============================================================================
// convert flags from clear target
//=============================================================================
DWORD DX9DeviceHolder::ConvertFlagsFromClearTarget_(const u32& clear_target)const
{
	return (DWORD)clear_target;
}

} // namespace device_holder
} // namespace directx9
} // namespace graphic

//---------------------------------- EOF --------------------------------------
