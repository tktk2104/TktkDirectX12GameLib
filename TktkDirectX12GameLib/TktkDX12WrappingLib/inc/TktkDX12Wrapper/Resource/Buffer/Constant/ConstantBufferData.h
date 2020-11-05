#ifndef CONSTANT_BUFFER_DATA_H_
#define CONSTANT_BUFFER_DATA_H_

#include <forward_list>
#include "../../../Includer/D3d12Includer.h"
#include "../CopySourceDataCarrier.h"

namespace tktk
{
	// 定数バッファを管理するクラス
	class ConstantBufferData
	{
	public:

		ConstantBufferData(ID3D12Device* device, const CopySourceDataCarrier& constantBufferData);
		~ConstantBufferData();

		// ムーブコンストラクタ
		ConstantBufferData(ConstantBufferData&& other) noexcept;

	public:

		// 引数のディスクリプタハンドルに定数バッファビューを作る
		void createCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// 自身のバッファのポインタを取得する
		ID3D12Resource* getBufferPtr() const;

	private:

		ID3D12Resource*						m_constantBuffer{ nullptr };
	};
}
#endif // !CONSTANT_BUFFER_DATA_H_