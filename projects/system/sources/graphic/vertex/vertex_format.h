//*****************************************************************************
//
// vertex format
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _VERTEX_FORMAT_H_
#define _VERTEX_FORMAT_H_

namespace graphic
{
namespace vertex
{
//*****************************************************************************
// 
//*****************************************************************************
enum class FORMAT
{
	NONE			= 0x0000,
	POSITION	= 0x0001,
	NORMAL		= 0x0002,
	COLOR			= 0x0004,
	TEXCOORD0	= 0x0008,
	TEXCOORD1	= 0x0010,
	TEXCOORD2	= 0x0020,
	TEXCOORD3	= 0x0040,
	TEXCOORD4	= 0x0080,
};
} // namespace vertex
} // namespace graphic
#endif // _VERTEX_FORMAT_H_

//---------------------------------- EOF --------------------------------------