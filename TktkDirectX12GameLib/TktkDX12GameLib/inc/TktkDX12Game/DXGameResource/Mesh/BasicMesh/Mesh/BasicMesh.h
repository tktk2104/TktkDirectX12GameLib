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
		unsigned int craete(const BasicMeshInitParam& initParam);

		// 指定の「BasicMeshData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		unsigned int copy(unsigned int originalHandle);

		// 使用しているマテリアルを更新する
		void setMaterialHandle(unsigned int meshHandle, unsigned int materialSlot, unsigned int materialHandle);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeShadowMap(unsigned int handle) const;

		// 指定の通常メッシュを描画する
		void drawMesh(unsigned int handle, const MeshDrawFuncBaseArgs& baseArgs) const;

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