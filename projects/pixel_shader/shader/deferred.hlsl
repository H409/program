//*****************************************************************************
//
// defferd
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// structure declaration
//*****************************************************************************
struct IN_PIXEL
{
	float2 texcoord : TEXCOORD0;
};

struct OUT_PIXEL
{
	float4 color : COLOR0;
};

float3 _light_vector;
float3 _light_deffuse;

sampler _color_sampler;
sampler _normal_sampler;
sampler _position_sampler;

OUT_PIXEL main(IN_PIXEL in_pixel)
{
	OUT_PIXEL out_pixel;

	float4 color = tex2D(_color_sampler,in_pixel.texcoord);
	float4 normal_depth = tex2D(_normal_sampler,in_pixel.texcoord);
	float4 position = tex2D(_position_sampler,in_pixel.texcoord);

	// light
	float light;
	float3 light_vector = normalize(_light_vector);
	light = max(-dot(normal_depth.xyz,light_vector),0.0f);
	light = light * 0.5f + 0.5f;
	float3 light_color = _light_deffuse * light;
	//light_color = float3(1.0f,1.0f,1.0f);

//<<<<<<< HEAD
	//out_pixel.color = float4(0.0f,1.0f,0.0f, 1.0f);
	out_pixel.color = float4(normal_depth.xyz, 1.0f);
	out_pixel.color = float4(light_color.rgb * color.rgb,1.0f);
//=======
//	out_pixel.color = float4(light_color.rgb * color.rgb,1.0f);
	out_pixel.color = float4(color.rgb,1.0f);
//>>>>>>> 808aa2ac0b5bf515e2c9503b52f80804ac50d856

	return out_pixel;
}

//---------------------------------- EOF --------------------------------------
