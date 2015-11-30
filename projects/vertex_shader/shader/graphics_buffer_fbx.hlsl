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

struct IN_VS{
	float3	pos :SV_POSITION;
	float3	nor : NORMAL;
	float2	uv :TEXCOORD0;
	float4	col : COLOR0;
	float4	blend:BLENDWEIGHT;
	int4	idx : BLENDINDICES;
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

float4x4 _world_matrix:register(c0);
float4x4 _view_matrix:register(c4);
float4x4 _projection_matrix:register(c8);
float4x4 bone[50]:register(c18);


OUT_VERTEX main(IN_VS in_vertex)
{
	OUT_VERTEX out_vertex = ( OUT_VERTEX )1 ;

	// Ω∑∆›∏ﬁópç¿ïWïœä∑
	float w[ 4 ] = ( float[ 4 ] )in_vertex.blend ;

	float last_blend_weight = 0.0f ;
	float4x4 comb = ( float4x4 )0 ;

	for( int i = 0 ; i < 3 ; i++ )
	{
		last_blend_weight += w[ i ];
		comb += bone[ in_vertex.idx[ i ] ] * w[ i ];
	}

	comb += bone[ in_vertex.idx[ 3 ] ] * ( 1.0f - last_blend_weight );
	out_vertex.position = mul( float4( in_vertex.pos , 1.0f ) , comb );
	out_vertex.position = mul( out_vertex.position , _view_matrix );
	out_vertex.position = mul( out_vertex.position , _projection_matrix );

	out_vertex.texcoord = in_vertex.uv;
	out_vertex.normal_depth.xyz = mul( float4( in_vertex.nor ,0.0f ) , comb ).xyz ;
	out_vertex.normal_depth.w = out_vertex.position.z / out_vertex.position.w ;
	//out_vertex.color = in_vertex.col ;
	out_vertex.world_position.xyzw = mul( float4( in_vertex.pos , 1.0f ) , _world_matrix );

	return out_vertex;
}


	//VS_OUT Out = (VS_OUT)0;

	//// Ω∑∆›∏ﬁópç¿ïWïœä∑
	//float w[4] = (float[4])In.blend;

	//float last_blend_weight = 0.0f;
	//float4x4 comb = (float4x4)0;

	//for (int i = 0; i < 3; i++)
	//{
	//	last_blend_weight += w[i];
	//	comb += bone[In.idx[i]] * w[i];
	//}

	//comb += bone[In.idx[3]] * (1.0f - last_blend_weight);
	//Out.pos = mul(float4(In.pos, 1.0f), comb);
	////Out.pos = mul(float4(In.pos, 1.0f), world);
	//Out.pos = mul(Out.pos, view);
	//Out.pos = mul(Out.pos, projection);

	//// ñ@ê¸ÇÃåvéZ
	//float4 wNormal = mul(float4(In.nor, 0.0f), comb);

	//// √∏Ω¡¨UVÇÕÇªÇÃÇ‹Ç‹
	//Out.tex_uv = In.uv;

	//// ƒ©∞›UVÇÃåvéZ
	//Out.toon_uv.x = -dot(wNormal, light_directional)*0.5f + 0.5f;
	//Out.toon_uv.y = 0.0f;

	//// êFèÓïÒÇÕ255Ç≈ì¸Ç¡ÇƒÇ¢ÇÈÇÃÇ≈ê≥ãKâªÇµÇƒì]ëó
	//Out.col = (In.col / 255.0f) * mat_diffuse;
	//return Out;
//---------------------------------- EOF --------------------------------------
