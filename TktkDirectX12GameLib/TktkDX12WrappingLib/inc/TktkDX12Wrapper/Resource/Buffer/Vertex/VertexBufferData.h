#ifndef VERTEX_BUFFER_DATA_H_
#define VERTEX_BUFFER_DATA_H_

#include <forward_list>
#include "../../../Includer/D3d12Includer.h"
#include "VertexDataCarrier.h"

namespace tktk
{
	// 頂点バッファを管理するクラス
	class VertexBufferData
	{
	public:

		VertexBufferData(ID3D12Device* device, const VertexDataCarrier& vertexData);
		~VertexBufferData();

		// ムーブコンストラクタ
		VertexBufferData(VertexBufferData&& other) noexcept;

	public:

		// コマンドリストに頂点バッファを登録する
		void set(ID3D12GraphicsCommandList* commandList) const;

		// 自身のバッファのポインタを取得する
		ID3D12Resource* getBufferPtr() const;

	private:

		ID3D12Resource*						m_vertexBuffer		{ nullptr };
		D3D12_VERTEX_BUFFER_VIEW			m_vertexBufferView	{};
	};
}
#endif // !VERTEX_BUFFER_DATA_H_