#ifndef FIRST_PERSON_MODULE_MAKER_H_
#define FIRST_PERSON_MODULE_MAKER_H_

#include "FirstPersonModule.h"

namespace tktk
{
	// 「FirstPersonModule」を作るヘルパークラス
	class FirstPersonModuleMaker
	{
	private: /* プライベートコンストラクタ達 */

		FirstPersonModuleMaker() = default;
		FirstPersonModuleMaker(const FirstPersonModuleMaker& other) = default;
		FirstPersonModuleMaker& operator = (const FirstPersonModuleMaker& other) = default;

	public:

		// インスタンス作成開始
		static FirstPersonModuleMaker& makeStart(GameObjectPtr user);

		// ステートを指定し、作成を開始する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class StateIdType>
		static FirstPersonModuleMaker& makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<FirstPersonModule> create();

	public:  /* パラメータ設定関数 */

		// 初期毎秒回転角度を設定する
		FirstPersonModuleMaker& rotateDegSpeedPerSec(float value);

		// 初期毎秒移動距離を設定する
		FirstPersonModuleMaker& moveSpeedPerSec(float value);

		// 常にカメラの方向に移動するかを設定する（移動キーでy軸の座標を変化させるか？）
		FirstPersonModuleMaker& alwaysMoveForward(bool value);

		// スペースとシフトでy軸の座標を変化させるかを設定する
		FirstPersonModuleMaker& enableUpDownKey(bool value);

	private:

		// 自身のポインタ
		static FirstPersonModuleMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user					{ };
		std::vector<int>	m_targetState			{  };
		float				m_rotateDegSpeedPerSec	{ 100.0f };
		float				m_moveSpeedPerSec		{ 100.0f };
		bool				m_alwaysMoveForward		{ false };
		bool				m_enableUpDownKey		{ false };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// ステートを指定し、作成を開始する
	// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class StateIdType>
	inline FirstPersonModuleMaker& FirstPersonModuleMaker::makeStart(std::initializer_list<StateIdType> targetState, GameObjectPtr user)
	{
		// 作成開始処理を行う
		auto& result = makeStart(user);

		// 初期化子リストを配列に変換
		auto targetStateArray = std::vector<StateIdType>(targetState);

		// 対象のステートの階層数分のメモリを確保
		result.m_targetState.reserve(targetStateArray.size());

		// 対象のステートの階層を設定する
		for (const auto& node : targetStateArray) result.m_targetState.push_back(static_cast<int>(node));

		// 自身の参照を返す
		return result;
	}
}
#endif // !FIRST_PERSON_MODULE_MAKER_H_