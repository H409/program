//*****************************************************************************
//
// sprite 3D
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "sprite_3d.h"
#include "system/win_system.h"

namespace mesh {
//*****************************************************************************
// constant definition
//*****************************************************************************
const float2 Sprite3D::DEFAULT_SIZE = float2(1.0f,1.0f);
const float2 Sprite3D::DEFAULT_ANCHOR_POINT = float2(0.5f,0.5f);
const float4 Sprite3D::DEFAULT_COLOR = float4(1.0f,1.0f,1.0f,1.0f);

//=============================================================================
// constructor
//=============================================================================
Sprite3D::Sprite3D(void)
	:Sprite3D(DEFAULT_SIZE)
{
}

//=============================================================================
// constructor
//=============================================================================
Sprite3D::Sprite3D(const float2& in_size)
	:size_(in_size)
	,anchor_point_(DEFAULT_ANCHOR_POINT)
{
	struct VERTEX
	{
		float3 _position;
		float2 _texcoord;
	};

	float3 positions[4] =
	{
		float3(-size_._x * (       anchor_point_._x), size_._y * (       anchor_point_._y),0.0f),
		float3( size_._x * (1.0f - anchor_point_._x), size_._y * (       anchor_point_._y),0.0f),
		float3(-size_._x * (       anchor_point_._x),-size_._y * (1.0f - anchor_point_._y),0.0f),
		float3( size_._x * (1.0f - anchor_point_._x),-size_._y * (1.0f - anchor_point_._y),0.0f),
	};

	float2 texcoords[4] =
	{
		float2(0.0f,0.0f),
		float2(1.0f,0.0f),
		float2(0.0f,1.0f),
		float2(1.0f,1.0f),
	};

	auto directx9 = GET_DIRECTX9_DEVICE();

	directx9->CreateVertexBuffer(sizeof(VERTEX) * 4,D3DUSAGE_WRITEONLY,0,D3DPOOL_MANAGED,&direct3dvertexbuffer9_,nullptr);

	VERTEX* vertex = nullptr;

	direct3dvertexbuffer9_->Lock(0,0,(void**)&vertex,0);

	for(u32 i = 0;i < 4;++i)
	{
		vertex[i]._position = positions[i];
		vertex[i]._texcoord = texcoords[i];
	}

	direct3dvertexbuffer9_->Unlock();
	stride_ = sizeof(VERTEX);
	primitive_type_ = D3DPT_TRIANGLESTRIP;
	primitive_count_ = 2;
}

//=============================================================================
// destructor
//=============================================================================
Sprite3D::~Sprite3D(void)
{
	SafeRelease(direct3dvertexbuffer9_);
}

//=============================================================================
// set anchor point
//=============================================================================
void Sprite3D::SetAnchorPoint(const float2 & in_anchor_point)
{
	DEBUG_ASSERT(in_anchor_point._x >= 0.0f && in_anchor_point._x <= 1.0f);
	DEBUG_ASSERT(in_anchor_point._y >= 0.0f && in_anchor_point._y <= 1.0f);
	anchor_point_ = in_anchor_point;
}

//=============================================================================
// set color
//=============================================================================
void Sprite3D::SetColor(const float4 & in_color)
{
	color_ = in_color;
}

} // namespace mesh

	//---------------------------------- EOF --------------------------------------
