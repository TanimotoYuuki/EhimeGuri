/*!
 * @brief	・ｽX・ｽv・ｽ・ｽ・ｽC・ｽg・ｽp・ｽﾌシ・ｽF・ｽ[・ｽ_・ｽ[・ｽB
 */

struct VSInput{
	float4 pos : POSITION;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

struct LinearWipe
{
    float2 direction;
    float size;
};

cbuffer cb : register(b0){
	float4x4 mvp;		//・ｽ・ｽ・ｽ[・ｽ・ｽ・ｽh・ｽr・ｽ・ｽ・ｽ[・ｽv・ｽ・ｽ・ｽW・ｽF・ｽN・ｽV・ｽ・ｽ・ｽ・ｽ・ｽs・ｽ・ｽB
	float4 mulColor;	//・ｽ・ｽZ・ｽJ・ｽ・ｽ・ｽ[・ｽB
};

cbuffer SpriteRenderCb : register(b1)
{
    LinearWipe linearWipe; //繝ｪ繝九い繝ｯ繧､繝・
    int linearWipeDrawingMode; //謠冗判繝｢繝ｼ繝・
    float drawingRate; //繧､繝ｼ繧ｸ繝ｳ繧ｰ蜑ｲ蜷・
    int screenDrawingMode; //謠冗判繝｢繝ｼ繝・
};

Texture2D<float4> colorTexture : register(t0);	//・ｽJ・ｽ・ｽ・ｽ[・ｽe・ｽN・ｽX・ｽ`・ｽ・ｽ・ｽB
sampler Sampler : register(s0);

void CalcLinearWipeFromNormal(PSInput In);
void CalcLinearWipeFromDirection(PSInput In);
void CalcLinearWipeFromRound(PSInput In);
void CalcLinearWipeFromVertical(PSInput In);
void CalcLinearWipeFromHorizontal(PSInput In);
void CalcLinearWipeFromCheckerBoard(PSInput In);
float4 CalcMonochrome(float4 color);
float4 CalcSepia(float4 color);
float4 CalcNega(float4 color);
float4 CalcNoise(PSInput In, float4 color);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
    float4 color = colorTexture.Sample(Sampler, In.uv) * mulColor;
    
    //繝ｪ繝九い繝ｯ繧､繝・
    switch (linearWipeDrawingMode)
    {
    case 0: //騾壼ｸｸ
        CalcLinearWipeFromNormal(In);
        break;
    case 1: //譁ｹ蜷・
        CalcLinearWipeFromDirection(In);
        break;
    case 2: //蜀・ｽ｢
        CalcLinearWipeFromRound(In);
        break;
    case 3: //邵ｦ縺倥∪
        CalcLinearWipeFromVertical(In);
        break;
    case 4: //讓ｪ縺倥∪
        CalcLinearWipeFromHorizontal(In);
        break;
    case 5: //繝√ぉ繝・き繝ｼ繝懊・繝・
        CalcLinearWipeFromCheckerBoard(In);
        break;
    default:
        break;
    }
    
    //逕ｻ蜒丞刈蟾･
    switch (screenDrawingMode)
    {
    case 0: //繝｢繝弱け繝ｭ
        color = CalcMonochrome(color);
        break;
    case 1: //繧ｻ繝斐い
        color = CalcSepia(color);
        break;
    case 2: //繝阪ぎ繝昴ず蜿崎ｻ｢
        color = CalcNega(color);
        break;
    case 3: //繝弱う繧ｺ
        color = CalcNoise(In, color);
        break;
    default:
        break;
    }

	return color;
}

//騾壼ｸｸ繝ｯ繧､繝・
void CalcLinearWipeFromNormal(PSInput In)
{
    clip(In.pos.x - linearWipe.size);
}

//譁ｹ蜷代Ρ繧､繝・
void CalcLinearWipeFromDirection(PSInput In)
{
    float t = dot(linearWipe.direction, In.pos.xy);
    clip(t - linearWipe.size);
}

//蜀・ｽ｢繝ｯ繧､繝・
void CalcLinearWipeFromRound(PSInput In)
{
    float2 posFromCenter = In.pos.xy - float2(800.0f, 450.0f);
    clip(length(posFromCenter) - linearWipe.size);
}

//邵ｦ縺倥∪繝ｯ繧､繝・
void CalcLinearWipeFromVertical(PSInput In)
{
    float t = (int) fmod(In.pos.x, 64.0f);
    clip(t - linearWipe.size);
}

//讓ｪ縺倥∪繝ｯ繧､繝・
void CalcLinearWipeFromHorizontal(PSInput In)
{
    float t = (int) fmod(In.pos.y, 64.0f);
    clip(t - linearWipe.size);
}

//繝√ぉ繝・き繝ｼ繝懊・繝峨Ρ繧､繝・
void CalcLinearWipeFromCheckerBoard(PSInput In)
{
    float t = floor(In.pos.y / 128.0f);
    t = fmod(t, 2.0f);
    t = (int) fmod(In.pos.x + 64.0f * t, 128.0f);
    clip(t - linearWipe.size);
}

//繝｢繝弱け繝ｭ蜉蟾･
float4 CalcMonochrome(float4 color)
{
    float y = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    
    float3 monochromeColor = float3(y, y, y);
    color.xyz = lerp(color, monochromeColor, drawingRate);
    return color;
}

//繧ｻ繝斐い蜉蟾･
float4 CalcSepia(float4 color)
{
    float y = 0.299f * color.r + 0.587f * color.g + 0.144f * color.b;
    
    float3 sepiaColor;
    sepiaColor.r = y * 0.9f;
    sepiaColor.g = y * 0.7f;
    sepiaColor.b = y * 0.4f;
    
    color.xyz = lerp(color, sepiaColor, drawingRate);
    return color;
}

//繝阪ぎ繝昴ず蜿崎ｻ｢
float4 CalcNega(float4 color)
{
    float3 negaColor;
    negaColor.x = 1.0f - color.x;
    negaColor.y = 1.0f - color.y;
    negaColor.z = 1.0f - color.z;
    
    color.xyz = lerp(color, negaColor, drawingRate);
    return color;
}

// 繝上ャ繧ｷ繝･髢｢謨ｰ
float hash(float n)
{
    return frac(sin(n) * 43758.5453);
}

//3谺｡蜈・・繧ｯ繝医Ν縺九ｉ繧ｷ繝ｳ繝励Ξ繝・け繧ｹ繝弱う繧ｺ繧堤函謌舌☆繧矩未謨ｰ
float SimplexNoise(float3 x)
{
    float3 p = floor(x);
    float3 f = frac(x);
    
    f = f * f * (3.0f - 2.0f * f);
    float n = p.x + p.y * 57.0f + 113.0f * p.z;
    
    return lerp(lerp(lerp(hash(n + 0.0), hash(n + 1.0), f.x),
                     lerp(hash(n + 57.0), hash(n + 58.0), f.x), f.y),
                lerp(lerp(hash(n + 113.0), hash(n + 114.0), f.x),
                     lerp(hash(n + 170.0), hash(n + 171.0), f.x), f.y), f.z);
}

//繝弱う繧ｺ
float4 CalcNoise(PSInput In,float4 color)
{
    float t = SimplexNoise(In.pos.xyz);
    
    t = (t - 0.5f) * 2.0f;
    
    float2 uv = In.uv + t * 0.01f;
    color = colorTexture.Sample(Sampler, uv);
    return color;
}