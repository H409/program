//*****************************************************************************
//
// font factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "font_factory.h"
#include "font.h"

namespace graphic
{
namespace font
{

//=============================================================================
// constructor
//=============================================================================
FontFactory::FontFactory(const Font::TYPE& in_type,const u16& in_size)
	:type_(in_type)
	,size_(in_size)
{
}

//=============================================================================
// destructor
//=============================================================================
FontFactory::~FontFactory(void)
{
}

//=============================================================================
// create
//=============================================================================
Font* FontFactory::Create(const std::string& in_key)
{
	auto font = new Font(in_key,type_,size_);

	return font;
}

} // namespace font
} // namespace graphic

//---------------------------------- EOF --------------------------------------
