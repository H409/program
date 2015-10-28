//==============================================================================
//
// 雲シェーダー
// Author : syuki nishida
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// struct definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// 頂点シェーダ入力
//------------------------------------------------
struct VertexShaderInput {
  float3 position    : POSITION0;
  float3 normal      : NORMAL0;
  float2 texcoord    : TEXCOORD0;
  float4 w_mtx1      : TEXCOORD1;
  float4 w_mtx2      : TEXCOORD2;
  float4 w_mtx3      : TEXCOORD3;
  float4 w_mtx4      : TEXCOORD4;
};

//------------------------------------------------
// 頂点シェーダ出力
//------------------------------------------------
struct VertexShaderOutput {
  float4 position    : POSITION;
  float3 normal      : TEXCOORD1;
  float2 texcoord    : TEXCOORD0;
};

//------------------------------------------------
// ピクセルシェーダ出力
//------------------------------------------------
struct PixelShaderOutput {
  float4 render_target0 : COLOR0;
  float4 render_target1 : COLOR1;
  float4 render_target2 : COLOR2;
  float4 render_target3 : COLOR3;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// global-variable definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
float4x4 uniform_matrix_view_projection;
float4 uniform_vector_light_direction;
float4 uniform_ambient = float4(0.2f, 0.2f, 0.2f, 1.0f);
float4 uniform_diffuse_material = float4(1.0f, 1.0f, 1.0f, 1.0f);

texture uniform_map_diffuse;
// テクスチャサンプラー
sampler diffuse_sampler = sampler_state {
  Texture = <uniform_map_diffuse>;
  MinFilter = ANISOTROPIC;
  MagFilter = LINEAR;
  MipFilter = LINEAR;
  MaxAnisotropy = 16;
  AddressU = WRAP;
  AddressV = WRAP;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// VS implementation
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
VertexShaderOutput VS(VertexShaderInput vertex_shader_input) {

  // 出力データの用意
  VertexShaderOutput outData = (VertexShaderOutput)0;

  // 座標変換
  float4x4 w_mtx = (float4x4)0;

  w_mtx._11 = vertex_shader_input.w_mtx1.x;
  w_mtx._12 = vertex_shader_input.w_mtx1.y;
  w_mtx._13 = vertex_shader_input.w_mtx1.z;
  w_mtx._14 = vertex_shader_input.w_mtx1.w;
  w_mtx._21 = vertex_shader_input.w_mtx2.x;
  w_mtx._22 = vertex_shader_input.w_mtx2.y;
  w_mtx._23 = vertex_shader_input.w_mtx2.z;
  w_mtx._24 = vertex_shader_input.w_mtx2.w;
  w_mtx._31 = vertex_shader_input.w_mtx3.x;
  w_mtx._32 = vertex_shader_input.w_mtx3.y;
  w_mtx._33 = vertex_shader_input.w_mtx3.z;
  w_mtx._34 = vertex_shader_input.w_mtx3.w;
  w_mtx._41 = vertex_shader_input.w_mtx4.x;
  w_mtx._42 = vertex_shader_input.w_mtx4.y;
  w_mtx._43 = vertex_shader_input.w_mtx4.z;
  w_mtx._44 = vertex_shader_input.w_mtx4.w;

  float4x4 wvp = mul(w_mtx, uniform_matrix_view_projection);
  outData.position = mul(float4(vertex_shader_input.position, 1.0f),wvp);

  outData.normal = vertex_shader_input.normal;

  outData.texcoord = vertex_shader_input.texcoord;

  return outData;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PS implementation
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PixelShaderOutput PS(VertexShaderOutput vertex_shader_output) {
  PixelShaderOutput output = (PixelShaderOutput)0;

  output.render_target0 = tex2D(diffuse_sampler, vertex_shader_output.texcoord);
  output.render_target1.xyz = vertex_shader_output.normal.xyz;
  output.render_target1.w = 1.0f;

  output.render_target3 = 
    tex2D(diffuse_sampler, vertex_shader_output.texcoord);

  return output;
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// technique definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
technique Techniques {
  pass P0 {
    VertexShader = compile vs_2_0 VS();
    PixelShader = compile ps_2_0 PS();
  }
}
// EOF