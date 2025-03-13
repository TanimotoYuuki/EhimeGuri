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

cbuffer WipeCb : register(b1)
{
    LinearWipe linearWipe; //リニアワイプ
    int Mode; //描画モード
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
sampler Sampler : register(s0);

void CalcLinearWipeFromNormal(PSInput In);
void CalcLinearWipeFromDirection(PSInput In);
void CalcLinearWipeFromRound(PSInput In);
void CalcLinearWipeFromVertical(PSInput In);
void CalcLinearWipeFromHorizontal(PSInput In);
void CalcLinearWipeFromCheckerBoard(PSInput In);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
    switch (Mode)
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
    
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
}

//通常
void CalcLinearWipeFromNormal(PSInput In)
{
    clip(In.pos.x - linearWipe.size);
}

//方向
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
