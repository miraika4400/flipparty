//******************************
// 
//******************************
float4x4 WorldViewProj : WORLDVIEWPROJ; // 
float4x4 World :WORLD;                  // 
float3   LightDirection;                // 
float4   DiffuseColor;                  // 
float3 Eye;                             // 
float4 SpecularColor;                   // 
float fWaveRate;                        // 
float fWaveMove;                        // 
float fCubeRate;

//******************************
// �\���̒�`
//******************************
struct VS_OUTPUT 
{
	float4 Position : POSITION;  // ���W
	float4 Color    : COLOR0;    // �J���[
	float4 Specular :COLOR1;     // �X�y�L����
	float3 Normal   : TEXCOORD0;
	float3 Tangent  : TEXCOORD1; // 
	float2 TexCoord : TEXCOORD2; // 
	float3 CubeTexCoord :TEXCOORD3; // �L���[�u�e�N�X�`��UV
};

// �ʏ�e�N�X�`���T���v��
texture Tex;
sampler Sampler = sampler_state {
	Texture = Tex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// �o���v�}�b�v�e�N�X�`��
texture TexNormal;
sampler SamplerNormal = sampler_state {
	Texture = TexNormal;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// �o���v�}�b�v�e�N�X�`��
texture TexNormal2;
sampler SamplerNormal2 = sampler_state {
	Texture = TexNormal2;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// �L���[�u�e�N�X�`��
texture CubeTex;
samplerCUBE SamplerCube = sampler_state {
	Texture = CubeTex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//******************************
// �s�N�Z���V�F�[�_
//******************************
float4 PS(VS_OUTPUT In) :COLOR
{
	float2 uv = In.TexCoord;
	uv.x += fWaveMove / 6;
	uv.y += fWaveMove/5;

	// �o���v�}�b�v�̐ݒ�
	float3 BNormal = normalize(cross(In.Normal, In.Tangent));
	float3x3 tangentMatrix = float3x3(BNormal, In.Tangent, In.Normal);
	float3 b = tex2D(SamplerNormal, uv);
	b = mul(b, tangentMatrix);
	float Bump = max(0, dot(b, LightDirection));

	float3 BNormal2 = normalize(cross(In.Normal, In.Tangent));
	float3x3 tangentMatrix2 = float3x3(BNormal2, In.Tangent, In.Normal);
	float3 b2 = tex2D(SamplerNormal2, uv);
	b2 = mul(b2, tangentMatrix2);
	float Bump2 = max(0, dot(b2, LightDirection));

	float fBump = Bump2 + ((Bump - Bump2)*fWaveRate);
	// ��Z
	//float4 fOut = ((texCUBE(SamplerCube, In.CubeTexCoord)/1) * In.Color )  * Bump;
	float4 fOut = ((texCUBE(SamplerCube, In.CubeTexCoord) / fCubeRate) * In.Color ) * fBump;
	fOut.a = 0.5f;

	return fOut;
}

//******************************
// ���_�V�F�[�_
//******************************
VS_OUTPUT VS(float3 Position :POSITION , float4 Diffuse : COLOR0 , float3 Normal : NORMAL , float2 TexCoord : TEXCOORD)
{
	// return
	VS_OUTPUT Out;
	// ���[���h���W�̐ݒ�
	Out.Position = mul(float4(Position, 1), WorldViewProj);
	
	// �@��
	float3 N = mul(Normal, World);
	// ���K��
	N = normalize(N);

	// ���C�g�̌����̐��K��
	float3 L = normalize(LightDirection);
	float LightPower = dot(N, L);

	LightPower = max(0, LightPower);

	// �J���[�̐ݒ�
	Out.Color = Diffuse * LightPower;
	Out.Color.a = 1.0f;

	// �X�y�L�����̐ݒ�
	float3 H = normalize(normalize(LightDirection) + normalize(Eye - Out.Position));
	Out.Specular = SpecularColor * dot(N, H);
	Out.Specular = pow(Out.Specular, 8);

	// �e�N�X�`��UV�̐ݒ�
	Out.TexCoord = TexCoord;

	// �ڐ�
	Out.Tangent = mul(float3(1.0f, 0.0f, 0.0f), World);

	// �@��
	Out.Normal = Normal;

	// �L���[�u�e�N�X�`��UV
	Out.CubeTexCoord = reflect(Out.Position - Eye, N);

	return Out;
}

//******************************
// �e�N�j�b�N���e�N�X�`������
//******************************
technique Shader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}