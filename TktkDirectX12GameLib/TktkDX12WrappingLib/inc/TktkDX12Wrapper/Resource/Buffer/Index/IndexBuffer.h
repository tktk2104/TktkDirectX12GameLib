#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "IndexBufferData.h"

namespace tktk
{
	// 「IndexBufferData」を管理するクラス
	class IndexBuffer
	{
	public:

		explicit IndexBuffer(unsigned int indexBufferNum);
		~IndexBuffer() = default;

	public:

		// 「IndexBufferData」のインスタンスを作る
		void create(unsigned int id, ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// コマンドリストに指定のインデックスバッファを登録する
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

		// インデックスバッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateBuffer(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

	private:

		tktkContainer::HeapArray<IndexBufferData> m_indexBufferDataArray;
	};
}
#endif // !INDEX_BUFFER_H_