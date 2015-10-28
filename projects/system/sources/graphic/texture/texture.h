//*****************************************************************************
//
// texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/base.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace texture
{
class Texture : public utility::base::Base
{
public:
	// get buffer
	virtual void* GetBuffer(void)const = 0;

	// destructor
	virtual ~Texture(void) = default;

protected:
	// constructor
	Texture(void) = default;

private:

};

} // namespace texture
} // namespace graphic

#endif // _TEXTURE_H_

//---------------------------------- EOF --------------------------------------
