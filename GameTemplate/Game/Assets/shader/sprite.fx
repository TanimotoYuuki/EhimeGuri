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
};

Texture2D<float4> colorTexture : register(t0);	//�J���[�e�N�X�`���B
sampler Sampler : register(s0);

void CalcLinearWipeFromSimple(PSInput In);
void CalcLinearWipeFromDirection(PSInput In);
void CalcLinearWipeFromRound(PSInput In);
void CalcLinearWipeFromVertical(PSInput In);
void CalcLinearWipeFromHorizontal(PSInput In);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
    //CalcLinearWipeFromSimple(In);
    //CalcLinearWipeFromDirection(In);
    //CalcLinearWipeFromRound(In);
    //CalcLinearWipeFromVertical(In);
    CalcLinearWipeFromHorizontal(In);
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
}

void CalcLinearWipeFromSimple(PSInput In)
{
    clip(In.pos.x - linearWipe.size);
}

void CalcLinearWipeFromDirection(PSInput In)
{
    float t = dot(linearWipe.direction, In.pos.xy);
    clip(t - linearWipe.size);
}

void CalcLinearWipeFromRound(PSInput In)
{
    float2 posFromCenter = In.pos.xy - float2(800.0f, 450.0f);
    clip(length(posFromCenter) - linearWipe.size);
}

void CalcLinearWipeFromVertical(PSInput In)
{
    float t = (int) fmod(In.pos.x, 64.0f);
    clip(t - linearWipe.size);
}

void CalcLinearWipeFromHorizontal(PSInput In)
{
    float t = (int) fmod(In.pos.y, 64.0f);
    clip(t - linearWipe.size);
}
