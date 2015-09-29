//*****************************************************************************
//
// texture
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "texture.h"

namespace core
{
namespace texture
{
//=============================================================================
// constructor
//=============================================================================
Texture::Texture(const std::string& in_path)
	:type_(TYPE::LOAD)
	,path_(in_path)
{
}

//=============================================================================
// destructor
//=============================================================================
Texture::~Texture(void)
{
}

} // namespace texture
} // namespace core

//---------------------------------- EOF --------------------------------------
