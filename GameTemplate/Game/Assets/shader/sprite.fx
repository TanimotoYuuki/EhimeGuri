/*!
 * @brief	�X�v���C�g�p�̃V�F�[�_�[�B
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
	float4x4 mvp;		//���[���h�r���[�v���W�F�N�V�����s��B
	float4 mulColor;	//��Z�J���[�B
};

cbuffer SpriteRenderCb : register(b1)
{
    LinearWipe linearWipe; //リニアワイプ
    int linearWipeDrawingMode; //描画モード
    float drawingRate; //イージング割合
    int screenDrawingMode; //描画モード
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
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
    
    //リニアワイプ
    switch (linearWipeDrawingMode)
    {
    case 0: //通常
        CalcLinearWipeFromNormal(In);
        break;
    case 1: //方向
        CalcLinearWipeFromDirection(In);
        break;
    case 2: //円形
        CalcLinearWipeFromRound(In);
        break;
    case 3: //縦じま
        CalcLinearWipeFromVertical(In);
        break;
    case 4: //横じま
        CalcLinearWipeFromHorizontal(In);
        break;
    case 5: //チェッカーボード
        CalcLinearWipeFromCheckerBoard(In);
        break;
    default:
        break;
    }
    
    //画像加工
    switch (screenDrawingMode)
    {
    case 0: //モノクロ
        color = CalcMonochrome(color);
        break;
    case 1: //セピア
        color = CalcSepia(color);
        break;
    case 2: //ネガポジ反転
        color = CalcNega(color);
        break;
    case 3: //ノイズ
        color = CalcNoise(In, color);
        break;
    default:
        break;
    }

	return color;
}

//通常ワイプ
void CalcLinearWipeFromNormal(PSInput In)
{
    clip(In.pos.x - linearWipe.size);
}

//方向ワイプ
void CalcLinearWipeFromDirection(PSInput In)
{
    float t = dot(linearWipe.direction, In.pos.xy);
    clip(t - linearWipe.size);
}

//円形ワイプ
void CalcLinearWipeFromRound(PSInput In)
{
    float2 posFromCenter = In.pos.xy - float2(800.0f, 450.0f);
    clip(length(posFromCenter) - linearWipe.size);
}

//縦じまワイプ
void CalcLinearWipeFromVertical(PSInput In)
{
    float t = (int) fmod(In.pos.x, 64.0f);
    clip(t - linearWipe.size);
}

//横じまワイプ
void CalcLinearWipeFromHorizontal(PSInput In)
{
    float t = (int) fmod(In.pos.y, 64.0f);
    clip(t - linearWipe.size);
}

//チェッカーボードワイプ
void CalcLinearWipeFromCheckerBoard(PSInput In)
{
    float t = floor(In.pos.y / 128.0f);
    t = fmod(t, 2.0f);
    t = (int) fmod(In.pos.x + 64.0f * t, 128.0f);
    clip(t - linearWipe.size);
}

//モノクロ加工
float4 CalcMonochrome(float4 color)
{
    float y = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    
    float3 monochromeColor = float3(y, y, y);
    color.xyz = lerp(color, monochromeColor, drawingRate);
    return color;
}

//セピア加工
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

//ネガポジ反転
float4 CalcNega(float4 color)
{
    float3 negaColor;
    negaColor.x = 1.0f - color.x;
    negaColor.y = 1.0f - color.y;
    negaColor.z = 1.0f - color.z;
    
    color.xyz = lerp(color, negaColor, drawingRate);
    return color;
}

// ハッシュ関数
float hash(float n)
{
    return frac(sin(n) * 43758.5453);
}

//3次元ベクトルからシンプレックスノイズを生成する関数
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

//ノイズ
float4 CalcNoise(PSInput In,float4 color)
{
    float t = SimplexNoise(In.pos.xyz);
    
    t = (t - 0.5f) * 2.0f;
    
    float2 uv = In.uv + t * 0.01f;
    color = colorTexture.Sample(Sampler, uv);
    return color;
}