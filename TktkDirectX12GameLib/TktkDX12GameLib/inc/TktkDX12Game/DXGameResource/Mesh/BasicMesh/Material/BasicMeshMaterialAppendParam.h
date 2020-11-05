#ifndef BASIC_MESH_MATERIAL_APPEND_PARAM_H_
#define BASIC_MESH_MATERIAL_APPEND_PARAM_H_

#include <memory>
#include <utility>

namespace tktk
{
	class BasicMeshMaterialAppendParam
	{
	public:

		BasicMeshMaterialAppendParam(size_t cbufferHandle, size_t dataSize, void* dataTopPos);
		~BasicMeshMaterialAppendParam();

		// ムーブコンストラクタ
		BasicMeshMaterialAppendParam(BasicMeshMaterialAppendParam&& other) noexcept;

	public:

		// 定数バッファを更新する内容の変数を書き換える
		void updateParam(size_t dataSize, const void* dataTopPos);

		// 定数バッファを更新する
		void updateCbuffer() const;

	private:

		// 定数バッファのコピー用バッファを更新する
		void updateCopyBuffer() const;

	private:

		// 定数バッファにコピーする為のバッファハンドル
		size_t	m_createUploadBufferHandle{ 0U };

		// 変更対象の定数バッファハンドル
		size_t	m_cbufferHandle;

		// 定数バッファの大きさ
		size_t	m_dataSize;

		// 定数バッファを更新する内容の変数のポインタ
		std::shared_ptr<void> m_dataTopPos;
	};
}
#endif // !BASIC_MESH_MATERIAL_APPEND_PARAM_H_