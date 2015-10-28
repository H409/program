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
#ifndef _RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "texture.h"
#include "texture_format.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace texture
{
class RenderTexture : public Texture
{
public:
	// get frame buffer
	virtual void* GetFrameBuffer(void)const = 0;

	// destructor
	virtual ~RenderTexture(void) = default;

protected:
	// constructor
	RenderTexture(void) = default;

private:

};

} // namespace texture
} // namespace graphic

#endif // _BASE_RENDER_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
