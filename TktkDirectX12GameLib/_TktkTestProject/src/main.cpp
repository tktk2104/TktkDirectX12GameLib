#include <TktkFileIoLibDefinition.h>
#include <TktkMathLibDefinition.h>
#include <TktkDX12WrappingLibDefinition.h>
#include <TktkDX12GameLibDefinition.h>

#include <TktkDX12Game/_MainManager/DX12GameManager.h>

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

#include <TktkDX12Game/Component/ComponentManager.h>
#include <TktkDX12Game/Component/ComponentBase.h>

#include "Scene/LoadingScene.h"
#include "Scene/MainScene.h"

#include "Enum/_ResourceIds/ResourceIds.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR pCmdLine, int nCmdShow)
{
	// 「DX12GameManager」の初期設定をする
	{
		tktk::DX12GameManagerInitParam initParam{};

		{
			auto& resourceInitParam = initParam.dx3dResParam;

			resourceInitParam.viewPortNum		= 0U;
			resourceInitParam.scissorRectNum	= 0U;
			resourceInitParam.pipeLineStateNum	= PipeLineStateNum;
			resourceInitParam.rootSignatureNum	= RootSignatureNum;

			{
				auto& descriptorHeapInitParam = resourceInitParam.descriptorHeapInitParam;

				descriptorHeapInitParam.basicDescriptorHeapNum	= BasicDescriptorHeapNum;
				descriptorHeapInitParam.rtvDescriptorHeapNum	= RtvDescriptorHeapNum;
				descriptorHeapInitParam.dsvDescriptorHeapNum	= 0U;
			}

			{
				auto& bufferResourceInitParam = resourceInitParam.bufferResourceInitParam;

				bufferResourceInitParam.vertexBufferNum			= VertexBufferNum;
				bufferResourceInitParam.indexBufferNum			= IndexBufferNum;
				bufferResourceInitParam.constantBufferNum		= CbufferNum;
				bufferResourceInitParam.textureBufferNum		= TextureBufferNum;
				bufferResourceInitParam.depthStencilBufferNum	= 0U;
				bufferResourceInitParam.renderTargetBufferNum	= RenderTargetBufferNum;
			}
		}

		{
			auto& windowParam = initParam.windowParam;

			windowParam.hInstance	= hInstance;
			windowParam.nCmdShow	= nCmdShow;
			windowParam.windowName	= "TestProject";
			windowParam.windowSize	= { 1920.0f, 1080.0f };
		}
		
		{
			auto& dxGameResourceNum = initParam.dxGameResourceNum;

			dxGameResourceNum.sceneNum				= SceneNum;
			dxGameResourceNum.soundNum				= SoundNum;
			dxGameResourceNum.spriteMaterialNum		= SpriteMaterialNum;
			dxGameResourceNum.line2DMaterialNum		= line2DMaterialNum;
			dxGameResourceNum.basicMeshNum			= BasicMeshNum;
			dxGameResourceNum.basicMeshMaterialNum	= BasicMeshMaterialNum;
			dxGameResourceNum.skeletonNum			= SkeletonNum;
			dxGameResourceNum.motionNum				= MotionNum;
			dxGameResourceNum.postEffectMaterialNum = PostEffectMaterialNum;
			dxGameResourceNum.cameraNum				= CameraNum;
			dxGameResourceNum.lightNum				= LightNum;
		}

		// DX12GameManagerのセットアップ
		tktk::DX12GameManager::initialize(initParam);
	}

	// シーンを追加する
	tktk::DX12GameManager::addScene<LoadingScene>(toInt(SceneId::Loading));
	tktk::DX12GameManager::addScene<MainScene>(toInt(SceneId::Main));

	// 読み込みシーンを有効にする
	tktk::DX12GameManager::enableScene(toInt(SceneId::Loading));

	// 衝突判定の組み合わせを設定する
	tktk::DX12GameManager::addCollisionGroup(1, 2);

	// プログラム開始
	tktk::DX12GameManager::run();

	return 0;
}