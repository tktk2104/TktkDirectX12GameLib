#ifndef BASIC_MESH_MATERIAL_H_
#define BASIC_MESH_MATERIAL_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "BasicMeshMaterialData.h"

namespace tktk
{
	// 「BasicMeshMaterialData」を管理するクラス
	class BasicMeshMaterial
	{
	public:

		BasicMeshMaterial(const ShaderFilePaths& basicShaderFilePaths, const std::string& monoColorShaderPsFilePath, const tktkContainer::ResourceContainerInitParam& initParam);
		~BasicMeshMaterial() = default;

	public:

		// 「BasicMeshMaterialData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(const BasicMeshMaterialInitParam& initParam);

		// 指定の「BasicMeshMaterialData」のインスタンスのコピーを作り、そのリソースのハンドルを返す
		size_t copy(size_t originalHandle);

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(size_t handle)  const;

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのハンドルと値を設定する
		void addAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのハンドルと値を更新する
		void updateAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos);

	private:

		// 通常メッシュマテリアル描画用のルートシグネチャを作る
		void createRootSignature() const;

		// 通常メッシュマテリアル描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths, const std::string& monoColorShaderPsFilePath) const;

	private:

		tktkContainer::ResourceContainer<BasicMeshMaterialData> m_basicMeshMaterialArray;
	};
}
#endif // !BASIC_MESH_MATERIAL_H_