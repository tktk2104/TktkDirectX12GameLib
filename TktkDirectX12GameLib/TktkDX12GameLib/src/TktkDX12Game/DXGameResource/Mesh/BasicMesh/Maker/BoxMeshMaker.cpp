#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Maker/BoxMeshMaker.h"

#include <vector>
#include <TktkMath/MathHelper.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Structs/BasicMonoColorMeshCbuffer.h"

namespace tktk
{
	struct VertexData
	{
		tktkMath::Vector3	point;
		tktkMath::Vector3	normal;
		tktkMath::Vector2	texcoord;
		unsigned char		bones[4]{ 0, 0, 0, 0 };
		float				weight[4]{ 1.0f, 0.0f , 0.0f, 0.0f };
		tktkMath::Vector3	tangent;
		tktkMath::Vector3	binormal;
	};

	void BoxMeshMaker::make()
	{
		std::vector<VertexData> vertices{
			{ { -1.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  1.0f, -1.0f, -1.0f }, {  1.0f, -1.0f, -1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -1.0f, -1.0f,  1.0f }, { -1.0f, -1.0f,  1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  1.0f, -1.0f,  1.0f }, {  1.0f, -1.0f,  1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			{ { -1.0f,  1.0f, -1.0f }, { -1.0f,  1.0f, -1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  1.0f,  1.0f, -1.0f }, {  1.0f,  1.0f, -1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -1.0f,  1.0f,  1.0f }, { -1.0f,  1.0f,  1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  1.0f,  1.0f,  1.0f }, {  1.0f,  1.0f,  1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } }
		};

		for (auto& node : vertices)
		{
			tktkMath::Vector3::orthoNormalize(&node.normal, &node.tangent, &node.binormal);
		}

		// 頂点バッファを作る
		DX12GameManager::setSystemHandle(SystemVertexBufferType::Box, DX12GameManager::createVertexBuffer(vertices));

		std::vector<unsigned short> indices{
			0, 1, 3,
			0, 3, 2,
			0, 5, 1,
			0, 4, 5,
			1, 5, 3,
			3, 5, 7,
			2, 3, 7,
			2, 7, 6,
			0, 2, 6,
			0, 6, 4,
			4, 7, 5,
			4, 6, 7
		};

		// インデックスバッファを作る
		DX12GameManager::setSystemHandle(SystemIndexBufferType::Box, DX12GameManager::createIndexBuffer(indices));

		// 立方体メッシュの作成に必要な情報
		BasicMeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);

#ifdef _M_AMD64 /* x64ビルドなら */
		meshInitParam.indexNum = static_cast<unsigned int>(indices.size());
#else
		meshInitParam.indexNum = indices.size();
#endif // _M_AMD64
		
		meshInitParam.primitiveTopology		= MeshPrimitiveTopology::TriangleList;

		{
			// マテリアルの作成に必要な情報
			BasicMeshMaterialInitParam materialParam{};

			// 単色のパイプラインステートを使う
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMonoColorMesh);

			materialParam.materialAmbient	= { 0.3f, 1.0f }; // ※マテリアルの環境光の値は定数値を設定する
			materialParam.materialDiffuse	= tktkMath::Color_v::white;
			materialParam.materialSpecular	= tktkMath::Color_v::white;
			materialParam.materialEmissive	= tktkMath::Color_v::white;
			materialParam.materialShiniess	= 10.0f;

			// ディスクリプタヒープを作る
			{
				BasicDescriptorHeapInitParam descriptorHeapInitParam{};
				descriptorHeapInitParam.shaderVisible = true;
				descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

				{ /* シェーダーリソースビューのディスクリプタの情報 */
					auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
					srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

					// シャドウマップの１種類
					srvDescriptorParam.descriptorParamArray = {
						{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)	}
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
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial)	},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BasicMonoColorMeshCbuffer)	}
					};
				}

				materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);

				// TODO : 「SystemBasicDescriptorHeapType::Box」この値が本当に必要か調べる
				DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType::Box, materialParam.useDescriptorHeapHandle);
			}

			// 立方体メッシュのマテリアルを作る
			DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType::Box, DX12GameManager::createBasicMeshMaterial(materialParam));

			// 単色ワイヤーフレーム用のパイプラインステートを取得する
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMonoColorMeshWireFrame);

			// 立方体メッシュワイヤーフレームのマテリアルを作る
			DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType::BoxWireFrame, DX12GameManager::createBasicMeshMaterial(materialParam));
		}

#ifdef _M_AMD64 /* x64ビルドなら */

		// 立方体メッシュを作る
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::Box), 0, static_cast<unsigned int>(indices.size()) } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::Box, DX12GameManager::createBasicMesh(meshInitParam));

		// 立方体メッシュワイヤーフレームを作る
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::BoxWireFrame), 0, static_cast<unsigned int>(indices.size()) } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::BoxWireFrame, DX12GameManager::createBasicMesh(meshInitParam));
#else
		// 立方体メッシュを作る
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::Box), 0, indices.size() } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::Box, DX12GameManager::createBasicMesh(meshInitParam));

		// 立方体メッシュワイヤーフレームを作る
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::BoxWireFrame), 0, indices.size() } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::BoxWireFrame, DX12GameManager::createBasicMesh(meshInitParam));
#endif // _M_AMD64
	}
}