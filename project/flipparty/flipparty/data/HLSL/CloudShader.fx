float4x4 WorldViewProj : WORLDVIEWPROJ;
float4x4 World :WORLD;
float3   LightDirection;
float4   DiffuseColor;
float3   Eye;

struct VS_OUTPUT {
	float4 Posision :POSITION;      // 座標
	float2 ToonTexCoord :TEXCOORD1;      // テクスチャ座標
	float4 Color    :COLOR;         // カラー
};

/* テクスチャのサンプラ― */
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
/* 頂点シェーダ */
//////////////////////////////////
VS_OUTPUT VS(float3 Position : POSITION, float4 Diffuse : COLOR, float3 Normal : NORMAL)
{
	VS_OUTPUT Out;

	// ワールド座標
	Out.Posision = mul(float4(Position, 1), WorldViewProj);

	// 法線
	float3 N = mul(Normal, (float3x3)World);
	// 正規化
	N = normalize(N);
	float3 H = normalize(normalize(mul(LightDirection, (float3x3)World)) + normalize(mul(Eye, (float3x3)World) - Out.Posision));

	// ライトの処理
	float LightPower = dot(N, LightDirection);
	LightPower = max(0, LightPower);

	// トゥーンシェーダ―UV
	Out.ToonTexCoord = float2(LightPower, 0.5f);
	// カラーの設定
	Out.Color = DiffuseColor;
	
	return Out;
}

//////////////////////////////////
/* ピクセルシェーダ */
//////////////////////////////////
float4 PS(VS_OUTPUT In) :COLOR
{
	float4 fOut = tex2D(ToonSampler, In.ToonTexCoord);
	fOut.a = 1.0f;
	fOut *= In.Color;

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