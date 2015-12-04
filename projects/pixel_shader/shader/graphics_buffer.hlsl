//*****************************************************************************
//
// graphics buffer
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// structure declaration
//*****************************************************************************
struct IN_PIXEL
{
	float4 normal_depth : NORMAL0;
	float2 texcoord : TEXCOORD0;
	float4 color : COLOR0;
	float4 world_position : TEXCOORD1;
};

struct OUT_PIXEL
{
	float4 color : COLOR0;
	float4 normal_depth : COLOR1;
	float4 position : COLOR2;
};

sampler _texture_sampler;

//=============================================================================
// graphics buffer
//=============================================================================
OUT_PIXEL GraphicsBuffer(IN_PIXEL in_pixel,sampler texture_sampler)
{
	OUT_PIXEL out_pixel;

	out_pixel.color = 0;
	out_pixel.normal_depth = 0;
	out_pixel.position = 0;

	out_pixel.color = in_pixel.color * tex2D(texture_sampler,in_pixel.texcoord);
	out_pixel.normal_depth = float4(normalize(in_pixel.normal_depth.xyz),1.0f);//in_pixel.normal_depth.w);
	out_pixel.position = in_pixel.world_position;

	return out_pixel;
}

OUT_PIXEL main(IN_PIXEL in_pixel)
{
	return GraphicsBuffer(in_pixel,_texture_sampler);
}

//---------------------------------- EOF --------------------------------------
