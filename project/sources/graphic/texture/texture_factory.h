//*****************************************************************************
//
// texture factory
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _TEXTURE_FACTORY_H_
#define _TEXTURE_FACTORY_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/flyweight.h"
#include "texture.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace texture
{

class BaseTextureFactory : public common::base::Flyweight<std::string,Texture>
{
public:
	// constructor
	BaseTextureFactory(void);

	// destructor
	virtual ~BaseTextureFactory(void);

protected:

private:
	static const std::string DIRECTORY_PATH;
	virtual Texture* Create(const std::string& key) override;
};

} // namespace texture
} // namespace graphic

#endif // _TEXTURE_FACTORY_H_

//---------------------------------- EOF --------------------------------------
