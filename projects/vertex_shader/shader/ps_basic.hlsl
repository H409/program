sampler _texture_sampler;

float4 PS(in float2 uv : TEXCOORD0) : COLOR0
{
	float4 texture_color = tex2D(_texture_sampler,uv);

	//return float4(1.0f,0.0f,0.0f,1.0f);
	return texture_color;
}
