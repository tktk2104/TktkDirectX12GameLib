// 入力頂点情報
struct PS_INPUT
{
	float4 Position     : SV_POSITION;
	float4 AlbedoColor	: ALBEDOCOLOR;
};

// 単色塗りつぶしシェーダー
float4 main(PS_INPUT Input) : SV_TARGET
{
	return Input.AlbedoColor;
}