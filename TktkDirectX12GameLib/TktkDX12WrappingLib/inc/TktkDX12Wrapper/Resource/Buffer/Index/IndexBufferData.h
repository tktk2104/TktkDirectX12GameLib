#ifndef INDEX_BUFFER_DATA_H_
#define INDEX_BUFFER_DATA_H_

#include <vector>
#include <forward_list>
#include "../../../Includer/D3d12Includer.h"

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

		// インデックスバッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

		// 自身のバッファのポインタを取得する
		ID3D12Resource* getBufferPtr() const;

	private:

		ID3D12Resource*						m_indexBuffer		{ nullptr };
		D3D12_INDEX_BUFFER_VIEW				m_indexBufferView	{};
		std::forward_list<ID3D12Resource*>	m_uploadBufferList	{};
	};
}
#endif // !INDEX_BUFFER_DATA_H_
