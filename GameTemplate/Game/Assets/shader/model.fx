/*!
 * @brief	シンプルなモデルシェーダー。
 */
////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
    float3 normal	: NORMAL;		//法線
	float2 uv 		: TEXCOORD0;	//UV座標。
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
    float3 normal		: NORMAL;		//法線
	float2 uv 			: TEXCOORD0;	//uv座標。
    float3 worldPos		: TEXCOORD1;    //ワールド座標
};

struct DirectionLight
{
    float3 direction; //ライトの方向
    float3 color; //ライトのカラー
};

struct PointLight
{
    float3 position; //ライトの位置
    float3 color; //ライトのカラー
    float range; //ライトの影響範囲
};

struct SpotLight
{
    float3 position; //ライトの位置
    float3 color; //ライトのカラー
    float range; //ライトの影響範囲
    float3 direction; //ライトの放射方向
    float angle; //ライトの放射角度
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};

//ライト用の定数バッファ
cbuffer LightCb : register(b1)
{
    DirectionLight directionLight;
    float3 eyePos;
    float3 ambientLig;
    PointLight pointLight[10];
    SpotLight spotLight[10];
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromDirectionLight(SPSIn psIn);
float3 CalcLigFromPointLight(SPSIn psIn, int num);
float3 CalcLigFromSpotLight(SPSIn psIn, int num);

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
	psIn.pos = mul(m, vsIn.pos);
    psIn.worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

    psIn.normal = mul(m, vsIn.normal);
	psIn.uv = vsIn.uv;

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain( SPSIn psIn ) : SV_Target0
{
    //ディレクションライト
    float3 directionLig = CalcLigFromDirectionLight(psIn);
    
    float3 pointLig[10];
    float3 spotLig[10];
    for (int i = 0; i < 10; i++)
    {
        //ポイントライト
        pointLig[i] = CalcLigFromPointLight(psIn, i);
        //スポットライト
        spotLig[i] = CalcLigFromSpotLight(psIn, i);
    }
	//最終的な光を求める
    //float3 lig = directionLig;
    float3 lig;
    for (int j = 0; j < 10; j++)
    {
        lig += pointLig[j];
        lig += spotLig[j];
    }
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	
    albedoColor.xyz *= lig;
	
	return albedoColor;
}

//拡散反射光
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    float t = dot(normal, lightDirection) * -1.0f;
    if (t < 0.0f)
    {
        t = 0.0f;
    }
	
    return lightColor * t;
}

//鏡面反射光
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    float3 refVec = reflect(lightDirection, normal);
	
    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);
	
    float t = dot(refVec, toEye);
    if (t < 0.0f)
    {
        t = 0.0f;
    }
	
    t = pow(t, 5.0f);
	
    return lightColor * t;
}

//ディレクションライト
float3 CalcLigFromDirectionLight(SPSIn psIn)
{
    //拡散反射光を求める
    float3 diffuseLig = CalcLambertDiffuse(directionLight.direction, directionLight.color, psIn.normal);
    
    //鏡面反射光を求める
    float3 specularLig = CalcPhongSpecular(directionLight.direction, directionLight.color, psIn.worldPos, psIn.normal);
 
    //拡散反射光 + 鏡面反射光 + 環境光
    return diffuseLig + specularLig + ambientLig;
}

//ポイントライト
float3 CalcLigFromPointLight(SPSIn psIn, int num)
{
    //ポイントライトの向きを求める
    float3 ligDir = psIn.worldPos - pointLight[num].position;
    ligDir = normalize(ligDir);
    
    //拡散反射光を求める
    float3 diffusePoint = CalcLambertDiffuse(ligDir, pointLight[num].color, psIn.normal);
    
    //鏡面反射光を求める
    float3 specularPoint = CalcPhongSpecular(ligDir, pointLight[num].color, psIn.worldPos, psIn.normal);
    
    //ポイントライトとの距離を求める
    float distance = length(psIn.worldPos - pointLight[num].position);
    
    //距離による影響率を求める
    float affect = 1.0f - 1.0f / pointLight[num].range * distance;
    
    if(affect<0.0f)
    {
        affect = 0.0f;
    }
    
    affect = pow(affect, 3.0f);
    
    //影響率を乗算して反射光を弱める
    diffusePoint *= affect;
    specularPoint *= affect;
    
    return diffusePoint + specularPoint;
}

//スポットライト
float3 CalcLigFromSpotLight(SPSIn psIn, int num)
{
    //スポットライトの向きを求める
    float3 ligDir = psIn.worldPos - spotLight[num].position;
    ligDir = normalize(ligDir);
    
    //拡散反射光を求める
    float3 diffuseSpot = CalcLambertDiffuse(ligDir, spotLight[num].color, psIn.normal);
    
    //鏡面反射光を求める
    float3 specularSpot = CalcPhongSpecular(ligDir, spotLight[num].color, psIn.worldPos, psIn.normal);
    
    //スポットライトとの距離を求める
    float distance = length(psIn.worldPos - spotLight[num].position);
    
    //距離による影響率を求める
    float affect = 1.0f - 1.0f / spotLight[num].range * distance;
    
    if(affect<0.0f)
    {
        affect = 0.0f;
    }
    
    affect = pow(affect, 3.0f);
    
    //距離による影響率を乗算して反射光を弱める
    diffuseSpot *= affect;
    specularSpot *= affect;
    
    ///入射光と射出方向の角度を求める
    float angle = dot(ligDir, spotLight[num].direction);
    angle = abs(acos(angle));
    
    //角度による影響率を求める
    affect = 1.0f - 1.0f / spotLight[num].angle * angle;
    
    if(affect<0.0f)
    {
        affect = 0.0f;
    }
    
    affect = pow(affect, 0.5f);
    
    //角度による影響率を乗算して反射光を弱める
    diffuseSpot *= affect;
    specularSpot *= affect;
    
    return diffuseSpot + specularSpot;
}