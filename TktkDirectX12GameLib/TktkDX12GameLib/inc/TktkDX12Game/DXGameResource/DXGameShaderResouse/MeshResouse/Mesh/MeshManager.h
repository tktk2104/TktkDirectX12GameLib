#ifndef MESH_MANAGER_H_
#define MESH_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include <string>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	class MeshData;

	struct DrawMeshShaderFilePaths;
	struct MeshInitParam;
	struct CopySourceDataCarrier;
	struct MeshDrawFuncBaseArgs;

	// 「MeshData」を管理するクラス
	class MeshManager
	{
	public:

		explicit MeshManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~MeshManager();
	
	public:

		// 「MeshData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t craete(const MeshInitParam& initParam);

		// 指定の「MeshData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		size_t copy(size_t originalHandle);

		// 使用しているマテリアルを更新する
		void setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle);

		// 指定のメッシュをインスタンス描画する時に使用する値を削除する
		void clearInstanceParam(size_t handle);

		// 指定のメッシュをインスタンス描画する時に使用する値を追加する
		void addInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam);

		// スキニングメッシュをインスタンス描画する時に使用する骨行列を追加する
		void addInstanceBoneMatrix(size_t handle, const std::array<tktkMath::Matrix4, 128>& boneMatrix);

		// 指定のメッシュでシャドウマップを書き込む
		void writeShadowMap(size_t handle) const;

		// 指定のスキニングメッシュでシャドウマップを書き込む
		void writeShadowMapUseBone(size_t handle) const;

		// 指定のメッシュをインスタンス描画する
		void draw(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// スキニングメッシュをインスタンス描画する
		void drawUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		tktkContainer::ResourceContainer<MeshData> m_basicMeshArray;
	};
}
#endif // !MESH_MANAGER_H_