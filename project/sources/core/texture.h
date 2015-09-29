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
#include "common/base/base.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace core
{
namespace texture
{
class Texture : public common::base::Base
{
public:
	enum class TYPE
	{
		NONE = 0,
		LOAD,
		CREATE,
	};

	// constructor
	explicit Texture(const std::string& in_path);

	// destructor
	virtual ~Texture(void);

	// accessor
	const TYPE& __type(void)const { return type_; }
	const std::string& __path(void)const{ return path_; }

private:
	TYPE type_;
	std::string path_;

};

} // namespace texture
} // namespace core

#endif // _TEXTURE_H_

//---------------------------------- EOF --------------------------------------
