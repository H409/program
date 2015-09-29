//*****************************************************************************
//
// directx9 render texture factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_RENDER_TEXTURE_FACTORY_H_
#define _DX9_RENDER_TEXTURE_FACTORY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/base/texture/base_render_texture_factory.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace directx9
{
namespace texture
{
class DX9RenderTextureFactory : public base::texture::BaseRenderTextureFactory
{
public:
	// constructor
	DX9RenderTextureFactory(LPDIRECT3DDEVICE9 in_direct3ddevice9);

	// destructor
	virtual ~DX9RenderTextureFactory(void);

protected:


private:
	LPDIRECT3DDEVICE9 direct3ddevice9_;

	TRenderTexture Create_(const u16& in_width,const u16& in_height,const base::texture::FORMAT& in_format)override;
};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_RENDER_TEXTURE_FACTORY_H_

//---------------------------------- EOF --------------------------------------
