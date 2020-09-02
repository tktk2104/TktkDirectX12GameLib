#ifndef COPY_BUFFER_H_
#define COPY_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "CopyBufferData.h"

namespace tktk
{
	// 「CopyBufferData」を管理するクラス
	class CopyBuffer
	{
	public:

		explicit CopyBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~CopyBuffer() = default;

	public:

		// 「CopyBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(ID3D12Device* device, const CopyBufferInitParam& initParam);

		// 「CopyBufferData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		unsigned int copy(ID3D12Device* device, unsigned int originalHandle);

		// 指定のコピーバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(unsigned int handle);

		// 引数のポインタのデータを指定のコピーバッファにコピーする
		void updateBuffer(unsigned int handle, unsigned int bufferSize, const void* bufferDataTopPos);

		// 指定のコピーバッファのコピー先のバッファの種類を取得する
		BufferType getTargetBufferType(unsigned int handle) const;

		// 指定のコピーバッファのコピー先のバッファのハンドルを取得する
		unsigned int getTargetBufferHandle(unsigned int handle) const;

		// 引数のバッファに指定のコピーバッファの内容をコピーするGPU命令を設定する
		void copyBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const;

	private:

		tktkContainer::ResourceContainer<CopyBufferData> m_copyBufferDataArray;
	};
}
#endif // !COPY_BUFFER_H_