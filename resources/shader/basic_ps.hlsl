//*****************************************************************************
//
// basic
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

struct IN_PIXEL
{
	float4 color	: COLOR0;
	float2 texcoord	: TEXCOORD;
};

texture _texture;

sampler _texture_sampler = sampler_state
{
	Texture = <_texture>;
	MinFilter = ANISOTROPIC;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 16;
	AddressU = WRAP;
	AddressV = WRAP;
};

//=============================================================================
// pixel shader
//=============================================================================
float4 main(IN_PIXEL in_pixel) : COLOR0
{
	float4 texture_color = tex2D(_texture_sampler,in_pixel.texcoord);

	return float4(0.0f,0.0f,1.0f,1.0f);//texture_color * in_pixel.color;
}

//---------------------------------- EOF --------------------------------------
