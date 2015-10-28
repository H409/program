//*****************************************************************************
//
// sprite
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "sprite.h"

namespace render {
namespace mesh {
//*****************************************************************************
// constant definition
//*****************************************************************************
const float2 Sprite::DEFAULT_SIZE = float2(1.0f,1.0f);
const float2 Sprite::DEFAULT_ANCHOR_POINT = float2(0.5f,0.5f);
const float4 Sprite::DEFAULT_COLOR = float4(1.0f,1.0f,1.0f,1.0f);

//=============================================================================
// constructor
//=============================================================================
Sprite::Sprite(void)
	:Sprite(DEFAULT_SIZE)
{
}

//=============================================================================
// constructor
//=============================================================================
Sprite::Sprite(const float2& in_size)
	:size_(in_size)
{
	//auto mesh_buffer = std::make_shared<MeshBuffer>();

	float3 positions[4] =
	{
		float3(-size_._x * (       anchor_point_._x),-size_._y * (       anchor_point_._y),0.0f),
		float3( size_._x * (1.0f - anchor_point_._x),-size_._y * (       anchor_point_._y),0.0f),
		float3(-size_._x * (       anchor_point_._x), size_._y * (1.0f - anchor_point_._y),0.0f),
		float3( size_._x * (1.0f - anchor_point_._x), size_._y * (1.0f - anchor_point_._y),0.0f),
	};
}

//=============================================================================
// destructor
//=============================================================================
Sprite::~Sprite(void)
{
}

//=============================================================================
// set anchor point
//=============================================================================
void Sprite::SetAnchorPoint(const float2 & in_anchor_point)
{
	DEBUG_ASSERT(in_anchor_point._x >= 0.0f && in_anchor_point._x <= 1.0f && in_anchor_point._y >= 0.0f && in_anchor_point._y <= 1.0f);
	anchor_point_ = in_anchor_point;
}

//=============================================================================
// set color
//=============================================================================
void Sprite::SetColor(const float4 & in_color)
{
	color_ = in_color;
}

} // namespace mesh
} // namespace render

	//---------------------------------- EOF --------------------------------------
