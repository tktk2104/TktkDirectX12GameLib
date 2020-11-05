#ifndef BASIC_MESH_H_
#define BASIC_MESH_H_

#include <string>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "BasicMeshData.h"

namespace tktk
{
	// 「BasicMeshData」を管理するクラス
	class BasicMesh
	{
	public:

		BasicMesh(const std::string& writeShadowMapVsFilePath, const tktkContainer::ResourceContainerInitParam& initParam);
		~BasicMesh() = default;
	
	public:

		// 「BasicMeshData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t craete(const BasicMeshInitParam& initParam);

		// 指定の「BasicMeshData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
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

		tktkContainer::ResourceContainer<BasicMeshData> m_basicMeshArray;
	};
}
#endif // !BASIC_MESH_H_