#include "TktkDX12Game/DXGameResource/DrawFuncRunnerManager/PostEffect/PostEffectDrawFuncRunnerManager.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawFuncRunner.h"

#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/Structs/DrawGameAreaCBufferData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/Structs/BasicPostEffectCBufferData.h"

namespace tktk
{
    PostEffectDrawFuncRunnerManager::PostEffectDrawFuncRunnerManager(const tktkContainer::ResourceContainerInitParam& initParam)
        : m_drawFuncRunnerList(initParam)
    {
    }

	// デストラクタを非インライン化する
	PostEffectDrawFuncRunnerManager::~PostEffectDrawFuncRunnerManager() = default;

	void PostEffectDrawFuncRunnerManager::createSystemResource()
	{
		// 描画エリア描画用のポストエフェクトマテリアルを作る
		createDrawGameAreaDrawFuncRunner();

		// 何も処理を行わないポストエフェクトマテリアルを作る
		createNotPostEffectDrawFuncRunner();

		// モノクロ描画用のポストエフェクトマテリアルを作る
		createPostEffectMonochromeDrawFuncRunner();

		// 反転色描画用のポストエフェクトマテリアルを作る
		createPostEffectNegativeDrawFuncRunner();

		// 平均化ぼかし描画用のポストエフェクトマテリアルを作る
		createPostEffectAveragingBlurDrawFuncRunner();

		// エンボス加工描画用のポストエフェクトマテリアルを作る
		createPostEffectEmbossDrawFuncRunner();

		// シャープネス加工描画用のポストエフェクトマテリアルを作る
		createPostEffectSharpnessDrawFuncRunner();
	}

	size_t PostEffectDrawFuncRunnerManager::create(size_t postEffectMaterialHandle, const PostEffectDrawFuncRunnerInitParam& initParam)
    {
		// ポストエフェクト描画コンポーネントを作る
		auto drawFuncRunner = DX12GameManager::createComponent<PostEffectDrawFuncRunner>(GameObjectPtr(), postEffectMaterialHandle, initParam);

		// 最初は非アクティブ状態
		drawFuncRunner->setActive(false);

		// 管理コンテナに追加する
        return m_drawFuncRunnerList.create(drawFuncRunner);
    }

    void PostEffectDrawFuncRunnerManager::startPostEffect(size_t handle)
    {
		// 何も処理を行わないポストエフェクトの実行コンポーネントを非アクティブにする
		m_notPostEffectDrawFuncRunner->setActive(false);

		// 指定のポストエフェクトの実行コンポーネントをアクティブにする
		(*m_drawFuncRunnerList.getMatchHandlePtr(handle))->setActive(true);
    }

    void PostEffectDrawFuncRunnerManager::stopPostEffect()
    {
		// 全てのポストエフェクトの実行コンポーネントを非アクティブにする
		for (const auto& node : m_drawFuncRunnerList) node->setActive(false);

		// 何も処理を行わないポストエフェクトの実行コンポーネントをアクティブにする
		m_notPostEffectDrawFuncRunner->setActive(true);
    }

	void PostEffectDrawFuncRunnerManager::createDrawGameAreaDrawFuncRunner()
	{
		// ポストエフェクトマテリアルを作る為の初期化構造体を作る
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::DrawGameArea);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::DrawGameArea);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea) };

		// ポストエフェクトマテリアルを作る
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// ゲーム画面の大きさを取得
		const auto& screenSize			= DX12GameManager::getScreenSize();

		// ゲーム描画エリアの大きさを取得
		const auto& drawGameAreaSize	= DX12GameManager::getDrawGameAreaSize();

		// レターボックス（ゲーム画面の余白の大きさ）
		auto letterBoxSize = tktkMath::Vector2_v::zero;

		// レターボックスの大きさを計算する
		if (screenSize.x / drawGameAreaSize.x >= screenSize.y / drawGameAreaSize.y)
		{
			letterBoxSize.x = (screenSize.x - (screenSize.y * drawGameAreaSize.x / drawGameAreaSize.y)) / 2;
		}
		else
		{
			letterBoxSize.y = (screenSize.y - (screenSize.x * drawGameAreaSize.y / drawGameAreaSize.x)) / 2;
		}

		// ゲーム描画エリア描画用ポストエフェクト用の定数バッファの初期値を決める
		DrawGameAreaCBufferData drawGameAreaCbufferData{};
		drawGameAreaCbufferData.drawGameAreaSizeRate = { 1.0f - (letterBoxSize.x / screenSize.x * 2.0f), 1.0f - (letterBoxSize.y / screenSize.y * 2.0f) };

		// ポストエフェクトマテリアルに新しいパラメータを追加する
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle, 
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::DrawGameArea), std::make_shared<DrawGameAreaCBufferData>(drawGameAreaCbufferData))
		);

		// 作ったポストエフェクトマテリアルとシステムIDを結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::DrawGameArea, createdHandle);

		// ポストエフェクト描画コンポーネントを作る為の初期化構造体を作る
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.drawPriority			= 10000.0f;
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// ポストエフェクト描画コンポーネントを作る
		m_drawGameAreaDrawFuncRunner = DX12GameManager::createComponent<PostEffectDrawFuncRunner>(GameObjectPtr(), createdHandle, drawFuncRunnerInitParam);
	}

	void PostEffectDrawFuncRunnerManager::createNotPostEffectDrawFuncRunner()
	{
		// ポストエフェクトマテリアルを作る為の初期化構造体を作る
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				=  DX12GameManager::getSystemHandle(SystemPipeLineStateType::NotPostEffect);
		materialInitParam.useDescriptorHeapHandle				=  DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::NotPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// ポストエフェクトマテリアルを作る
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// 作ったポストエフェクトマテリアルとシステムIDを結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::NotPostEffect, createdHandle);

		// ポストエフェクト描画コンポーネントを作る為の初期化構造体を作る
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// ポストエフェクト描画コンポーネントを作る
		m_notPostEffectDrawFuncRunner = DX12GameManager::createComponent<PostEffectDrawFuncRunner>(GameObjectPtr(), createdHandle, drawFuncRunnerInitParam);
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectMonochromeDrawFuncRunner()
	{
		// ポストエフェクトマテリアルを作る為の初期化構造体を作る
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectMonochrome);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// ポストエフェクトマテリアルを作る
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// 作ったポストエフェクトマテリアルとシステムIDを結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::Monochrome, createdHandle);

		// 通常のポストエフェクト用の定数バッファの初期値を決める
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// ポストエフェクトマテリアルに新しいパラメータを追加する
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// ポストエフェクト描画コンポーネントを作る為の初期化構造体を作る
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// ポストエフェクト描画コンポーネントを作り、システムIDと結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::Monochrome, create(createdHandle, drawFuncRunnerInitParam));
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectNegativeDrawFuncRunner()
	{
		// ポストエフェクトマテリアルを作る為の初期化構造体を作る
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectNegative);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// ポストエフェクトマテリアルを作る
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// 作ったポストエフェクトマテリアルとシステムIDを結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::Negative, createdHandle);

		// 通常のポストエフェクト用の定数バッファの初期値を決める
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// ポストエフェクトマテリアルに新しいパラメータを追加する
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// ポストエフェクト描画コンポーネントを作る為の初期化構造体を作る
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// ポストエフェクト描画コンポーネントを作り、システムIDと結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::Negative, create(createdHandle, drawFuncRunnerInitParam));
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectAveragingBlurDrawFuncRunner()
	{
		// ポストエフェクトマテリアルを作る為の初期化構造体を作る
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectAveragingBlur);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// ポストエフェクトマテリアルを作る
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// 作ったポストエフェクトマテリアルとシステムIDを結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::AveragingBlur, createdHandle);

		// 通常のポストエフェクト用の定数バッファの初期値を決める
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// ポストエフェクトマテリアルに新しいパラメータを追加する
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// ポストエフェクト描画コンポーネントを作る為の初期化構造体を作る
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// ポストエフェクト描画コンポーネントを作り、システムIDと結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::AveragingBlur, create(createdHandle, drawFuncRunnerInitParam));
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectEmbossDrawFuncRunner()
	{
		// ポストエフェクトマテリアルを作る為の初期化構造体を作る
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectEmbossing);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// ポストエフェクトマテリアルを作る
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// 作ったポストエフェクトマテリアルとシステムIDを結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::Embossing, createdHandle);

		// 通常のポストエフェクト用の定数バッファの初期値を決める
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// ポストエフェクトマテリアルに新しいパラメータを追加する
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// ポストエフェクト描画コンポーネントを作る為の初期化構造体を作る
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// ポストエフェクト描画コンポーネントを作り、システムIDと結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::Embossing, create(createdHandle, drawFuncRunnerInitParam));
	}

	void PostEffectDrawFuncRunnerManager::createPostEffectSharpnessDrawFuncRunner()
	{
		// ポストエフェクトマテリアルを作る為の初期化構造体を作る
		PostEffectMaterialInitParam materialInitParam{};
		materialInitParam.usePipeLineStateHandle				= DX12GameManager::getSystemHandle(SystemPipeLineStateType::PostEffectSharpness);
		materialInitParam.useDescriptorHeapHandle				= DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicPostEffect);
		materialInitParam.autoClearRtvDescriptorHeapHandleArray = { DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::PostEffectTarget) };

		// ポストエフェクトマテリアルを作る
		auto createdHandle = DX12GameManager::createPostEffectMaterial(materialInitParam);

		// 作ったポストエフェクトマテリアルとシステムIDを結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectMaterialType::Sharpness, createdHandle);

		// 通常のポストエフェクト用の定数バッファの初期値を決める
		BasicPostEffectCBufferData basicPostEffectCBufferData{};
		basicPostEffectCBufferData.effectRate = 1.0f;

		// ポストエフェクトマテリアルに新しいパラメータを追加する
		DX12GameManager::addPostEffectMaterialAppendParam(
			createdHandle,
			PostEffectMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::BasicPostEffect), std::make_shared<BasicPostEffectCBufferData>(basicPostEffectCBufferData))
		);

		// ポストエフェクト描画コンポーネントを作る為の初期化構造体を作る
		PostEffectDrawFuncRunnerInitParam drawFuncRunnerInitParam{};
		drawFuncRunnerInitParam.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::DrawGameArea);

		// ポストエフェクト描画コンポーネントを作り、システムIDと結びつける
		DX12GameManager::setSystemHandle(SystemPostEffectDrawFuncRunnerType::Sharpness, create(createdHandle, drawFuncRunnerInitParam));
	}
}