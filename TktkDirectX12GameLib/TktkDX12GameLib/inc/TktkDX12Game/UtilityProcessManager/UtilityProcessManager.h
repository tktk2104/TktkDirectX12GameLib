#ifndef UTILITY_PROCESS_MANAGER_H_
#define UTILITY_PROCESS_MANAGER_H_

/* std::unique_ptr */
#include <memory>

/* HINSTANCE, HWND */
#include <Windows.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "InputManager/InputGetter/MouseInputGetter/MouseBtnType.h"
#include "InputManager/InputGetter/DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "InputManager/InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"
#include "InputManager/CommandTypeManager/CommandIdCarrier.h"
#include "InputManager/CommandTypeManager/DirectionCommandId.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemViewportType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemScissorRectType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemVertexBufferType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemIndexBufferType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemConstantBufferType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemTextureBufferType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRenderTargetBufferType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDepthStencilBufferType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicDescriptorHeapType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRtvDescriptorHeapType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDsvDescriptorHeapType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRootSignatureType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPipeLineStateType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemCameraType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemLightType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicMeshType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicMeshMaterialType.h"
#include "ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPostEffectMaterialType.h"
#include "ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	class InputManager;
	class ElapsedTimer;
	class ResourceHandleGetter;

	class UtilityProcessManager
	{
	public:

		UtilityProcessManager(HINSTANCE hInstance, HWND handle, float padStickPlayWidth);
		~UtilityProcessManager();

	public:

		void update();

	//************************************************************
	public: /* コマンドIDを使用した処理 */

		// IDに対応した入力が押されているかを判定
		bool isPush(CommandIdCarrier commandId) const;

		// IDに対応した入力が押され始めたかを判定
		bool isTrigger(CommandIdCarrier commandId) const;

		// 移動方向を取得
		const tktkMath::Vector2& moveVec()const;

		// 視点移動方向を取得
		const tktkMath::Vector2& lookVec()const;

	//************************************************************
	public: /* マウス関連の処理 */

		// 指定のボタンが押されているか
		bool isPush(MouseBtnType btnType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(MouseBtnType btnType) const;

		// マウスカーソルの座標を取得する
		tktkMath::Vector2 mousePos(HWND hWnd) const;

	//************************************************************
	public: /* キーボード関連の処理 */

		// 指定のキーが押されているかを判定
		bool isPush(KeybordKeyType keyType) const;

		// 指定のキーが押され始めたかを判定
		bool isTrigger(KeybordKeyType keyType) const;

	//************************************************************
	public: /* ゲームパッド関連の処理 */

		// 左スティックの傾きを取得（-1.0～1.0の間）
		tktkMath::Vector2 getLstick() const;

		// 右スティックの傾きを取得（-1.0～1.0の間）
		tktkMath::Vector2 getRstick() const;

		// 指定のボタンが押されているかを判定
		bool isPush(GamePadBtnType btnType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(GamePadBtnType btnType) const;

	//************************************************************
	public: /* コマンドIDの登録処理 */

		// 各種入力と入力コマンドIDを結びつける
		void addCommand(CommandIdCarrier commandId, MouseBtnType btnType);
		void addCommand(CommandIdCarrier commandId, KeybordKeyType keyType);
		void addCommand(CommandIdCarrier commandId, GamePadBtnType btnType);

		// 各種入力と移動入力コマンドIDを結びつける
		void addDirectionCommand(DirectionCommandId directionCommandId, MouseBtnType btnType);
		void addDirectionCommand(DirectionCommandId directionCommandId, KeybordKeyType keyType);
		void addDirectionCommand(DirectionCommandId directionCommandId, GamePadBtnType btnType);

	//************************************************************
	public: /* タイム関係の処理 */

		// 経過時間を初期化する
		void resetElapsedTime();

		// 前フレームとの時間の差を求める
		float deltaTime();

		// 前フレームとの時間の差を求める（TimeScaleを無視）
		float noScaleDeltaTime();

		// プログラムが起動してからの時間（秒）を返す
		float getCurTimeSec();

		// 最大のdeltaTimeの値を設定（正の数）
		void setMaximumDeltaTime(float maximumDeltaTime);

		// 時間の経過速度割合を取得する
		float getTimeScale();

		// 時間の経過速度割合を設定する（0.0～float_max）
		void setTimeScale(float timeScaleRate);

		// 基準となるFPSを設定する
		void setBaseFps(unsigned int baseFps = 60U);

		// 基準となるFPSを取得する
		unsigned int getBaseFps();

		// 瞬間的なFPSを取得する
		float fps();

	public:

		size_t getSystemHandle(SystemViewportType type)				const;
		size_t getSystemHandle(SystemScissorRectType type)			const;
		size_t getSystemHandle(SystemVertexBufferType type)			const;
		size_t getSystemHandle(SystemIndexBufferType type)			const;
		size_t getSystemHandle(SystemCBufferType type)				const;
		size_t getSystemHandle(SystemTextureBufferType type)		const;
		size_t getSystemHandle(SystemRtBufferType type)				const;
		size_t getSystemHandle(SystemDsBufferType type)				const;
		size_t getSystemHandle(SystemBasicDescriptorHeapType type)	const;
		size_t getSystemHandle(SystemRtvDescriptorHeapType type)	const;
		size_t getSystemHandle(SystemDsvDescriptorHeapType type)	const;
		size_t getSystemHandle(SystemRootSignatureType type)		const;
		size_t getSystemHandle(SystemPipeLineStateType type)		const;
		size_t getSystemHandle(SystemCameraType type)				const;
		size_t getSystemHandle(SystemLightType type)				const;
		size_t getSystemHandle(SystemBasicMeshType type)			const;
		size_t getSystemHandle(SystemBasicMeshMaterialType type)	const;
		size_t getSystemHandle(SystemPostEffectMaterialType type)	const;

	public:

		void setSystemHandle(SystemViewportType type,				size_t handle);
		void setSystemHandle(SystemScissorRectType type,			size_t handle);
		void setSystemHandle(SystemVertexBufferType type,			size_t handle);
		void setSystemHandle(SystemIndexBufferType type,			size_t handle);
		void setSystemHandle(SystemCBufferType type,				size_t handle);
		void setSystemHandle(SystemTextureBufferType type,			size_t handle);
		void setSystemHandle(SystemRtBufferType type,				size_t handle);
		void setSystemHandle(SystemDsBufferType type,				size_t handle);
		void setSystemHandle(SystemBasicDescriptorHeapType type,	size_t handle);
		void setSystemHandle(SystemRtvDescriptorHeapType type,		size_t handle);
		void setSystemHandle(SystemDsvDescriptorHeapType type,		size_t handle);
		void setSystemHandle(SystemRootSignatureType type,			size_t handle);
		void setSystemHandle(SystemPipeLineStateType type,			size_t handle);
		void setSystemHandle(SystemCameraType type,					size_t handle);
		void setSystemHandle(SystemLightType type,					size_t handle);
		void setSystemHandle(SystemBasicMeshType type,				size_t handle);
		void setSystemHandle(SystemBasicMeshMaterialType type,		size_t handle);
		void setSystemHandle(SystemPostEffectMaterialType type,		size_t handle);

	public:

		size_t getSceneHandle				(ResourceIdCarrier id) const;
		size_t getSoundHandle				(ResourceIdCarrier id) const;
		size_t getPostEffectMaterialHandle	(ResourceIdCarrier id) const;
		size_t getSpriteMaterialHandle		(ResourceIdCarrier id) const;
		size_t getLine2DMaterialHandle		(ResourceIdCarrier id) const;
		size_t getBillboardMaterialHandle	(ResourceIdCarrier id) const;
		size_t getSkeletonHandle			(ResourceIdCarrier id) const;
		size_t getMotionHandle				(ResourceIdCarrier id) const;
		size_t getBasicMeshHandle			(ResourceIdCarrier id) const;
		size_t getBasicMeshMaterialHandle	(ResourceIdCarrier id) const;
		size_t getCameraHandle				(ResourceIdCarrier id) const;
		size_t getLightHandle				(ResourceIdCarrier id) const;

	public:

		void setSceneHandle				(ResourceIdCarrier id, size_t handle);
		void setSoundHandle				(ResourceIdCarrier id, size_t handle);
		void setPostEffectMaterialHandle(ResourceIdCarrier id, size_t handle);
		void setSpriteMaterialHandle	(ResourceIdCarrier id, size_t handle);
		void setLine2DMaterialHandle	(ResourceIdCarrier id, size_t handle);
		void setBillboardMaterialHandle	(ResourceIdCarrier id, size_t handle);
		void setSkeletonHandle			(ResourceIdCarrier id, size_t handle);
		void setMotionHandle			(ResourceIdCarrier id, size_t handle);
		void setBasicMeshHandle			(ResourceIdCarrier id, size_t handle);
		void setBasicMeshMaterialHandle	(ResourceIdCarrier id, size_t handle);
		void setCameraHandle			(ResourceIdCarrier id, size_t handle);
		void setLightHandle				(ResourceIdCarrier id, size_t handle);

	private:

		std::unique_ptr<InputManager>			m_inputManager;
		std::unique_ptr<ElapsedTimer>			m_elapsedTimer;
		std::unique_ptr<ResourceHandleGetter>	m_resourceHandleGetter;
	};
}
#endif // !UTILITY_PROCESS_MANAGER_H_