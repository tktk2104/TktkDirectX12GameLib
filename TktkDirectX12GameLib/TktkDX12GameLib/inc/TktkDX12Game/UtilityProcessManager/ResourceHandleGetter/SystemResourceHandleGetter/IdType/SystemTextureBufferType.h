#ifndef SYSTEM_TEXTURE_BUFFER_TYPE_H_
#define SYSTEM_TEXTURE_BUFFER_TYPE_H_

namespace tktk
{
	// システムで使用しているテクスチャバッファの種類
	enum class SystemTextureBufferType
	{
		White4x4,		// 4x4白テクスチャ
		Black4x4,		// 4x4黒テクスチャ

		FlatNormal4x4,	// 4x4平らな法線テクスチャ

		Text,			// テキスト描画用テクスチャ

		MeshBoneMatrix,	// シェーダーにボーン情報を渡す時に使用する1Dテクスチャ
	};
}
#endif // !SYSTEM_TEXTURE_BUFFER_TYPE_H_