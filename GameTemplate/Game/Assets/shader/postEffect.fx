cbuffer cb : register(b0)
{
    float4x4 mvp;       //MVPçsóÒ
    float4 mulColor;    //èÊéZÉJÉâÅ[
};

struct VSInput
{
    float4 pos : POSITION;
    float2 uv  : TEXCOORD;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv  : TEXCOORD;
};

Texture2D<float4> sceneTexture : register(t0);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}

float4 PSMain(PSInput In) : SV_Target0
{
    float4 color = sceneTexture.Sample(Sampler, In.uv);
    
    float y = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    color.r = y;
    color.g = y;
    color.b = y;
    
    return color;
}

float4 PSLuminance(PSInput In) : SV_Target0
{
    float4 color = sceneTexture.Sample(Sampler, In.uv);
    
    float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
    
    clip(t - 1.0f);
    return color;
}