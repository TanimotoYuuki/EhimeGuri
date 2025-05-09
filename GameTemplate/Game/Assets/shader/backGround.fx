////////////////////////////////
/// バックグラウンドシェーダー
////////////////////////////////

//頂点シェーダーの入力
struct VSInput
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

//ピクセルシェーダーの入力
struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

//スプライトの定数バッファ
cbuffer cb : register(b0)
{
    float4x4 mvp;        //MVP関数
    float4 mulColor;     //乗算カラー
};

//バックグラウンドレンダーの定数バッファを取得
cbuffer BackGroundRenderCb : register(b1)
{
    bool  scrollFlag;               //背景をスクロールするか？
    float screenEdgeCorrection;     //画像の画面端補正
    float rate;                     //割合
}

Texture2D<float4> colorTexture : register(t0);
sampler Sampler : register(s0);

//頂点シェーダー
PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    
    //背景をスクロールするなら
    if (scrollFlag == true)
    {
        //画面端の補正
        psIn.pos.x += screenEdgeCorrection;
        //プレイヤーが移動したら横にイージングする
        psIn.pos.x -= lerp(0.0f, screenEdgeCorrection * 2, rate);
    }
    
    return psIn;
}

//ピクセルシェーダー
float4 PSMain(PSInput In) : SV_Target0
{
    float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
    return color;
}