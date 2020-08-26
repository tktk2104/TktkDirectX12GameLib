#ifndef BASIC_MESH_MATERIAL_APPEND_PARAM_H_
#define BASIC_MESH_MATERIAL_APPEND_PARAM_H_

#include <memory>
#include <utility>

namespace tktk
{
	class BasicMeshMaterialAppendParam
	{
	public:

		BasicMeshMaterialAppendParam(unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos);

	public:

		// 定数バッファを更新する内容の変数を書き換える
		void updateParam(unsigned int dataSize, const void* dataTopPos);

		// 定数バッファを更新する
		void updateCbuffer() const;


	private:

		// 変更対象の定数バッファハンドル
		unsigned int m_cbufferHandle;

		// 定数バッファの大きさ
		unsigned int m_dataSize;

		// 定数バッファを更新する内容の変数のポインタ
		std::shared_ptr<void> m_dataTopPos;
	};
}
#endif // !BASIC_MESH_MATERIAL_APPEND_PARAM_H_