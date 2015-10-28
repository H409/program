//*****************************************************************************
//
// application
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//*****************************************************************************
// include
//*****************************************************************************

//*****************************************************************************
// forward declaration
//*****************************************************************************
class BaseSystem;

// HACK TEST
namespace graphic
{
namespace vertex
{
class VertexBuffer;
class VertexDeclaration;
}
namespace shader
{
class Shader;
}
}

//*****************************************************************************
// class definition
//*****************************************************************************
class Application
{
public:
	using TSystem = std::shared_ptr<BaseSystem>;

	// constructor
	Application(TSystem in_system);

	// destructor
	virtual ~Application(void);

	// update
	void Update(void);

	// is stop
	bool IsStop(void)const;

private:
	TSystem system_;

	bool is_stop_;

	// HACK TEST
	std::shared_ptr<graphic::vertex::VertexBuffer> vertex_buffer_;
	std::shared_ptr<graphic::vertex::VertexDeclaration> vertex_declaration_;
	std::shared_ptr<graphic::shader::Shader> vertex_shader_;
	std::shared_ptr<graphic::shader::Shader> pixel_shader_;

};

#endif // _APPLICATION_H_

//---------------------------------- EOF --------------------------------------
