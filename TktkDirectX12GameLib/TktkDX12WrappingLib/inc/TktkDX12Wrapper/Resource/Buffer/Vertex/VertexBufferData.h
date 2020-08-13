#ifndef VERTEX_BUFFER_DATA_H_
#define VERTEX_BUFFER_DATA_H_

#include <forward_list>
#include "../../../Includer/D3d12Includer.h"

namespace tktk
{
	// 頂点バッファを管理するクラス
	class VertexBufferData
	{
	public:

		VertexBufferData(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);
		~VertexBufferData();

	public:

		// コマンドリストに頂点バッファを登録する
		void set(ID3D12GraphicsCommandList* commandList) const;

		// 頂点バッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

	private:

		ID3D12Resource*				m_vertexBuffer		{ nullptr };
		D3D12_VERTEX_BUFFER_VIEW	m_vertexBufferView	{};
		std::forward_list<ID3D12Resource*> m_uploadBufferList{};
	};
}
#endif // !VERTEX_BUFFER_DATA_H_