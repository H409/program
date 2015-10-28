#include "mesh_buffer.h"
#include "mesh_buffer.h"
#include "mesh_buffer.h"
//*****************************************************************************
//
// mesh buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "mesh_buffer.h"
#include "mesh_format.h"

namespace render {
namespace mesh {
//=============================================================================
// constructor
//=============================================================================
MeshBuffer::MeshBuffer(const TElements& in_elements,const u32& in_count)
	:buffer_(nullptr)
	,count_(in_count)
{
	stride_ = 0;

	elements_.reserve(in_elements.size());

	for(auto format : in_elements)
	{
		stride_ += format._byte_size;
		elements_.push_back(format);
	}

	size_ = stride_ * in_count;

	buffer_ = new u8[size_];
}

//=============================================================================
// destructor
//=============================================================================
MeshBuffer::~MeshBuffer(void)
{
	SafeDeleteArray(buffer_);
}

//=============================================================================
// set buffer
//=============================================================================
void MeshBuffer::SetBuffer(const void* in_buffer,const u32& in_offset,const u32& in_byte_count)
{
	DEBUG_ASSERT(size_ >= in_offset + in_byte_count);
	memcpy(buffer_ + in_offset,in_buffer,in_byte_count);
}

//=============================================================================
// set buffer
//=============================================================================
void MeshBuffer::SetBuffer(const TElement& in_element,const void* in_buffer,const u32& in_buffer_offset,const u32& in_buffer_stride)
{
	u32 offset = 0;

	for(auto element : elements_)
	{
		if(element == in_element)
		{
			for(u32 i = 0;i < count_;++i)
			{
				memcpy(&buffer_[i * stride_ + offset],&((u8*)in_buffer)[i * in_buffer_stride + in_buffer_offset],element._byte_size);
			}

			return;
		}
		offset += element._byte_size;
	}
}

//=============================================================================
// get buffer
//=============================================================================
const void * MeshBuffer::GetBuffer(void)const
{
	return buffer_;
}

//=============================================================================
// get formats
//=============================================================================
const MeshBuffer::TElements& MeshBuffer::GetElements(void)const
{
	return elements_;
}

//=============================================================================
// get size
//=============================================================================
const u32& MeshBuffer::GetSize(void)const
{
	return size_;
}

//=============================================================================
// get stride
//=============================================================================
const u32 & MeshBuffer::GetStride(void)const
{
	return stride_;
}

//=============================================================================
// convert
//=============================================================================
MeshBuffer* MeshBuffer::Convert(const TElements& in_elements)
{
	auto mesh_buffer = new MeshBuffer(in_elements,count_);

	for(auto element : in_elements)
	{
		auto buffer = GetBuffer_(element);

		if(buffer != nullptr)
		{
			SetBuffer(element,buffer,0,element._byte_size);
		}

		SafeDeleteArray(buffer);
	}

	return mesh_buffer;
}

//=============================================================================
// get buffer
//=============================================================================
void* MeshBuffer::GetBuffer_(const TElement& in_element)
{
	u32 offset = 0;

	for(auto element : elements_)
	{
		if(element == in_element)
		{
			auto buffer = new u8[in_element._byte_size * count_];

			for(u32 i = 0;i < count_;++i)
			{
				memcpy(&buffer[i * element._byte_size],&buffer_[i * stride_ + offset],element._byte_size);
			}
			return buffer;
		}
		offset += element._byte_size;
	}

	return nullptr;
}

} // namespace mesh
} // namespace render

	//---------------------------------- EOF --------------------------------------
