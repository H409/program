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
	float3 normal : NORMAL0;
	float2 texcoord : TEXCOORD0;
	float4 color : COLOR0;
};

//=============================================================================
// 
//=============================================================================
struct OUT_VERTEX
{
	float4 position : POSITION;
	float4 normal_depth : NORMAL0;
	float2 texcoord : TEXCOORD0;
	float4 color : COLOR0;
	float4 world_position : TEXCOORD1;
};

float4x4 _world_matrix;
float4x4 _view_matrix;
float4x4 _projection_matrix;

//=============================================================================
// deferred
//=============================================================================
OUT_VERTEX Deferred(IN_VERTEX in_vertex,float4x4 in_world_matrix,float4x4 in_world_view_projection_matrix)
{
	OUT_VERTEX out_vertex;

	out_vertex.position = mul(float4(in_vertex.position,1.0f),in_world_view_projection_matrix);
	out_vertex.texcoord = in_vertex.texcoord;
	out_vertex.normal_depth.xyz = mul(float4(in_vertex.normal,0.0f),in_world_matrix).xyz;
	out_vertex.normal_depth.w = out_vertex.position.z / out_vertex.position.w;
	out_vertex.world_position.xyzw = mul(float4(in_vertex.position,1.0f),in_world_matrix);
	out_vertex.color = in_vertex.color;

	return out_vertex;
}

OUT_VERTEX main(IN_VERTEX in_vertex)
{
	OUT_VERTEX out_vertex;

	float4x4 wvp;
	wvp = mul(mul(_world_matrix,_view_matrix),_projection_matrix);

	out_vertex = Deferred(in_vertex,_world_matrix,wvp);

	return out_vertex;
}

//---------------------------------- EOF --------------------------------------
