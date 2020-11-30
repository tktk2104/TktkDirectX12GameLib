
// カメラの行列の情報
cbuffer CameraBuffer : register(b0)
{
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
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
	uint		InstanceId		: SV_InstanceID;
};

// 出力頂点情報
struct VS_OUTPUT
{
	float4 Position     : SV_POSITION;
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
	float4 LocalPosition = mul(LocalMatrix, Input.Position);
	// 定数バッファで取得したワールド行列を使って座標変換する
	float4 WorldPosition = mul(Input.WorldMatrix, LocalPosition);
	// 定数バッファで取得したビュー行列を使って座標変換する
	float4 ViewPosition = mul(ViewMatrix, WorldPosition);;
	
	// パースペクティブ空間での頂点座標を計算
	Output.Position = mul(ProjectionMatrix, ViewPosition);

	return Output;
}