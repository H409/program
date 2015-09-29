//*****************************************************************************
//
// resource texture
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
#include "common/base/base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace graphic
{
class Texture;
} // namespace graphic

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace texture
{

class Texture : public common::base::Base
{
protected:
	// constructor
	Texture(void);

	// destructor
	virtual ~Texture(void);

private:

};

} // namespace texture
} // namespace graphic

#endif // _TEXTURE_H_

//---------------------------------- EOF --------------------------------------
