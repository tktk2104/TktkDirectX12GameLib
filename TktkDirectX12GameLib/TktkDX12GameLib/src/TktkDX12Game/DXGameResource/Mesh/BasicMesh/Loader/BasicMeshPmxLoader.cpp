#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmxLoader.h"

#include <TktkFileIo/lodepmx.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	// スケルトンを作る
	inline void craeteSkeleton(unsigned int createSkeletonId, const std::vector<tktkFileIo::lodepmx::loadData::OutBone>& boneData);

	BasicMeshLoadPmxReturnValue BasicMeshPmxLoader::loadPmx(const BasicMeshLoadPmxArgs& args)
	{
		// ロードを行う
		auto outData = tktkFileIo::lodepmx::load(args.filePath);

		// 頂点バッファを作る
		unsigned int createdVertexBufferHandle = DX12GameManager::createVertexBuffer(outData.vertexData);

		// インデックスバッファを作る
		unsigned int createdIndexBufferHandle = DX12GameManager::createIndexBuffer(outData.indexData);

		// 通常メッシュの作成に必要な情報
		BasicMeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle = createdVertexBufferHandle;
		meshInitParam.useIndexBufferHandle = createdIndexBufferHandle;

#ifdef _M_AMD64 /* x64ビルドなら */
		meshInitParam.indexNum = static_cast<unsigned int>(outData.indexData.size());
#else
		meshInitParam.indexNum = outData.indexData.size();
#endif // _M_AMD64

		meshInitParam.primitiveTopology = MeshPrimitiveTopology::TriangleList;
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		// 読み込んだテクスチャハンドルの配列
		std::vector<unsigned int> loadTextureBufferHandle{};
		loadTextureBufferHandle.reserve(outData.textureFilePaths.size());

		// 読み込んだテクスチャファイルパスを巡回
		for (const auto& textureFilePath : outData.textureFilePaths)
		{
			loadTextureBufferHandle.push_back(DX12GameManager::cpuPriorityLoadTextureBuffer(textureFilePath));
		}

		// 現在のインデックス（インデックスバッファの位置）
		unsigned int curIndex = 0U;

		// マテリアルの数だけループ
		for (unsigned int i = 0; i < outData.materialData.size(); i++)
		{
			// マテリアルの作成に必要な情報
			BasicMeshMaterialInitParam materialParam{};

			// デフォルトのパイプラインステートを使う
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMesh);



			materialParam.materialAmbient = { 0.3f, 1.0f }; // ※マテリアルの環境光の値は定数値を設定する
			materialParam.materialDiffuse = outData.materialData.at(i).diffuse;
			materialParam.materialSpecular = outData.materialData.at(i).speqular;
			materialParam.materialEmissive = outData.materialData.at(i).emissive;
			materialParam.materialShiniess = outData.materialData.at(i).shiniess;

			// ディスクリプタヒープを作る
			{
				BasicDescriptorHeapInitParam descriptorHeapInitParam{};
				descriptorHeapInitParam.shaderVisible = true;
				descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

				{ /* シェーダーリソースビューのディスクリプタの情報 */
					auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
					srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

					// アルベドマップとシャドウマップの２種類
					srvDescriptorParam.descriptorParamArray = {
						{ BufferType::texture,		loadTextureBufferHandle.at(outData.materialData.at(i).textureId)	},
						{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)		}
					};
				}

				{ /* 頂点シェーダー用のコンスタントバッファービューのディスクリプタの情報 */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// 
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BoneMatCbuffer)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)				},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial)	},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshShadowMap)		}
					};
				}

				{ /* ピクセルシェーダー用のコンスタントバッファービューのディスクリプタの情報 */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// 
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial)	}
					};
				}
				materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
			}

			// 通常メッシュのマテリアルを作る
			unsigned int meshMaterialHandle = DX12GameManager::createBasicMeshMaterial(materialParam);

			// 通常メッシュのサブセット情報を更新
			meshInitParam.materialSlots.push_back({ meshMaterialHandle, curIndex, outData.materialData.at(i).indexCount });

			// 現在のインデックスを加算
			curIndex += outData.materialData.at(i).indexCount;
		}
		DX12GameManager::createBasicMeshAndAttachId(args.createBasicMeshId, meshInitParam);

		// スケルトンを作る
		craeteSkeleton(args.createSkeletonId, outData.boneData);

		// TODO : 作成したメッシュの情報を返す予定
		return { };
	}

	// スケルトンを作る
	void craeteSkeleton(unsigned int createSkeletonId, const std::vector<tktkFileIo::lodepmx::loadData::OutBone>& boneData)
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