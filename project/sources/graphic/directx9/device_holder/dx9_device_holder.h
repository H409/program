//*****************************************************************************
//
// directx9 device holder
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_DEVICE_HOLDER_H_
#define _DX9_DEVICE_HOLDER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/base/device_holder/base_device_holder.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace device_holder
{
class DX9DeviceHolder : public graphic::base::device_holder::BaseDeviceHolder
{
public:
	// constructor
	DX9DeviceHolder(const HWND& in_hwnd,const u16& in_width,const u16& in_height);

	// destructor
	virtual ~DX9DeviceHolder(void);

private:
	// constructor
	DX9DeviceHolder(void);

	HWND hwnd_;
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	LPDIRECT3D9 direct3d9_;
	D3DPRESENT_PARAMETERS d3dpresent_parameters_;
	D3DDISPLAYMODE d3ddisplaymode_;
	LPDIRECT3DSURFACE9 default_render_target_;
	LPDIRECT3DSURFACE9 default_depthStencil_;

	// begin draw
	bool BeginDraw_(void);

	// end draw
	bool EndDraw_(void);

	// clear
	bool Clear_(const u32& in_count,const float4* in_rects,const u32& in_target,const float4& in_color,const f32& in_z,const u32& in_stencil);

	// set render target
	bool SetRenderTarget_(const u32& in_index,TRenderTexture in_render_texture)override;

	// set depth buffer
	bool SetDepthBuffer_(TDepthBuffer in_depth_buffer)override;

	// set depth stencil surface
	bool SetDepthStencilSurface_(LPDIRECT3DSURFACE9 in_direct3dsurface9);

	// デフォルトレンダーステートの設定
	void SetDefaultRenderState_(void);

	// デフォルトサンプラーステートの設定
	void SetDefaultSamplerState_(void);

	// デフォルトテクスチャステージステートの設定
	void SetDefaultTextureStageState_(void);

	// convert D3DRECT from float4
	D3DRECT ConvertD3DRECTFromFloat4_(const float4& in_rect)const;
	D3DCOLOR ConvertD3DCOLORFromFloat4_(const float4& in_color)const;
	DWORD ConvertFlagsFromClearTarget_(const u32& clear_target)const;

};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_DEVICE_HOLDER_H_

//---------------------------------- EOF --------------------------------------
