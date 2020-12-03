#ifndef COPY_BUFFER_DATA_H_
#define COPY_BUFFER_DATA_H_

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12Resource */
#include <d3d12.h>
#undef min
#undef max

#include "../BufferType.h"
#include "UploadBufferInitParam.h"
#include "../CopySourceDataCarrier.h"

namespace tktk
{
	// アップロードバッファを管理するクラス
	class UploadBufferData
	{
	public:

		UploadBufferData(ID3D12Device* device, const UploadBufferInitParam& initParam);
		~UploadBufferData();

		// コピー用コンストラクタ
		UploadBufferData(ID3D12Device* device, const UploadBufferData& other);

		// ムーブコンストラクタ
		UploadBufferData(UploadBufferData&& other) noexcept;

	public:

		// 引数のポインタのデータをアップロードバッファにコピーする
		void updateBuffer(const CopySourceDataCarrier& bufferData);

		// 自身のアップロード先のバッファの種類を取得する
		BufferType getTargetBufferType() const;

		// 自身のアップロード先のバッファのハンドルを取得する
		size_t getTargetBufferHandle() const;

		// 引数のバッファに自身のバッファの内容をアップロードするGPU命令を行う
		void copyBuffer(ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const;

		// 引数のテクスチャバッファに自身のバッファの内容をアップロードするGPU命令を行う
		void copyTexture(ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer, const D3D12_TEXTURE_COPY_LOCATION& srcCopyLoaction) const;

	private:

		BufferType		m_targetBufferType;
		size_t			m_targetBufferHandle;
		size_t			m_uploadBufferSize;
		ID3D12Resource* m_uploadBuffer		{ nullptr };
	};
}
#endif // !COPY_BUFFER_DATA_H_