#ifndef BASIC_MESH_MATERIAL_H_
#define BASIC_MESH_MATERIAL_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "BasicMeshMaterialData.h"

namespace tktk
{
	// 「BasicMeshMaterialData」を管理するクラス
	class BasicMeshMaterial
	{
	public:

		BasicMeshMaterial(const ShaderFilePaths& basicShaderFilePaths, const std::string& monoColorShaderPsFilePath, unsigned int basicMeshMaterialNum);
		~BasicMeshMaterial() = default;

	public:

		// 「BasicMeshMaterialData」のインスタンスを作る
		void create(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// 指定の「BasicMeshMaterialData」のインスタンスのコピーを作る
		void copy(unsigned int id, unsigned int originalId);

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(unsigned int id)  const;

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addAppendParam(unsigned int id, unsigned int cbufferId, unsigned int dataSize, void* dataTopPos);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateAppendParam(unsigned int id, unsigned int cbufferId, unsigned int dataSize, const void* dataTopPos);

	private:

		// 通常メッシュマテリアル描画用のルートシグネチャを作る
		void createRootSignature() const;

		// 通常メッシュマテリアル描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths, const std::string& monoColorShaderPsFilePath) const;

	private:

		tktkContainer::HeapArray<BasicMeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !BASIC_MESH_MATERIAL_H_