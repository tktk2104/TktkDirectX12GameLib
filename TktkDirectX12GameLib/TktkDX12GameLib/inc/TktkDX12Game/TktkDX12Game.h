#ifndef TKTK_DX12_GAME_H_
#define TKTK_DX12_GAME_H_

/* std::string */
#include <string>

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "EventMessage/MessageTypeCarrier.h"
#include "EventMessage/MessageAttachment.h"
#include "DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "DXGameResource/GameObjectResouse/GameObject/GameObjectPtr.h"
#include "DXGameResource/GameObjectResouse/GameObject/GameObjectTagCarrier.h"
#include "DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "UtilityProcessManager/InputManager/InputGetter/MouseInputGetter/MouseBtnType.h"
#include "UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"
#include "UtilityProcessManager/InputManager/CommandTypeManager/CommandIdCarrier.h"
#include "UtilityProcessManager/InputManager/CommandTypeManager/DirectionCommandId.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemViewportType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemScissorRectType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemVertexBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemIndexBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemConstantBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemTextureBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRenderTargetBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDepthStencilBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicDescriptorHeapType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRtvDescriptorHeapType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDsvDescriptorHeapType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRootSignatureType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPipeLineStateType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemCameraType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemLightType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicMeshType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicMeshMaterialType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPostEffectMaterialType.h"
#include "UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	// ゲームの各種処理を呼ぶ
	// ※細かい処理を呼びたい場合は「DX12GameManager」を使ってください
	class DX12Game
	{
	//************************************************************
	/* ウィンドウの処理 */
	public:

		// ゲーム描画エリアサイズを取得する
		static const tktkMath::Vector2& getDrawGameAreaSize();

		// スクリーンサイズを取得する
		static const tktkMath::Vector2& getScreenSize();

	//************************************************************
	/* シーンの処理 */
	public:

		// シーンを有効にする
		// ※内部で対応するリソースハンドルに変換される
		static void enableScene(ResourceIdCarrier id);

		// シーンを無効にする
		// ※内部で対応するリソースハンドルに変換される
		static void disableScene(ResourceIdCarrier id);

	//************************************************************
	/* ゲームオブジェクトの処理 */
	public:

		// 全てのGameObjectにメッセージを送信する
		static void sendMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment = {});

		// ゲームオブジェクトを作成し、そのポインタを返す
		static GameObjectPtr createGameObject();

		// 引数のタグを持ったゲームオブジェクトを取得する
		// ※該当オブジェクトが無かった場合、空のGameObjectPtrを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		static GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag);

		// 引数のタグを持ったゲームオブジェクトを全て取得する
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag);

		// 引数のタグを持ったゲームオブジェクトを全て削除する
		static void destroyGameObjectsWithTag(GameObjectTagCarrier tag);

	//************************************************************
	/* 入力関係の処理 */
	public:

		// IDに対応した入力が押されているかを判定
		static bool isPush(CommandIdCarrier commandId);
		// IDに対応した入力が押され始めたかを判定
		static bool isTrigger(CommandIdCarrier commandId);

		// 指定のボタンが押されているか
		static bool isPush(MouseBtnType btnType);
		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(MouseBtnType btnType);
		
		// 指定のキーが押されているかを判定
		static bool isPush(KeybordKeyType keyType);
		// 指定のキーが押され始めたかを判定
		static bool isTrigger(KeybordKeyType keyType);

		// 指定のボタンが押されているかを判定
		static bool isPush(GamePadBtnType btnType);
		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(GamePadBtnType btnType);

		// 移動方向を取得
		static const tktkMath::Vector2& moveVec();

		// 視点移動方向を取得
		static const tktkMath::Vector2& lookVec();

		// マウスカーソルの座標を取得する
		static tktkMath::Vector2 mousePos();

	//************************************************************
	/* タイム関係の処理 */
	public:

		// 経過時間を初期化する
		static void resetElapsedTime();

		// 前フレームとの時間の差を求める
		static float deltaTime();

		// 前フレームとの時間の差を求める（TimeScaleを無視）
		static float noScaleDeltaTime();

		// プログラムが起動してからの時間（秒）を返す
		static float getCurTimeSec();

		// 最大のdeltaTimeの値を設定（正の数）
		static void setMaximumDeltaTime(float maximumDeltaTime);

		// 時間の経過速度割合を取得する
		static float getTimeScale();

		// 時間の経過速度割合を設定する（0.0〜float_max）
		static void setTimeScale(float timeScaleRate);

		// 基準となるFPSを設定する
		static void setBaseFps(unsigned int baseFps = 60U);

		// 基準となるFPSを取得する
		static unsigned int getBaseFps();

		// 瞬間的なFPSを取得する
		static float fps();

	//************************************************************
	/* リソースを読み込むための処理 */
	public:

		// 音声データを読み込む（対応している音声データ形式はwav）
		static void loadSound(ResourceIdCarrier soundId, const std::string& filePath);

		// テクスチャを読み込みスプライトマテリアルを作る（対応している画像データ形式はpng）
		static void loadSprite(ResourceIdCarrier spriteId, const std::string& filePath);

		// テクスチャを読み込みビルボードマテリアルを作る（対応している画像データ形式はpng）
		static void loadBillboard(ResourceIdCarrier billBoardId, bool isEffect, const std::string& filePath);

		// メッシュを読み込む（対応しているメッシュ形式はpmdとpmx）
		static void loadMesh(ResourceIdCarrier meshId, ResourceIdCarrier skeletonId, bool writeShadow, const std::string& filePath);

		// モーションを読み込む（対応しているモーション形式はvmd）
		static void loadMotion(ResourceIdCarrier motionId, const std::string& filePath);

		// テクスチャを読み込みスカイボックスメッシュを作る（対応している画像データ形式はpng）
		static void loadSkyBox(ResourceIdCarrier meshId, const std::string& filePath);

		// テクスチャを読み込みボックスメッシュを作る（対応している画像データ形式はpng）
		static void loadBoxMesh(ResourceIdCarrier meshId, bool writeShadow, const std::string& filePath);

	//************************************************************
	/* システムのリソースを使うためのハンドルを取得するための処理 */
	public:

		static size_t getSystemHandle(SystemViewportType type);
		static size_t getSystemHandle(SystemScissorRectType type);
		static size_t getSystemHandle(SystemVertexBufferType type);
		static size_t getSystemHandle(SystemIndexBufferType type);
		static size_t getSystemHandle(SystemCBufferType type);
		static size_t getSystemHandle(SystemTextureBufferType type);
		static size_t getSystemHandle(SystemRtBufferType type);
		static size_t getSystemHandle(SystemDsBufferType type);
		static size_t getSystemHandle(SystemBasicDescriptorHeapType type);
		static size_t getSystemHandle(SystemRtvDescriptorHeapType type);
		static size_t getSystemHandle(SystemDsvDescriptorHeapType type);
		static size_t getSystemHandle(SystemRootSignatureType type);
		static size_t getSystemHandle(SystemPipeLineStateType type);
		static size_t getSystemHandle(SystemCameraType type);
		static size_t getSystemHandle(SystemLightType type);
		static size_t getSystemHandle(SystemMeshType type);
		static size_t getSystemHandle(SystemMeshMaterialType type);
		static size_t getSystemHandle(SystemPostEffectMaterialType type);
	};
}
#endif // !TKTK_DX12_GAME_H_