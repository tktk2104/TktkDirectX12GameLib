
// ライト計算に必要な情報
cbuffer LightBuffer : register(b0)
{
	float4		lightAmbient;
	float4		lightDiffuse;
	float4		lightSpeqular;
	float3		lightPosition;
	float		lightDataPad;
}

// マテリアルの情報
cbuffer MaterialBuffer : register(b1)
{
	float4		materialAmbient;
	float4		materialDiffuse;
	float4		materialSpecular;
	float4		materialEmissive;
	float		materialShiniess;
	float3		materialDataPad;
}

// 入力頂点情報
struct PS_INPUT
{
	float4 Position     : SV_POSITION;
	float2 TexCoord     : TEXCOORD0;
	float3 View			: TEXCOORD1;
	float3 Light		: TEXCOORD2;
	float4 LightBasePos : TEXCOORD3;
};

// アルベドマップ
SamplerState	g_AlbedoMapSampler  : register(s0);
Texture2D		g_AlbedoMapTexture  : register(t0);

// ライトからの深度テクスチャ
SamplerState		g_LightDepthSampler : register(s1);
Texture2D<float>	g_LightDepthTexture	: register(t1);

//// 法線マップ
//SamplerState g_NormalMapSampler  : register(s1);
//Texture2D    g_NormalMapTexture  : register(t1);

float4 main(PS_INPUT Input) : SV_TARGET
{
	float3 N = float3(0.0, 0.0, 1.0);//g_NormalMapTexture.Sample(g_NormalMapSampler, Input.TexCoord).xyz
	float3 V = normalize(Input.View);
	float3 L = normalize(Input.Light);
	float3 H = normalize(L + V);
	
	float diffuse = max(dot(L, N), 0.0);
	float specular = pow(max(dot(N, H), 0.0), materialShiniess);
	
	float3 posFromLightVP	= Input.LightBasePos.xyz / Input.LightBasePos.w;
	float2 shadowUV			= (posFromLightVP.xy + float2(1, - 1)) * float2(0.5, -0.5);
	float depthFromLight	= g_LightDepthTexture.Sample(g_LightDepthSampler, shadowUV);

	float shadowWeight = 1.0;

	if (depthFromLight < posFromLightVP.z - 0.001)
	{
		shadowWeight = 0.5;
	}

	float4 baseColor = g_AlbedoMapTexture.Sample(g_AlbedoMapSampler, Input.TexCoord) * shadowWeight;
	
	float4 resultColor
		= materialAmbient	* lightAmbient	* baseColor
		+ materialDiffuse	* lightDiffuse	* diffuse * baseColor
		+ materialSpecular	* lightSpeqular * specular * baseColor
		+ materialEmissive	* baseColor;
	
	resultColor.a = baseColor.a * materialDiffuse.a;
	
	return resultColor;
}