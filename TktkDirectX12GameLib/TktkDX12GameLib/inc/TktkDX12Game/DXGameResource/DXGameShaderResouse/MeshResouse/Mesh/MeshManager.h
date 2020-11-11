#ifndef MESH_MANAGER_H_
#define MESH_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include <string>

namespace tktk
{
	struct MeshManagerInitParam;
	class MeshData;
	struct MeshInitParam;
	struct MeshDrawFuncBaseArgs;

	// 「MeshData」を管理するクラス
	class MeshManager
	{
	public:

		MeshManager(const MeshManagerInitParam& initParam);
		~MeshManager();
	
	public:

		// 「MeshData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t craete(const MeshInitParam& initParam);

		// 指定の「MeshData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		size_t copy(size_t originalHandle);

		// 使用しているマテリアルを更新する
		void setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeShadowMap(size_t handle) const;

		// 指定の通常メッシュを描画する
		void drawMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		// シャドウマップ書き込み用のルートシグネチャを作る
		void createWriteShadowMapRootSignature() const;

		// シャドウマップ書き込み用のパイプラインステートを作る
		void createWriteShadowMapGraphicsPipeLineState(const std::string& writeShadowMapVsFilePath) const;

	private:

		tktkContainer::ResourceContainer<MeshData> m_basicMeshArray;
	};
}
#endif // !MESH_MANAGER_H_