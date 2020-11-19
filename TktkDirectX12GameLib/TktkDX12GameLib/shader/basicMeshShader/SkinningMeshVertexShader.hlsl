
// �J�����̍s��̏��
cbuffer CameraBuffer : register(b0)
{
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
};

// ���C�g�v�Z�ɕK�v�ȏ��
cbuffer LightBuffer : register(b1)
{
	float4		lightAmbient;
	float4		lightDiffuse;
	float4		lightSpeqular;
	float3		lightPosition;
	float		lightDataPad;
}

// �V���h�E�}�b�v���g�����`��ɕK�v�ȏ��
cbuffer ShadowMapBuffer : register(b2)
{
	float4x4	shadowMapViewProjMat;
}

// �X�L�j���O���b�V���A�j���[�V�����ɕK�v�ȏ��
cbuffer BoneMatBuffer : register(b3)
{
	float4x4    boneMatrices[128];
};

// ���͒��_���
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

// �o�͒��_���
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

	// ���̒��_���g�p���郁�b�V���̃{�[���̃��[�J���s����v�Z����
	float4x4 LocalMatrix 
		= mul(boneMatrices[Input.BlendIndices.x], Input.BlendWeight.x)
		+ mul(boneMatrices[Input.BlendIndices.y], Input.BlendWeight.y);

	// �y���̒��_���W�̍��W�ϊ��z
	// �{�[���̃��[�J���s����g���č��W�ϊ�����
	float4 LocalPosition	= mul(LocalMatrix,	Input.Position);
	// �萔�o�b�t�@�Ŏ擾�������[���h�s����g���č��W�ϊ�����
	float4 WorldPosition	= mul(Input.WorldMatrix,	LocalPosition);
	// �萔�o�b�t�@�Ŏ擾�����r���[�s����g���č��W�ϊ�����
	float4 ViewPosition		= mul(ViewMatrix,	WorldPosition);
	
	// ���W�ϊ��Ŏg�p����4x4�̍s���3x3�̍s��ɒ���
	float3x3 LocalMatrix3	= (float3x3)LocalMatrix;
	float3x3 WorldMatrix3	= (float3x3)Input.WorldMatrix;
	float3x3 ViewMatrix3	= (float3x3)ViewMatrix;
	
	// �y���̒��_�@���̍��W�ϊ��z�i�����͒��_���W�̍��W�ϊ��Ƃقړ����j
	float3 localNormal		= mul(LocalMatrix3, Input.Normal);
	float3 worldNormal		= mul(WorldMatrix3, localNormal);
	float3 viewNormal		= mul(ViewMatrix3, worldNormal);

	// �y���̒��_�^���W�F���g�̍��W�ϊ��z�i�����͒��_���W�̍��W�ϊ��Ƃقړ����j
	float3 localTangent		= mul(LocalMatrix3, Input.Tangent);
	float3 worldTangent		= mul(WorldMatrix3, localTangent);
	float3 viewTangent		= mul(ViewMatrix3,	worldTangent);
	
	// �y���̒��_�o�C�m�[�}���̍��W�ϊ��z�i�����͒��_���W�̍��W�ϊ��Ƃقړ����j
	float3 localBinormal	= mul(LocalMatrix3, Input.Binormal);
	float3 worldBinormal	= mul(WorldMatrix3, localBinormal);
	float3 viewBinormal		= mul(ViewMatrix3,	worldBinormal);

	// �r���[��Ԃł̃��C�g���W���v�Z����
	float3 viewLight		= mul(ViewMatrix, float4(lightPosition, 1.0)).xyz;

	// �ڋ�ԕϊ��s����v�Z
	float3x3 matTBN			= float3x3(normalize(viewTangent), normalize(viewBinormal), normalize(viewNormal));

	// �p�[�X�y�N�e�B�u��Ԃł̒��_���W���v�Z
	Output.Position			= mul(ProjectionMatrix, ViewPosition);
	// TexCoord�����̂܂ܓn��
	Output.TexCoord			= Input.TexCoord;
	// �ڋ�Ԃł́u���_���J�����̃x�N�g���v���v�Z
	Output.View				= mul(matTBN, -ViewPosition.xyz);
	// �ڋ�Ԃł́u���_�����C�g�̃x�N�g���v���v�Z
	Output.VLight			= mul(matTBN, (viewLight - ViewPosition.xyz));
	// �V���h�E�}�b�v�̕`��Ɏg�p�������W��Ԃł̒��_���W���v�Z
	Output.LightBasePos		= mul(shadowMapViewProjMat, WorldPosition);

	return Output;
}