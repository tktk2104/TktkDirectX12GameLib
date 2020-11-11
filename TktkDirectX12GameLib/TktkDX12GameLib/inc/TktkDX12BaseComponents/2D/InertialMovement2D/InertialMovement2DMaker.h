#ifndef INERTIAL_MOVEMENT_2D_MAKER_H_
#define INERTIAL_MOVEMENT_2D_MAKER_H_

#include "InertialMovement2D.h"

namespace tktk
{
	// InertialMovement2Dのインスタンスを作成するクラス
	class InertialMovement2DMaker
	{
	private: /* プライベートコンストラクタ達 */

		InertialMovement2DMaker() = default;
		InertialMovement2DMaker(const InertialMovement2DMaker& other) = default;
		InertialMovement2DMaker& operator = (const InertialMovement2DMaker& other) = default;

	public:

		// インスタンス作成開始
		static InertialMovement2DMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<InertialMovement2D> create();

		// 速度を１秒間でどれだけ減速させるかを設定
		InertialMovement2DMaker& decelerationPerSec(float value);

		// 初期速度を設定
		InertialMovement2DMaker& initVelocity(const tktkMath::Vector2& value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		// 自身のポインタ
		static InertialMovement2DMaker m_self;

	private: /* 変数達 */

		GameObjectPtr		m_user					{ };
		float				m_decelerationPerSec	{ 64.0f };
		tktkMath::Vector2	m_initVelocity			{ tktkMath::Vector2_v::zero };
	};
}
#endif // !INERTIAL_MOVEMENT_2D_MAKER_H_