#ifndef INDEX_BUFFER_DATA_H_
#define INDEX_BUFFER_DATA_H_

/* std::vector */
#include <vector>

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12Resource, D3D12_INDEX_BUFFER_VIEW */
#include <d3d12.h>
#undef min
#undef max

namespace tktk
{
	// インデックスバッファを管理するクラス
	class IndexBufferData
	{
	public:

		IndexBufferData(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);
		~IndexBufferData();

		// ムーブコンストラクタ
		IndexBufferData(IndexBufferData&& other) noexcept;

	public:

		// コマンドリストにインデックスバッファを登録する
		void set(ID3D12GraphicsCommandList* commandList) const;

		// 自身のバッファのポインタを取得する
		ID3D12Resource* getBufferPtr() const;

	private:

		ID3D12Resource*						m_indexBuffer		{ nullptr };
		D3D12_INDEX_BUFFER_VIEW				m_indexBufferView	{};
	};
}
#endif // !INDEX_BUFFER_DATA_H_
