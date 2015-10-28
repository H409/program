//*****************************************************************************
//
// applicaton
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "application.h"
#include "base_system.h"
#include "graphic/graphic_device.h"
#include "graphic/shader/shader.h"
#include "graphic/vertex/vertex_buffer.h"
#include "math/math.h"

//=============================================================================
// constructor
//=============================================================================
Application::Application(TSystem in_system)
	:system_(in_system)
	,is_stop_(false)
{
	//auto device = graphic::
	auto graphic_device = system_->GetGraphicDevice();

	vertex_buffer_ = graphic_device->CreateVertexBuffer(sizeof(float3) * 4);

	graphic::GraphicDevice::TVertexElements vertex_elements =
	{
		{0,0,graphic::GraphicDevice::TVertexElement::TYPE::FLOAT3,graphic::GraphicDevice::TVertexElement::USAGE::POSITION,0},
	};

	float3 position[] = 
	{
		float3(-50.0f,-50.0f,0.0f),
		float3( 50.0f,-50.0f,0.0f),
		float3(-50.0f, 50.0f,0.0f),
		float3( 50.0f, 50.0f,0.0f),
	};

	vertex_buffer_->Stream(position,0,sizeof(position));

	vertex_declaration_ = graphic_device->CreateVertexDeclaration(vertex_elements);

	//vertex_shader_ = graphic_device->LoadVertexShader("resources/shader/basic.hlsl");
	//pixel_shader_ = graphic_device->LoadPixelShader("resources/shader/basic.hlsl");
}

//=============================================================================
// destructor
//=============================================================================
Application::~Application(void)
{
}

//=============================================================================
// update
//=============================================================================
void Application::Update(void)
{
	auto graphic_device = system_->GetGraphicDevice();

	float4x4 projection_matrix;
	float4x4 view_matrix;
	float4x4 world_matrix;

	view_matrix = utility::math::Identity();

	projection_matrix = utility::math::Identity();

	projection_matrix = utility::math::OrthoLH(800.0f,600.0f,0.0f,1.0f);

	//vertex_shader_->SetValue("_view_matrix",&view_matrix,sizeof(view_matrix));
	//vertex_shader_->SetValue("_projection_matrix",&projection_matrix,sizeof(projection_matrix));
	//vertex_shader_->SetValue("_world_matrix",&world_matrix,sizeof(world_matrix));

	// begin draw
	if(graphic_device->BeginDraw())
	{
		// set render target
		

		// set depth buffer
		

		// clear buffer
		graphic_device->Clear();

		// set shader
		//shader_->Set();

		// set vertex declaration
		DEBUG_ASSERT(graphic_device->SetVertexDeclaration(vertex_declaration_));

		// set vertex buffer
		DEBUG_ASSERT(graphic_device->SetVertexBuffer(vertex_buffer_,0,sizeof(float3)));

		// draw
		//DEBUG_ASSERT(graphic_device->Draw(graphic::GraphicDevice::PRIMITIVE_TYPE::TRIANGLESTRIP,0,2));

		graphic_device->Draw();

		// end draw
		graphic_device->EndDraw();
	}
}

//=============================================================================
// is stop
//=============================================================================
bool Application::IsStop(void) const
{
	return is_stop_;
}

//---------------------------------- EOF --------------------------------------
