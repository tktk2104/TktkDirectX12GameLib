
// カメラの行列の情報
cbuffer CameraBuffer : register(b0)
{
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
};

// ライト計算に必要な情報
cbuffer LightBuffer : register(b1)
{
	float4		lightAmbient;
	float4		lightDiffuse;
	float4		lightSpeqular;
	float3		lightPosition;
	float		lightDataPad;
}

// シャドウマップを使った描画に必要な情報
cbuffer ShadowMapBuffer : register(b2)
{
	float4x4	shadowMapViewProjMat;
}

// 入力頂点情報
struct VS_INPUT
{
	float4		Position		: POSITION;
	float3		Normal			: NORMAL;
	float2		TexCoord		: TEXCOORD;
	int4		BlendIndices	: BLENDINDICES;
	float4		BlendWeight		: BLENDWEIGHT;
	float3		Tangent			: TANGENT;
	float3		Binormal		: BINORMAL;

	float4x4	WorldMatrix		: WORLDMATRIX;
	uint		InstanceId      : SV_InstanceID;
};

// 出力頂点情報
struct VS_OUTPUT
{
	float4 Position     : SV_POSITION;
	float2 TexCoord     : TEXCOORD0;
	float3 View			: TEXCOORD1;
	float3 VLight		: TEXCOORD2;
	float4 LightBasePos : TEXCOORD3;
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	// 【この頂点座標の座標変換】
	// 定数バッファで取得したワールド行列を使って座標変換する
	float4 WorldPosition = mul(Input.WorldMatrix, Input.Position);
	// 定数バッファで取得したビュー行列を使って座標変換する
	float4 ViewPosition = mul(ViewMatrix, WorldPosition);

	// 座標変換で使用する4x4の行列を3x3の行列に直す
	float3x3 WorldMatrix3 = (float3x3)Input.WorldMatrix;
	float3x3 ViewMatrix3 = (float3x3)ViewMatrix;

	// 【この頂点法線の座標変換】（処理は頂点座標の座標変換とほぼ同じ）
	float3 worldNormal = mul(WorldMatrix3, Input.Normal);
	float3 viewNormal = mul(ViewMatrix3, worldNormal);

	// 【この頂点タンジェントの座標変換】（処理は頂点座標の座標変換とほぼ同じ）
	float3 worldTangent = mul(WorldMatrix3, Input.Tangent);
	float3 viewTangent = mul(ViewMatrix3, worldTangent);

	// 【この頂点バイノーマルの座標変換】（処理は頂点座標の座標変換とほぼ同じ）
	float3 worldBinormal = mul(WorldMatrix3, Input.Binormal);
	float3 viewBinormal = mul(ViewMatrix3, worldBinormal);

	// ビュー空間でのライト座標を計算する
	float3 viewLight = mul(ViewMatrix, float4(lightPosition, 1.0)).xyz;

	// 接空間変換行列を計算
	float3x3 matTBN = float3x3(normalize(viewTangent), normalize(viewBinormal), normalize(viewNormal));

	// パースペクティブ空間での頂点座標を計算
	Output.Position = mul(ProjectionMatrix, ViewPosition);
	// TexCoordをそのまま渡す
	Output.TexCoord = Input.TexCoord;
	// 接空間での「頂点→カメラのベクトル」を計算
	Output.View = mul(matTBN, -ViewPosition.xyz);
	// 接空間での「頂点→ライトのベクトル」を計算
	Output.VLight = mul(matTBN, (viewLight - ViewPosition.xyz));
	// シャドウマップの描画に使用した座標空間での頂点座標を計算
	Output.LightBasePos = mul(shadowMapViewProjMat, WorldPosition);

	return Output;
}