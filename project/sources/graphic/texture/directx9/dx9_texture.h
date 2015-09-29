//*****************************************************************************
//
// directx9 texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _DX9_TEXTURE_H_
#define _DX9_TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "graphic/texture/texture.h"

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
namespace texture
{

class DX9Texture : public graphic::texture::Texture
{
public:
	// constructor
	DX9Texture(const std::string& path,LPDIRECT3DDEVICE9 direct3ddevice9);
	DX9Texture(const u32& in_id,LPDIRECT3DDEVICE9 in_direct3ddevice9);

	// destructor
	virtual ~DX9Texture(void);

	// get buffer
	void* GetBuffer(void) override;

protected:
	LPDIRECT3DDEVICE9 direct3ddevice9_;
	LPDIRECT3DTEXTURE9 direct3dtexture9_;

};

} // namespace texture
} // namespace directx9
} // namespace graphic

#endif // _DX9_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
