#ifndef FIRST_PERSON_MODULE_H_
#define FIRST_PERSON_MODULE_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	class FirstPersonModule
		: public ComponentBase
	{
	public:

		FirstPersonModule(
			float rotateDegSpeedPerSec,		// 毎秒の回転角度（度数法）
			float moveSpeedPerSec,			// 毎秒の移動速度
			bool alwaysMoveForward,			// 常に前方に移動するか
			bool enableUpDownKey			// スペース、シフトキーで上下に移動するか
		);
		~FirstPersonModule() = default;

	public:

		void start();
		void update();

	public:

		float getRotateDegSpeedPerSec();
		// 毎秒回転角度を設定する
		void setRotateDegSpeedPerSec(float deg);

		float getMoveSpeedPerSec();
		// 毎秒移動距離を設定する
		void setMoveSpeedPerSec(float speed);

		bool getAlwaysMoveForward();
		// 常にカメラの方向に移動するかを設定する（移動キーでy軸の座標を変化させるか？）
		void setAlwaysMoveForward(bool flag);

		bool getEnableUpDownKey();
		// スペースとシフトでy軸の座標を変化させるかを設定する
		void setEnableUpDownKey(bool flag);

	private:

		void rotate();

		void moveHorizontal();

		void moveVertical();

	private:

		// 自身の３次元座標コンポーネント
		ComponentPtr<Transform3D> m_transform;

		// 毎秒の回転角度（度数法）
		float m_rotateDegSpeedPerSec;

		// 毎秒の移動速度
		float m_moveSpeedPerSec;

		// 常に前方に移動するか
		bool m_alwaysMoveForward{ false };

		// スペース、シフトキーで上下に移動するか
		bool m_enableUpDownKey{ false };
	};
}
#endif // !FIRST_PERSON_MODULE_H_