// ���͒��_���
struct PS_INPUT
{
	float4 Position     : SV_POSITION;
	float4 AlbedoColor	: ALBEDOCOLOR;
};

// �P�F�h��Ԃ��V�F�[�_�[
float4 main(PS_INPUT Input) : SV_TARGET
{
	return Input.AlbedoColor;
}