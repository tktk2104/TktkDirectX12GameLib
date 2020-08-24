#ifndef BASIC_MESH_H_
#define BASIC_MESH_H_

#include <string>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "BasicMeshData.h"

namespace tktk
{
	// 「BasicMeshData」を管理するクラス
	class BasicMesh
	{
	public:

		BasicMesh(const std::string& writeShadowMapVsFilePath, unsigned int basicMeshNum);
	
	public:

		// 「BasicMeshData」のインスタンスを作る
		void craete(unsigned int id, const BasicMeshInitParam& initParam);

		// 指定の「BasicMeshData」のインスタンスのコピーを作る
		void copy(unsigned int id, unsigned int originalId);

		// 使用しているマテリアルを更新する
		void setMaterialId(unsigned int id, unsigned int materialSlot, unsigned int materialId);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData) const;

		// 指定の通常メッシュを描画する
		void drawMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		// シャドウマップ書き込み用のルートシグネチャを作る
		void createWriteShadowMapRootSignature() const;

		// シャドウマップ書き込み用のパイプラインステートを作る
		void createWriteShadowMapGraphicsPipeLineState(const std::string& writeShadowMapVsFilePath) const;

		// メッシュの座標変換用の定数バッファを更新する
		void updateMeshTransformCbuffer(const MeshTransformCbuffer& transformBufferData) const;

		// メッシュのシャドウマップ使用用の定数バッファを更新する
		void updateMeshShadowMapCBuffer(const MeshShadowMapCBuffer&	shadowMapBufferData) const;

	private:

		tktkContainer::HeapArray<BasicMeshData> m_basicMeshArray;
	};
}
#endif // !BASIC_MESH_H_