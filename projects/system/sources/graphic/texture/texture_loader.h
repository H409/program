//*****************************************************************************
//
// texture loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/flyweight.h"
#include "texture.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace texture
{
class TextureLoader : public utility::base::Flyweight<std::string,Texture>
{
public:
	using TTexture = Texture;

	// destructor
	virtual ~TextureLoader(void) = default;

protected:
	// constructor
	TextureLoader(void) = default;

private:
	virtual TTexture* Create(const std::string& key) = 0;
};

} // namespace texture
} // namespace graphic

#endif // _CUBE_TEXTURE_LOADER_H_

//---------------------------------- EOF --------------------------------------
