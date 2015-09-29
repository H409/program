//*****************************************************************************
//
// base element
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_ELEMENT_H_
#define _BASE_ELEMENT_H_

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
namespace element
{
class BaseElement : public common::base::Base
{
public:
	// destructor
	virtual ~BaseElement(void);

	// get buffer
	virtual void* GetBuffer(void) = 0;

protected:
	// constructor
	BaseElement(void);

private:
};

} // namespace element
} // namespace base
} // napaspace graphic

#endif // _BASE_ELEMENT_H_

//---------------------------------- EOF --------------------------------------
