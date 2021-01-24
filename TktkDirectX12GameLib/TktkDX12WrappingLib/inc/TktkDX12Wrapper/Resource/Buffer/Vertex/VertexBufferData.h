#ifndef VERTEX_BUFFER_DATA_H_
#define VERTEX_BUFFER_DATA_H_

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12Resource, D3D12_VERTEX_BUFFER_VIEW */
#include <d3d12.h>
#undef min
#undef max

#include "VertexDataCarrier.h"

namespace tktk
{
	// 頂点バッファを管理するクラス
	class VertexBufferData
	{
	public:

		VertexBufferData(ID3D12Device* device, size_t strideDataSize, size_t allDataSize);
		~VertexBufferData();

		// ムーブコンストラクタ
		VertexBufferData(VertexBufferData&& other) noexcept;

	public:

		// コマンドリストに頂点バッファを登録する
		void set(ID3D12GraphicsCommandList* commandList) const;

		// 自身のバッファのポインタを取得する
		ID3D12Resource* getBufferPtr() const;

		// 自身のバッファビューを取得する
		const D3D12_VERTEX_BUFFER_VIEW& getBufferView() const;

	private:

		ID3D12Resource*						m_vertexBuffer		{ nullptr };
		D3D12_VERTEX_BUFFER_VIEW			m_vertexBufferView	{};
	};
}
#endif // !VERTEX_BUFFER_DATA_H_