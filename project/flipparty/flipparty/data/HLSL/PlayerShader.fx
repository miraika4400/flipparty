float4x4 WorldViewProj : WORLDVIEWPROJ;
float4x4 World :WORLD;
float3   LightDirection;
float4   DiffuseColor;
float3   Eye;
float4   SpecularColor;
float    fTexV;

struct VS_OUTPUT {
	float4 Posision :POSITION;      // ���W
	float2 TexCoord :TEXCOORD;      // �e�N�X�`�����W
	float2 ToonTexCoord :TEXCOORD1;      // �e�N�X�`�����W
	float4 Color    :COLOR;         // �J���[
	float4 Specular :COLOR1;        // �X�y�L�����[
};

/* �e�N�X�`���̃T���v���\ */
texture Tex;
sampler Sampler = sampler_state {
	Texture = Tex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;

	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = clamp;
	AddressV = Wrap;
	AddressW = Wrap;
};

/* �e�N�X�`���̃T���v���\ */
texture ToonTex;
sampler ToonSampler = sampler_state {
	Texture = ToonTex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;

	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = clamp;
	AddressV = Wrap;
	AddressW = Wrap;
};

//////////////////////////////////
/* ���_�V�F�[�_ */
//////////////////////////////////
VS_OUTPUT VS(float3 Position : POSITION, float2 TexCoord : TEXCOORD, float4 Diffuse : COLOR, float3 Normal : NORMAL)
{
	VS_OUTPUT Out;

	// ���[���h���W
	Out.Posision = mul(float4(Position, 1), WorldViewProj);

	// �e�N�X�`����UV
	Out.TexCoord = TexCoord;

	// �@��
	float3 N = mul(Normal, (float3x3)World);
	// ���K��
	N = normalize(N);
	float3 H = normalize(normalize(mul(LightDirection, (float3x3)World)) + normalize(mul(Eye, (float3x3)World) - Out.Posision));

	// ���C�g�̏���
	float LightPower = dot(N, LightDirection);
	LightPower = max(0, LightPower);

	Out.ToonTexCoord = float2(LightPower, 0.5f);
	Out.Color = DiffuseColor;
	
	Out.Specular = SpecularColor * dot(N, H);
	Out.Specular = pow(Out.Specular,4);
	return Out;
}

//////////////////////////////////
/* �s�N�Z���V�F�[�_ */
//////////////////////////////////
float4 PS(VS_OUTPUT In) :COLOR
{
	float2 TexCoord = In.TexCoord;
	TexCoord.y += fTexV;
	float4 fOut = tex2D(Sampler, TexCoord) * tex2D(ToonSampler, In.ToonTexCoord) * In.Color ;
	fOut.a = 1.0f;
	return fOut;
}

technique Shader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}