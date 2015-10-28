//*****************************************************************************
//
// mesh format
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _MESH_FORMAT_H_
#define _MESH_FORMAT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/non_copyable.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace render {
namespace mesh {
struct ELEMENT
{
	enum class TYPE
	{
		NONE = -1,
		FLOAT1,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		COLOR,
		UBYTE4,
		SHORT2,
		SHORT4,
		UBYTE4N,
		SHORT2N,
		SHORT4N,
		USHORT2N,
		USHORT4N,
		UDEC3,
		DEC3N,
		FLOAT16_2,
		FLOAT16_4,
		UNUSED,
	};

	enum class USAGE
	{
		NONE = -1,
		POSITION,
		BLENDWEIGHT,
		BLENDINDICES,
		NORMAL,
		PSIZE,
		TEXCOORD,
		TANGENT,
		BINORMAL,
		TESSFACTOR,
		POSITIONT,
		COLOR,
		FOG,
		DEPTH,
		SAMPLE,
	};

	u32 _byte_size;
	TYPE _type;
	USAGE _usage;
	u32 _usage_index;

	//
	bool operator==(const ELEMENT& in_element)
	{
		if(_byte_size != in_element._byte_size)
		{
			return false;
		}
		if(_usage != in_element._usage)
		{
			return false;
		}

		if(_usage_index != in_element._usage_index)
		{
			return false;
		}

		return true;
	}
};

struct FORMAT
{
	enum class PRIMITIVE_TYPE
	{
		TRIANGLE_LIST,
	};

	PRIMITIVE_TYPE _primitive_type;
	std::vector<ELEMENT> _elements;
};

} // namespace mesh
} // namespace render

#endif // _BASE_MESH_H_

//---------------------------------- EOF --------------------------------------
