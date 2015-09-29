//*****************************************************************************
//
// base texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_TEXTURE_H_
#define _BASE_TEXTURE_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/base.h"

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
class BaseTexture : public common::base::Base
{
public:
	// get buffer
	virtual void* GetBuffer(void)const = 0;

	// destructor
	virtual ~BaseTexture(void);

protected:
	// constructor
	BaseTexture(void);

private:

};

} // namespace texture
} // namespace base
} // namespace graphic

#endif // _BASE_TEXTURE_H_

//---------------------------------- EOF --------------------------------------
