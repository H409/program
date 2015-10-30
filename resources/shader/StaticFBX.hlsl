float4x4 world :register(c0);
float4x4 view :register(c4);
float4x4 projection:register(c8);

float4 mat_diffuse:register(c12);
float4 mat_ambient:register(c13);
float4 mat_emissive:register(c14);
float4 mat_speculer:register(c15);

float3 light_directional:register(c16);

struct VS_IN{
	float3	pos:SV_POSITION;
	float3	nor : NORMAL;
	float2	uv :TEXCOORD0;
	float4	col : COLOR0;
};

struct VS_OUT{
	float4 pos		: SV_POSITION;
	float4 col		: COLOR0;
	float2 tex_uv	: TEXCOORD0;
	float2 toon_uv	: TEXCOORD1;
};

// ’¸“_¼ª°ÀŞ°
VS_OUT vs_main(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;
	Out.pos = mul(float4(In.pos, 1.0f), world);
	Out.pos = mul(Out.pos, view);
	Out.pos = mul(Out.pos, projection);

	// –@ü‚ÌŒvZ
	float4 wNormal = mul(float4(In.nor, 0.0f), world);

	// Ã¸½Á¬UV‚Í‚»‚Ì‚Ü‚Ü
	Out.tex_uv = In.uv;

	// Ä©°İUV‚ÌŒvZ
	Out.toon_uv.x = -dot(wNormal, light_directional)*0.5f + 0.5f;
	Out.toon_uv.y = 0.0f;

	// Fî•ñ‚Í255‚Å“ü‚Á‚Ä‚¢‚é‚Ì‚Å³‹K‰»‚µ‚Ä“]‘—
	Out.col = (In.col / 255.0f) * mat_diffuse;
	return Out;
}

sampler tex_sumpler:register(s0);
sampler toon_sumpler:register(s1);

// Ëß¸¾Ù¼ª°ÀŞ°
float4 ps_main(VS_OUT In) : SV_TARGET
{
	return In.col * tex2D(tex_sumpler, In.tex_uv) * tex2D(toon_sumpler, In.toon_uv);
}