#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshPmdLoader.h"

#include <TktkFileIo/lodepmd.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialCBufferData.h"

namespace tktk
{
	// スケルトンを作る
	inline void craeteSkeleton(int createSkeletonId, const std::vector<tktkFileIo::lodepmd::loadData::OutBone>& boneData);

	// 読み込み関数
	MeshLoadPmdReturnValue MeshPmdLoader::loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// pmdファイルのロード処理の出力変数
		tktkFileIo::lodepmd::loadData outData{};

		// ロードを行う
		tktkFileIo::lodepmd::load(&outData, args.filePath);

		// 頂点バッファを作る
		size_t createdVertexBufferHandle = DX12GameManager::createVertexBuffer(outData.vertexData);

		// インデックスバッファを作る
		size_t createdIndexBufferHandle = DX12GameManager::createIndexBuffer(outData.indexData);

		// 一旦ローカル変数に配列を格納
		auto tempInstanceVertParam = std::vector<tktkMath::Matrix4>(128U);

		// 通常メッシュの作成に必要な情報
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= createdVertexBufferHandle;
		meshInitParam.useIndexBufferHandle	= createdIndexBufferHandle;
		meshInitParam.indexNum				= outData.indexData.size();
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		// 現在のインデックス（インデックスバッファの位置）
		size_t curIndex				= 0U;

		// マテリアルの数だけループ
		for (size_t i = 0; i < outData.materialData.size(); i++)
		{
			// マテリアルの作成に必要な情報
			MeshMaterialInitParam materialParam{};

			// デフォルトのパイプラインステートを使う
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::SkinningMesh);

			size_t createdTextureBufferHandle = 0U;

			// マテリアルにテクスチャが設定されていたら
			if (outData.materialData.at(i).textureFilePath != "")
			{
				// テクスチャを読み込む
				createdTextureBufferHandle = DX12GameManager::loadTextureBuffer(outData.materialData.at(i).textureFilePath);
			}
			// テクスチャが設定されていなかったら
			else
			{
				// 最初の大きさの環境光の色のテクスチャを作成する

				TexBufFormatParam formatParam{};
				formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
				formatParam.arraySize = 1U;
				formatParam.mipLevels = 1U;
				formatParam.sampleDescCount = 1U;
				formatParam.sampleDescQuality = 0U;

				TexBuffData dataParam{};

				for (size_t j = 0; j < 16; j++)
				{
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.r));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.g));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.b));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.a));
				}

				dataParam.width = 4U;
				dataParam.height = 4U;

				// テクスチャが小さすぎるのでコマンドリスト
				createdTextureBufferHandle = DX12GameManager::createTextureBuffer(formatParam, dataParam);
			}

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
						{ BufferType::texture,		createdTextureBufferHandle												},
						{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)			},
						{ BufferType::texture,		DX12GameManager::getSystemHandle(SystemTextureBufferType::FlatNormal4x4)}
					};
				}

				{ /* 頂点シェーダー用のコンスタントバッファービューのディスクリプタの情報 */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// カメラ、ライト、シャドウマップの３つ
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap)	}
					};
				}

				{ /* ピクセルシェーダー用のコンスタントバッファービューのディスクリプタの情報 */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// ライト、メッシュマテリアルの２つ
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)			},
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
		DX12GameManager::createMeshAndAttachId(args.createBasicMeshId.value, meshInitParam, funcRunnerInitParam);

		// スケルトンを作る
		craeteSkeleton(args.createSkeletonId.value, outData.boneData);

		// TODO : 作成したメッシュの情報を返す予定
		return { };
	}

	// スケルトンを作る
	void craeteSkeleton(int createSkeletonId, const std::vector<tktkFileIo::lodepmd::loadData::OutBone>& boneData)
	{
		// 骨情報の作成に必要な情報
		SkeletonInitParam skeletonInitParam{};
		skeletonInitParam.boneDataArray.reserve(boneData.size());

		for (const auto& node : boneData)
		{
			skeletonInitParam.boneDataArray.push_back({ node.name, node.parentNo, node.pos });
		}

		// スケルトンを作成する
		DX12GameManager::createSkeletonAndAttachId(createSkeletonId, skeletonInitParam);
	}
}