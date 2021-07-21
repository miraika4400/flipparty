float4x4 matWorldViewProj;   // ���[���h�r���[�ˉe�ϊ��s��

struct VS_OUTPUT
{
   float4 Pos : POSITION;   // �ˉe�ϊ����W
   float4 ShadowMapTex : TEXCOORD0;   // Z�o�b�t�@�e�N�X�`��
};

// ���_�V�F�[�_
VS_OUTPUT ZBufferCalc_VS( float4 Pos : POSITION )
{
   VS_OUTPUT Out = (VS_OUTPUT)0;

   // ���ʂɃ��[���h�r���[�ˉe�s�������
   Out.Pos = mul( Pos, matWorldViewProj );

   // �e�N�X�`�����W�𒸓_�ɍ��킹��
   Out.ShadowMapTex = Out.Pos;

   return Out;
}


// �s�N�Z���V�F�[�_
float4 ZBufferPlot_PS( float4 ShadowMapTex : TEXCOORD0 ) : COLOR
{
   // Z�l�Z�o
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
