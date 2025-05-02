struct VSInput
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

struct LinearWipe
{
    float2 direction;
    float size;
};

cbuffer cb : register(b0)
{
    float4x4 mvp;
    float4 mulColor;
};

cbuffer BackGroundRenderCb : register(b1)
{
    bool  scrollFlag;               //背景をスクロールするか？
    float screenEdgeCorrection;     //画像の画面端補正
    float rate;                     //割合
}

Texture2D<float4> colorTexture : register(t0);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    
    if (scrollFlag == true)
    {
        psIn.pos.x += screenEdgeCorrection;
        psIn.pos.x -= lerp(0.0f, screenEdgeCorrection * 2, rate);
    }
    
    return psIn;
}
float4 PSMain(PSInput In) : SV_Target0
{
    float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
    return color;
}