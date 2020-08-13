#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <forward_list>
#include "../../../Includer/D3d12Includer.h"

namespace tktk
{
	// 定数バッファを管理するクラス
	class ConstantBufferData
	{
	public:

		ConstantBufferData(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);
		~ConstantBufferData();

	public:

		// 引数のディスクリプタハンドルに定数バッファビューを作る
		void createCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 定数バッファを更新する
		// ※アップロードバッファを新規に作成し、そのバッファから自身にコピーする命令をコマンドリストに登録する
		void updateBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// 全てのアップロード用のバッファを削除する
		void deleteUploadBufferAll();

	private:

		ID3D12Resource* m_constantBuffer{ nullptr };
		std::forward_list<ID3D12Resource*> m_uploadBufferList{};
	};
}
#endif // !CONSTANT_BUFFER_DATA_H_