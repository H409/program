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
	float2 texcoord	: TEXCOORD0;
};

struct OUT_VERTEX
{
	float4 position	: POSITION;
	float4 color	: COLOR0;
	float2 texcoord	: TEXCOORD0;
};

//*****************************************************************************
// constant table
//*****************************************************************************
float4x4 _world_matrix;
float4x4 _view_matrix;
float4x4 _projection_matrix;
float4 _color = float4(1.0f,1.0f,1.0f,1.0f);

//=============================================================================
// vertex shader
//=============================================================================
OUT_VERTEX main(IN_VERTEX in_vertex)
{
	OUT_VERTEX out_vertex;

	float4x4 wvp;
	wvp = mul(mul(_world_matrix,_view_matrix),_projection_matrix);
	out_vertex.position = mul(float4(in_vertex.position,1.0f),wvp);
	out_vertex.texcoord = in_vertex.texcoord;
	out_vertex.color = _color;

	return out_vertex;
}

//---------------------------------- EOF --------------------------------------
