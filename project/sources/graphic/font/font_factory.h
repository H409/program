//*****************************************************************************
//
// font factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _FONT_FACTORY_H_
#define _FONT_FACTORY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/flyweight.h"
#include "font.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace font
{

class FontFactory : public common::base::Flyweight<std::string,Font>
{
public:
	// constructor
	FontFactory(const Font::TYPE& in_type,const u16& in_size);

	// destructor
	virtual ~FontFactory(void);

protected:

private:
	Font::TYPE type_;
	u16 size_;

	Font* Create(const std::string& in_key) override;
};

} // namespace font
} // namespace graphic

#endif // _FONT_FACTORY_H_

//---------------------------------- EOF --------------------------------------
