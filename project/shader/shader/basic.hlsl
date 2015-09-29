//*****************************************************************************
//
// basic
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
	float2 texcoord	: TEXCOORD;
};

struct OUT_VERTEX
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 texcoord	: TEXCOORD;
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
	wvp = mul(mul(_world_matrix,_view_matrix),_projection_matrix);
	out_vertex.position = mul(float4(in_vertex.position,1.0f),wvp);
	out_vertex.texcoord = in_vertex.texcoord;
	out_vertex.color = _color;

	return out_vertex;
}

//=============================================================================
// pixel shader
//=============================================================================
float4 PS(OUT_VERTEX out_vertex) : SV_TARGET
{
	float4 texture_color = tex2D(_texture_sampler,out_vertex.texcoord);

	return texture_color * out_vertex.color;
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
