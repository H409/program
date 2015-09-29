//*****************************************************************************
//
// base texture loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_TEXTURE_LOADER_H_
#define _BASE_TEXTURE_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/flyweight.h"
#include "base_texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace base
{
namespace texture
{
class BaseTextureLoader : public common::base::Flyweight<std::string,BaseTexture>
{
public:
	// constructor
	BaseTextureLoader(void);

	// destructor
	virtual ~BaseTextureLoader(void);

protected:

private:
	virtual BaseTexture* Create(const std::string& key) = 0;
};

} // namespace texture
} // namespace base
} // namespace graphic

#endif // _BASE_TEXTURE_LOADER_H_

//---------------------------------- EOF --------------------------------------
