float4x4 matWorldViewProj;   // ワールドビュー射影変換行列

struct VS_OUTPUT
{
   float4 Pos : POSITION;   // 射影変換座標
   float4 ShadowMapTex : TEXCOORD0;   // Zバッファテクスチャ
};

// 頂点シェーダ
VS_OUTPUT ZBufferCalc_VS( float4 Pos : POSITION )
{
   VS_OUTPUT Out = (VS_OUTPUT)0;

   // 普通にワールドビュー射影行列をする
   Out.Pos = mul( Pos, matWorldViewProj );

   // テクスチャ座標を頂点に合わせる
   Out.ShadowMapTex = Out.Pos;

   return Out;
}


// ピクセルシェーダ
float4 ZBufferPlot_PS( float4 ShadowMapTex : TEXCOORD0 ) : COLOR
{
   // Z値算出
   return ShadowMapTex.z / ShadowMapTex.w;
}

technique ZValuePlotTec
{
   pass P0
   {
      VertexShader = compile vs_2_0 ZBufferCalc_VS();
      PixelShader = compile ps_2_0 ZBufferPlot_PS();
   }
}
