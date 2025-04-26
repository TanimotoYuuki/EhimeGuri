/*!
 * @brief	繧ｷ繝ｳ繝励Ν縺ｪ繝｢繝・Ν繧ｷ繧ｧ繝ｼ繝繝ｼ縲・
 */
////////////////////////////////////////////////
// 讒矩菴・
////////////////////////////////////////////////
//繧ｹ繧ｭ繝九Φ繧ｰ逕ｨ縺ｮ鬆らせ繝・・繧ｿ繧偵・縺ｨ縺ｾ縺ｨ繧√・
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｸ縺ｮ蜈･蜉帙・
struct SVSIn{
	float4 pos 		: POSITION;		//繝｢繝・Ν縺ｮ鬆らせ蠎ｧ讓吶・
    float3 normal	: NORMAL;		//豕慕ｷ・
	float2 uv 		: TEXCOORD0;	//UV蠎ｧ讓吶・
    float3 tangent  : TANGENT;      //謗･繝吶け繝医Ν
    float3 biNormal : BINORMAL;     //蠕薙・繧ｯ繝医Ν
	SSkinVSIn skinVert;				//繧ｹ繧ｭ繝ｳ逕ｨ縺ｮ繝・・繧ｿ縲・
};
//繝斐け繧ｻ繝ｫ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｸ縺ｮ蜈･蜉帙・
struct SPSIn{
	float4 pos 			: SV_POSITION;	//繧ｹ繧ｯ繝ｪ繝ｼ繝ｳ遨ｺ髢薙〒縺ｮ繝斐け繧ｻ繝ｫ縺ｮ蠎ｧ讓吶・
    float3 normal		: NORMAL;		//豕慕ｷ・
	float2 uv 			: TEXCOORD0;	//uv蠎ｧ讓吶・
    float3 tangent      : TANGENT;      //謗･繝吶け繝医Ν
    float3 biNormal     : BINORMAL;     //蠕薙・繧ｯ繝医Ν
    float3 worldPos		: TEXCOORD1;    //繝ｯ繝ｼ繝ｫ繝牙ｺｧ讓・
    float3 normalInView : TEXCOORD2;    //繧ｫ繝｡繝ｩ遨ｺ髢薙・豕慕ｷ・
    float4 posInLVP     : TEXCOORD3;    //繝ｩ繧､繝医ン繝･繝ｼ繧ｹ繧ｯ繝ｪ繝ｼ繝ｳ遨ｺ髢薙〒縺ｮ繝斐け繧ｻ繝ｫ縺ｮ蠎ｧ讓・
};

struct SPSOut{
    float4 color : SV_Target0;
};

struct DirectionLight
{
    float3 direction; //繝ｩ繧､繝医・譁ｹ蜷・
    float3 color;     //繝ｩ繧､繝医・繧ｫ繝ｩ繝ｼ
};

struct PointLight
{
    float3 position; //繝ｩ繧､繝医・菴咲ｽｮ
    float3 color;    //繝ｩ繧､繝医・繧ｫ繝ｩ繝ｼ
    float range;     //繝ｩ繧､繝医・蠖ｱ髻ｿ遽・峇
};

struct SpotLight
{
    float3 position;    //繝ｩ繧､繝医・菴咲ｽｮ
    float3 color;       //繝ｩ繧､繝医・繧ｫ繝ｩ繝ｼ
    float range;        //繝ｩ繧､繝医・蠖ｱ髻ｿ遽・峇
    float3 direction;   //繝ｩ繧､繝医・謾ｾ蟆・婿蜷・
    float angle;        //繝ｩ繧､繝医・謾ｾ蟆・ｧ貞ｺｦ
};

struct HemLight
{
    float3 groundColor;     //蝨ｰ髱｢濶ｲ
    float3 skyColor;        //螟ｩ逅・牡
    float3 groundNormal;    //蝨ｰ髱｢縺ｮ豕慕ｷ・
};

////////////////////////////////////////////////
// 螳壽焚繝舌ャ繝輔ぃ縲・
////////////////////////////////////////////////
//繝｢繝・Ν逕ｨ縺ｮ螳壽焚繝舌ャ繝輔ぃ
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
    float alphaColor;
    float scrollSpeed;
    float deltaTime;
};

//繝ｩ繧､繝育畑縺ｮ螳壽焚繝舌ャ繝輔ぃ
cbuffer LightCb : register(b1)
{
    DirectionLight directionLight;  //繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝・
    float3 eyePos;                  //繧ｫ繝｡繝ｩ縺ｮ菴咲ｽｮ
    float3 ambientLig;              //迺ｰ蠅・・
    PointLight pointLight[10];      //繝昴う繝ｳ繝医Λ繧､繝・
    SpotLight spotLight[10];        //繧ｹ繝昴ャ繝医Λ繧､繝・
    HemLight hemLight;              //蜊顔帥繝ｩ繧､繝・
    float4x4 mLVP;                  //繝ｩ繧､繝医ン繝･繝ｼ繝励Ο繧ｸ繧ｧ繧ｯ繧ｷ繝ｧ繝ｳ陦悟・
};

////////////////////////////////////////////////
// 繧ｰ繝ｭ繝ｼ繝舌Ν螟画焚縲・
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//繧｢繝ｫ繝吶ラ繝槭ャ繝・
Texture2D<float4> g_normalMap :register(t1);            //豕慕ｷ壹・繝・・
Texture2D<float4> g_specularMap : register(t2);         //繧ｹ繝壹く繝･繝ｩ繝槭ャ繝・
//Texture2D<float4> g_aoMap : register(t10);            //AO繝槭ャ繝・
Texture2D<float4> g_shadowMap : register(t10);          //繧ｷ繝｣繝峨え繝槭ャ繝・
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//繝懊・繝ｳ陦悟・
sampler g_sampler : register(s0);	//繧ｵ繝ｳ繝励Λ繧ｹ繝・・繝医・

////////////////////////////////////////////////
// 髢｢謨ｰ螳夂ｾｩ縲・
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal,float specular);
float3 CalcLigFromDirectionLight(SPSIn psIn, float3 normal, float specular);
float3 CalcLigFromPointLight(SPSIn psIn, int num, float3 normal, float specular);
float3 CalcLigFromSpotLight(SPSIn psIn, int num, float3 normal, float specular);
float3 CalcLimPower(SPSIn psIn);
float3 CalcLigFromHemLight(SPSIn psIn);
float3 CalcNormalMap(SPSIn psIn);
float CalcSpecularMap(SPSIn psIn);
//float3 CalcAoMap(SPSIn psIn);
float CalcShadowMap(SPSIn psIn);

/// <summary>
//繧ｹ繧ｭ繝ｳ陦悟・繧定ｨ育ｮ励☆繧九・
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
/// 鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｳ繧｢髢｢謨ｰ縲・
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
    float4 worldPos = psIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

    psIn.normal = normalize(mul(m, vsIn.normal));
    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));
	psIn.uv = vsIn.uv;
    
    if(scrollSpeed!=0.0f)
    {
        psIn.uv.x += scrollSpeed * deltaTime;
    }

    psIn.normalInView = mul(mView, psIn.normal);
    
    psIn.posInLVP = mul(mLVP, worldPos);
    
	return psIn;
}

/// <summary>
/// 繧ｹ繧ｭ繝ｳ縺ｪ縺励Γ繝・す繝･逕ｨ縺ｮ鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// 繧ｹ繧ｭ繝ｳ縺ゅｊ繝｡繝・す繝･縺ｮ鬆らせ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// 繝斐け繧ｻ繝ｫ繧ｷ繧ｧ繝ｼ繝繝ｼ縺ｮ繧ｨ繝ｳ繝医Μ繝ｼ髢｢謨ｰ縲・
/// </summary>
SPSOut PSMain(SPSIn psIn, int isShadowReceiver) : SV_Target0
{
    SPSOut psOut;
    
    //豕慕ｷ壹・繝・・ 
    float3 normalMap = CalcNormalMap(psIn);
    
     //繧ｹ繝壹く繝･繝ｩ繝槭ャ繝・
    float specularMap = CalcSpecularMap(psIn);
   
    //繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝・
    float3 directionLig = CalcLigFromDirectionLight(psIn, normalMap, specularMap);
    
    //隍・焚蛟九・繝ｩ繧､繝・ぅ繝ｳ繧ｰ險育ｮ・
    float3 pointLig[10];
    float3 spotLig[10];
    for (int i = 0; i < 10; i++)
    {
        //繝昴う繝ｳ繝医Λ繧､繝・
        pointLig[i] = CalcLigFromPointLight(psIn, i, normalMap, specularMap);
        //繧ｹ繝昴ャ繝医Λ繧､繝・
        spotLig[i] = CalcLigFromSpotLight(psIn, i, normalMap, specularMap);
    }
    
    //繝ｪ繝繝ｩ繧､繝・
    float3 limLig = CalcLimPower(psIn);
    
    //蜊顔帥繝ｩ繧､繝・
    float3 hemLig = CalcLigFromHemLight(psIn);
     
    ////AO繝槭ャ繝・
    //float3 aoMap = CalcAoMap(psIn);
    
	//譛邨ら噪縺ｪ蜈峨ｒ豎ゅａ繧・
    float3 lig = directionLig + ambientLig + hemLig /*+ normalMap + specularMap*/;
    
    for (int j = 0; j < 10; j++)
    {
        lig += pointLig[j];
        lig += spotLig[j];
    }
    
    lig += limLig;
    
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);
	
    albedoColor.xyz *= lig;
    
    float shadow = 1.0f;
    if(isShadowReceiver==1)
    {
        shadow = CalcShadowMap(psIn);
    }
    
    albedoColor.xyz *= shadow;
    
    albedoColor.a *= alphaColor;
    psOut.color = albedoColor;
	
	return psOut;
}

SPSOut PSShadowReceiverMain(SPSIn psIn) : SV_Target0
{
    return PSMain(psIn, 1);
}

SPSOut PSNormalMain(SPSIn psIn) : SV_Target0
{
    return PSMain(psIn, 0);
}

////諡｡謨｣蜿榊ｰ・・
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{    
    return max(0.0f, dot(normal, -lightDirection)) * lightColor;
}

//髀｡髱｢蜿榊ｰ・・
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal,float specular)
{
    float3 refVec = reflect(lightDirection, normal);
	
    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);
	
    float t = saturate(dot(refVec, toEye));
    if (t < 0.0f)
    {
        t = 0.0f;
    }
	
    t = pow(t, 5.0f);
    
    float3 specLig = lightColor * t;
    specLig *= specular * 10.0f;
	
    return specLig;
}

//繝・ぅ繝ｬ繧ｯ繧ｷ繝ｧ繝ｳ繝ｩ繧､繝・
float3 CalcLigFromDirectionLight(SPSIn psIn, float3 normal, float specular)
{
    //諡｡謨｣蜿榊ｰ・・繧呈ｱゅａ繧・
    float3 diffuseLig = CalcLambertDiffuse(directionLight.direction, directionLight.color, normal);
    
    //髀｡髱｢蜿榊ｰ・・繧呈ｱゅａ繧・
    float3 specularLig = CalcPhongSpecular(directionLight.direction, directionLight.color, psIn.worldPos, normal, specular);
 
    //諡｡謨｣蜿榊ｰ・・ + 髀｡髱｢蜿榊ｰ・・
    return diffuseLig + specularLig;
}

//繝昴う繝ｳ繝医Λ繧､繝・
float3 CalcLigFromPointLight(SPSIn psIn, int num, float3 normal, float specular)
{
    //繝昴う繝ｳ繝医Λ繧､繝医・蜷代″繧呈ｱゅａ繧・
    float3 ligDir = psIn.worldPos - pointLight[num].position;
    ligDir = normalize(ligDir);
    
    //諡｡謨｣蜿榊ｰ・・繧呈ｱゅａ繧・
    float3 diffusePoint = CalcLambertDiffuse(ligDir, pointLight[num].color, normal);
    
    //髀｡髱｢蜿榊ｰ・・繧呈ｱゅａ繧・
    float3 specularPoint = CalcPhongSpecular(ligDir, pointLight[num].color, psIn.worldPos, normal, specular);
    
    //繝昴う繝ｳ繝医Λ繧､繝医→縺ｮ霍晞屬繧呈ｱゅａ繧・
    float distance = length(psIn.worldPos - pointLight[num].position);
    
    //霍晞屬縺ｫ繧医ｋ蠖ｱ髻ｿ邇・ｒ豎ゅａ繧・
    float affect = 1.0f - 1.0f / pointLight[num].range * distance;
    
    if(affect<0.0f)
    {
        affect = 0.0f;
    }
    
    affect = pow(affect, 3.0f);
    
    //蠖ｱ髻ｿ邇・ｒ荵礼ｮ励＠縺ｦ蜿榊ｰ・・繧貞ｼｱ繧√ｋ
    diffusePoint *= affect;
    specularPoint *= affect;
    
    return diffusePoint + specularPoint;
}

//繧ｹ繝昴ャ繝医Λ繧､繝・
float3 CalcLigFromSpotLight(SPSIn psIn, int num, float3 normal, float specular)
{
    //繧ｹ繝昴ャ繝医Λ繧､繝医・蜷代″繧呈ｱゅａ繧・
    float3 ligDir = psIn.worldPos - spotLight[num].position;
    ligDir = normalize(ligDir);
    
    //諡｡謨｣蜿榊ｰ・・繧呈ｱゅａ繧・
    float3 diffuseSpot = CalcLambertDiffuse(ligDir, spotLight[num].color, normal);
    
    //髀｡髱｢蜿榊ｰ・・繧呈ｱゅａ繧・
    float3 specularSpot = CalcPhongSpecular(ligDir, spotLight[num].color, psIn.worldPos, normal, specular);
    
    //繧ｹ繝昴ャ繝医Λ繧､繝医→縺ｮ霍晞屬繧呈ｱゅａ繧・
    float distance = length(psIn.worldPos - spotLight[num].position);
    
    //霍晞屬縺ｫ繧医ｋ蠖ｱ髻ｿ邇・ｒ豎ゅａ繧・
    float affect = 1.0f - 1.0f / spotLight[num].range * distance;
    
    if(affect<0.0f)
    {
        affect = 0.0f;
    }
    
    affect = pow(affect, 3.0f);
    
    //霍晞屬縺ｫ繧医ｋ蠖ｱ髻ｿ邇・ｒ荵礼ｮ励＠縺ｦ蜿榊ｰ・・繧貞ｼｱ繧√ｋ
    diffuseSpot *= affect;
    specularSpot *= affect;
    
    ///蜈･蟆・・縺ｨ蟆・・譁ｹ蜷代・隗貞ｺｦ繧呈ｱゅａ繧・
    float angle = dot(ligDir, spotLight[num].direction);
    angle = abs(acos(angle));
    
    //隗貞ｺｦ縺ｫ繧医ｋ蠖ｱ髻ｿ邇・ｒ豎ゅａ繧・
    affect = 1.0f - 1.0f / spotLight[num].angle * angle;
    
    if(affect<0.0f)
    {
        affect = 0.0f;
    }
    
    affect = pow(affect, 0.5f);
    
    //隗貞ｺｦ縺ｫ繧医ｋ蠖ｱ髻ｿ邇・ｒ荵礼ｮ励＠縺ｦ蜿榊ｰ・・繧貞ｼｱ繧√ｋ
    diffuseSpot *= affect;
    specularSpot *= affect;
    
    return diffuseSpot + specularSpot;
}

//繝ｪ繝繝ｩ繧､繝・
float3 CalcLimPower(SPSIn psIn)
{
    //繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｮ豕慕ｷ壹→蜈峨・蜈･蟆・婿蜷代↓萓晏ｭ倥☆繧九Μ繝縺ｮ蠑ｷ縺輔ｒ豎ゅａ繧・
    float power1 = 1.0f - max(0.0f, dot(directionLight.direction, psIn.normal));
    
    //繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｮ豕慕ｷ壹→隕也ｷ壹・譁ｹ蜷代↓萓晏ｭ倥☆繧九Μ繝縺ｮ蠑ｷ縺輔ｒ豎ゅａ繧・
    float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);
    
    //譛邨ら噪縺ｪ繝ｪ繝縺ｮ蠑ｷ縺輔ｒ豎ゅａ繧・
    float limPower = power1 * power2;
    
    limPower = pow(limPower, 1.3f);
    
    return limPower * directionLight.color;
}

//蜊顔帥繝ｩ繧､繝・
float3 CalcLigFromHemLight(SPSIn psIn)
{
    //繧ｵ繝ｼ繝輔ぉ繧､繧ｹ縺ｮ豕慕ｷ壹→蝨ｰ髱｢縺ｮ豕慕ｷ壹→縺ｮ蜀・ｩ阪ｒ豎ゅａ繧・
    float t = dot(psIn.normal, hemLight.groundNormal);
    
    //蜀・ｩ阪・邨先棡繧・・・縺ｮ遽・峇縺ｫ螟画鋤縺吶ｋ
    t = (t + 1.0f) / 2.0f;
    
    return lerp(hemLight.groundColor, hemLight.skyColor, t);
}

//豕慕ｷ壹・繝・・
float3 CalcNormalMap(SPSIn psIn)
{
    float3 normal = psIn.normal;   
    //豕慕ｷ壹・繝・・縺九ｉ繧ｿ繝ｳ繧ｸ繧ｧ繝ｳ繝医せ繝壹・繧ｹ縺ｮ豕慕ｷ壹ｒ繧ｵ繝ｳ繝励Μ繝ｳ繧ｰ縺吶ｋ
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;
    localNormal = (localNormal - 0.5f) * 2.0f;
    
    //繧ｿ繝ｳ繧ｸ繧ｧ繝ｳ繝医せ繝壹・繧ｹ縺ｮ豕慕ｷ壹ｒ繝ｯ繝ｼ繝ｫ繝峨せ繝壹・繧ｹ縺ｫ螟画鋤縺吶ｋ
    normal = psIn.tangent * localNormal.x
           + psIn.biNormal * localNormal.y
           + normal * localNormal.z;
    
    return normal;
}

//繧ｹ繝壹く繝･繝ｩ繝槭ャ繝・
float CalcSpecularMap(SPSIn psIn)
{    
    float specPower = g_specularMap.Sample(g_sampler, psIn.uv).r;
    return specPower;
}

////AO繝槭ャ繝・
//float3 CalcAoMap(SPSIn psIn)
//{
//    //迺ｰ蠅・・繧呈ｱゅａ繧・
//    float3 ambient = ambientLig;
    
//    float ambientPower = g_aoMap.Sample(g_sampler, psIn.uv);
    
//    ambient *= ambientPower;
    
//    return ambient;
//}

float CalcShadowMap(SPSIn psIn)
{
    float2 shadowMapUV = psIn.posInLVP.xy / psIn.posInLVP.w;
    shadowMapUV *= float2(0.5f, -0.5f);
    shadowMapUV += 0.5f;
    
    float shadowMap = 1.0f;
    float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;
    if(shadowMapUV.x>0.0f&&shadowMapUV.x<1.0f
        && shadowMapUV.y>0.0f&&shadowMapUV.y<1.0f)
    {
        //shadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV);
        float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
        if(zInLVP>zInShadowMap)
        {
            shadowMap = 0.5f;
        }
    }
    
    return shadowMap;
}