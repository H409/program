//*****************************************************************************
//
// instancing
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// structure definition
//*****************************************************************************
struct IN_VERTEX
{
	float3 position	: POSITION0;
	float3 normal	: NORMAL0;
	float2 texcoord	: TEXCOORD0;
	float4 world0 : TEXCOORD1;
	float4 world1 : TEXCOORD2;
	float4 world2 : TEXCOORD3;
	float4 world3 : TEXCOORD4;
};

struct IN_PIXEL
{
	float4 color	: COLOR0;
	float2 texcoord	: TEXCOORD0;
};

struct OUT_VERTEX
{
	float4 position	: POSITION;
	IN_PIXEL pixel;
};

//*****************************************************************************
// constant table
//*****************************************************************************
float4x4 _world_matrix;
float4x4 _view_matrix;
float4x4 _projection_matrix;
float4 _color = float4(1.0f,1.0f,1.0f,1.0f);
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
// vertex shader
//=============================================================================
OUT_VERTEX VS(IN_VERTEX in_vertex)
{
	OUT_VERTEX out_vertex;

	float4x4 wvp;
	float4x4 world_matrix = float4x4(in_vertex.world0,in_vertex.world1,in_vertex.world2,in_vertex.world3);
	wvp = mul(mul(world_matrix,_view_matrix),_projection_matrix);
	out_vertex.position = mul(float4(in_vertex.position,1.0f),wvp);
	out_vertex.pixel.texcoord = in_vertex.texcoord;
	out_vertex.pixel.color = _color;

	return out_vertex;
}

//=============================================================================
// pixel shader
//=============================================================================
float4 PS(IN_PIXEL in_pixel) : COLOR0
{
	float4 texture_color = tex2D(_texture_sampler,in_pixel.texcoord);

	return float4(1.0f,0.0f,0.0f,1.0f);
}

//=============================================================================
// technique
//=============================================================================
technique Techniques
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
}

//---------------------------------- EOF --------------------------------------
