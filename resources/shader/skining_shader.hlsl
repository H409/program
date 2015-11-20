float4x4 world :register(c0);
float4x4 view :register(c4);
float4x4 projection:register(c8);

float4 mat_diffuse:register(c12);
float4 mat_ambient:register(c13);
float4 mat_emissive:register(c14);
float4 mat_speculer:register(c15);

float3 light_directional:register(c16);

float4x4 bone[50]:register(c18);

struct VS_IN{
	float3	pos:SV_POSITION;
	float3	nor : NORMAL;
	float2	uv :TEXCOORD0;
	float4	col : COLOR0;
	float4	blend:BLENDWEIGHT;
	int4	idx : BLENDINDICES;
};

struct VS_OUT{
	float4 pos		: SV_POSITION;
	float4 col		: COLOR0;
	float2 tex_uv	: TEXCOORD0;
	float2 toon_uv	: TEXCOORD1;
};

// í∏ì_º™∞¿ﬁ∞
VS_OUT vs_main(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	// Ω∑∆›∏ﬁópç¿ïWïœä∑
	float w[4] = (float[4])In.blend;

	float last_blend_weight = 0.0f;
	float4x4 comb = (float4x4)0;

	for (int i = 0; i < 3; i++)
	{
		last_blend_weight += w[i];
		comb += bone[In.idx[i]] * w[i];
	}

	comb += bone[In.idx[3]] * (1.0f - last_blend_weight);
	Out.pos = mul(float4(In.pos, 1.0f), comb);
	//Out.pos = mul(float4(In.pos, 1.0f), world);
	Out.pos = mul(Out.pos, view);
	Out.pos = mul(Out.pos, projection);

	// ñ@ê¸ÇÃåvéZ
	float4 wNormal = mul(float4(In.nor, 0.0f), comb);

	// √∏Ω¡¨UVÇÕÇªÇÃÇ‹Ç‹
	Out.tex_uv = In.uv;

	// ƒ©∞›UVÇÃåvéZ
	Out.toon_uv.x = -dot(wNormal, light_directional)*0.5f + 0.5f;
	Out.toon_uv.y = 0.0f;

	// êFèÓïÒÇÕ255Ç≈ì¸Ç¡ÇƒÇ¢ÇÈÇÃÇ≈ê≥ãKâªÇµÇƒì]ëó
	Out.col = (In.col / 255.0f) * mat_diffuse;
	return Out;
}



sampler tex_sumpler:register(s0);
sampler toon_sumpler:register(s1);

// Àﬂ∏æŸº™∞¿ﬁ∞
float4 ps_main(VS_OUT In) : SV_TARGET
{
	return float4( 0 , 1 , 0 , 1 );
	return In.col * tex2D(tex_sumpler, In.tex_uv) * tex2D(toon_sumpler,In.toon_uv);
}