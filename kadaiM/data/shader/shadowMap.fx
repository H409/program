// -------------------------------------------------------------
// �V���h�E�}�b�v
// 
// Copyright (c) 2002-2003 IMAGIRE Takashi. All rights reserved.
// -------------------------------------------------------------

// -------------------------------------------------------------
// �O���[�o���ϐ�
// -------------------------------------------------------------
float4x4 mWVP;		// ���[�J������ˉe��Ԃւ̍��W�ϊ�
float4x4 mWLP;		// ���[�J������ˉe��Ԃւ̍��W�ϊ�
float4x4 mWLPB;		// �e�N�X�`�����W�n�ւ̎ˉe
float4   vCol;		// ���b�V���̐F
float4	 vLightDir;	// ���C�g�̕���

// -------------------------------------------------------------
// �e�N�X�`��
// -------------------------------------------------------------
texture ShadowMap;
sampler ShadowMapSamp = sampler_state
{
    Texture = <ShadowMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// -------------------------------------------------------------
texture DecaleMap;
sampler DecaleMapSamp = sampler_state
{
    Texture = <DecaleMap>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = NONE;

    AddressU = Clamp;
    AddressV = Clamp;
};
// -------------------------------------------------------------
// ���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
// -------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos			: POSITION;
	float4 Diffuse		: COLOR0;
	float4 Ambient		: COLOR1;
	float4 ShadowMapUV	: TEXCOORD0;
	float4 Depth		: TEXCOORD1;
	float2 DecaleTex	: TEXCOORD2;
};

// -------------------------------------------------------------
// 1�p�X�ځF���_�V�F�[�_�v���O����
// -------------------------------------------------------------
VS_OUTPUT VS_pass0(
      float4 Pos    : POSITION,          // ���f���̒��_
      float3 Normal : NORMAL	         // ���f���̖@��
){
    VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^
    
    // ���W�ϊ�
	float4 pos = mul( Pos, mWLP );
	
    // �ʒu���W
    Out.Pos = pos;
    
    // �J�������W�n�ł̐[�x���e�N�X�`���ɓ����
    Out.ShadowMapUV = pos;

    return Out;
}
// -------------------------------------------------------------
// 1�p�X�ځF�s�N�Z���V�F�[�_�v���O����
// -------------------------------------------------------------
float4 PS_pass0(VS_OUTPUT In) : COLOR
{   
    float4 Out;
    
    Out = In.ShadowMapUV.z / In.ShadowMapUV.w;
    Out.a = 1;
    return Out;
}
// -------------------------------------------------------------
// ���_�V�F�[�_�v���O����
// -------------------------------------------------------------
VS_OUTPUT VS(
      float4 Pos    : POSITION,          // ���f���̒��_
      float3 Normal : NORMAL,	         // ���f���̖@��
      float2 Tex    : TEXCOORD0	         // �e�N�X�`�����W
){
    VS_OUTPUT Out = (VS_OUTPUT)0;        // �o�̓f�[�^
	float4	uv;
	
	// ���W�ϊ�
    Out.Pos = mul(Pos, mWVP);
	// �F
	Out.Diffuse = vCol * max( dot(vLightDir, Normal), 0);// �g�U�F
	Out.Ambient = vCol * 0.3f;						     // ���F
	
	// �V���h�E�}�b�v
	Out.ShadowMapUV = mul(Pos, mWLPB);
	
	// ��r�̂��߂̐[�x�l
	Out.Depth       = mul(Pos, mWLP);
		
	// �f�J�[���e�N�X�`��
	Out.DecaleTex   = Tex;
		
    return Out;
}
// -------------------------------------------------------------
// 2�p�X�ځF�s�N�Z���V�F�[�_�v���O���� (�e�N�X�`������)
// -------------------------------------------------------------
float4 PS_pass1(VS_OUTPUT In) : COLOR
{   
    float4 Color;
	float  shadow = tex2Dproj( ShadowMapSamp, In.ShadowMapUV ).x;
	float4 decale = tex2D( DecaleMapSamp, In.DecaleTex );
    
    Color.a = 1;
    
    Color = In.Ambient
		 + ((shadow * In.Depth.w < In.Depth.z-0.03f) ? 0 : In.Diffuse);

    return Color * decale;
}  
// -------------------------------------------------------------
// 2�p�X�ځF�s�N�Z���V�F�[�_�v���O���� (�e�N�X�`���Ȃ�)
// -------------------------------------------------------------
float4 PS_pass2(VS_OUTPUT In) : COLOR
{   
    float4 Color;
	float  shadow = tex2Dproj( ShadowMapSamp, In.ShadowMapUV ).x;
    
    Color.a = 1;
    
    Color = In.Ambient
		 + ((shadow * In.Depth.w < In.Depth.z-0.03f) ? 0 : In.Diffuse);

    return Color;
}  
// -------------------------------------------------------------
// �e�N�j�b�N
// -------------------------------------------------------------
technique TShader
{
    pass P0// �V���h�E�}�b�v�̍쐬
    {
        // �V�F�[�_
        VertexShader = compile vs_1_1 VS_pass0();
        PixelShader  = compile ps_2_0 PS_pass0();
    }
    pass P1// �e�N�X�`������
    {
        // �V�F�[�_
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS_pass1();
    }
    pass P2// �e�N�X�`���Ȃ�
    {
        // �V�F�[�_
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_2_0 PS_pass2();
    }
}
