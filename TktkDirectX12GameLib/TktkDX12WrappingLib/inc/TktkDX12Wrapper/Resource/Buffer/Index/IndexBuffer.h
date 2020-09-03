#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "IndexBufferData.h"

namespace tktk
{
	// 「IndexBufferData」を管理するクラス
	class IndexBuffer
	{
	public:

		explicit IndexBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~IndexBuffer() = default;

	public:

		// 「IndexBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// 指定のインデックスバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(unsigned int handle);

		// コマンドリストに指定のインデックスバッファを登録する
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// 指定のインデックスバッファのポインタを取得する
		ID3D12Resource* getBufferPtr(unsigned int handle) const;

	private:

		tktkContainer::ResourceContainer<IndexBufferData> m_indexBufferDataArray;
	};
}
#endif // !INDEX_BUFFER_H_