//*****************************************************************************
//
// shader loader
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _SHADER_LOADER_H_
#define _SHADER_LOADER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/flyweight.h"
#include "shader.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace shader
{
class ShaderLoader : public utility::base::Flyweight<std::string,Shader>
{
public:
	using TShader = Shader;

	// constructor
	ShaderLoader(void);

	// destructor
	virtual ~ShaderLoader(void);

protected:

private:
	virtual TShader* Create(const std::string& key) = 0;
};

} // namespace shader
} // namespace graphic

#endif // _SHADER_LOADER_H_

//---------------------------------- EOF --------------------------------------
