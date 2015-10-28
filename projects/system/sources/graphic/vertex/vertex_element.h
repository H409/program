//*****************************************************************************
//
// vertex element
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _VERTEX_ELEMENT_H_
#define _VERTEX_ELEMENT_H_

//*****************************************************************************
// include
//*****************************************************************************
#include "base/base.h"

//*****************************************************************************
// class definition
//*****************************************************************************
namespace graphic
{
namespace vertex
{
struct VERTEX_ELEMENT
{
	enum class TYPE
	{
		NONE = -1,
		FLOAT1,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		D3DCOLOR,
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

	u32 _stream;
	u32 _offset;
	TYPE _type;
	USAGE _usage;
	u32 _usage_index;
};
} // namespace vertex
} // namespace graphic

#endif // _VERTEX_DECLARATION_H_

//---------------------------------- EOF --------------------------------------

