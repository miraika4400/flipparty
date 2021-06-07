float4x4 WorldViewProj : WORLDVIEWPROJ;
float4x4 World :WORLD;
float3   LightDirection;
float4   DiffuseColor;
float3   Eye;
float4   SpecularColor;


// ���_�V�F�[�_�A�E�g�v�b�g
struct VS_OUTPUT {
	float4 Posision :POSITION;      // ���W
	float2 TexCoord :TEXCOORD;      // �e�N�X�`�����W
	float4 Color    :COLOR0;         // �J���[
	float4 Specular :COLOR1;        // �X�y�L�����[
	float3 CubeTexCoord :TEXCOORD1; // �L���[�u�e�N�X�`��
};

// �e�N�X�`���̐ݒ�
texture Tex;
sampler Sampler = sampler_state {
	Texture = Tex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// �L���[�u�e�N�X�`���̐ݒ�
texture CubeTex;
samplerCUBE SamplerCube = sampler_state {
	Texture = CubeTex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//******************************
// �e�N�X�`������s�N�Z���V�F�[�_
//******************************
float4 PsTex(VS_OUTPUT In) :COLOR
{
	float4 fOut = tex2D(Sampler, In.TexCoord) * (In.Color + In.Specular);
	
	return fOut;
}


//******************************
// �e�N�X�`���Ȃ��s�N�Z���V�F�[�_
//******************************
float4 PsNotTex(VS_OUTPUT In) :COLOR
{
	float4 fOut = In.Color + In.Specular;
	fOut = texCUBE(SamplerCube, In.CubeTexCoord) / 5 + fOut;
	fOut.a = 0.7f;
	return fOut;
}

//******************************
// ���_�V�F�[�_
//******************************
VS_OUTPUT VS(float3 Position : POSITION, float2 TexCoord : TEXCOORD,float4 Diffuse : COLOR0, float3 Normal : NORMAL)
{
	VS_OUTPUT Out;

	// ���W�̐ݒ�
	Out.Posision = mul(float4(Position, 1), WorldViewProj);
	
	// ���[���h�}�g���b�N�X��������
	float3 N = mul(Normal, (float3x3)World);
	N = normalize(N);
	float3 E = mul(Eye, (float3x3)World);
	E = normalize(E);
	float3 H = normalize(normalize(LightDirection) + normalize(Eye - Position));

	// �X�y�L�����J���[�̐ݒ�
	Out.Specular = SpecularColor * dot(N, H);
	Out.Specular = pow(Out.Specular, 8);
	Out.Specular.a = 1.0f;
	// ��������
	float LightPower = dot(N, LightDirection);
	LightPower = max(0, LightPower);
	// �f�B�t�[�Y�J���[�̐ݒ�
	Out.Color = DiffuseColor * LightPower;
	Out.Color.a = 1.0f;

	// �e�N�X�`��UV
	Out.TexCoord = TexCoord;
	Out.CubeTexCoord = reflect(Out.Posision - E, N);

	return Out;
}

//******************************
// �e�N�j�b�N���e�N�X�`������
//******************************
technique TexShader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PsTex();
	}

}

//******************************
// �e�N�j�b�N���e�N�X�`���Ȃ�
//******************************
technique NotTexShader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PsNotTex();
	}
}