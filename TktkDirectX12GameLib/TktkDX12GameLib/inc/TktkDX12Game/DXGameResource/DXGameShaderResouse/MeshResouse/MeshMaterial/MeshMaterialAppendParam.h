#ifndef MESH_MATERIAL_APPEND_PARAM_H_
#define MESH_MATERIAL_APPEND_PARAM_H_

/* std::shared_ptr<> */
#include <memory>

namespace tktk
{
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;

	// メッシュマテリアルの追加パラメータ
	class MeshMaterialAppendParam
	{
	public:

		MeshMaterialAppendParam(const MeshMaterialAppendParamInitParam& initParam);
		~MeshMaterialAppendParam();

		// ムーブコンストラクタ
		MeshMaterialAppendParam(MeshMaterialAppendParam&& other) noexcept;

	public:

		// 定数バッファを更新する内容の変数を書き換える
		void updateParam(const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

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
#endif // !MESH_MATERIAL_APPEND_PARAM_H_