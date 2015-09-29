//*****************************************************************************
//
// base render texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_RENDER_TEXTURE_H_
#define _BASE_RENDER_TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base_texture.h"
#include "texture_format.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace texture
{
class BaseRenderTexture : public BaseTexture
{
public:
	// get frame buffer
	virtual void* GetFrameBuffer(void)const = 0;

	// destructor
	virtual ~BaseRenderTexture(void);

protected:
	// constructor
	BaseRenderTexture(void);

private:

};

} // namespace texture
} // namespace base
} // namespace graphic

#endif // _BASE_RENDER_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
