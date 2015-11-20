//*****************************************************************************
//
// defferd
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//=============================================================================
// 
//=============================================================================
struct IN_VERTEX
{
	float3 position	: POSITION0;
	float2 texcoord : TEXCOORD0;
};

//=============================================================================
// 
//=============================================================================
struct OUT_VERTEX
{
	float4 position : POSITION;
	float2 texcoord : TEXCOORD0;
};

float4x4 _world_matrix;
float4x4 _view_matrix;
float4x4 _projection_matrix;

//=============================================================================
// deferred
//=============================================================================
OUT_VERTEX Deferred(IN_VERTEX in_vertex,float4x4 in_world_view_projection_matrix)
{
	OUT_VERTEX out_vertex;

	out_vertex.position = mul(float4(in_vertex.position,1.0f),in_world_view_projection_matrix);
	out_vertex.texcoord = in_vertex.texcoord;

	return out_vertex;
}

OUT_VERTEX main(IN_VERTEX in_vertex)
{
	OUT_VERTEX out_vertex;

	float4x4 wvp;
	wvp = mul(mul(_world_matrix,_view_matrix),_projection_matrix);

	out_vertex = Deferred(in_vertex,wvp);

	return out_vertex;
}

//---------------------------------- EOF --------------------------------------
