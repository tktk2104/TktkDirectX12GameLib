#ifndef COPY_BUFFER_H_
#define COPY_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "UploadBufferData.h"

namespace tktk
{
	// 「UploadBufferData」を管理するクラス
	class UploadBuffer
	{
	public:

		explicit UploadBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~UploadBuffer() = default;

	public:

		// 「UploadBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(ID3D12Device* device, const UploadBufferInitParam& initParam);

		// 「UploadBufferData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		size_t duplicate(ID3D12Device* device, size_t originalHandle);

		// 指定のアップロードバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 引数のポインタのデータを指定のアップロードバッファにコピーする
		void updateBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// 指定のアップロードバッファのアップロード先のバッファの種類を取得する
		BufferType getTargetBufferType(size_t handle) const;

		// 指定のアップロードバッファのアップロード先のバッファのハンドルを取得する
		size_t getTargetBufferHandle(size_t handle) const;

		// 引数のバッファに指定のアップロードバッファの内容をアップロードするGPU命令を行う
		void copyBuffer(size_t handle, ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const;

		// 引数のテクスチャバッファに指定のアップロードバッファの内容をアップロードするGPU命令を行う
		void copyTexture(size_t handle, ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer, const D3D12_TEXTURE_COPY_LOCATION& srcCopyLoaction) const;

	private:

		tktkContainer::ResourceContainer<UploadBufferData> m_uploadBufferDataArray;
	};
}
#endif // !COPY_BUFFER_H_