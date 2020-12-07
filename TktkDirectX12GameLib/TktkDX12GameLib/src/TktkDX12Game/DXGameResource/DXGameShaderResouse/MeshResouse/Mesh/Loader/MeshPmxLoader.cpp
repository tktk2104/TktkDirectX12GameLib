#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshPmxLoader.h"

#include <TktkFileIo/lodepmx.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialCBufferData.h"

#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunnerInitParam.h"

namespace tktk
{
	// スケルトンを作る
	inline size_t craeteSkeleton(int createSkeletonId, const std::vector<tktkFileIo::lodepmx::loadData::OutBone>& boneData);

	MeshLoadPmxReturnValue MeshPmxLoader::loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// ロードを行う
		auto outData = tktkFileIo::lodepmx::load(args.filePath);

		// 頂点バッファを作る
		size_t createdVertexBufferHandle = DX12GameManager::createVertexBuffer(outData.vertexData);

		// インデックスバッファを作る
		size_t createdIndexBufferHandle = DX12GameManager::createIndexBuffer(outData.indexData);

		// 一旦ローカル変数に配列を格納
		auto tempInstanceVertParam = std::vector<tktkMath::Matrix4>(128U);

		// 通常メッシュの作成に必要な情報
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle = createdVertexBufferHandle;
		meshInitParam.useIndexBufferHandle	= createdIndexBufferHandle;
		meshInitParam.indexNum				= outData.indexData.size();
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		// 読み込んだテクスチャハンドルの配列
		std::vector<size_t> loadTextureBufferHandle{};
		loadTextureBufferHandle.reserve(outData.textureFilePaths.size());

		// 読み込んだテクスチャファイルパスを巡回
		for (const auto& textureFilePath : outData.textureFilePaths)
		{
			loadTextureBufferHandle.push_back(DX12GameManager::cpuPriorityLoadTextureBuffer(textureFilePath));
		}

		// 現在のインデックス（インデックスバッファの位置）
		size_t curIndex = 0U;

		// マテリアルの数だけループ
		for (size_t i = 0; i < outData.materialData.size(); i++)
		{
			// マテリアルの作成に必要な情報
			MeshMaterialInitParam materialParam{};

			// デフォルトのパイプラインステートを使う
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::SkinningMesh);

			// ディスクリプタヒープを作る
			{
				BasicDescriptorHeapInitParam descriptorHeapInitParam{};
				descriptorHeapInitParam.shaderVisible = true;
				descriptorHeapInitParam.descriptorTableParamArray.resize(4U);

				{ /* シェーダーリソースビューのディスクリプタの情報 */
					auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
					srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

					// アルベドマップとシャドウマップとノーマルマップの３種類
					srvDescriptorParam.descriptorParamArray = {
						{ BufferType::texture,		loadTextureBufferHandle.at(outData.materialData.at(i).textureId)		},
						{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)			},
						{ BufferType::texture,		DX12GameManager::getSystemHandle(SystemTextureBufferType::FlatNormal4x4)}
					};
				}

				{ /* 頂点シェーダー用のコンスタントバッファービューのディスクリプタの情報 */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// カメラ、ライト、シャドウマップ、ボーン行列の４つ
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)			},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)			},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap)		}
					};
				}

				{ /* ピクセルシェーダー用のコンスタントバッファービューのディスクリプタの情報 */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// ライト、メッシュマテリアルの２つ
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial)	}
					};
				}

				{ /* シェーダーリソースビューのディスクリプタの情報 */
					auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(3U);
					srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

					// 骨行列テクスチャの１種類
					srvDescriptorParam.descriptorParamArray = {
						{ BufferType::texture,		DX12GameManager::getSystemHandle(SystemTextureBufferType::MeshBoneMatrix) }
					};
				}

				materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
			}

			// 通常メッシュのマテリアルを作る
			size_t meshMaterialHandle = DX12GameManager::createMeshMaterial(materialParam);

			// メッシュマテリアル定数バッファ
			auto meshMaterialCbufferPtr = std::make_shared<MeshMaterialCBufferData>();

			// “メッシュマテリアル定数バッファ”の値を初期化する
			meshMaterialCbufferPtr->materialAmbient		= { 0.3f, 1.0f }; // ※マテリアルの環境光の値は定数値を設定する
			meshMaterialCbufferPtr->materialDiffuse		= outData.materialData.at(i).diffuse;
			meshMaterialCbufferPtr->materialSpecular	= outData.materialData.at(i).speqular;
			meshMaterialCbufferPtr->materialEmissive	= outData.materialData.at(i).emissive;
			meshMaterialCbufferPtr->materialShiniess	= outData.materialData.at(i).shiniess;

			// 作った“メッシュマテリアル定数バッファ”をマテリアルに追加する
			DX12GameManager::addMeshMaterialAppendParam(
				meshMaterialHandle,
				MeshMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial), meshMaterialCbufferPtr)
			);

			// 通常メッシュのサブセット情報を更新
			meshInitParam.materialSlots.push_back({ meshMaterialHandle, curIndex, outData.materialData.at(i).indexCount });

			// 現在のインデックスを加算
			curIndex += outData.materialData.at(i).indexCount;
		}

		// スケルトンを作る
		size_t skeletonHandle = craeteSkeleton(args.createSkeletonId.value, outData.boneData);

		DX12GameManager::createMeshAndAttachId(args.createBasicMeshId.value, meshInitParam, funcRunnerInitParam);

		// TODO : 作成したメッシュの情報を返す予定
		return { skeletonHandle };
	}

	// スケルトンを作る
	size_t craeteSkeleton(int createSkeletonId, const std::vector<tktkFileIo::lodepmx::loadData::OutBone>& boneData)
	{
		// 骨情報の作成に必要な情報
		SkeletonInitParam skeletonInitParam{};
		skeletonInitParam.boneDataArray.reserve(boneData.size());

		for (const auto& node : boneData)
		{
			skeletonInitParam.boneDataArray.push_back({ node.name, node.parentNo, node.pos });
		}

		// スケルトンを作成する
		return DX12GameManager::createSkeletonAndAttachId(createSkeletonId, skeletonInitParam);
	}
}