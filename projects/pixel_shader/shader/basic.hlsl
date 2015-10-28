//*****************************************************************************
//
// basic
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include
//*****************************************************************************
#include "basic_format.hlsl"

//=============================================================================
// constant table
//=============================================================================
sampler _texture_sampler;

//=============================================================================
// pixel shader
//=============================================================================
BASIC_OUT_PIXEL main(BASIC_IN_PIXEL in_pixel)
{
	return Basic(in_pixel,_texture_sampler);
}

//---------------------------------- EOF --------------------------------------
