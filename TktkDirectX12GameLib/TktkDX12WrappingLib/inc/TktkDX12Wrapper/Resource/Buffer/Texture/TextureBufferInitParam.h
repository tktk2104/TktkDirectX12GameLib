#ifndef TEXTURE_BUFFER_INIT_PARAM_H_
#define TEXTURE_BUFFER_INIT_PARAM_H_

#include <vector>
#include "../../../Includer/D3d12Includer.h"

namespace tktk
{
	// テクスチャデータ
	struct TexBuffData
	{
		std::vector<unsigned char>	textureData;	// 生の色情報データ
		unsigned int				width;			// テクスチャの横幅
		unsigned int				height;			// テクスチャの縦幅
	};

	// テクスチャのフォーマットデータ
	struct TexBufFormatParam
	{
		D3D12_RESOURCE_DIMENSION	resourceDimension;	// 何次元のテクスチャか？
		DXGI_FORMAT					format;				// 色情報のフォーマット
		unsigned int				arraySize;			// テクスチャ情報の配列の数
		unsigned int				mipLevels;			// ミップレベル
		unsigned int				sampleDescCount;	// サンプルデスクの数
		unsigned int				sampleDescQuality;	// サンプルデスクの品質
	};
}
#endif // !TEXTURE_BUFFER_INIT_PARAM_H_