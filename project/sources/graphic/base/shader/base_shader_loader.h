//*****************************************************************************
//
// base shader loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _BASE_SHADER_LOADER_H_
#define _BASE_SHADER_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "common/base/flyweight.h"
#include "base_shader.h"

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
namespace shader
{
class BaseShaderLoader : public common::base::Flyweight<std::string,BaseShader>
{
public:
	// constructor
	BaseShaderLoader(void);

	// destructor
	virtual ~BaseShaderLoader(void);

protected:

private:
	virtual BaseShader* Create(const std::string& key) = 0;
};

} // namespace texture
} // namespace base
} // namespace graphic

#endif // _BASE_TEXTURE_LOADER_H_

//---------------------------------- EOF --------------------------------------
