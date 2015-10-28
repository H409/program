//*****************************************************************************
//
// mesh buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MESH_BUFFER_H_
#define _MESH_BUFFER_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"

//*****************************************************************************
// forward declaration
//*****************************************************************************
namespace render {
namespace mesh {
struct ELEMENT;
} // mesh
} // render

//*****************************************************************************
// class definition
//*****************************************************************************
namespace render {
namespace mesh {
class MeshBuffer : public utility::base::NonCopyable
{
public:
	using TElement = ELEMENT;
	using TElements = std::vector<TElement>;

	// constructor
	MeshBuffer(const TElements& in_elements,const u32& in_count);

	// destructor
	virtual ~MeshBuffer(void);

	// set buffer
	void SetBuffer(const void* in_buffer,const u32& in_offset,const u32& in_byte_count);
	void SetBuffer(const TElement& in_element,const void* in_buffer,const u32& in_buffer_offset,const u32& in_buffer_stride);

	// get buffer
	const void* GetBuffer(void)const;

	// get elements
	const TElements& GetElements(void)const;

	// get size
	const u32& GetSize(void)const;

	// get stride
	const u32& GetStride(void)const;

	// convert
	MeshBuffer* Convert(const TElements& in_elements);

private:
	u8* buffer_;
	u32 size_;
	u32 stride_;
	u32 count_;
	TElements elements_;

	// get buffer
	void* GetBuffer_(const TElement& in_element);
};

} // namespace mesh
} // namespace render

#endif // _BASE_MESH_H_

//---------------------------------- EOF --------------------------------------
