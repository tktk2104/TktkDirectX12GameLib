
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
	float4		Position			: POSITION;
	float3		Normal				: NORMAL;
	float2		TexCoord			: TEXCOORD;
	int4		BlendIndices		: BLENDINDICES;
	float4		BlendWeight			: BLENDWEIGHT;
	float3		Tangent				: TANGENT;
	float3		Binormal			: BINORMAL;

	float4x4	WorldMatrix			: WORLDMATRIX;
	uint		InstanceId			: SV_InstanceID;
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

// 骨行列情報テクスチャ
Texture2D		g_BoneMatricesTexture  : register(t0);

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	float4x4 use1stMat = float4x4(
		g_BoneMatricesTexture.Load(int3((Input.BlendIndices.x * 4) + 0, Input.InstanceId, 0)),
		g_BoneMatricesTexture.Load(int3((Input.BlendIndices.x * 4) + 1, Input.InstanceId, 0)),
		g_BoneMatricesTexture.Load(int3((Input.BlendIndices.x * 4) + 2, Input.InstanceId, 0)),
		g_BoneMatricesTexture.Load(int3((Input.BlendIndices.x * 4) + 3, Input.InstanceId, 0))
		);

	float4x4 use2ndMat = float4x4(
		g_BoneMatricesTexture.Load(int3((Input.BlendIndices.y * 4) + 0, Input.InstanceId, 0)),
		g_BoneMatricesTexture.Load(int3((Input.BlendIndices.y * 4) + 1, Input.InstanceId, 0)),
		g_BoneMatricesTexture.Load(int3((Input.BlendIndices.y * 4) + 2, Input.InstanceId, 0)),
		g_BoneMatricesTexture.Load(int3((Input.BlendIndices.y * 4) + 3, Input.InstanceId, 0))
		);

	// この頂点が使用するメッシュのボーンのローカル行列を計算する
	float4x4 LocalMatrix 
		= mul(use1stMat, Input.BlendWeight.x)
		+ mul(use2ndMat, Input.BlendWeight.y);

	// 【この頂点座標の座標変換】
	// ボーンのローカル行列を使って座標変換する
	float4 LocalPosition	= mul(LocalMatrix,	Input.Position);
	// 定数バッファで取得したワールド行列を使って座標変換する
	float4 WorldPosition	= mul(Input.WorldMatrix,	LocalPosition);
	// 定数バッファで取得したビュー行列を使って座標変換する
	float4 ViewPosition		= mul(ViewMatrix,	WorldPosition);
	
	// 座標変換で使用する4x4の行列を3x3の行列に直す
	float3x3 LocalMatrix3	= (float3x3)LocalMatrix;
	float3x3 WorldMatrix3	= (float3x3)Input.WorldMatrix;
	float3x3 ViewMatrix3	= (float3x3)ViewMatrix;
	
	// 【この頂点法線の座標変換】（処理は頂点座標の座標変換とほぼ同じ）
	float3 localNormal		= mul(LocalMatrix3, Input.Normal);
	float3 worldNormal		= mul(WorldMatrix3, localNormal);
	float3 viewNormal		= mul(ViewMatrix3, worldNormal);

	// 【この頂点タンジェントの座標変換】（処理は頂点座標の座標変換とほぼ同じ）
	float3 localTangent		= mul(LocalMatrix3, Input.Tangent);
	float3 worldTangent		= mul(WorldMatrix3, localTangent);
	float3 viewTangent		= mul(ViewMatrix3,	worldTangent);
	
	// 【この頂点バイノーマルの座標変換】（処理は頂点座標の座標変換とほぼ同じ）
	float3 localBinormal	= mul(LocalMatrix3, Input.Binormal);
	float3 worldBinormal	= mul(WorldMatrix3, localBinormal);
	float3 viewBinormal		= mul(ViewMatrix3,	worldBinormal);

	// ビュー空間でのライト座標を計算する
	float3 viewLight		= mul(ViewMatrix, float4(lightPosition, 1.0)).xyz;

	// 接空間変換行列を計算
	float3x3 matTBN			= float3x3(normalize(viewTangent), normalize(viewBinormal), normalize(viewNormal));

	// パースペクティブ空間での頂点座標を計算
	Output.Position			= mul(ProjectionMatrix, ViewPosition);
	// TexCoordをそのまま渡す
	Output.TexCoord			= Input.TexCoord;
	// 接空間での「頂点→カメラのベクトル」を計算
	Output.View				= mul(matTBN, -ViewPosition.xyz);
	// 接空間での「頂点→ライトのベクトル」を計算
	Output.VLight			= mul(matTBN, (viewLight - ViewPosition.xyz));
	// シャドウマップの描画に使用した座標空間での頂点座標を計算
	Output.LightBasePos		= mul(shadowMapViewProjMat, WorldPosition);

	return Output;
}