#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Maker/SphereMeshMaker.h"

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
		unsigned char		bones[4]	{ 0, 0, 0, 0 };
		float				weight[4]	{ 1.0f, 1.0 , 1.0f, 1.0f };
		tktkMath::Vector3	tangent;
		tktkMath::Vector3	binormal;
	};

	void SphereMeshMaker::make()
	{
		int uMax = 24;
		int vMax = 12;

		std::vector<VertexData> vertices;
		vertices.resize(uMax * (vMax + 1));

		for (int v = 0; v <= vMax; v++)
		{
			for (int u = 0; u < uMax; u++)
			{
				VertexData tempVertexData;

				float x = tktkMath::MathHelper::sin(180.0f * v / vMax) * tktkMath::MathHelper::cos(360.0f * u / uMax);
				float y = tktkMath::MathHelper::cos(180.0f * v / vMax);
				float z = tktkMath::MathHelper::sin(180.0f * v / vMax) * tktkMath::MathHelper::sin(360.0f * u / uMax);

				tempVertexData.point = tktkMath::Vector3(x, y, z);
				tempVertexData.normal = tktkMath::Vector3(0.0f, 0.0f, 1.0f);

				tempVertexData.texcoord = tktkMath::Vector2(0.5f, 0.5f);

				tktkMath::Vector3::orthoNormalize(
					&tempVertexData.normal,
					&tempVertexData.tangent,
					&tempVertexData.binormal
				);

				tempVertexData.bones[0] = 0;
				tempVertexData.bones[1] = 0;
				tempVertexData.bones[2] = 0;
				tempVertexData.bones[3] = 0;

				tempVertexData.weight[0] = 1.0f;
				tempVertexData.weight[1] = 0.0f;
				tempVertexData.weight[2] = 0.0f;
				tempVertexData.weight[3] = 0.0f;

				vertices.at(uMax * v + u) = (tempVertexData);
			}
		}

		int i = 0;

		std::vector<unsigned short> indices;
		indices.resize(2 * vMax * (uMax + 1));

		for (int v = 0; v < vMax; v++)
		{
			for (int u = 0; u <= uMax; u++)
			{
				if (u == uMax)
				{
					indices.at(i) = v * uMax;
					i++;
					indices.at(i) = (v + 1) * uMax;
					i++;
				}
				else
				{
					indices.at(i) = (v * uMax) + u;
					i++;
					indices.at(i) = indices.at(i - 1) + uMax;
					i++;
				}
			}
		}

		// 頂点バッファを作る
		DX12GameManager::setSystemHandle(SystemVertexBufferType::Sphere, DX12GameManager::createVertexBuffer(vertices));

		// インデックスバッファを作る
		DX12GameManager::setSystemHandle(SystemIndexBufferType::Sphere, DX12GameManager::createIndexBuffer(indices));

		// 球体メッシュの作成に必要な情報
		BasicMeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle = DX12GameManager::getSystemHandle(SystemVertexBufferType::Sphere);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Sphere);
		meshInitParam.indexNum			= indices.size();
		meshInitParam.primitiveTopology = MeshPrimitiveTopology::TriangleStrip;

		{
			// マテリアルの作成に必要な情報
			BasicMeshMaterialInitParam materialParam{};

			// 単色のパイプラインステートを使う
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMonoColorMesh);

			materialParam.materialAmbient = { 0.3f, 1.0f }; // ※マテリアルの環境光の値は定数値を設定する
			materialParam.materialDiffuse  = tktkMath::Color_v::white;
			materialParam.materialSpecular = tktkMath::Color_v::white;
			materialParam.materialEmissive = tktkMath::Color_v::white;
			materialParam.materialShiniess = 10.0f;

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

				// TODO : 「SystemBasicDescriptorHeapType::Sphere」この値が本当に必要か調べる
				DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType::Sphere, materialParam.useDescriptorHeapHandle);
			}

			// 球体メッシュのマテリアルを作る
			DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType::Sphere, DX12GameManager::createBasicMeshMaterial(materialParam));

			//// 球体メッシュのマテリアルにアルベドカラーのパラメータを追加する
			//DX12GameManager::addMaterialAppendParam(DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::Sphere), DX12GameManager::getSystemHandle(SystemCBufferType::BasicMonoColorMeshCbuffer), BasicMonoColorMeshCbuffer());
		
			// 単色ワイヤーフレーム用のパイプラインステートを取得する
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMonoColorMeshWireFrame);

			// 球体メッシュワイヤーフレームのマテリアルを作る
			DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType::SphereWireFrame, DX12GameManager::createBasicMeshMaterial(materialParam));

			//// 球体メッシュワイヤーフレームのマテリアルにアルベドカラーのパラメータを追加する
			//DX12GameManager::addMaterialAppendParam(DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::SphereWireFrame), DX12GameManager::getSystemHandle(SystemCBufferType::BasicMonoColorMeshCbuffer), BasicMonoColorMeshCbuffer());
		}

		// 球体メッシュを作る
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::Sphere), 0, indices.size() } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::Sphere, DX12GameManager::createBasicMesh(meshInitParam));

		// 球体メッシュワイヤーフレームを作る
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::SphereWireFrame), 0, indices.size() } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::SphereWireFrame, DX12GameManager::createBasicMesh(meshInitParam));
	}
}