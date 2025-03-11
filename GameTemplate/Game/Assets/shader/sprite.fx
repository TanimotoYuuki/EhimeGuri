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

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = mul( mvp, In.pos );
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
    //CalcSimpleLinearWipe(In);
    //CalcDirectionLinearWipe(In);
    CalcLinearWipeFromRound(In);
	return colorTexture.Sample(Sampler, In.uv) * mulColor;
}

void CalcSimpleLinearWipe(PSInput In)
{
    clip(In.pos.x - linearWipe.size);
}

void CalcDirectionLinearWipe(PSInput In)
{
    float t = dot(linearWipe.direction, In.pos.xy);
    clip(t - linearWipe.size);
}

void CalcLinearWipeFromRound(PSInput In)
{
    float2 posFromCenter = In.pos.xy - float2(800.0f, 450.0f);
    clip(length(posFromCenter) - linearWipe.size);
}