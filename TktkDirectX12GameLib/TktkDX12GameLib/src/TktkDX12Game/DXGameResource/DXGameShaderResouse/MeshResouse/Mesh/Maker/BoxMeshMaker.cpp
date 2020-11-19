#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Maker/BoxMeshMaker.h"

#include <vector>
#include <TktkMath/MathHelper.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MonoColorInstanceVertData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MonoColorMeshCbuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialCbuffer.h"

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

	BoxMeshMaker::BoxMeshMaker()
	{
		// 頂点情報
		std::vector<VertexData> vertices{
			/* 上の面 */
			{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f,			0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f / 3.0f,	0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f,			0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			/* 下の面 */
			{ { -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f,			1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 2.0f / 3.0f,	1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 2.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f,			0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
	
			/* 左の面 */
			{ { -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 2.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f,			0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f,			0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 2.0f / 3.0f,	0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			/* 右の面 */
			{ {  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f / 3.0f,	1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f,			1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f,			0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			/* 手前の面*/
			{ { -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 2.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 2.0f / 3.0f,	0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f / 3.0f,	0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			/* 奥の面 */
			{ { -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 2.0f / 3.0f,	1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f / 3.0f,	1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 2.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } }
		};

		for (auto& node : vertices) tktkMath::Vector3::orthoNormalize(&node.normal, &node.tangent, &node.binormal);

		// 頂点バッファを作る
		DX12GameManager::setSystemHandle(SystemVertexBufferType::Box, DX12GameManager::createVertexBuffer(vertices));

		// インデックス情報
		std::vector<unsigned short> indices{
			3,1,0,
			2,1,3,

			6,4,5,
			7,4,6,

			11,9,8,
			10,9,11,

			14,12,13,
			15,12,14,

			19,17,16,
			18,17,19,

			22,20,21,
			23,20,22
		};

		// インデックスバッファを作る
		DX12GameManager::setSystemHandle(SystemIndexBufferType::Box, DX12GameManager::createIndexBuffer(indices));
	}

	// デストラクタを非インライン化する
	BoxMeshMaker::~BoxMeshMaker() = default;

	size_t BoxMeshMaker::makeBoxMeshWireFrame(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// マテリアルの作成に必要な情報
		MeshMaterialInitParam materialParam{};

		// 単色シンプルメッシュワイヤーフレームパイプラインステートを取得する
		materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::MonoColorSimpleMeshWireFrame);

		// ディスクリプタヒープを作る
		{
			BasicDescriptorHeapInitParam descriptorHeapInitParam{};
			descriptorHeapInitParam.shaderVisible = true;
			descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

			{ /* 頂点シェーダー用のコンスタントバッファービューのディスクリプタの情報 */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// カメラの１種類
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)		}
				};
			}

			// 作ったディスクリプタヒープのハンドルをマテリアル作成引数に代入する
			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}
		// 単色のシンプル立方体メッシュワイヤーフレームのマテリアルを作る
		size_t boxMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// システムハンドルと結びつける
		DX12GameManager::setSystemHandle(SystemMeshMaterialType::BoxWireFrame, boxMeshMaterialhandle);

		// 一旦ローカル変数に配列を格納
		auto tempInstanceVertParam = std::vector<MonoColorInstanceVertData>(128U);

		// 単色のシンプル立方体メッシュワイヤーフレームの作成に必要な情報
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots =		{ { boxMeshMaterialhandle, 0, IndicesSize } };

		// 単色のシンプル立方体メッシュワイヤーフレームを作り、そのハンドルを返す
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}

	size_t BoxMeshMaker::makeMonoColorBoxMesh(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// マテリアルの作成に必要な情報
		MeshMaterialInitParam materialParam{};

		// 単色のシンプルメッシュパイプラインステートを使う
		materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::MonoColorSimpleMesh);

		// ディスクリプタヒープを作る
		{
			BasicDescriptorHeapInitParam descriptorHeapInitParam{};
			descriptorHeapInitParam.shaderVisible = true;
			descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

			{ /* 頂点シェーダー用のコンスタントバッファービューのディスクリプタの情報 */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// カメラの１種類
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)		}
				};
			}

			// 作ったディスクリプタヒープのハンドルをマテリアル作成引数に代入する
			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}
		// 単色のシンプル立方体メッシュのマテリアルを作る
		size_t boxMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// システムハンドルと結びつける
		DX12GameManager::setSystemHandle(SystemMeshMaterialType::Box, boxMeshMaterialhandle);

		// 一旦ローカル変数に配列を格納
		auto tempInstanceVertParam = std::vector<MonoColorInstanceVertData>(128U);

		// 立方体メッシュの作成に必要な情報
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle = DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots			= { { boxMeshMaterialhandle, 0, IndicesSize } };

		// 単色のシンプル立方体メッシュを作り、そのハンドルを返す
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}

	size_t BoxMeshMaker::makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// マテリアルの作成に必要な情報
		MeshMaterialInitParam materialParam{};

		// シンプルメッシュパイプラインステートを使う
		materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::SimpleMesh);

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
					{ BufferType::texture, albedoMapTextureHandle },
					{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)	}
				};
			}

			{ /* 頂点シェーダー用のコンスタントバッファービューのディスクリプタの情報 */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// カメラ、ライト、シャドウマップの３種類
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)		},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap)	}
				};
			}

			{ /* ピクセルシェーダー用のコンスタントバッファービューのディスクリプタの情報 */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// ライト、メッシュマテリアルの２種類
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)			},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial)	}
				};
			}

			// 作ったディスクリプタヒープのハンドルをマテリアル作成引数に代入する
			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}
		// シンプル立方体メッシュのマテリアルを作る
		size_t boxMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// メッシュマテリアル定数バッファ
		auto boxMeshMaterialCbufferPtr = std::make_shared<MeshMaterialCbuffer>();

		// “メッシュマテリアル定数バッファ”の値を初期化する
		boxMeshMaterialCbufferPtr->materialAmbient	= { 0.3f, 1.0f };
		boxMeshMaterialCbufferPtr->materialDiffuse	= tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialSpecular = tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialEmissive = { 0.1f, 1.0f };
		boxMeshMaterialCbufferPtr->materialShiniess = 1.0f;

		// 作った“メッシュマテリアル定数バッファ”をマテリアルに追加する
		DX12GameManager::addMeshMaterialAppendParam(
			boxMeshMaterialhandle,
			MeshMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial), boxMeshMaterialCbufferPtr)
		);

		// 一旦ローカル変数に配列を格納
		auto tempInstanceVertParam = std::vector<tktkMath::Matrix4>(2048U);

		// 立方体メッシュの作成に必要な情報
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots			= { { boxMeshMaterialhandle, 0, IndicesSize } };

		// シンプル立方体メッシュを作り、そのハンドルを返す
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}

	size_t BoxMeshMaker::makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// マテリアルの作成に必要な情報
		MeshMaterialInitParam materialParam{};

		// 反転したシンプルメッシュパイプラインステートを使う
		materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::InvertSimpleMesh);

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
					{ BufferType::texture, skyBoxTextureHandle },
					{ BufferType::texture, DX12GameManager::getSystemHandle(SystemTextureBufferType::White)	}
				};
			}

			{ /* 頂点シェーダー用のコンスタントバッファービューのディスクリプタの情報 */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// カメラ、ライト、シャドウマップの３種類
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)		},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap)	}
				};
			}

			{ /* ピクセルシェーダー用のコンスタントバッファービューのディスクリプタの情報 */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// ライト、メッシュマテリアルの２種類
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)			},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial)	}
				};
			}

			// 作ったディスクリプタヒープのハンドルをマテリアル作成引数に代入する
			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}
		// 反転したシンプル立方体メッシュのマテリアルを作る
		size_t boxMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// メッシュマテリアル定数バッファ
		auto boxMeshMaterialCbufferPtr = std::make_shared<MeshMaterialCbuffer>();

		// “メッシュマテリアル定数バッファ”の値を初期化する
		boxMeshMaterialCbufferPtr->materialAmbient	= tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialDiffuse	= tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialSpecular = tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialEmissive = tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialShiniess = 1.0f;

		// 作った“メッシュマテリアル定数バッファ”をマテリアルに追加する
		DX12GameManager::addMeshMaterialAppendParam(
			boxMeshMaterialhandle,
			MeshMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial), boxMeshMaterialCbufferPtr)
		);

		// 一旦ローカル変数に配列を格納
		auto tempInstanceVertParam = std::vector<tktkMath::Matrix4>(128U);

		// 立方体メッシュの作成に必要な情報
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots			= { { boxMeshMaterialhandle, 0, IndicesSize } };

		// 反転したシンプル立方体メッシュを作り、そのハンドルを返す
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}
}