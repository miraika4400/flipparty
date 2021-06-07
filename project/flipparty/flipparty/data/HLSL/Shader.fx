float4x4 WorldViewProj : WORLDVIEWPROJ;
float4x4 World :WORLD;
float3   LightDirection;
float4   DiffuseColor;
float3   Eye;
float4   SpecularColor;


// 頂点シェーダアウトプット
struct VS_OUTPUT {
	float4 Posision :POSITION;      // 座標
	float2 TexCoord :TEXCOORD;      // テクスチャ座標
	float4 Color    :COLOR0;         // カラー
	float4 Specular :COLOR1;        // スペキュラー
	float3 CubeTexCoord :TEXCOORD1; // キューブテクスチャ
};

// テクスチャの設定
texture Tex;
sampler Sampler = sampler_state {
	Texture = Tex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// キューブテクスチャの設定
texture CubeTex;
samplerCUBE SamplerCube = sampler_state {
	Texture = CubeTex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//******************************
// テクスチャありピクセルシェーダ
//******************************
float4 PsTex(VS_OUTPUT In) :COLOR
{
	float4 fOut = texCUBE(SamplerCube, In.CubeTexCoord)/10 + tex2D(Sampler, In.TexCoord) * (In.Color + In.Specular);
	
	return fOut;
}


//******************************
// テクスチャなしピクセルシェーダ
//******************************
float4 PsNotTex(VS_OUTPUT In) :COLOR
{
	float4 fOut = In.Color + In.Specular;
	fOut = texCUBE(SamplerCube, In.CubeTexCoord)/10  + fOut;
	fOut.a = 1.0f;
	return fOut;
}

//******************************
// 頂点シェーダ
//******************************
VS_OUTPUT VS(float3 Position : POSITION, float2 TexCoord : TEXCOORD,float4 Diffuse : COLOR0, float3 Normal : NORMAL)
{
	VS_OUTPUT Out;

	// 座標の設定
	Out.Posision = mul(float4(Position, 1), WorldViewProj);
	
	// ワールドマトリックスをかける
	float3 N = mul(Normal, (float3x3)World);
	N = normalize(N);
	float3 E = mul(Eye, (float3x3)World);
	E = normalize(E);
	float3 H = normalize(normalize(LightDirection) + normalize(Eye - Position));

	// スペキュラカラーの設定
	Out.Specular = SpecularColor * dot(N, H);
	Out.Specular = pow(Out.Specular, 8);
	Out.Specular.a = 1.0f;
	// 光源処理
	float LightPower = dot(N, LightDirection);
	LightPower = max(0, LightPower);
	// ディフーズカラーの設定
	Out.Color = DiffuseColor * LightPower;
	Out.Color.a = 1.0f;

	// テクスチャUV
	Out.TexCoord = TexCoord;
	Out.CubeTexCoord = reflect(Out.Posision - E, N);

	return Out;
}

//******************************
// テクニック＊テクスチャあり
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
// テクニック＊テクスチャなし
//******************************
technique NotTexShader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PsNotTex();
	}
}