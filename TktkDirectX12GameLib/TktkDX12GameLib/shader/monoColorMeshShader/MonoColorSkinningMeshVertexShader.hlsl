
// カメラの行列の情報
cbuffer CameraBuffer : register(b0)
{
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
};

// スキニングメッシュアニメーションに必要な情報
cbuffer BoneMatBuffer : register(b1)
{
	float4x4    boneMatrices[128];
};

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
	float4		AlbedoColor		: ALBEDOCOLOR;
	uint		InstanceId		: SV_InstanceID;
};

// 出力頂点情報
struct VS_OUTPUT
{
	float4 Position     : SV_POSITION;
	float4 AlbedoColor	: ALBEDOCOLOR;
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	// この頂点が使用するメッシュのボーンのローカル行列を計算する
	float4x4 LocalMatrix
		= mul(boneMatrices[Input.BlendIndices.x], Input.BlendWeight.x)
		+ mul(boneMatrices[Input.BlendIndices.y], Input.BlendWeight.y);

	// 【この頂点座標の座標変換】
	// ボーンのローカル行列を使って座標変換する
	float4 LocalPosition = mul(LocalMatrix, Input.Position);
	// 定数バッファで取得したワールド行列を使って座標変換する
	float4 WorldPosition = mul(Input.WorldMatrix, LocalPosition);
	// 定数バッファで取得したビュー行列を使って座標変換する
	float4 ViewPosition = mul(ViewMatrix, WorldPosition);

	// パースペクティブ空間での頂点座標を計算
	Output.Position = mul(ProjectionMatrix, ViewPosition);
	
	// アルベドカラーをそのまま渡す
	Output.AlbedoColor = Input.AlbedoColor;

	return Output;
}