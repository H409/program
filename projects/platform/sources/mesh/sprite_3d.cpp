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
	:Mesh(true,false)
	,size_(in_size)
	,anchor_point_(DEFAULT_ANCHOR_POINT)
	,texcoord_(0.0f,1.0f,0.0f,1.0f)
	,index_(0)
	,division_width_(1)
	,division_height_(1)
{
	auto directx9 = GET_DIRECTX9_DEVICE();

	directx9->CreateVertexBuffer(sizeof(VERTEX) * 4,D3DUSAGE_WRITEONLY,0,D3DPOOL_MANAGED,&direct3dvertexbuffer9_,nullptr);

	stride_ = sizeof(VERTEX);
	primitive_type_ = D3DPT_TRIANGLESTRIP;
	primitive_count_ = 2;

	UpdateVertexBuffer_();
}

//=============================================================================
// destructor
//=============================================================================
Sprite3D::~Sprite3D(void)
{
	SafeRelease(direct3dvertexbuffer9_);
}

//=============================================================================
// set size
//=============================================================================
void Sprite3D::SetSize(const float2& in_size)
{
	size_ = in_size;
	is_dirty_ = true;
}

//=============================================================================
// set size
//=============================================================================
void Sprite3D::SetSize(const f32& in_width,const f32& in_height)
{
	SetSize(float2(in_width,in_height));
}

//=============================================================================
// set anchor point
//=============================================================================
void Sprite3D::SetAnchorPoint(const float2 & in_anchor_point)
{
	DEBUG_ASSERT(in_anchor_point._x >= 0.0f && in_anchor_point._x <= 1.0f);
	DEBUG_ASSERT(in_anchor_point._y >= 0.0f && in_anchor_point._y <= 1.0f);
	anchor_point_ = in_anchor_point;
	is_dirty_ = true;
}

//=============================================================================
// set texcoord
//=============================================================================
void Sprite3D::SetTexcoord(const float4& in_texcoord)
{
	texcoord_ = in_texcoord;
	is_dirty_ = true;
}

//=============================================================================
// set texcoord
//=============================================================================
void Sprite3D::SetTexcoord(const f32& in_left,const f32& in_right,const f32& in_top,const f32& in_bottom)
{
	SetTexcoord(float4(in_left,in_right,in_top,in_bottom));
}

//=============================================================================
// set texcoord
//=============================================================================
void Sprite3D::SetTexcoord(const u32& in_index)
{
	SetTexcoord(in_index,division_width_,division_height_);
}

//=============================================================================
// set texcoord
//=============================================================================
void Sprite3D::SetTexcoord(const u32& in_index,const u32& in_division_width,const u32& in_division_height)
{
	index_ = in_index;
	division_width_ = in_division_width;
	division_height_ = in_division_height;

	u32 index_u = index_ % division_width_;
	u32 index_v = index_ / division_width_;
	float offset_u = 1.0f / division_width_;
	float offset_v = 1.0f / division_height_;

	float left = offset_u * index_u;
	float right = offset_u * (index_u + 1);
	float top = offset_v * index_v;
	float bottom = offset_v * (index_v + 1);

	SetTexcoord(left,right,top,bottom);
}

//=============================================================================
// update vertex buffer
//=============================================================================
void Sprite3D::UpdateVertexBuffer_(void)
{
	float3 positions[4] =
	{
		float3(-size_._x * (anchor_point_._x), size_._y * (anchor_point_._y),0.0f),
		float3(size_._x * (1.0f - anchor_point_._x), size_._y * (anchor_point_._y),0.0f),
		float3(-size_._x * (anchor_point_._x),-size_._y * (1.0f - anchor_point_._y),0.0f),
		float3(size_._x * (1.0f - anchor_point_._x),-size_._y * (1.0f - anchor_point_._y),0.0f),
	};

	float2 texcoords[4] =
	{
		float2(texcoord_._left,texcoord_._top),
		float2(texcoord_._right,texcoord_._top),
		float2(texcoord_._left,texcoord_._bottom),
		float2(texcoord_._right,texcoord_._bottom),
	};

	VERTEX* vertex = nullptr;

	direct3dvertexbuffer9_->Lock(0,0,(void**)&vertex,0);

	for(u32 i = 0;i < 4;++i)
	{
		vertex[i]._position = positions[i];
		vertex[i]._texcoord = texcoords[i];
		vertex[i]._normal = float3(0.0f,0.0f,-1.0f);
		vertex[i]._color = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	}

	direct3dvertexbuffer9_->Unlock();
}

} // namespace mesh

	//---------------------------------- EOF --------------------------------------
