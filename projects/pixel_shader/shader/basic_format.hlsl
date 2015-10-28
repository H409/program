//*****************************************************************************
//
// basic
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//=============================================================================
// structure declaration
//=============================================================================
struct BASIC_IN_PIXEL
{
	float4 color	: COLOR0;
	float2 texcoord	: TEXCOORD;
};

struct BASIC_OUT_PIXEL
{
	float4 color0 : COLOR0;
};

//=============================================================================
// basic
//=============================================================================
BASIC_OUT_PIXEL Basic(BASIC_IN_PIXEL in_basic_in_pixel,sampler texture_sampler)
{
	BASIC_OUT_PIXEL basic_out_pixel;

	basic_out_pixel.color0 = tex2D(texture_sampler,in_basic_in_pixel.texcoord) *in_basic_in_pixel.color;

	return basic_out_pixel;
}

//---------------------------------- EOF --------------------------------------
