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
		static FirstPersonModuleMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

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
		StateTypeHierarchy		m_targetState			{  };
		float				m_rotateDegSpeedPerSec	{ 100.0f };
		float				m_moveSpeedPerSec		{ 100.0f };
		bool				m_alwaysMoveForward		{ false };
		bool				m_enableUpDownKey		{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_MAKER_H_