//*****************************************************************************
//
// mesh cylinder
//
// Author		: Eyuu Yuminaga
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include"mesh_cylinder.h"
#include "system/win_system.h"

namespace mesh {
	//*****************************************************************************
	// constant definition
	//*****************************************************************************
	const D3DCOLOR MeshCylinder::DEFAULT_COLOR = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	const D3DXVECTOR2 MeshCylinder::DEFAULT_POSITION = D3DXVECTOR2(0.0f, 0.0f);

	//=============================================================================
	// constructor
	//=============================================================================
	MeshCylinder::MeshCylinder(const u32& in_width_count, const u32& in_height_count)
		:MeshCylinder(1.0f, 1.0f, in_width_count, in_height_count)
	{
	}

	//=============================================================================
	// constructor
	//=============================================================================
	MeshCylinder::MeshCylinder(const f32& in_block_width, const f32& in_block_height, const u32& in_width_count, const u32& in_height_count)
		:Mesh(true, true)
		, size_(in_width_count * in_block_width, in_height_count *in_block_height)
		, block_size_(in_block_width, in_block_height)
		, width_count_(in_width_count)
		, height_count_(in_height_count)
		, index_count_(0)
		, indexs_(nullptr)
		, division_width_(1)
		, division_height_(1)
	{
		auto directx9 = GET_DIRECTX9_DEVICE();

		vertex_count_ = 4 * width_count_*height_count_;
		index_count_ = 4 * width_count_*height_count_ + 2 * (width_count_ - 1)*height_count_ + 2 * (height_count_ - 1);
		indexs_ = new u32[width_count_*height_count_];
		memset(indexs_, 0, sizeof(u32)*width_count_*height_count_);

		// create vertex buffer
		directx9->CreateVertexBuffer(sizeof(VERTEX) * vertex_count_, D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &direct3dvertexbuffer9_, NULL);

		// create index buffer
		directx9->CreateIndexBuffer(sizeof(u32) * index_count_, D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &direct3dindexbuffer9_, NULL);

		division_height_ = 10;

		u32* index = nullptr;
		u32 rect_count = vertex_count_ / 4;

		u32 count = 0;

		direct3dindexbuffer9_->Lock(NULL, NULL, (void**)&index, NULL);

		for (u32 i = 0; i < height_count_; ++i)
		{
			for (u32 j = 0; j < width_count_; ++j)
			{
				index[count + 0] = (i * width_count_ + j) * 4 + 0;
				index[count + 1] = (i * width_count_ + j) * 4 + 1;
				index[count + 2] = (i * width_count_ + j) * 4 + 2;
				index[count + 3] = (i * width_count_ + j) * 4 + 3;

				count += 4;

				if (j != (width_count_ - 1))
				{
					index[count + 0] = (i * width_count_ + j) * 4 + 3;
					index[count + 1] = (i * width_count_ + j) * 4 + 4;
					count += 2;
				}
				else if (i != (height_count_ - 1))
				{
					index[count + 0] = (i * width_count_ + j) * 4 + 3;
					index[count + 1] = ((i + 1) * width_count_) * 4 + 0;
					count += 2;
				}
			}
		}

		direct3dindexbuffer9_->Unlock();

		primitive_count_ = index_count_ - 2;
		primitive_type_ = D3DPT_TRIANGLESTRIP;
		stride_ = sizeof(VERTEX);

		UpdateVertexBuffer_();
	}
	//=============================================================================
	// destructor
	//=============================================================================
	MeshCylinder::~MeshCylinder(void)
	{
		//relase vertex buffer
		SafeRelease(direct3dvertexbuffer9_);
		SafeRelease(direct3dindexbuffer9_);
		SafeDeleteArray(indexs_);
	}
	//=============================================================================
	// set index
	//=============================================================================
	void MeshCylinder::SetIndex(u32 x, u32 y, u32 index)
	{
		indexs_[y * width_count_ + x] = index;
		is_dirty_ = true;
	}

	//=============================================================================
	// set index
	//=============================================================================
	void MeshCylinder::SetIndex(const std::vector<u32>& in_indexs)
	{
		DEBUG_ASSERT(in_indexs.size() == width_count_ * height_count_);

		auto size = width_count_ * height_count_;

		for (u32 i = 0; i < size; ++i)
		{
			indexs_[i] = in_indexs[i];
		}
		is_dirty_ = true;
	}

	//=============================================================================
	// set color
	//=============================================================================

	//=============================================================================
	// set texcoord
	//=============================================================================
	void MeshCylinder::SetTexcoord(u32 in_division_width, u32 in_division_height)
	{
		division_width_ = in_division_width;
		division_height_ = in_division_height;
		is_dirty_ = true;
	}

	//=============================================================================
	// update vertex buffer
	//=============================================================================
	void MeshCylinder::UpdateVertexBuffer_(void)
	{
		VERTEX* vertex = nullptr;
		float2 offset = float2(-size_._x * anchor_point_._x, size_._y * anchor_point_._y);

		//ƒVƒŠƒ“ƒ_[‚Ì”¼Œa
		float cylinderradius = size_._x / D3DX_PI / 2;
		//–Êˆê–‡‚²‚Æ‚ÌŠp“x(X)
		float faceangle_x = (D3DX_PI * 2) / width_count_;
		//–Êˆê–‡‚²‚Æ‚ÌŠp“x(Y)
		float faceangle_y = (D3DX_PI * 2) / height_count_;

		// lock
		direct3dvertexbuffer9_->Lock(0, 0, (void**)&vertex, 0);

		for (int i = 0; i < height_count_; ++i)
		{

			for (int j = 0; j < width_count_; ++j)
			{
				/*float left = 1.0f / division_width_  * ((indexs_[i * width_count_ + j] % division_width_) + 0);
				float right = 1.0f / division_width_  * ((indexs_[i * width_count_ + j] % division_width_) + 1);
				float top = 1.0f / division_height_ * ((indexs_[i * width_count_ + j] / division_width_) + 0);
				float bottom = 1.0f / division_height_ * ((indexs_[i * width_count_ + j] / division_width_) + 1);*/

				float left = (1.0f / width_count_)*j;
				float right = (1.0f / width_count_)*j + (1.0f / width_count_);
				float top = 1.0f / division_height_ * ((indexs_[i * width_count_ + j] / division_width_) + 1);
				float bottom = 1.0f / division_height_ * ((indexs_[i * width_count_ + j] / division_width_) + 0);
				
				vertex[(i * width_count_ + j) * 4 + 0]._position = float3(-(cosf(faceangle_x*(-j - 0)))*cylinderradius, (-block_size_._y*(-i - 1)),(sinf(faceangle_x*(-j - 0)))*cylinderradius);
				vertex[(i * width_count_ + j) * 4 + 1]._position = float3(-(cosf(faceangle_x*(-j - 0)))*cylinderradius, (-block_size_._y*(-i - 0)),(sinf(faceangle_x*(-j - 0)))*cylinderradius);
				vertex[(i * width_count_ + j) * 4 + 2]._position = float3(-(cosf(faceangle_x*(-j - 1)))*cylinderradius, (-block_size_._y*(-i - 1)),(sinf(faceangle_x*(-j - 1)))*cylinderradius);
				vertex[(i * width_count_ + j) * 4 + 3]._position = float3(-(cosf(faceangle_x*(-j - 1)))*cylinderradius, (-block_size_._y*(-i - 0)),(sinf(faceangle_x*(-j - 1)))*cylinderradius);

				vertex[(i * width_count_ + j) * 4 + 0]._normal = float3(0.0f, 1.0f, 0.0f);
				vertex[(i * width_count_ + j) * 4 + 1]._normal = float3(0.0f, 1.0f, 0.0f);
				vertex[(i * width_count_ + j) * 4 + 2]._normal = float3(0.0f, 1.0f, 0.0f);
				vertex[(i * width_count_ + j) * 4 + 3]._normal = float3(0.0f, 1.0f, 0.0f);

				vertex[(i * width_count_ + j) * 4 + 0]._texcoord = float2(left, bottom);
				vertex[(i * width_count_ + j) * 4 + 1]._texcoord = float2(left, top);
				vertex[(i * width_count_ + j) * 4 + 2]._texcoord = float2(right, bottom);
				vertex[(i * width_count_ + j) * 4 + 3]._texcoord = float2(right, top);

				vertex[(i * width_count_ + j) * 4 + 0]._color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[(i * width_count_ + j) * 4 + 1]._color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[(i * width_count_ + j) * 4 + 2]._color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[(i * width_count_ + j) * 4 + 3]._color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}

		// unlock
		direct3dvertexbuffer9_->Unlock();
	}
} //namespace mesh