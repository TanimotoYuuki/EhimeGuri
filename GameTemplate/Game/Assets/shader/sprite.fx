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
    int drawingMode; //描画モード
    float drawingRate;
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
    switch (drawingMode)
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
    color=CalcMonochrome(color);
    
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
