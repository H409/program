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
	float3 position : POSITION0;
	float3 normal : NORMAL0;
	float2 texcoord : TEXCOORD0;
	float4 world0 : TEXCOORD1;
	float4 world1 : TEXCOORD2;
	float4 world2 : TEXCOORD3;
	float4 world3 : TEXCOORD4;
	float2 index : TEXCOORD5;
	float2 offset : TEXCOORD6;
};

struct OUT_INSTANCING
{
	float4 position;
	float2 texcoord;
};

//*****************************************************************************
// constant table
//*****************************************************************************
float4x4 _view_matrix;
float4x4 _projection_matrix;
float4 _color = float4(1.0f,1.0f,1.0f,1.0f);

//=============================================================================
// vertex shader
//=============================================================================
OUT_INSTANCING Instancing(IN_VERTEX in_vertex,float4x4 view_matrix,float4x4 projection_matrix)
{
	OUT_INSTANCING out_param;

	float4x4 wvp;
	float4x4 world_matrix = float4x4(in_vertex.world0,in_vertex.world1,in_vertex.world2,in_vertex.world3);
	wvp = mul(mul(world_matrix,view_matrix),projection_matrix);
	out_param.position = mul(float4(in_vertex.position,1.0f),wvp);
	out_param.texcoord = in_vertex.texcoord;

	return out_param;
}

//---------------------------------- EOF --------------------------------------
