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
		unsigned int create(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// 指定の頂点バッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(unsigned int handle);

		// コマンドリストに指定の頂点バッファを登録する
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定の頂点バッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

		// 指定の頂点バッファのポインタを取得する
		ID3D12Resource* getBufferPtr(unsigned int handle) const;

	private:

		tktkContainer::ResourceContainer<VertexBufferData> m_vertexBufferDataArray;
	};
}
#endif // !VERTEX_BUFFER_H_