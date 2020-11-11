#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

/* std::unique_ptr */
#include <memory>

/* HINSTANCE, HWND */
#include <Windows.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "InputGetter/MouseInputGetter/MouseBtnType.h"
#include "InputGetter/DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"
#include "CommandTypeManager/CommandIdCarrier.h"
#include "CommandTypeManager/DirectionCommandId.h"

namespace tktk
{
	class InputGetter;
	class CommandTypeManager;

	// 入力管理クラス
	class InputManager
	{
	public:

		explicit InputManager(HINSTANCE hInstance, HWND handle, float padStickPlayWidth);
		~InputManager();

	public:

		void update();

	public: /* コマンドIDを使用した処理 */

		// IDに対応した入力が押されているかを判定
		bool isPush(CommandIdCarrier commandId) const;

		// IDに対応した入力が押され始めたかを判定
		bool isTrigger(CommandIdCarrier commandId) const;

		// 移動方向を取得
		const tktkMath::Vector2& moveVec()const;

		// 視点移動方向を取得
		const tktkMath::Vector2& lookVec()const;

	public: /* マウス関連の処理 */

		// 指定のボタンが押されているか
		bool isPush(MouseBtnType btnType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(MouseBtnType btnType) const;

		// マウスカーソルの座標を取得する
		tktkMath::Vector2 mousePos(HWND hWnd) const;

	public: /* キーボード関連の処理 */

		// 指定のキーが押されているかを判定
		bool isPush(KeybordKeyType keyType) const;

		// 指定のキーが押され始めたかを判定
		bool isTrigger(KeybordKeyType keyType) const;

	public: /* ゲームパッド関連の処理 */

		// 左スティックの傾きを取得（-1.0～1.0の間）
		tktkMath::Vector2 getLstick() const;

		// 右スティックの傾きを取得（-1.0～1.0の間）
		tktkMath::Vector2 getRstick() const;

		// 指定のボタンが押されているかを判定
		bool isPush(GamePadBtnType btnType) const;

		// 指定のボタンが押され始めたかを判定
		bool isTrigger(GamePadBtnType btnType) const;

	public:

		// 各種入力と入力コマンドIDを結びつける
		void addCommand(CommandIdCarrier commandId, MouseBtnType btnType);
		void addCommand(CommandIdCarrier commandId, KeybordKeyType keyType);
		void addCommand(CommandIdCarrier commandId, GamePadBtnType btnType);

		// 各種入力と移動入力コマンドIDを結びつける
		void addDirectionCommand(DirectionCommandId directionCommandId, MouseBtnType btnType);
		void addDirectionCommand(DirectionCommandId directionCommandId, KeybordKeyType keyType);
		void addDirectionCommand(DirectionCommandId directionCommandId, GamePadBtnType btnType);

	private:

		// 現在の移動方向
		tktkMath::Vector2 m_curMoveVec{};

		// 現在の視点移動方向
		tktkMath::Vector2 m_curLookVec{};

		std::unique_ptr<InputGetter>		m_inputGetter;
		std::unique_ptr<CommandTypeManager> m_commandTypeManager;
	};
}
#endif // !INPUT_MANAGER_H_