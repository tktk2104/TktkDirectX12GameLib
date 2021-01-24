#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "VertexBufferData.h"

namespace tktk
{
	// 「VertexBufferData」を管理するクラス
	class VertexBuffer
	{
	public:

		explicit VertexBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~VertexBuffer() = default;

	public:

		// 「VertexBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(ID3D12Device* device, size_t strideDataSize, size_t allDataSize);

		// 指定の頂点バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// コマンドリストに指定の頂点バッファを登録する
		void set(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// コマンドリストに指定の頂点バッファを登録する（インスタンス描画用）
		void set(size_t meshVertHandle, size_t instancingVertHandle, ID3D12GraphicsCommandList* commandList) const;

		// 指定の頂点バッファのポインタを取得する
		ID3D12Resource* getBufferPtr(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<VertexBufferData> m_vertexBufferDataArray;
	};
}
#endif // !VERTEX_BUFFER_H_