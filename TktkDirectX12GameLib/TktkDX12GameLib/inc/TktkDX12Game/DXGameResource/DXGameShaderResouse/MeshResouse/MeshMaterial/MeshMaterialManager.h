#ifndef MESH_MATERIAL_MANAGER_H_
#define MESH_MATERIAL_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include <string>

namespace tktk
{
	class MeshMaterialData;

	struct MeshMaterialInitParam;
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;

	// 「MeshMaterialData」を管理するクラス
	class MeshMaterialManager
	{
	public:

		explicit MeshMaterialManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~MeshMaterialManager();

	public:

		// 「MeshMaterialData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(const MeshMaterialInitParam& initParam);

		// 指定の「BasicMeshMaterialData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		size_t copy(size_t originalHandle);

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(size_t handle)  const;

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのハンドルと値を設定する
		void addAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのハンドルと値を更新する
		void updateAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

	private:

		tktkContainer::ResourceContainer<MeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !MESH_MATERIAL_MANAGER_H_