
// �J�����̍s��̏��
cbuffer CameraBuffer : register(b0)
{
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
};

// ���͒��_���
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

// �o�͒��_���
struct VS_OUTPUT
{
	float4 Position     : SV_POSITION;
};

// ���s����e�N�X�`��
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

	// ���̒��_���g�p���郁�b�V���̃{�[���̃��[�J���s����v�Z����
	float4x4 LocalMatrix
		= mul(use1stMat, Input.BlendWeight.x)
		+ mul(use2ndMat, Input.BlendWeight.y);

	// �y���̒��_���W�̍��W�ϊ��z
	// �{�[���̃��[�J���s����g���č��W�ϊ�����
	float4 LocalPosition = mul(LocalMatrix, Input.Position);
	// �萔�o�b�t�@�Ŏ擾�������[���h�s����g���č��W�ϊ�����
	float4 WorldPosition = mul(Input.WorldMatrix, LocalPosition);
	// �萔�o�b�t�@�Ŏ擾�����r���[�s����g���č��W�ϊ�����
	float4 ViewPosition = mul(ViewMatrix, WorldPosition);;
	
	// �p�[�X�y�N�e�B�u��Ԃł̒��_���W���v�Z
	Output.Position = mul(ProjectionMatrix, ViewPosition);

	return Output;
}