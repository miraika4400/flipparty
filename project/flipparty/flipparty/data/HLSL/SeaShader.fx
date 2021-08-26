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
// 構造体定義
//******************************
struct VS_OUTPUT 
{
	float4 Position : POSITION;  // 座標
	float4 Color    : COLOR0;    // カラー
	float4 Specular :COLOR1;     // スペキュラ
	float3 Normal   : TEXCOORD0;
	float3 Tangent  : TEXCOORD1; // 
	float2 TexCoord : TEXCOORD2; // 
	float3 CubeTexCoord :TEXCOORD3; // キューブテクスチャUV
};

// 通常テクスチャサンプラ
texture Tex;
sampler Sampler = sampler_state {
	Texture = Tex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// バンプマップテクスチャ
texture TexNormal;
sampler SamplerNormal = sampler_state {
	Texture = TexNormal;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// バンプマップテクスチャ
texture TexNormal2;
sampler SamplerNormal2 = sampler_state {
	Texture = TexNormal2;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

// キューブテクスチャ
texture CubeTex;
samplerCUBE SamplerCube = sampler_state {
	Texture = CubeTex;
	MipFilter = LINEAR;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
};

//******************************
// ピクセルシェーダ
//******************************
float4 PS(VS_OUTPUT In) :COLOR
{
	float2 uv = In.TexCoord;
	uv.x += fWaveMove / 6;
	uv.y += fWaveMove/5;

	// バンプマップの設定
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
	// 乗算
	//float4 fOut = ((texCUBE(SamplerCube, In.CubeTexCoord)/1) * In.Color )  * Bump;
	float4 fOut = ((texCUBE(SamplerCube, In.CubeTexCoord) / fCubeRate) * In.Color ) * fBump;
	fOut.a = 0.5f;

	return fOut;
}

//******************************
// 頂点シェーダ
//******************************
VS_OUTPUT VS(float3 Position :POSITION , float4 Diffuse : COLOR0 , float3 Normal : NORMAL , float2 TexCoord : TEXCOORD)
{
	// return
	VS_OUTPUT Out;
	// ワールド座標の設定
	Out.Position = mul(float4(Position, 1), WorldViewProj);
	
	// 法線
	float3 N = mul(Normal, World);
	// 正規化
	N = normalize(N);

	// ライトの向きの正規化
	float3 L = normalize(LightDirection);
	float LightPower = dot(N, L);

	LightPower = max(0, LightPower);

	// カラーの設定
	Out.Color = Diffuse * LightPower;
	Out.Color.a = 1.0f;

	// スペキュラの設定
	float3 H = normalize(normalize(LightDirection) + normalize(Eye - Out.Position));
	Out.Specular = SpecularColor * dot(N, H);
	Out.Specular = pow(Out.Specular, 8);

	// テクスチャUVの設定
	Out.TexCoord = TexCoord;

	// 接線
	Out.Tangent = mul(float3(1.0f, 0.0f, 0.0f), World);

	// 法線
	Out.Normal = Normal;

	// キューブテクスチャUV
	Out.CubeTexCoord = reflect(Out.Position - Eye, N);

	return Out;
}

//******************************
// テクニック＊テクスチャあり
//******************************
technique Shader
{
	pass P0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}