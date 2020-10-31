#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <unordered_map>
#include <TktkMath/Structs/Vector2.h>
#include "../DirectInputWrapper/Keyboard/Keyboard.h"
#include "../DirectInputWrapper/GamePad/GamePad.h"
#include "../Mouse/Mouse.h"
#include "DirectionCommandType.h"

namespace tktk
{
	class InputManager
	{
	public:

		explicit InputManager(float padStickPlayWidth);

	public:

		void update();

	public:

		// IDに対応した入力が押されているかを判定
		bool isPush(int commandId) const;

		// IDに対応した入力が押され始めたかを判定
		bool isTrigger(int commandId) const;

		// 移動方向を取得
		const tktkMath::Vector2& moveVec()const;

		// 視点移動方向を取得
		const tktkMath::Vector2& lookVec()const;

	public:

		// 各種入力とIDを結びつける
		void addCommand(int commandId, KeybordKeyType keyType);
		void addCommand(int commandId, GamePadBtnType btnType);
		void addCommand(int commandId, MouseButtonType btnType);

		// 各種入力と移動コマンドを結びつける
		void addDirectionCommand(DirectionCommandType directionCommand, KeybordKeyType keyType);
		void addDirectionCommand(DirectionCommandType directionCommand, GamePadBtnType btnType);
		void addDirectionCommand(DirectionCommandType directionCommand, MouseButtonType btnType);

	private:

		// ゲームパッドのアナログスティックの傾きの遊び
		float m_padStickPlayWidth{};

		// 現在の移動方向
		tktkMath::Vector2 m_curMoveVec{};

		// 現在の視点移動方向
		tktkMath::Vector2 m_curLookVec{};

		// それぞれの入力の種類と移動コマンドの対応表
		std::unordered_multimap<DirectionCommandType, KeybordKeyType>	m_keyDirectionCommandMap;
		std::unordered_multimap<DirectionCommandType, GamePadBtnType>	m_padDirectionCommandMap;
		std::unordered_multimap<DirectionCommandType, MouseButtonType>	m_mouseDirectionCommandeMap;

		// それぞれの入力の種類とIDの対応表
		std::unordered_multimap<int, KeybordKeyType>		m_keyCommandMap;
		std::unordered_multimap<int, GamePadBtnType>		m_padCommandMap;
		std::unordered_multimap<int, MouseButtonType>	m_mouseCommandMap;
	};
}
#endif // !INPUT_MANAGER_H_