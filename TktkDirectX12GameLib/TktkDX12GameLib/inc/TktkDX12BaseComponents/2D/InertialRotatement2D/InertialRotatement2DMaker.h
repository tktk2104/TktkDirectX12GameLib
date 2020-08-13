#ifndef INERTIAL_ROTATEMENT_2D_MAKER_H_
#define INERTIAL_ROTATEMENT_2D_MAKER_H_

#include "InertialRotatement2D.h"

namespace tktk
{
	// InertialRotatement2Dのインスタンスを作成するクラス
	class InertialRotatement2DMaker
	{
	private: /* プライベートコンストラクタ達 */

		InertialRotatement2DMaker() = default;
		InertialRotatement2DMaker(const InertialRotatement2DMaker& other) = default;
		InertialRotatement2DMaker& operator = (const InertialRotatement2DMaker& other) = default;

	public:

		// インスタンス作成開始
		static InertialRotatement2DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<InertialRotatement2D> create();

		// 速度を１秒間でどれだけ減速させるかを設定
		InertialRotatement2DMaker& decelerationPerSec(float value);

		// 初期速度を設定
		InertialRotatement2DMaker& initVelocity(float value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		// 自身のポインタ
		static InertialRotatement2DMaker m_self;

	private: /* 変数達 */

		GameObjectPtr	m_user					{ };
		float			m_decelerationPerSec	{ 30.0f };
		float			m_initVelocity			{ 0.0f };
	};
}
#endif // !INERTIAL_ROTATEMENT_2D_MAKER_H_